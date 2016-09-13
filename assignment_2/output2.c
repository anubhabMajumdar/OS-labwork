#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>

typedef struct input
{
	int fact;
	int result;
	int wait;
	int finish;
	int destroy;
	int display;
}p;

/******************************************************************/

void set_value(p *shared_memory,int terms)
{
	int i;
	
	for (i=0;i<terms;i++)
	{
		shared_memory[i].fact=0;
		shared_memory[i].wait=0;
		shared_memory[i].finish=0;
		shared_memory[i].result=0;
		shared_memory[i].destroy=0;
		shared_memory[i].display=0;
		
	}
}	

/******************************************************************/

void allotment(p *shared_memory, p *array,int pointer)
{
	int i,point=0;
		while (shared_memory[point].wait==1)
		{
			point++;
				if (point>=10)
					point=0;
		}
		
		shared_memory[point].fact=array[i].fact;
		shared_memory[point].wait=1;
		shared_memory[point].result=0;
		shared_memory[point].finish=0;
	
		printf("allotment %d %d\n",shared_memory[point].fact,shared_memory[point].wait);
		
		array[pointer].fact=0;
		array[pointer].result=0;
		array[pointer].wait=0;
		array[pointer].finish=0;
}

/******************************************************************/

main()
{
	p *shared_memory,*start,*current;
	int memory_id,size=10*sizeof(p),i,j,ch=1,q_pointer=0,point=0;
	key_t key=9999;
	
	memory_id=shmget(key,size,IPC_CREAT|0666);
	shared_memory=shmat(memory_id,NULL,0);
	
	start=malloc(20*sizeof(p));
	current=start;
	
	set_value(shared_memory,10);	//inital value of shared memory
	set_value(start,20);		//initial value of queue
	
	ch=1;
	
	while (ch==1)
	{
			
			for (i=0;i<10;i++)
			{
				if (shared_memory[i].finish==1 && shared_memory[i].display==1)
				{
					printf("\nfact value=%d\nAnswer=%d\n\n",shared_memory[i].fact,shared_memory[i].result);
					shared_memory[i].finish=0;
					shared_memory[i].display=0;
					shared_memory[i].fact=0;
					shared_memory[i].result=0;
				}
			}
			
			printf("\n\n");
			
			
				for(i=0;i<10;i++)
				{
					if(shared_memory[i].wait==0 && shared_memory[i].display==0)
						shared_memory[i].destroy=1;
					else if (shared_memory[i].wait==1)
						i--;
					else if (shared_memory[i].finish==1 && shared_memory[i].display==1)
					{
						printf("\nfact value=%d\nAnswer=%d\n\n",shared_memory[i].fact,shared_memory[i].result);
						shared_memory[i].finish=0;
						shared_memory[i].display=0;
						shared_memory[i].fact=0;
						shared_memory[i].result=0;
						i--;
					}
				}				
			}
	}
	
	


