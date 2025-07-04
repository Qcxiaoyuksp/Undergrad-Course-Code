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

typedef struct SNode{
	ElemType data;
	struct SNode *next;
}SNode, *Stack;



Stack InitStack(Stack S,int n);
Status StackTraverse(Stack S);
Status ClearStack(Stack S1,Stack S2);//
ElemType Top(Stack S);
Status IsEmpty(Stack S);
Status Push(Stack S1, Stack S2, ElemType e);//
Status Recycle(Stack S1, Stack S2);

ElemType Pop(Stack S1,Stack S2);


void main()
{
	char c;
	int e,n;
	Stack S1,S2;
	S1 = (Stack )malloc(sizeof(SNode));
	S2 = (Stack )malloc(sizeof(SNode));
	S1->next = NULL;
	S2->next = NULL;

	while(1){
		printf("List Implementation by Sequence\n");
		printf("===========================================\n");
		printf("1. Initialize a stack; 2. Push an element;\n");
		printf("3. Pop an element;     4. TraverseStack;\n");
		printf("5. Is a stack empty;   6. Clear a stack;\n");
		printf("7. Return top value;   8. TraverseRecycleBin;\n");
		printf("9. For extension;      0. Exit;\n");
		printf("===========================================\n");
		
		scanf(" %c",&c);
		
		
		switch(c){
		case '1':
			printf("Input the number of nodes:\n");
			scanf(" %d",&n);
			S1=InitStack(S1,n);
			break;
		case '2':/*
			printf("Input an element:\n");
			scanf("%d",&e);
			if(Push(S1, S2, e)) 
				printf("push successfully!");
			else
				printf("push failure!");*/
			break;
		case '3':/*
			printf("Pop the element %d\n",Pop(S1,S2));*/
			break;
		case '4':
			StackTraverse(S1);
			break;
		case '5':
			if(!IsEmpty(S1)) 
				printf("Not Empty Stack!");
			else
				printf("Empty Stack!");
			break;
			
		case '6':/*
			if(ClearStack(S1,S2)) 
				printf("Clear successfully!");
			else
				printf("Clear failure!");*/
			break;
		case '7':
			if(Top(S1)) 
				printf("Top value is :%d",Top(S1));
			else
				printf("A null stack!");
			break;
		case '8':
			StackTraverse(S2);
			break;
		case '0':exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;	
		}
		
	}
	
	system("PAUSE");
	
}

ClearStack(Stack S1,Stack S2)
{
	

}

Stack InitStack(Stack S,int n)
{
    int i;
    SNode *p;
	
    printf("Please input %d the elements of a stack:\n",n);
   	
    for(i=n; i > 0 ; --i) {
		p = (Stack)malloc(sizeof(SNode));
		scanf("%d",&p->data);
		p->next = S->next;
		S->next = p; 
    } 
	return S;
}

ElemType Top(Stack S)
{
	if (S->next==NULL) 
	{  printf("A null stack!");
	   return 0;
	}
	
	return S->next->data;
}

Status StackTraverse(Stack S)
{
	SNode *p;
    p=S->next;
	if (p==NULL) //if (p==NULL)
	{  printf("A null list!");
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

Status Recycle(Stack S2, SNode *p)//insert p into S2
{
 		p->next = S2->next;
		S2->next = p; 
    	return OK;
}

Status Push(Stack S1, Stack S2, ElemType e)
{
    

	return OK;
}


ElemType Pop(Stack S1, Stack S2)
{

}

Status IsEmpty(Stack S)
{
	if (S->next==NULL) {
		return 1;
	}
    else
		return 0;
}


