#include<stdio.h>

int main()
{
	int i,j,k,n,m;
	printf("请输入你想建金字塔的层数：");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		for(j=n-i;j>=1&&j<n;j--)
		{
			printf(" ");
		}
		for(k=1;k>=1&&k<=i;k++)
		{
			printf("%d",k);
		}
		for(m=i-1;m>=1&&m<=n;m--)
		{
			printf("%d",m);
		}
	printf("\n");
	 } 
	 	
		 return 0;
 } 
