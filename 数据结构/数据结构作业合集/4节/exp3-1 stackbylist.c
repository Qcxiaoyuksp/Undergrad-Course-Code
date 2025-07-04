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

Status ClearStack(Stack S);
ElemType Top(Stack S);
Status IsEmpty(Stack S);
Status Push(Stack S, ElemType e);
ElemType Pop(Stack S);

void main()
{
	char c;
	int e,n;
	Stack S1;
	S1 = (Stack )malloc(sizeof(SNode));
	
	while(1){
		printf("List Implementation by Sequence\n");
		printf("===========================================\n");
		printf("1. Initialize a stack; 2. Push an element;\n");
		printf("3. Pop an element;     4. TraverseDispStack;\n");
		printf("5. Is a stack empty;   6. Clear a stack;\n");
		printf("7. Return top value;    0. Exit;\n");
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
			if(Push(S1, e)) 
				printf("push successfully!");
			else
				printf("push failure!");*/
			break;
		case '3':/*
			printf("Pop the element %d\n",Pop(S1));*/
			break;
		case '4':
			StackTraverse(S1);
			break;
		case '5':/*
			if(!IsEmpty(S1)) 
				printf("Not Empty Stack!");
			else
				printf("Empty Stack!");*/
			break;
			
		case '6':/*
			if(ClearStack(S1)) 
				printf("Clear successfully!");
			else
				printf("Clear failure!");*/
			break;
		case '7':/*
			if(Top(S1)) 
				printf("Top value is :%d",Top(S1));
			else
				printf("A null stack!");*/
			break;
		case '0':exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;	
		}
		
	}
	
	system("PAUSE");
	
}


Stack InitStack(Stack S,int n)
{
    int i;
    SNode *p;
	
    printf("Please input %d the elements of a stack:\n",n);
    S = (Stack )malloc(sizeof(SNode));
	
	S->next = NULL;
	
    for(i=n; i > 0 ; --i) {
		p = (Stack)malloc(sizeof(SNode));
		scanf("%d",&p->data);
		p->next = S->next;
		S->next = p; 
    } 
	return S;
}

Status StackTraverse(Stack S)
{
	SNode *p=S;
	if (p==NULL) //if (p==NULL)
	{  printf("A null list!");
	   return 0;
	}
	p=p->next;
	while (p!=NULL)//while (p!=NULL)
	{
		printf("%5d", p->data);
		p=p->next;
	}
    printf("\n");
	return OK;
}


Status ClearStack(Stack S)
{
	

}



ElemType Top(Stack S)
{


}



Status Push(Stack S, ElemType e)
{
 

}


ElemType Pop(Stack S)
{


}

Status IsEmpty(Stack S)
{


}


