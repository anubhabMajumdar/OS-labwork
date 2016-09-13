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
	pid_t proc_id;
	int busy;
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
	
/*------------------------------------------------------------------------*/	
	
	
int main()
{

	int shared_memory_id,shmget_id,*shmget_status,array_point=0;
	proc *shared_memory,*temp;
	int size=10*sizeof(proc);
	key_t key=8486;
	
	temp=(proc *)malloc(sizeof(proc));
	
	shared_memory_id=shmget(key,size,IPC_CREAT|0666);
	shmget_id=shmget(key,sizeof(int),IPC_CREAT|0666);
		
	shared_memory=shmat(shared_memory_id,NULL,0);
	shmget_status=shmat(shmget_id,NULL,0);
		
	while(*shmget_status!=0)
	{
			for(array_point=0;array_point<10;array_point++)
			{
				memcpy(temp,&shared_memory[array_point],sizeof(proc));
				printf("fact-value=%d\nAnswer=%d\nbusy=%d\n",temp->fact_value,temp->result,temp->busy);
				if (temp->busy==1)
				{
					temp->result=fact(temp->fact_value);
					temp->busy=0;
					printf("inside-if\nfact-value=%d\nAnswer=%d\nbusy=%d\n",temp->fact_value,temp->result,temp->busy);
					memcpy(&shared_memory[array_point],temp,sizeof(proc));
				}
			}
	}
	
	printf("Process Completed\n\n");
}				
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
