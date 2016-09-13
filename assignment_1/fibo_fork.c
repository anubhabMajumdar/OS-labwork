/* This program prints fibonacci series in 2 different process */

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

void childprocess(int start, int stop)
{
	int i;
	
	for (i=start;i<=stop;i++)
		{
			printf("Child Process : %d\n", fibonacci(i));
		}
	
}

void parentprocess(int start, int stop)
{
	int i;
	
	for (i=start;i<=stop;i++)
		{
			printf("Parent Process : %d\n", fibonacci(i));
		}
}	

void main()
{

int first=0,second=1,n=0,result,i;
pid_t p;
	
	printf("Enter n:");
	scanf("%d",&n);
	
	p=fork();
	
	if (p==0)
		childprocess(n+1,2*n);	
	else
		parentprocess(1,n);
		
}


