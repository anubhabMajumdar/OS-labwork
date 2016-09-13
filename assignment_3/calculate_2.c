#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>
#include <sys/sem.h>	/* Include this to use semaphores */

#define wait(s) semop(s, &pop, 1)  /* pop is the structure we pass for doing
				   the P(s) operation */
#define signal(s) semop(s, &vop, 1)  /* vop is the structure we pass for doing
				   the V(s) operation */

//==========================================================================================================//

typedef struct list
{
	int a[200];
	int head;
	int tail;
}queue;

typedef struct out_list
{
	int a[200][2];
	int head;
	int tail;
}queue2;

//============================================================================================================//

int fact(int n)
{
	int ans=1,i;
	
	for(i=n;i>=1;i--)
	{
		ans*=i;
	}
	
	return ans;
}


//============================================================================================================//

main()
{
	//-----------------input---------------------------------------------------------//
		
		int *shared_com, id_mem, id_com, key_q=8778, key_com=5678, size, limit_input=200;
	
		queue *shared_mem;
	
		size=sizeof(queue);
	
			id_mem=shmget(key_q,size,IPC_CREAT|0666);
			shared_mem=shmat(id_mem,NULL,0);
		
			id_com=shmget(key_com,sizeof(int),IPC_CREAT|0666);
			shared_com=shmat(id_com,NULL,0);
			
	//------------------------------Output---------------------------------------//
	
		queue2 *shared_output;
		
		int size_out, id_out, key_out=8899, i;
			
			size_out=sizeof(queue2);
			
		id_out=shmget(key_out, size_out, IPC_CREAT|0666);
		shared_output=shmat(id_out,NULL,0);
			
			for (i=0;i<limit_input;i++)
			{
				shared_output->a[i][0]=-1;
				shared_output->a[i][1]=-1;
			}
			
			shared_output->tail=0;
			shared_output->head=-1;
			
			
	//-----------------------------Semaphore---------------------------------//
	
	int pid=0, key_semaphore=6635, *semaphore, id_semaphore, limit_output=4;
		
		
		int semid1, semid2;
	struct sembuf pop, vop ;
	
	semid1 = semget(IPC_PRIVATE, 1, 0777|IPC_CREAT);
	semid2 = semget(IPC_PRIVATE, 1, 0777|IPC_CREAT);
	
	semctl(semid1, 0, SETVAL, 1);
	semctl(semid2, 0, SETVAL, 1);
	
	pop.sem_num = vop.sem_num = 0;
	pop.sem_flg = vop.sem_flg = 0;
	pop.sem_op = -1 ; vop.sem_op = 1 ;
	
	//----------------------------------Fork()------------------------------------------//
	
	for(i=1;i<limit_output;i++)
	{
		if (pid==0)
		{
			pid=fork();
				if (pid!=0)
				{
					pid=i;
				}	
		}		
		else
			break;
	}
	
		printf("Process %d created\n",pid);
		
		int answer, value;
		
	while (1)
	{
		wait(semid1);
		
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
					//printf("else\n")
					
					if ((*shared_com)==0)
					{
						printf("Process %d exiting\n",pid);
						signal(semid1);
						exit(0);
					}
					
				}		
			}
				//if ((shared_mem->a[(shared_mem->head)+1])!=-1)
				//	shared_mem->head++;	
		 }
		 
		 if (shared_mem->a[shared_mem->head]!=-1)
		 {
		 	printf("\npid-->%d got allotated to Value-->%d\n", pid, shared_mem->a[shared_mem->head]);
				answer=fact(shared_mem->a[shared_mem->head]);		 	
		 		value=shared_mem->a[shared_mem->head];

		 	shared_mem->a[shared_mem->head]=-1;
		 
		 	
		 	//output allocation in output queue
		 
			 if ((shared_output->tail)>=limit_input)
					shared_output->tail=0;
				while (shared_output->tail==shared_output->head)
				{
					if ((shared_output->a[(shared_output->tail)+1][0])==-1)
						break;
					else
						continue;
				}		
			
			shared_output->a[shared_output->tail][0]=value;
			shared_output->a[shared_output->tail][1]=answer;
			//printf("Value %d\tAnswer %d\n", shared_output->a[shared_output->tail][1], shared_output->tail);
			shared_output->tail++;
		}
		 
	signal(semid1);
	}	//end of while
	
			
}


							
	
	
	
	

