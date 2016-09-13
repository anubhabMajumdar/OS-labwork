/* reading values from shared memory */

#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>

typedef struct task_queue
{
	int fact_value;
	int ans;
	int proc_id;
	int busy_flag;
}tsk;

/*===================================================================================================*/

int factorial (int n)
{
	int i=n,fact=1;
	for(;i>=1;i--)
	{
		fact*=i;
	}
return (fact);
}

void print_struct(tsk a)
{
	printf("------------------------------------------------------\n");
	printf("Fact Value=%d\n",a.fact_value);
	printf("Answer=%d\n",a.ans);
	printf("Process id=%d\n",a.proc_id);
	printf("------------------------------------------------------\n");
}

void clear(tsk *a)
{
	a->fact_value=0;
	a->ans=0;
	a->proc_id=0;
	a->busy_flag=0;
}

/*====================================================================================================*/

int main()
{
	int shmget_id,shmget_status,i,fact_value;
	tsk *shared_memory;
	int *shared_status;
	int size=10*sizeof(tsk);
	key_t key=1234;
	pid_t *process=(pid_t *)malloc(10*sizeof(pid_t));
	
	shmget_id=shmget(key,size,IPC_CREAT|0666);
	shmget_status=shmget(key,sizeof(int),IPC_CREAT|0666);
	
	shared_memory=(tsk *)shmat(shmget_id,NULL,0);	
	shared_status=(int *)shmat(shmget_status,NULL,0);
	
	for(i=0;i<10;i++)
	{
		process[i]=0;
	}
	
	while (shared_status[0]==1)
	{
		for(i=0;i<10;i++)
			{
				if (i==0)
				{
					process[i]=fork();
				}
				else if (process[i-1]!=0)
				{
					process[i]=fork();
				}
				
				if (process[i]!=0 && shared_memory[i].fact_value!=0)
				{
					shared_memory[i].busy_flag=1;
					shared_memory[i].ans=factorial(shared_memory[i].fact_value);
					shared_memory[i].proc_id=process[i];
					print_struct(shared_memory[i]);
					clear(shared_memory);
				
				}
			}
	}
	
	/*while (1)
	{	
		if (shared_status[0]==0)
			continue;
		
		else if(shared_status[0]==1)
		{
			for (i=0;i<10;i++)
			{
				if(shared_memory[i].fact_value!=0 && process[i]!=0)
				{
					shared_memory[i].busy_flag=1;
					shared_memory[i].ans=factorial(shared_memory[i].fact_value);
					shared_memory[i].proc_id=process[i];
					print_struct(shared_memory[i]);
					clear(shared_memory);
				
				}
			}
		}
	
	
	}*/

}
		
