#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>

/*------------------------------------------------------------------------*/

typedef struct process_type
{
	int fact_value;
	int result;
	int assigned;
	int working;
	int finished;
}proc;

typedef struct schedular_type
{
	pid_t pid;
	int busy;
}schedule;
	
/*------------------------------------------------------------------------*/	

int fact(int n)
{
	int ans=1,i;
	
	for(i=n;i>=1;i--)
	{
		ans*=i;
	}
	
	return ans;
}

/*-------------------------------------------------------------------------*/

int main()
{

	int shared_memory_id,process_id,*shmget_status,shmget_id,array_point=0,q_size,p_size,p_select=0;
	
	proc *shared_memory,*temp_shared_memory;
	
	schedule *process_status;
	
	pid_t id;
	
	printf("Enter queue size:");
	scanf("%d",&q_size);
	
	printf("Enter Number of processes:");
	scanf("%d",&p_size);
	p_size+=1;
	
	int size_q=q_size*sizeof(proc); 
	
	int size_p=p_size*sizeof(schedule);
	
	key_t key=0000;
	
		shared_memory_id=shmget(key,size_q,IPC_CREAT|0666);
		shared_memory=(proc *)shmat(shared_memory_id,NULL,0);	//allocate shared memory for data structure
		if (shared_memory<0)
			exit(1);
		
		process_id=shmget(key,size_p,IPC_CREAT|0666);
		process_status=(schedule *)shmat(process_id,NULL,0);		//allocated memory for modifying process status
		
		if (process_status<0)
			exit(1);
		
		shmget_id=shmget(key,sizeof(int),IPC_CREAT|0666);
		shmget_status=(int *)shmat(process_id,NULL,0);		//allocate memory for continue
		if (shmget_status<0)
			exit(1);
		
		
				for (array_point=0;array_point<q_size;array_point++)
				{
					shared_memory[array_point].fact_value=0;
					shared_memory[array_point].result=0;
					shared_memory[array_point].assigned=0;
					shared_memory[array_point].working=0;
					shared_memory[array_point].finished=0;
				}	
				
				for (array_point=0;array_point<p_size;array_point++)
				{
					if (array_point==0)
						{
							process_status[array_point].pid=fork();
							printf("Process Created\n");
						}	
					else
					{
						if (process_status[array_point-1].pid!=0)
							{
								process_status[array_point].pid=fork();
								printf("Process Created\n");
							}	
						else
							process_status[array_point].pid=0;
					}
				}			
				
				
		array_point=0;
		
		printf("Start input process ?(1/0) :");
		scanf("%d",shmget_status);
		
		while(*shmget_status!=0)
		{	
				
			for (array_point=0;array_point<q_size;array_point++)
			{
				if (shared_memory[array_point].working==0 && shared_memory[array_point].assigned==0)
				{
					printf("\nPROCESS %d\nEnter fact_value:",array_point+1);	
					scanf("%d",&shared_memory[array_point].fact_value);
					shared_memory[array_point].assigned=1;				
				}
				else
					printf("\nPROCESS %d is being computed.....\n",array_point+1);
			}
			
				
			for(array_point=0;array_point<q_size;array_point++)
			{
				p_select=0;
					
					while(process_status[p_select].pid!=0 && process_status[p_select].busy!=0)
					{
						printf("\nProcess %d busy...\n",p_select);
						p_select++;
							
							if(p_select>=p_size)
								p_select=0;
					}
					
					printf("\nProcess %d allocated to fact value %d\n",p_select,shared_memory[array_point].fact_value);
					process_status[p_select]=1;				
					
					id=fork();
					
					if (id==0)
					{
						if (shared_memory[array_point].assigned==1)
						{
							shared_memory[array_point].result=fact(shared_memory[array_point].fact_value);
							shared_memory[array_point].finished=1;
							shared_memory[array_point].working=0;
							process_status[p_select]=0;
						}
					exit(0);
					}	
			}
			
			for(array_point=0;array_point<q_size;array_point++)
			{
				
				if (shared_memory[array_point].assigned==1 && shared_memory[array_point].working==0 &&shared_memory[array_point].finished==1)
				{	
					printf("\nPROCESS %d\n",array_point+1);
					printf("Fact_value:%d\n",shared_memory[array_point].fact_value);
					printf("Result:%d\n",shared_memory[array_point].result);
					
					shared_memory[array_point].fact_value=0;
					shared_memory[array_point].result=0;
					shared_memory[array_point].assigned=0;
					shared_memory[array_point].working=0;
					shared_memory[array_point].finished=0;
				}
				
				else
					printf("\nPROCESS %d computing.....\n",array_point+1);
				
				
			}		
			
			printf("Continue ? (1/0) :");
			scanf("%d",shmget_status);
			
		}
}



