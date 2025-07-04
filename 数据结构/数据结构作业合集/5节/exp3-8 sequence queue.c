

#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXQSIZE 5
 

typedef int Status;
//typedef int QElemType;
typedef char QElemType; 



typedef struct{
	QElemType *base;
	int front; //头指针，队非空时指向队头元素 
	int rear; //尾指针，队非空时指向队尾元素的下一位置 
} SqQueue; 

//SqQueue Q1;


Status InitQueue(SqQueue *Q);//Initialize an empty list
//Status ClearQueue(LinkQueue Q);
Status QueueEmpty(SqQueue *Q);
Status EnQueue(SqQueue *Q, QElemType e);
QElemType DeQueue(SqQueue *Q);
Status QueueTraverse(SqQueue *Q);


void main()
{
	char c;
	char e;
    SqQueue Q1;

	while(1){
	printf("Circular Queue Implementation by Sequence(char type)\n");
    printf("===========================================\n");
    printf("1. Initialize a queue; 2. EnQueue an element;\n");
	printf("3. DeQueue an element;     4. TraverseDispQueue;\n");
	printf("5. Is a queue empty;   6. Clear a stack;\n");
	printf("7. Destroy a queue;    0. Exit;\n");
    printf("===========================================\n");
 
    scanf(" %c",&c);
	

	switch(c){
	  case '1':
		  InitQueue(&Q1);
		  break;
	  case '2':
		  printf("Input an element:\n");
		  scanf(" %c",&e);
		  if(EnQueue(&Q1, e)) 
			  printf("EnQueue successfully!\n");
		  else
			  printf("EnQueue failure!\n");
		  break;
	  case '3':
		  printf("DeQueue the element %c\n",DeQueue(&Q1));
		  break;
	  case '4':
		  QueueTraverse(&Q1);
		  break;
	  case '5':
		  if(!QueueEmpty(&Q1)) 
			  printf("Not Empty!\n");
		  else
			  printf("Empty!\n");
		  break;
		  
	  case '6':
		
		   break;
	  case '0':exit(0);
	  default:
		  printf("Print an incorrect letter;\n");
		  break;	
	}

	}

   
	system("PAUSE");

}






Status InitQueue(SqQueue *Q)
{

	Q->base = (QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
	if (!Q->base ) exit(OVERFLOW);
	Q->front = Q->rear =0;

	return OK;
}



Status EnQueue(SqQueue *Q, QElemType e)
{
    if((Q->rear+1)%MAXQSIZE==Q->front)
		return ERROR;
	else
		{Q->base[Q->rear]=e;
	Q->rear++;}
	return OK;
}


QElemType DeQueue(SqQueue *Q)
{
	QElemType e;
	if(Q->front==Q->rear)
		return ERROR;
   else
	   {e=Q->base[Q->front];
	      Q->front++;}
   return e;
}


Status QueueEmpty(SqQueue *Q)
{
	if(Q->front == Q->rear)
		return OK ;
	else
		return  ERROR;
	
}





Status QueueTraverse(SqQueue *Q)
{
	int p;
	p=Q->front;
	if (QueueEmpty(Q)){
	  printf("This is an empty queue!");
      return ERROR;	
	}
	while((p)%MAXQSIZE!=Q->rear){
			printf("%c\t", Q->base[(p)%MAXQSIZE]);
	    	p++;	
	}
    printf("\n");
	return OK;
}

