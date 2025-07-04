/*
注意声明变量的类型，结构体变量，还是结构体指针型变量，访问结构体成员的方法不同。
*/

#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int QElemType;

typedef struct QNode{
   QElemType data;
   struct QNode *next;
 }QNode,*QueuePtr;

typedef struct{
   QueuePtr front;
   QueuePtr rear;
} LinkQueue;



Status InitQueue(LinkQueue *Q);//Initialize an empty list
void ClearQueue(LinkQueue *Q);
Status QueueEmpty(LinkQueue *Q);
Status EnQueue(LinkQueue *Q, QElemType e);
QElemType DeQueue(LinkQueue *Q);
Status QueueTraverse(LinkQueue *Q);


void main()
{
	char c;
	int e;
    LinkQueue Q1;

	while(1){
	printf("List Implementation by Sequence\n");
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
		  scanf("%d",&e);
		  if(EnQueue(&Q1, e)) 
			  printf("EnQueue successfully!");
		  else
			  printf("EnQueuefailure!");
		  break;
	  case '3':
		  printf("DeQueue the element %d\n",DeQueue(&Q1));
		  break;
	  case '4':
		   QueueTraverse(&Q1);
		  break;
	  case '5':
		  if(QueueEmpty(&Q1)) 
			  printf("Not Empty!");
		  else
			  printf("Empty!");
		  break;
		  
	  case '6':
		   ClearQueue(&Q1);
		   break;
	  case '0':exit(0);
	  default:
		  printf("Print an incorrect letter;\n");
		  break;	
	}

	}

   
	system("PAUSE");

}


//销毁链式队列 
void DestroyQueue(LinkQueue *Q)
{ 
 if (Q == NULL)
 {
  printf("参数错误\n");
  return ;
 }
 while (Q->front)
 {
  Q->rear=Q->front->next;
  free(Q->front);
  Q->front=Q->rear;

 }
}

//清空链式队列 
void ClearQueue(LinkQueue *Q)
{
 DestroyQueue( Q);
 InitQueue(Q);
}

//求链式队列长度 
int QueueLength(LinkQueue Q)
{
 QueuePtr p; int n=0;
 p=Q.front;
 while (p!=Q.rear)
 {
  n++;
  p=p->next; 
 }
 return n;
}

//取队头元素 
QElemType GetHead(LinkQueue Q)
{ 
 if (Q.front!=Q.rear)
  return Q.front->next->data;
}






Status InitQueue(LinkQueue *Q)
{

	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front) exit(OVERFLOW);
	Q->front->next=NULL;

	return OK;
}



Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr p;

	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q->rear->next=p;
	Q->rear=p;

	return OK;
}


QElemType DeQueue(LinkQueue *Q)
{
	if(Q->front==Q->rear)  return ERROR;

	QueuePtr p;

	p=Q->front->next;
	QElemType e=p->data;
	Q->front->next=p->next;
	if(Q->rear==p)
		Q->rear=Q->front;
	free(p);

	return e;
}


Status QueueEmpty(LinkQueue *Q)
{
	if(Q->rear==Q->front) return ERROR;
	return OK;
}




Status QueueTraverse(LinkQueue *Q)
{
	QueuePtr p;
	p=Q->front->next;
	if (!QueueEmpty(Q)){
	  printf("This is an empty queue!");
      return ERROR;	
	}
	else {
		while(p){
			printf("%d\t", p->data);
	    	p=p->next;	
		}

	}
	
	return OK;
}

