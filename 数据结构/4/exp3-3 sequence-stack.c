#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;
typedef int SElemType;

typedef struct{
   SElemType *base;
   SElemType *top;
   int stacksize;
}SqStack,*PSqStack;

SqStack S1;

Status InitStack(PSqStack S);//Initialize an empty list
Status ClearStack(PSqStack S);
Status StackEmpty(PSqStack S);
Status Push(PSqStack S, SElemType e);
SElemType Pop(PSqStack S);
Status StackTraverse(PSqStack S);


void main()
{
	char c;
	int e;

	while(1){
	printf("List Implementation by Sequence\n");
    printf("===========================================\n");
    printf("1. Initialize a stack; 2. Push an element;\n");
	printf("3. Pop an element;     4. TraverseDispStack;\n");
	printf("5. Is a stack empty;   6. Clear a stack;\n");
	printf("7. Destroy a stack;    0. Exit;\n");
    printf("===========================================\n");
 
    scanf(" %c",&c);
	

	switch(c){
	  case '1':
		  InitStack(&S1);
		  break;
	  case '2':
		  printf("Input an element:\n");
		  scanf("%d",&e);
		  if(Push(&S1, e)) 
			  printf("push successfully!");
		  else
			  printf("push failure!");
		  break;
	  case '3':
		  printf("Pop the element %d\n",Pop(&S1));
		  break;
	  case '4':
		   StackTraverse(&S1);
		  break;
	  case '5':
		  if(StackEmpty(&S1)) 
			  printf("Empty!");
		  else
			  printf("Not Empty!");
		  break;
		  
	  case '6':
	  	    ClearStack(&S1);
	  	  	printf("clear successfully!");
		   break;
	  case '7':
	  	   DestroyStack(&S1);
	  	   printf("destory successfully!");
		
		   break;
	  case '0':exit(0);
	  default:
		  printf("Print an incorrect letter;\n");
		  break;	
	}

	}

   
	system("PAUSE");

}



Status InitStack(PSqStack S)
{

	S->base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S) 
	exit(OVERFLOW);
	S->top = S->base ;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}



Status Push(PSqStack S, SElemType e)
{
	if(S->top-S->base>=S->stacksize-1){
		S->base = (SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S->base) exit(OVERFLOW);
		S->top=S->base+S->stacksize;
		S->stacksize=S->stacksize+STACKINCREMENT;
	} 
	* S-> top++=e;
	
	return OK;
}


SElemType Pop(PSqStack S)
{
	if(S->top==S->base){
		return ERROR;
	}
	return *-- S-> top;
  
}


Status StackEmpty(PSqStack S)
{
	if(S->top == S->base ){
		return 1;
	}
	else{
		return 0;
	}
}


Status StackTraverse(PSqStack S)
{
	SElemType *p;
	p=S->top;
	if (StackEmpty(S)){
	  printf("This is an empty stack!");
      return ERROR;	
	}
	else {
		while(p > S->base){
			printf("%d ", *--p);
			
		}
	}
	
	return OK;
}

Status ClearStack(PSqStack S)
{
	if(S->base){
		S->top=S->base;
	}
	return OK;
}

Status DestroyStack(PSqStack S)
{
	free(S->base);
	S->top = S->base = NULL;
	return OK;
}
