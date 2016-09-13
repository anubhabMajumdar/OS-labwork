#include<stdio.h>

int fibonacci(int n)
{
	int sum;
	
	if (n<=1)
		return n;
	else
		sum=fibonacci(n-1)+fibonacci(n-2);
return sum;
}

void main()
{
	printf("%d\n",fibonacci(10));
	}
	
