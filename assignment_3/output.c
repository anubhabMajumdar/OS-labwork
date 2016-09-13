#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>

//==========================================================================================================//

typedef struct out_list
{
	int a[200][2];
	int head;
	int tail;
}queue;
//============================================================================================================//

main()
{

	int *shared_com , id_com, key_com=5678, size;
	
	id_com=shmget(key_com,sizeof(int),IPC_CREAT|0666);
	shared_com=shmat(id_com,NULL,0);
			
	queue *shared_output;
		
		int size_out, id_out, key_out=8899, i,limit_input=200;
			
			size_out=sizeof(queue);
			
		id_out=shmget(key_out, size_out, IPC_CREAT|0666);
		shared_output=shmat(id_out,NULL,0);
			
			/*for (i=0;i<limit_input;i++)
			{
				shared_output->a[i][0]=-1;
				shared_output->a[i][1]=-1;
			}
			
			shared_output->tail=0;
			shared_output->head=-1;
			*/
			while (1)
			{
			
				if (shared_output->head!=shared_output->tail)
				{
					shared_output->head++;
			
				}
		
					  
				else
				{
					if (shared_output->head>=limit_input)
						shared_output->head=0;
			
					while (shared_output->head==shared_output->tail)
					{
						if ((shared_output->a[(shared_output->head)+1][0])!=-1)
							break;
						else
						{
							if ((*shared_com)==0)
							{
								exit(0);
							}
					
						}		
					}
						//if ((shared_mem->a[(shared_mem->head)+1])!=-1)
						//	shared_mem->head++;	
				 }
				 
				 if (shared_output->a[shared_output->head][0]!=-1)
				 {
				 	printf("Value-->%d\tAnswer-->%d\n", shared_output->a[shared_output->head][0], shared_output->a[shared_output->head][1]);
					shared_output->a[shared_output->head][0]=-1;
					shared_output->a[shared_output->head][1]=-1;
				 }
			}
}			 	
			
	
	
	
	
	
	
	
	
	
	
	
		
	
			
		
	
	 	 


