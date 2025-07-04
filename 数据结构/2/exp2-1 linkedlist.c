/*
This is a framework for the implementation of a linked list.
*/

// 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef struct LNode{
  ElemType data;
  struct LNode *next;
}LNode, *LinkList;

LinkList CreatList_L(LinkList L,int n);
LinkList CreatList_LT(LinkList L, int n);
Status DispList_L(LinkList L);
Status ListInsert_L(LinkList L,int i, ElemType e);
Status ListDelete_L(LinkList L,int i);
LNode * GetElem_L(LinkList L,int i);
Status ClearList_L(LinkList L);

void main()
{
	char c;
	int e,d,n;
	LinkList L1;
	L1 = (LinkList)malloc(sizeof(LNode));

	while(1){
	printf("List Implementation by Sequence\n");
    printf("=================================================\n");
    printf("1. Create a list;     2. Create a list from tail; \n");
	printf("3. Display a list;    4. Insert an element; \n");
	printf("5. Delete an element; 6. Get an element; \n");
	printf("7. Clear a list;      0. Exit; \n");
	printf("=================================================\n");
 
    scanf(" %c",&c);//fflush(stdin); 
	
	switch(c){
	  
	  case '1':
		  printf("Input the number of nodes:\n");
		  scanf(" %d",&n);
		  L1 = CreatList_L(L1,n);
		  break;
	  case '2':
		  printf("Input the number of nodes:\n");
		  scanf(" %d", &n);
		  L1 = CreatList_LT(L1, n);
		  break;
	  case '3':
		  DispList_L(L1);
		  break;
	   case '4':
		   printf("Input a location and an element:\n");
		   scanf("%d%d",&d,&e);
		   if(ListInsert_L(L1,d,e)) 
			   printf("insert successfully!\n");
		   else
			   printf("insert failure!\n");
		   break;
	   case '5':
		   printf("Input a location:\n");
		   scanf(" %d",&d);
		   ListDelete_L(L1,d);
		   break;
	   case '6':
		   printf("Input a location to get an element:\n");
		   scanf(" %d",&d);
		   if(!GetElem_L(L1,d))
			   printf("Location Error!\n");
		   else
			   printf("The element is %d\n",GetElem_L(L1,d)->data);
		   break;
	   case '7':
		   if (ClearList_L(L1))
			   printf("clear successfully!\n");
		   else
			   printf("clear failure!\n");
	 
		  break;
	   case '0':exit(0);
	   default:
		   printf("Print an incorrect letter;\n");
		  break;	
	  }

	}
  
	system("PAUSE");

}

/*用头插法创建一个单链表*/
LinkList CreatList_L(LinkList L,int n)
{
    int i;
    LNode *p;

    L = (LinkList )malloc(sizeof(LNode));

	L->next = NULL;

    for(i=n; i > 0 ; --i) {
		p = (LinkList )malloc(sizeof(LNode));
		printf("Please input the %d-th element:\n",n-i+1);
		scanf("%d",&p->data);
		p->next = L->next;
		L->next = p;
    } 
	printf("A linked list with %d elements has been created!\n", n);
	return L;
}
/*用尾插法创建一个单链表*/
LinkList CreatList_LT(LinkList L, int n)
{
	int i;
	LNode* p, *r;
	L = (LinkList)malloc(sizeof(LNode));
	r = L;
	L->next = NULL;

	for (i = n; i > 0; --i) {
		p = (LinkList)malloc(sizeof(LNode));
		printf("Please input the %d-th element:\n", n - i + 1);
		scanf("%d", &p->data);
		r->next = p;
		r = p;
	}
	r->next = NULL;
	printf("A linked list with %d elements has been created!\n", n);
	return L;
}


/*显示一个单链表各元素*/
Status DispList_L(LinkList L)
{
	LNode *p=L;
	if (p==NULL) //if (p==NULL)
	{  printf("A list has not be created!\n");
	   return 0;
	}
	p=p->next;
	if (p == NULL) //if (p==NULL)
	{
		printf("A null list!\n");
		return 0;
	}
	while (p!=NULL)//while (p!=NULL)
	{
		printf("%5d", p->data);
		p=p->next;
	}
    printf("\n");
	return OK;
}

/*在第i个位置后插入元素e*/
Status ListInsert_L(LinkList L,int i, ElemType e)
{
	int j = 0;
    LNode *p, *s;
    p = L;
    while (p->next != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p != NULL)
    {
        s = (LinkList) malloc(sizeof(LNode));
        s->data = e;
        s->next = p->next;
        p->next = s;
        return OK;
    }
    return ERROR;
   
	
}

/*删除第i个位置元素*/
Status ListDelete_L(LinkList L,int i)
{
	int j = 0;
    LNode *p, *s;
    p = L;
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p->next != NULL && j == i - 1) {
        s = p->next;
        p->next = s->next;
        free(s);
        printf("delete successfully!");
    }
    else
    {
        printf("delete failure!");
    }
    return OK;

}

/*返回第i个位置元素*/
LNode *GetElem_L(LinkList L, int i)
{
	LNode *p;
	p = L->next;
	int j = 1;
    if (p == NULL){
        printf("A null list\n");
        return 0;
    }
    while (p && j < i){
        p = p->next;
        j++;
    }
    if (!p || j > i) return ERROR;
    else return p;
}

/*清空一个单链表*/
Status ClearList_L(LinkList L)
{
	LNode *s;
    if (L == NULL)
    {
        printf("A null list!\n");
        return 0;
    }
    while (L->next !=NULL)
    {
        s = L->next;
        L->next = s->next;
        free(s);
    }
	return OK;
}



