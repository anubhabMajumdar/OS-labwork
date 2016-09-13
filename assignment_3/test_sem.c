#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>	/* Include this to use semaphores */

#define wait(s) semop(s, &pop, 1)  /* pop is the structure we pass for doing
				   the P(s) operation */
#define signal(s) semop(s, &vop, 1)  /* vop is the structure we pass for doing
				   the V(s) operation */
main()
{
	int semid1, limit_output=4, i, pid;
	struct sembuf pop, vop ;
	
	semid1 = semget(IPC_PRIVATE, 1, 0777|IPC_CREAT);
	
	semctl(semid1, 0, SETVAL, 1);
	
	pop.sem_num = vop.sem_num = 0;
	pop.sem_flg = vop.sem_flg = 0;
	pop.sem_op = -1 ; vop.sem_op = 1 ;
	
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
	printf("%d created\n",pid);
	while(1)
	{
		wait(semid1);
		printf("%d entered critical section\n",pid);
		printf("%d exited critical section\n",pid);
		signal(semid1);
	}
	
	
	
}
