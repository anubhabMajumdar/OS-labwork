#include<stdio.h>
#include<string.h>

void type_print(char *str)
{
	int i=0;
	while(str[i]!='\n')
	{
		printf("%c",str[i]);
		i++;
	}
	//printf("%d",i);
}

void take_input(char *inp)
{
	int i=0;
	for (i=0;i<100 && ((inp[i]=getchar())!='\n');i++);
	
}

int compare(char *a,char *b)
{
	int n;
	if ((a[0]=='\n') && (b[0]=='\n'))
	{
		return 0;
	}
	
	if ((a[0]=='\n') && (b[0]!='\n'))
	{
		return -1;
	}
	
	if ((a[0]!='\n') && (b[0]=='\n'))
	{
		return 1;
	}
	
	n=compare(a+1,b+1);	 
}

void makefile()
{
	printf("file made\n");	
}




main()
{
	char a[100];
	type_print("$anubhab>\n");
	take_input(a);
	while(compare(a,"exit\n")!=0)
	{
		type_print("$anubhab>\n");
		take_input(a);
		
		if (compare(a,"mkfs\n")==0)
			makefile();
		
	}	
}
#include<stdio.h>
#include<string.h>

void type_print(char *str)
{
	int i=0;
	while(str[i]!='\n')
	{
		printf("%c",str[i]);
		i++;
	}
	//printf("%d",i);
}

void take_input(char *inp)
{
	int i=0;
	for (i=0;i<100 && ((inp[i]=getchar())!='\n');i++);
	
}

int compare(char *a,char *b)
{
	int n;
	if ((a[0]=='\n') && (b[0]=='\n'))
	{
		return 0;
	}
	
	if ((a[0]=='\n') && (b[0]!='\n'))
	{
		return -1;
	}
	
	if ((a[0]!='\n') && (b[0]=='\n'))
	{
		return 1;
	}
	
	n=compare(a+1,b+1);	 
}

void makefile()
{
	printf("file made\n");	
}




main()
{
	char a[100];
	type_print("$anubhab>\n");
	take_input(a);
	while(compare(a,"exit\n")!=0)
	{
		type_print("$anubhab>\n");
		take_input(a);
		
		if (compare(a,"mkfs\n")==0)
			makefile();
		
	}	
}
#include<stdio.h>
#include<string.h>

void type_print(char *str)
{
	int i=0;
	while(str[i]!='\n')
	{
		printf("%c",str[i]);
		i++;
	}
	//printf("%d",i);
}

void take_input(char *inp)
{
	int i=0;
	for (i=0;i<100 && ((inp[i]=getchar())!='\n');i++);
	
}

int compare(char *a,char *b)
{
	int n;
	if ((a[0]=='\n') && (b[0]=='\n'))
	{
		return 0;
	}
	
	if ((a[0]=='\n') && (b[0]!='\n'))
	{
		return -1;
	}
	
	if ((a[0]!='\n') && (b[0]=='\n'))
	{
		return 1;
	}
	
	n=compare(a+1,b+1);	 
}

void makefile()
{
	printf("file made\n");	
}




main()
{
	char a[100];
	type_print("$anubhab>\n");
	take_input(a);
	while(compare(a,"exit\n")!=0)
	{
		type_print("$anubhab>\n");
		take_input(a);
		
		if (compare(a,"mkfs\n")==0)
			makefile();
		
	}	
}
import os

def run():
	#print("anubhab>",end='')
	#inp=input()
	inp=""
	while(inp!="exit"):
		print("anubhab>",end='')
		inp=input()
		parse_input(inp)
	#test('osfile1')
							
def parse_input(inp):
	l=inp.split()
	try:
		if (l[0]=='mkfs'):
			print('File being created....\nName :',l[1],'\nSize :',l[3])
			create_file(l[1],l[2],l[3])
			print("File successfully created")
		elif (l[0]=='use'):
			rename_drive(l[1],l[2])
			print("Done\n")
		elif (l[0]=='test'):
			test(l[1])	
		elif (l[0]=='cp'):
			file_copy(l[1],l[2])	
				
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
		
	for i in range(size_file):
		f.write('\0')
	
	f.close()
	
	g=open(name,'r+')	
	g.seek(0,0)
	#file-name + blocksize + file-size + number_of_files	
	new_name=name+" "+blocksize+" "+size+" " + '0' + "\n"
	g.write(new_name)
	f.close()

def rename_drive(name,drive_name):

	g=open(name,'r+')	
	g.seek(0,0)
	line=g.readline()
	items=line.split()
	items[0]=drive_name
	
	g.seek(0,0)
	new_name=items[0]+" "+items[1]+" "+items[2]+" "+items[3]+"\n"
	g.write(new_name)
	g.close()
	
	l=os.listdir(".")
	for filename in l:
		if filename==name:
			os.rename(filename,drive_name)
			

def file_copy(source,destinantion):
	size_source=os.path.getsize(source)
	l=destinantion.split(":")
	file_to_open=l[0]+":"
	f=open(file_to_open)
	first_line=f.readline()
	print(first_line)
	first_line=first_line.split()
	
	dest_name=first_line[0]
	#print(dest_name)
	blocksize=int(first_line[1])
	#print(blocksize)
	size=first_line[2]
	size_file=int(size[0:len(size)-2])
	#print(size_file)
	no_of_files=int(first_line[3])
	#print(no_of_files)
	
	no_of_files+=1
	
	
	








def test(name):
	
	f=open(name,'r')
	print(f.readline(),"\n")
	print(f.readline(),"\n")
	f.close()
	
	
run()
#test('entertainment:')
import os
import pickle
import time
import math
import struct
import datetime

cp=0

def int_str(x):
	
	byt = struct.pack('i',x)
	string = str(byt,'utf-8')
	
	return string 

def str_int(x):
	
	byt=bytes(x,'utf-8')
	num=struct.unpack('i',byt)[0]
	
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
	
	
#======================================================================================================#
	
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
	
	no_of_block