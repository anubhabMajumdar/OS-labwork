#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdio.h>
#include <sys/stat.h>

//==========================================================================================================//

typedef struct list
{
	int a[200];
	int head;
	int tail;
}queue;

//==========================================================================================================//


main()
{
	int *shared_com, id_mem, id_com, key_q=8778, key_com=2123, size, limit=200, in, i ;
	
	queue *shared_mem;
	
	size=sizeof(queue);
	
		id_mem=shmget(key_q,size,IPC_CREAT|0666);
		shared_mem=shmat(id_mem,NULL,0);
		
		id_com=shmget(key_com,sizeof(int),IPC_CREAT|0666);
		shared_com=shmat(id_com,NULL,0);
	
	// Initial values
	
	*shared_com=0;
	shared_mem->head=-1;
	shared_mem->tail=0;
		for(i=0;i<limit;i++)
			shared_mem->a[i]=-1;
	
				
	printf("Start Process (1/0)-->");
	scanf("%d", shared_com);
	
	while ((*shared_com)==1)
	{
		printf("Enter Number-->");
		
			if ((shared_mem->tail)>=limit)
				shared_mem->tail=0;
			while (shared_mem->tail==shared_mem->head)
			{
				if ((shared_mem->a[(shared_mem->tail)+1])==-1)
					break;
				else
					printf("Queue Full. Kindly wait\n");
			}	
			
		scanf("%d", &in);
		
		shared_mem->a[shared_mem->tail]=in;
		shared_mem->tail++;
		
		printf("Continue Process (1/0)-->");
		scanf("%d", shared_com);
	}
	
	
}
			 
		
