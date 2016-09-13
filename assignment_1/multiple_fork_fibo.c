/* This program prints fibonacci series in multiple different process */

#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <stdio.h>

int fibonacci(int n)
{
	int sum;
	
	if (n<=1)
		return n;
	else
		sum=fibonacci(n-1)+fibonacci(n-2);
return sum;

}

void process(int id, int start, int stop)
{
	int i;
	
	for (i=start;i<=stop;i++)
		{
			printf("Child Process %d: %d\n",id , fibonacci(i));
		}
	
}

void main()
{
	int n,proc,i;
	pid_t id=0;
	
		printf("Enter n:");
		scanf("%d",&n);
		
		printf("Enter number of child process:");
		scanf("%d",&proc);
		
		for(i=0;i<proc;i++)
		{
			if (id==0)
				id=fork();
			if (id==0)
				process(i,(i*n/proc)+1,(i+1)*n/proc);
				//kill(id,s);
		}
}
				
				
			
	
	
	
	
	
	
	
	
	
	
	
