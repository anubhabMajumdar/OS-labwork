#include<stdio.h>

void main()
{
	int ans=1,i;
	long long n=23;
	
	for(i=n;i>=1;i--)
	{
		//printf("%d",ans);
		ans*=i;
	}
	
	printf("%d",ans);
}

