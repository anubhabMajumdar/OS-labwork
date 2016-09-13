#include<stdio.h>
#include<string.h>

void type_print(char *str)
{
	int i=0;
	while(str[i]!='\n')
	{
		printf("%c",str[i]);
		i++;
	}
	//printf("%d",i);
}

void take_input(char *inp)
{
	int i=0;
	for (i=0;i<100 && ((inp[i]=getchar())!='\n');i++);
	
}

int compare(char *a,char *b)
{
	int n;
	if ((a[0]=='\n') && (b[0]=='\n'))
	{
		return 0;
	}
	
	if ((a[0]=='\n') && (b[0]!='\n'))
	{
		return -1;
	}
	
	if ((a[0]!='\n') && (b[0]=='\n'))
	{
		return 1;
	}
	
	n=compare(a+1,b+1);	 
}

void makefile()
{
	printf("file made\n");	
}




main()
{
	char a[100];
	type_print("$anubhab>\n");
	take_input(a);
	while(compare(a,"exit\n")!=0)
	{
		type_print("$anubhab>\n");
		take_input(a);
		
		if (compare(a,"mkfs\n")==0)
			makefile();
		
	}	
}
