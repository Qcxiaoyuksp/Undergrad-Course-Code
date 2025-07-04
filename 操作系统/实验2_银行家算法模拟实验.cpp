#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define N 10
#define M 10

typedef struct{
	int ip;
	int able[N];
	int visited[N];
	int remain[M];
}WorkNode;   /*工作节点*/

 /*ass为进程已分配资源,need为最大需求,r为各种资源的个数*/
int ass[N][M],need[N][M],r[M],top=-1,pnum=0,rnum=0;    

/*currnet为当前工作节点*/
WorkNode stack[N],current; 

int main()
{
	int i,ct = 0;
	
	void add(int [],int []);     /*进程完成,释放资源*/
	int small(int [],int []);      /*已有的资源是否能满足最大请求*/
	void init();                     /*初始化*/
	void output();
    //void output();       　　/*输出堆栈中的一种可能*/
	int bankalgo();               /*银行家算法主要部分，回溯法*/
	
	init();
	for(i=0;i<pnum;i++)
 		if(small(need[i],current.remain) )
 		  	current.able[++current.ip]=i;
	if(current.ip==-1)
	{
 		printf("it is unsafe\n");
 		return 0;
	}
	ct = bankalgo();
	printf("\nit is safe,and it has %d solutions\n",ct);
 	//else printf("\nit is unsafe\n");
 	
	return 0;
}

void init()
{
	int i,j,sum=0;
	system("cls");
	//clrscr();
 	printf("process number:");
 	scanf("%d",&pnum);
	printf("resource number:");
	scanf("%d",&rnum);
	printf("resource series:");
 	for(i=0;i<rnum;i++)
		scanf("%d",&r[i]);
	printf("assined matrix:");
	for(i=0;i<pnum;i++)
	{ 
		printf("p%d:",i);
  		for(j=0;j<rnum;j++)
   			scanf("%d",&ass[i][j]);
	}
 	printf("needed matrix:\n");
 	for(i=0;i<pnum;i++)
	{
  		printf("p%d:",i);
 		for(j=0;j<rnum;j++)
   			scanf("%d",&need[i][j]);
 	}
	memset(current.visited,0,sizeof(current.visited));
	for(i=0;i<rnum;i++)
	{
  		for(j=0;j<pnum;j++)
   		sum+=ass[j][i];
		current.remain[i]=r[i]-sum;
  		sum=0;
    }
	current.ip=-1;
}

void output()
{
	int i;
	for(i=0;i<=top;i++)
		printf("p%d -> ", stack[i].able[stack[i].ip]);
 	printf("\n");
}

void add(int x[],int y[])
{
	int i;
	for(i=0;i<rnum;i++)
		x[i]+=y[i];
}

int small(int x[],int y[])
{
	int i;
	for(i=0;i<rnum;i++)
	{
		if(x[i]>y[i])break;
	}
	if(i==rnum)return 1;
	return 0;
}

int bankalgo()
{
	int i,ct=0;
	while(1)
	{   
		stack[++top]=current;
		current.visited[current.able[current.ip]]=1;
		add(current.remain,ass[current.able[current.ip]]);
		current.ip=-1;
 		for(i=0;i<pnum;i++)
			if(!current.visited[i] && small(need[i],current.remain) )
   				current.able[++current.ip]=i;
		if(current.ip==-1)
  		{
   			if(top==pnum-1)
			{
   				output();
  				ct++;
 			}
  			else if(top<0) break;
  	 		current=stack[top--];
  	 		while(current.ip==0) current=stack[top--];
   			current.ip--;
 	 	}
 	 	
 	 	if (top < 0) break;
	}
	return ct;
}
