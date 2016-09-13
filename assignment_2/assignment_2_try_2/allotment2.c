#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>

//==========================================================================================================//

typedef struct list
{
	int a[200];
	int head;
	int tail;
}queue;

typedef struct type
{
	int num;
	int ans;
	int wait;
	int finish;
	int display;
	int destroy;
}structure;

typedef struct input
{
	structure str[4];
}inp;

//============================================================================================================//

main()
{
	//------------------output------------------------------------//
		inp *shared_struct;
		
		int key=0635, id, limit_output=4;
		
			id=shmget(key, sizeof(inp), IPC_CREAT|0666);
			shared_struct=shmat(id, NULL, 0);
	//------------------------------------------------------------//
	
	//-----------------input--------------------------------------//
		int *shared_com, id_mem, id_com, key_q=8778, key_com=2123, size, limit_input=200;
	
		queue *shared_mem;
	
		size=sizeof(queue);
	
			id_mem=shmget(key_q,size,IPC_CREAT|0666);
			shared_mem=shmat(id_mem,NULL,0);
		
			id_com=shmget(key_com,sizeof(int),IPC_CREAT|0666);
			shared_com=shmat(id_com,NULL,0);
	//--------------------------------------------------------------//
	
	int i, pid=0;
		
			
	for(i=0;i<limit_output;i++)
	{
		shared_struct->str[i].wait=0;
		shared_struct->str[i].finish=0;
		shared_struct->str[i].display=0;
		shared_struct->str[i].destroy=0;
	}
	
	while (1)
	{
		//check queue status
			
			if (shared_mem->head!=shared_mem->tail)
			{
				shared_mem->head++;
			}
			else
			{
				if (shared_mem->head>=limit_input)
					shared_mem->head=0;
				
				while (shared_mem->head==shared_mem->tail)
				{
					if ((shared_mem->a[(shared_mem->head)+1])!=-1)
						break;
					else
					{
						//printf("Queue empty\n");
						
						if ((*shared_com)==0)
						{
							for (i=0;i<limit_output;i++)
								shared_struct->str[i].destroy=1;	
							exit(0);	
						}
					}		
				}	
			 }
			 
			 if (pid>=limit_output)
			 	pid=0;
			 
			 	while ((shared_struct->str[pid].wait==1) && (shared_struct->str[pid].finish==0) && (shared_struct->str[pid].display==0)) 	
				{
					pid++;
						if (pid>=limit_output)
							pid=0;
				}
							
			 if (shared_mem->a[shared_mem->head]!=-1)
			 {
				shared_struct->str[pid].num=shared_mem->a[shared_mem->head];
				shared_struct->str[pid].wait=1;
				shared_struct->str[pid].display=0;
				shared_struct->str[pid].finish=0;
					printf("%d alloted to process %d\n",shared_mem->a[shared_mem->head], pid);
				shared_mem->a[shared_mem->head]=-1;
			 }
		}
}					
			 
	
			
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
