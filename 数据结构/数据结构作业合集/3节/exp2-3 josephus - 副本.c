#include "stdio.h"
#include "stdlib.h"
#define S sizeof(struct node)

struct node
{
  int num;
  struct node *next;
};
typedef struct node NODE;

NODE *createlinklist(int n)
{
   NODE *head,*p,*q;
   int i=1;
   head=p=(struct node*)malloc(sizeof(struct node));
//   p->num=i;
   for(i=1;i<=n;i++)
   {
       q=(struct node*)malloc(sizeof(struct node));
       if(q==0) return(0);
       p->next=q;
       p=q;
       p->num=i;
   }
   p->next=head->next; /*to have the last cell keep a pointer to the first*/

   return head;
}

void printlinklist(NODE *p,int n)
{
   int i;
   NODE *q = p;
   if(q->next == NULL){
      printf("the list is NULL!");
      return;
   }
   printf("Print all players:\n");
   p=p->next;
   for(i=1;i<=n;i++)
   { 
      if(q == NULL){
         printf("the list is NULL!");
         return;
       }
    printf("%d ",p->num);
    p=p->next;
   }
   printf("\n");
}

void joseph(NODE *p,int n,int m,int k)
{
	int i,j;
	NODE *a;
 
  	for(i=1;i<m;i++)
	{
	    if (p==NULL) 
		{  
	        printf("A list has not be created!\n");
	    }
	        p=p->next;
	}
	 while(p->next!=p)
	 {
	 		for(j=1;j<k;j++)
	 		{
	 			p=p->next;
			 }
		 a=p->next;
		 p->next=a->next;
		 free(a);
		 
		 
	 }
  
	printf("最后剩下的是%d号\n",p->num);
}

void main()
{
   NODE *head;
   int n,m,k;
   printf("Please input the number of players N:\n");
   scanf("%d",&n);
   printf("Input the beginning position m:\n");
   scanf("%d",&m);
   printf("Input the passed number k:\n");
   scanf("%d",&k);
   head=createlinklist(n);
   printlinklist(head,n);
   printf("The order of the eliminated person:\n");
   joseph(head,n,m,k);
   system("PAUSE");
}

