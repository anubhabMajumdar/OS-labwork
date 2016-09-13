/* This program prints numbers in different process */

#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

void main()
{
int i=0;
pid_t p;
	p=fork();
	
	if (p==0)
	{
		for (;i<10;i++)
		{
			printf("Parent Process : %d\n",i);
		}
	}
	
	else
	{
		printf("UNIQUE CHILD ID=%d\n",p);
		for (i=i+10;i<20;i++)
		{
			printf("Child Process : %d\n",i);
		}
	}
}


