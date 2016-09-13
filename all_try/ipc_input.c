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
}proc;

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

	int shared_memory_id,shmget_id,*shmget_status,array_point=0;
	
	proc *shared_memory,*temp,*temp_shared_memory;
	
	pid_t id;
	
	int size=10*sizeof(proc);
	
	key_t key=8365;
	
		shared_memory_id=shmget(key,size,IPC_CREAT|0666);
		shared_memory=shmat(shared_memory_id,NULL,0);
		
		shmget_id=shmget(key,sizeof(int),IPC_CREAT|0666);
		shmget_status=shmat(shmget_id,NULL,0);
		
		for (array_point=0;array_point<10;array_point++)
		{
			shared_memory[array_point].fact_value=0;
			shared_memory[array_point].result=0;
		}	
		
			array_point=0;
		
		printf("Start input process ?(1/0) :");
		scanf("%d",shmget_status);
		
		while(*shmget_status!=0)
		{	
			for (array_point=0;array_point<10;array_point++)
			{
				if (shared_memory[array_point].fact_value==0)
				{
					printf("Enter fact_value:");	
					scanf("%d",&shared_memory[array_point].fact_value);				
				}
			}
				
			for(array_point=0;array_point<10;array_point++)
			{
				
				id=fork();
					if (id==0)
					{
						if (shared_memory[array_point].fact_value>0)
						{
								shared_memory[array_point].result=fact(shared_memory[array_point].fact_value);
						}	
					exit(0);
					}	
			
			}
			
			for(array_point=0;array_point<10;array_point++)
			{
				if (shared_memory[array_point].result>0)
				{
					printf("Fact_value:%d\n",shared_memory[array_point].fact_value);
					printf("Result:%d\n",shared_memory[array_point].result);
					
					shared_memory[array_point].fact_value=0;
					shared_memory[array_point].result=0;
				}
			}		
			
			
			
			printf("Continue ? (1/0) :");
			scanf("%d",shmget_status);
			
		}
}
		
			
				
		
		
		
		
		
		
		
		
		
		
		
		
