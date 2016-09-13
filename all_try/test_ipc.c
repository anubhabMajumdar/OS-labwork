#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>

typedef struct input
{
	int class;
	int roll;
}myInput;

int main()
{

	int shmget_id,i=0,fact_value,ch=1;
	myInput *shared_memory,*temp;
	int size=10*sizeof(myInput);
	key_t key=5678;
	
		shmget_id=shmget(key,size,IPC_CREAT|0666);
		
		shared_memory=shmat(shmget_id,NULL,0);
		
		printf("created\n");
		
		temp=shared_memory;
		
		for(i=0;i<10;i++)
		{
			printf("class=");
			scanf("%d",&shared_memory[i].class);
			shared_memory[i].roll=shared_memory[i].class;
			
		}
		
		for(i=0;i<10;i++)
		{
			printf("class=%d\nroll=%d\n",shared_memory[i].class,shared_memory[i].roll);
		}
		
		
		i=shmdt(NULL);
}
			
