#define _CRT_SECURE_NO_WARNINGS
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
typedef char SElemType;

typedef struct{
   SElemType *base;
   SElemType *top;
   int stacksize;
}SqStack,*PSqStack;

SqStack S1;

Status InitStack(PSqStack S);//Initialize an empty list
Status ClearStack(PSqStack S);
Status DestroyStack(PSqStack S);
Status StackEmpty(PSqStack S);
int StackLength(PSqStack S);
Status Push(PSqStack S, SElemType e);
SElemType Pop(PSqStack S);
SElemType GetTop(PSqStack S);
Status StackTraverse(PSqStack S);
int BracketCheck(char *a);


void main()
{
	int c;
	char e;
	char str[100];

	while(1){
	printf("\nStack Implementation by Sequence\n");
    printf("===========================================\n");
    printf("1. Initialize a stack; 2. Push an element;\n");
	printf("3. Pop an element;     4. TraverseDispStack;\n");
	printf("5. Is a stack empty;   6. Clear a stack;\n");
	printf("7. Get stack length;   8. Get top element;\n");
	printf("9. Check if brackets are balanced;   \n");
	printf("10.Destroy a stack;   0. Exit;\n");
    printf("===========================================\n");
 
    scanf(" %d",&c);
	

	switch(c){
	  case 1:
		  InitStack(&S1);
		  printf("initialize successfully!\n");
		  break;
	  case 2:
		  printf("Input an element:\n");
		  scanf(" %c",&e);
		  if(Push(&S1, e)) 
			  printf("push successfully!\n");
		  else
			  printf("push failure!\n");
		  break;
	  case 3:
	  	if(Pop(&S1))
			  printf("Pop the element %c\n",Pop(&S1));
		else
			  printf("This is an empty stack!\n");
		  break;
	  case 4:
		   StackTraverse(&S1);
		  break;
	  case 5:
		  if(StackEmpty(&S1)) 
			  printf("Empty!\n");
		  else
			  printf("Not Empty!\n");
		  break;
	  case 6:
		ClearStack(&S1);
	  	printf("clear successfully!\n");
		break;
	  case 7:
	  	printf("stacklength is %d\n",StackLength(&S1));
	  	break;	   
	  case 8:
	  	if(GetTop(&S1))
			  printf("top element is %c\n",GetTop(&S1));
		else
			  printf("This is an empty stack!\n");
		break;
	  case 9:
	  	  printf("Input an expression\n");
		  scanf(" %s", str);	//	  gets(str);
		  if (BracketCheck(str))
			  printf("Balanced!\n");
		  else
			  printf("Not balanced!\n");
		   break;
	  case 10:
		DestroyStack(&S1);
	  	printf("destroy successfully!\n");
		break;
	  case 0:
	  	exit(0);
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
	if (!S->base) exit(OVERFLOW);
	S->top = S->base ;
	S->stacksize = STACK_INIT_SIZE;
	
	return OK;
}


Status Push(PSqStack S, SElemType e)
{
   
	if (S->top - S->base >= S->stacksize){
		S->base = (SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if (!S->base) exit(OVERFLOW);
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
    *S->top++ = e;  //等效于 *S->top=e; S->top++;
    
	return OK;
}


SElemType Pop(PSqStack S)
{
	
	if (S->top == S->base) //等效于 if(StackEmpty) 
		return ERROR;
	
	return *--S->top; //等效于 --S->top; e=*S->top; return e; 
}


SElemType  GetTop(PSqStack  S)
{
	
	if (S->top == S->base) return ERROR;
	
	return *(S->top - 1);
}


Status StackEmpty(PSqStack S)
{
	
	if(S->top==S->base)
		return TRUE;
	else 
		return FALSE;
}


Status StackTraverse(PSqStack S)
{
	SElemType *p;
	p=S->top;
	if (StackEmpty(S)){
	  printf("This is an empty stack!\n");
      return ERROR;	
	}
	else {
		while(p > S->base){
			printf("%5c", *--p);
			
		}
	}
	printf("\n");
	
	return OK;
}


int StackLength(PSqStack S)
{
	return S->top - S->base;
}

Status ClearStack(PSqStack S)
{
	
	if(S->base)
		S->top=S->base;
		
	return OK;
}


Status DestroyStack(PSqStack S)
{
	
	if(S->base){
		free(S->base);
		S->stacksize=0;
		S->top=S->base=NULL;
	}
	
	return 0;
}


int BracketCheck(char *a)
{
	int i=0;
	SqStack s;
	SElemType x;
	InitStack(&s);
	while(a[i])
	{
		switch(a[i])
		{
			case '(':
				Push(&s,a[i]);
				break;
			case '[':
				Push(&s,a[i]);
				break;
			case '{':
				Push(&s,a[i]);
				break;
			case ')':
				x=GetTop(&s);
				if(x=='(')
						Pop(&s);
				else
					return FALSE;
				break;
			case ']':
				x=GetTop(&s);
				if(x=='[')
						Pop(&s);
				else
					return FALSE;
				break;
			case '}':
				x=GetTop(&s);
				if(x=='{')
						Pop(&s);
				else
					return FALSE;
				break;
			default:
				break;
		}
		i++; 
	}
	if(s.top==s.base)
		return TRUE;
	return FALSE;
	
}

