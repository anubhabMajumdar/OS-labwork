#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>

//==========================================================================================================//

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
	inp *shared_struct;
	
	int key=0635, id, limit=4, pid=0, i;
	
	id=shmget(key, sizeof(inp), IPC_CREAT|0666);
	shared_struct=shmat(id, NULL, 0);
	
	for(i=1;i<limit;i++)
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
			
	while (shared_struct->str[pid].destroy==0)
	{
		if (shared_struct->str[pid].wait==1)
		{
			shared_struct->str[pid].ans=fact(shared_struct->str[pid].num);

			printf("Number-->%d\nAnswer-->%d\n\n", shared_struct->str[pid].num, shared_struct->str[pid].ans);
			
			shared_struct->str[pid].wait=0;
			shared_struct->str[pid].finish=1;
			shared_struct->str[pid].display=1;
		}
		
	}	
}

			
			
	
	
	
	
	
	
	
	
	
	
	
		
	
			
		
	
	 	 


