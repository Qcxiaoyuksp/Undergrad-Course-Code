/*
This is a framework for the implementation of a double linked list.
*/

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

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int Status;
typedef int ElemType;

typedef  struct DListNode {
	struct DListNode *prior;
	ElemType data;
	struct DListNode  *next;
} DListNode, *DLinkList;


DLinkList L1;

DLinkList CreatList_L(DLinkList L, int n);
DLinkList CreatList_LT(DLinkList L, int n);
Status DispList_L(DLinkList L);
Status DispList_LT(DLinkList L);
Status ListInsert_L(DLinkList L, int i, ElemType e);
Status ListDelete_L(DLinkList L, int i);
DListNode *GetElem_L(DLinkList L, int i);
DListNode *GetNext_L(DLinkList L, DListNode *p); 
DListNode *GetPrior_L(DLinkList L, DListNode *p);
Status DestroyList_L(DLinkList L);

void main()
{
	char c;
	int e, d, n;
	DListNode *Prior, *Next, *Current;
	while (1){
		printf("List Implementation by Sequence\n");
		printf("===============================================================\n");
		printf("1. Create a list;      2. Create a list by inserting from tail; \n");
		printf("3. Display a list;     4. Display a list from tail; \n");
		printf("5. Insert an element;  6. Delete an element; \n");
		printf("7. Get an element;     8. Get neighbors of an element\n");
		printf("9. Destroy a list;     0. Exit;\n");
		printf("===============================================================\n");

		scanf(" %c", &c);

		switch (c){

		case '1':
			printf("Input the number of nodes:\n");
			scanf(" %d", &n);
			L1 = CreatList_L(L1, n);
			break;
		case '2':/*
			printf("Input the number of nodes:\n");
			scanf(" %d", &n);
			L1 = CreatList_LT(L1, n);
			break;*/
		case '3':
			DispList_L(L1);
			break;
		case '4':
			DispList_LT(L1);
			break;
		case '5':/*
			printf("Input a location and an element:\n");
			scanf("%d%d", &d, &e);
			if (ListInsert_L(L1, d, e))
				printf("insert successfully!\n");
			else
				printf("insert failure!\n");
			break;*/
		case '6':/*
			printf("Input a location:\n");
			scanf(" %d", &d);
			if (ListDelete_L(L1, d))
				printf("delete successfully!\n");
			else
				printf("delete failure!\n");
			break;*/
			
		case '7':
			printf("Input a location to get an element:\n");
			scanf(" %d", &d);
			if (!GetElem_L(L1, d))
				printf("Location Error!\n");
			else
				printf("The element is %d\n", GetElem_L(L1, d)->data);
			break;
		case '8':/*
			printf("Input a location to get neighbors:\n");
			scanf(" %d", &d);
			Current = GetElem_L(L1, d);
			if (Current){
				Prior = GetPrior_L(L1, Current);
				Next = GetNext_L(L1, Current);
				if (!Prior && Next){
					printf("The prior element of %d is the head node \n", Current->data);
					printf("The next element of %d is %d\n", Current->data, Next->data);
				}
				else if (Prior && !Next){
					printf("The prior element of %d is %d\n", Current->data, Prior->data);
					printf("The next element of %d is the head node \n", Current->data);

				}
				else{
					printf("The prior element of %d is %d\n", Current->data, Prior->data);
					printf("The next element of %d is %d\n", Current->data, Next->data);
				}


			}
			else{
               printf("Location Error!\n");
			}
					
			break;*/

		case '9':

			DestroyList_L(L1);

			break;
		case '0':exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;
		}

	}

	system("PAUSE");

}
//头插法
DLinkList CreatList_L(DLinkList L, int n)
{
	int i;
	DListNode *p;

	L = (DLinkList)malloc(sizeof(DListNode));

	L->next = L;
	L->prior = L;

	for (i = n; i > 0; --i) {
		p = (DLinkList)malloc(sizeof(DListNode));
		printf("Please input the %d-th element:\n", n - i + 1);
		scanf("%d", &p->data);
		p->next = L->next;
		p->prior = L;
		L->next = p;
		p->next->prior = p;
	}
	printf("A double linked list with %d elements has been created!\n", n);
	return L;
}
/*
//尾插法
DLinkList CreatList_LT(DLinkList L, int n)
{
	int i;
	DListNode *p;

	L = (DLinkList)malloc(sizeof(DListNode));

	L->next = L;
	L->prior = L;



	printf("A double linked list with %d elements has been created!\n", n);
	return L;
}
*/

Status DispList_L(DLinkList L)
{
	DListNode *p = L;
	if (L->next == L) //if (L->prior == L)
	{
		printf("A null list!");
		return 0;
	}
	p = p->next;
	while (p != L)//while (p!=NULL)
	{
		printf("%5d", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

Status DispList_LT(DLinkList L)
{
	DListNode *p = L;
	if (L->next == L) //if (L->prior == L)
	{
		printf("A null list!");
		return 0;
	}
	p = p->prior;
	while (p != L)//while (p!=NULL)
	{
		printf("%5d", p->data);
		p = p->prior;
	}
	printf("\n");
	return OK;
}
/* 
Status ListInsert_L(DLinkList L, int i, ElemType e)
{
	int j;
	DListNode *p, *s;
	p = L;
	j = 0;
	if (i<0) return ERROR;
	while (j<i)
	{
		p = p->next;
		if (!p) return ERROR;
		j++;
	}//find the i-1 th node

	s = (DLinkList)malloc(sizeof(DListNode));
	__________________;
	__________________;
	__________________;
	__________________;
	__________________;
	return OK;
}


Status ListDelete_L(DLinkList L, int i)
{
	int j=0;
	DListNode *p=L->next;
	
	if (i<0) return ERROR;
	while (j<i - 1){
		p = p->next;
		j++;
	}
	if (p==L) return ERROR;
	__________________;
	__________________;
	__________________;
	return OK;
}
*/
DListNode *GetElem_L(DLinkList L, int i)
{
	int j;
	DListNode *p;
	p = L;
	j = 0;
	if (i<0) return NULL;
	while (j<i)
	{
		p = p->next;
		if (!p) return NULL;
		j++;
	}//find the i-1 th node
	return p;
}
/*
DListNode *GetPrior_L(DLinkList L, DListNode *p)
{
	__________________;
	__________________;
	__________________;
	__________________;
}
DListNode *GetNext_L(DLinkList L, DListNode *p)
{
	if (p->next == L)
		return NULL;
	else
		return p->next;
}*/

Status DestroyList_L(DLinkList L)
{
	DListNode *p, *q;
	p = L->next;
	if (p==L) return ERROR;
	
	while (!(p==L)){
		L->next = p->next;
	    p->next->prior = L;
	    free(p);
		p = L->next;
	}
	return OK;
}




