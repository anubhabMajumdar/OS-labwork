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

	int shmget_id,i=0,fact_value,ans,ch=1;
	myInput *shared_memory;
	int size=10*sizeof(myInput);
	key_t key=5678;
	myInput inp;
	
		shmget_id=shmget(key,size,IPC_CREAT|0666);
		shared_memory=(myInput *)shmat(shmget_id,NULL,0);
		
		printf("created\n");
		for(i=0;i<10;i++)
		{
			if(shared_memory[i].class%2==0)
				{
					printf("class=%d\nroll=%d\n",shared_memory[i].class,shared_memory[i].roll);
					shared_memory[i].class=0;
					shared_memory[i].roll=0;
				}	
		}
		
}














