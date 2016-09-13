import os
import pickle
import time
import math
import struct
import datetime

cp=0

#======================================================================================================#

def struct_superblock(name,drive_size,drive_size_type,blocksize):
	partition_name = name[0]
	partition_size = drive_size
	partition_size_type = drive_size_type
	partition_blocksize = blocksize
	no_of_files=0
	'''if partition_size_type=='K':
		partition_size=int(partition_size*1024)
	else:
		partition_size=int(partition_size*1042*1024)
	'''
	no_of_inodes = int(((partition_size*1024*1024)/(64*partition_blocksize))/2)
	inode_size = int(285)
	start_data_block_add = int(34 + (no_of_inodes*inode_size) + (64*no_of_inodes))
	block_table_size =  int(64*no_of_inodes)
	block_table_pointer = int(34 + (inode_size*no_of_inodes))
	
	f=open(name,'rb+')
	
	t=(partition_name,partition_size,partition_size_type,partition_blocksize,no_of_inodes,inode_size,start_data_block_add,block_table_size,block_table_pointer,no_of_files)
	
	'''f.write(partition_name)
	f.write(int_str(partition_size))
	f.write(partition_size_type)
	f.write(int_str(partition_blocksize))
	f.write(int_str(no_of_inodes))
	f.write(int_str(inode_size))
	#f.write(int_str(start_data_block_add))
	f.write(int_str(block_table_size))
	#f.write(int_str(block_table_pointer))
	'''
	pickle.dump(t,f)
	f.close()


def struct_inode(flag=0,filename="",filesize=0,date="",l=[-1]*64):
	
	flag=flag
	filename=filename
	filesize=filesize
	date=date
	add_list=l
	
	t=(flag,filename,filesize,date,add_list)
	return t
	
def load_inodes(drive):
	
	f=open(drive,'rb+')
	superblock=pickle.load(f)
	no_of_inodes=superblock[4]
	#print("Number of inodes = ",no_of_inodes)
	
	inode_list=[]
	for i in range(no_of_inodes):
		inode_list.append(struct_inode())
		#print((i+1),"inode created successfully")
		
	pickle.dump(inode_list,f)
	
	f.close()

def load_bitvector(drive):
	
	f=open(drive,'rb+')
	superblock=pickle.load(f)
	inode_list=pickle.load(f)
	no_of_inodes=superblock[4]
	
	size=no_of_inodes*64
	
	bitvctor=[0]*size
	pickle.dump(bitvctor,f)
	
	f.close()

def load_data_blocks(drive):
	
	f=open(drive,'rb+')
	superblock=pickle.load(f)
	inode_list=pickle.load(f)
	bitvector=pickle.load(f)
	
	blocksize=superblock[3]
	no_of_inodes=superblock[4]
	
	data_block=[]
	for i in range(64*no_of_inodes):
		l=[]
		for j in range(blocksize):
			l.append('')
		
		data_block.append(l)
	
	pickle.dump(data_block,f)
	
	f.close()		

def find_next_free_block(bitvector):
	
	global cp
	
	if cp>len(bitvector):
		cp=0
	
	while (bitvector[cp]==1):
		cp+=1
	
	return cp		
	
	
#=========================================My System Calls===============================================#
	
def mycreate(drive,filename,filesize=0):
	
	f=open(drive,'rb+')
	
	superblock=pickle.load(f)
	inode_list=pickle.load(f)
	bitvector=pickle.load(f)
	data_block=pickle.load(f)
	
	no_of_files=superblock[-1]
	count=0
	while (no_of_files>0):
		if inode_list[count][0]==1:
			no_of_files-=1
			#print(inode_list[count][1])
			if (inode_list[count][1]==filename):
				print("File name already exists.Change file name")
				return None
		count+=1
				 
	
	count=-1
	for inode in inode_list:
		count+=1
		if (inode[0]==0):
			l=list(inode)
			
			l[0]=1
			l[1]=filename
			l[2]=filesize
			l[3]=str(datetime.datetime.now())

			break
			
	blocksize=superblock[3]
	no_of_inodes=len(inode_list)
	total_blocks=no_of_inodes*64
	
	no_of_blocks=math.ceil(filesize/blocksize)			
	
	if no_of_blocks>total_blocks:
		print('Not enough space in drive')
		return
		
	if no_of_blocks>64:
		print('File size exceeded')
		return
		
	t=tuple(l)
	
	inode_list[count]=t
	
	s=list(superblock)
	s[-1]+=1
	superblock=tuple(s)
	
	f.seek(0)
	
	pickle.dump(superblock,f)
	pickle.dump(inode_list,f)
	pickle.dump(bitvector,f)
	pickle.dump(data_block,f)
	
	f.close()
	
	return count	
		
def myopen(drive,filename):
	
	f=open(drive,'rb')
	
	superblock=pickle.load(f)
	inode_list=pickle.load(f)
	bitvector=pickle.load(f)
	data_block=pickle.load(f)
	
	f.close()
	
	no_of_files=superblock[-1]
	count=0
	while (no_of_files>0):
		if inode_list[count][0]==1:
			no_of_files-=1
			if (inode_list[count][1]==filename):
				return count
		count+=1
				 
	return None 
	
			
def mywrite(drive,filename,data,inode_number):
	
	print('Copying data to',drive,'/',filename)
	f=open(drive,'rb+')
	
	superblock=pickle.load(f)
	inode_list=pickle.load(f)
	bitvector=pickle.load(f)
	data_block=pickle.load(f)
	
	blocksize=superblock[3]
	#print(blocksize)
	i=inode_list[:]
	#inode=inode_list[inode_number][:]
	inode=i[inode_number][:]
	inode_copy=list(inode)
	inode_add=inode_copy[-1][:]
	#print(type(x))
	#inode=list(x)
	#print(inode_list[5])
	#inode=x[-1]
	#print(inode_copy[4])
	inode_data_add=0
	count=0
	#data_blocks=int(len(data)/blocksize)
	
	free_block_no=find_next_free_block(bitvector)
	#print(free_block_no)
	bitvector[free_block_no]=1
	inode_add[inode_data_add]=free_block_no
	#inode[-1][inode_data_add]=free_block_no
	#print(inode[4])
	
	inode_data_add+=1
	#count=blocksize*free_block_no
	#print(count)
	for i in data:
		data_block[free_block_no][count]=i
		#print(count)
		count+=1
		
		if (((count)%blocksize)==0):
			free_block_no = find_next_free_block(bitvector)
			#print(free_block_no)
			bitvector[free_block_no]=1
			#print(bitvector)
			#inode[-1][inode_data_add]=free_block_no
			inode_add[inode_data_add]=free_block_no
			#print(inode)
			#print(inode_list[5])
	
			inode_data_add+=1
			count=0
			#print(count)
		#print(inode)
	
	#inode[-1][inode_data_add]=-1		
	#i=inode_list[inode_number]
	#x=list(l)
	#l=list(x)
	#l[-1]=inode
	#t=tuple(l)
	#print(t)
	#inode_list[inode_number]=t
	#print(inode_list[1])
	inode_copy[-1]=inode_add
	t=tuple(inode_copy)
	inode_list[inode_number]=t
	f.seek(0)
	
	pickle.dump(superblock,f)	
	pickle.dump(inode_list,f)	
	pickle.dump(bitvector,f)
	pickle.dump(data_block,f)
	
	f.close()
		

def myread(drive,inode_number):
	
	f=open(drive,'rb')
	
	s=pickle.load(f)
	i=pickle.load(f)
	b=pickle.load(f)
	d=pickle.load(f)
	
	f.close()
	
	data=[]
	
	inode=i[inode_number]
	inode_add=inode[-1]
	
	count=0
	while (inode_add[count]!=-1):
		
		data_block=count
		
		block_data = d[data_block]
		
		for char in block_data:
			
			if (char!=''):
				data.append(char)
		
		count+=1
	
	return data
				
		
		
def mygetsize(drive,inode_number):
	
	f=open(drive,'rb')
	
	s=pickle.load(f)
	i=pickle.load(f)
	b=pickle.load(f)
	d=pickle.load(f)
	
	f.close()
	
	req_inode=i[inode_number]
	
	return req_inode[2]
				

def mydelete(drive,inode_number):
	
	print('Deleting file......')
	f=open(drive,'rb+')
	
	superblock=pickle.load(f)
	inode_list=pickle.load(f)
	bitvector=pickle.load(f)
	data_block=pickle.load(f)
	
	s=list(superblock)
	s[-1]-=1
	superblock=tuple(s)
	
	#no_of_files=superblock[-1]
	blocksize=superblock[3]
	
	i=inode_list[:]
	inode=i[inode_number][:]
	inode_copy=list(inode)
	inode_add=inode_copy[-1][:]
	
	inode_data_add=0
	count=0
	
	while (inode_add[count]!=-1):
		
		data_block[inode_add[count]][:]=['']*blocksize
		bitvector[inode_add[count]]=0
		inode_add[count]=-1
		count+=1
	
	
	inode_copy[0]=0
	inode_copy[1]=''
	inode_copy[2]=0
	inode_copy[3]=''
	
	inode_copy[-1]=inode_add
	t=tuple(inode_copy)
	inode_list[inode_number]=t
	
	f.seek(0)
	
	pickle.dump(superblock,f)	
	pickle.dump(inode_list,f)	
	pickle.dump(bitvector,f)
	pickle.dump(data_block,f)
	
	f.close()
	
	print('File successfully deleted')			
	
				
def myrename(drive,old,new):
	
	f=open(drive,'rb+')
	
	superblock=pickle.load(f)
	inode_list=pickle.load(f)
	bitvector=pickle.load(f)
	data_block=pickle.load(f)
	
	count=-1
	save=0
	
	for inode in inode_list:
		
		count+=1
		
		if inode[1]==old:
			i=list(inode)
			i[1]=new
			t=tuple(i)
			save=count
			
	inode_list[save]=t
	f.seek(0)
	
	#print(inode_list)
	
	pickle.dump(superblock,f)	
	pickle.dump(inode_list,f)	
	pickle.dump(bitvector,f)
	pickle.dump(data_block,f)
	
	f.close()
	
	print('File successfully renamed')			
	
	#myls(drive)
	
						
def myls(drive):
	
	f=open(drive,'rb')
	
	superblock=pickle.load(f)
	inode_list=pickle.load(f)
	bitvector=pickle.load(f)
	data_block=pickle.load(f)
	
	f.close()
	
	no_of_files=superblock[-1]
	count=0
	print("\nFilename\tSize\tDate and Time\n----------------------------------------------------")
	while (no_of_files>0):
		if inode_list[count][0]==1:
			no_of_files-=1
			print(inode_list[count][1],'\t',inode_list[count][2],'\t',inode_list[count][3])	
		
		count+=1
	
	print()

#======================================================================================================#

def run():				# main()		
	#print("anubhab>",end='')
	#inp=input()
	inp=""
	while(inp!="exit"):
		print("anubhab>",end='')
		inp=input()
		parse_input(inp)
	#test('osfile1')
							
def parse_input(inp):			# determines ui command
	l=inp.split()
	try:
		if (l[0]=='mkfs'):
			print('File being created....\nName :',l[1],'\nSize :',l[3])
			create_file(l[1],l[2],l[3])
			print("File successfully created")
		elif (l[0]=='use'):
			rename_drive(l[1],l[2])
			#print("Done\n")
		elif (l[0]=='test'):
			test(l[1])	
		elif (l[0]=='cp'):
			file_copy(l[1],l[2])	
		elif (l[0]=='ls'):
			file_list(l[1])
		elif (l[0]=='rm'):
			remove_file(l[1])
		elif (l[0]=='mv'):
			rename_file(l[1],l[2])		
		elif (l[0]!='exit'):
			print("Command doesn't exist")			
	except:
		pass

def create_file(name,blocksize,size):
	f=open(name,'w+')
	size_file=0
	size_file=int(size[0:len(size)-2])
	if size[-2]=='K':
		size_file=size_file*1024
		
	elif size[-2]=='M':
		size_file=size_file*1048576
		
	#for i in range(size_file):
	#	f.write('\0')
	
	f.close()
	
	struct_superblock(name,int(size[0:len(size)-2]),size[-2],int(blocksize))
	
	print("Superblock created")
	
		
def rename_drive(name,drive_name):

	l=os.listdir(".")
	for filename in l:
		if filename==name:
			os.rename(filename,drive_name)
	
	f=open(drive_name,'rb+')
	#f.seek(0)
	r=pickle.load(f)
	l=list(r)
	l[0]=drive_name[0]
	r=tuple(l)
	f.seek(0)
	pickle.dump(r,f)
	f.close()
	print("Superblock modified successfully")
	
	load_inodes(drive_name)
	print("Inodes loaded successfully")
	
	load_bitvector(drive_name)
	print("Bitvector loaded successfully")
	
	load_data_blocks(drive_name)
	
	print('Drive successfully mounted')


def file_copy(source,dest):
	
	if ((source[1]==':') & (dest[1]==':')) :
		
		txt=source.split(':')
		source_drive=txt[0]+":"
		source_filename=txt[1]
		
		l=dest.split(':')
		dest_drivename=l[0]+':'
		dest_filename=l[1]
		
		f=myopen(source_drive,source_filename)
		if f==None:
			print("Source file does not exist")
			return
			
		data=myread(source_drive,f)
		#print(data)
		
		source_size=mygetsize(source_drive,f)
		
		f=mycreate(dest_drivename,dest_filename,source_size)
		#print(f)
		if f==None:
			return
		mywrite(dest_drivename ,dest_filename,data, f)
		print("Write successfull")
		
		#d=myread(dest_drivename,f)
		#print(d)
		
	elif ((source[1]==':') & (dest[1]!=':')) :
		
		txt=source.split(':')
		source_drive=txt[0]+":"
		source_filename=txt[1]
		
		f=myopen(source_drive,source_filename)
		if f==None:
			print("Source file does not exist")
			return
			
		data=myread(source_drive,f)
		string=''
		for item in data:
			string=string+item
		#print(string)
			
		f=open(dest,'w')
		f.write(string)
		f.close()
		
		print("Copy successfully created")
		
		
	
	
	else:
		l=dest.split(':')
		dest_drivename=l[0]
		dest_filename=l[1]
		
		f=open(source,'r')
		source_txt=list(f.read())
		f.close()
		
		
		drive_name=dest_drivename+":"
		source_filesize=os.path.getsize(source)
		
		inode_number = myopen(drive_name,dest_filename)
		if inode_number!=None:
			print("File with name",dest_filename,"already exists. Change the file name")
			return
		if inode_number == None:
			inode_number = mycreate(drive_name,dest_filename,source_filesize)
			if inode_number==None:
				print("Specified file couldn't be created. Aborting.....'")
				return
		print('File opened successfully')
		#print(inode_number)
		#drive,filename,data,inode_number
		mywrite(drive_name,dest_filename,source_txt,inode_number)
		print("Write successfull")
		
		#getdata=myread(drive_name,inode_number)
		#print(str(getdata))	

def file_list(drive):
	
	myls(drive)
	
def remove_file(string):
	
	s=string.split(':')
	drive=s[0]+":"
	filename=s[1]
	
	f=myopen(drive,filename)
	if f==None:
		print("Specified file does not exist")
		return
	
	mydelete(drive,f)
		

def rename_file(old,new):
	
	s1=old.split(':')
	s2=new.split(':')
	
	drive=s1[0]+":"
	old_filename=s1[1]
	new_filename=s2[1]
	
	#print(drive,old_filename,new_filename)
	myrename(drive,old_filename,new_filename)


		
#======================================================================================================#

run()

