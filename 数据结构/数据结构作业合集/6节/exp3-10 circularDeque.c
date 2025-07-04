/*
双端队列（641. 设计循环双端队列），单调队列（从大到小）（239. 滑动窗口最大值）实现
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXQSIZE 10
 
typedef int Status;
typedef int QElemType;
//typedef char QElemType; 

typedef struct{
	QElemType *base;
	int front; //头指针，队非空时指向队头元素 
	int rear; //尾指针，队非空时指向队尾元素的下一位置 
} cirDeque;

Status InitQueue(cirDeque *Q);//Initialize an empty list
Status insertFront(cirDeque *Q, QElemType e);
Status insertRear(cirDeque *Q, QElemType e);
Status deleteFront(cirDeque *Q);
Status deleteRear(cirDeque *Q);
QElemType getFront(cirDeque *Q);
QElemType getRear(cirDeque *Q);
Status isEmpty(cirDeque *Q);
Status isFull(cirDeque *Q);
Status QueueTraverse(cirDeque *Q);
Status DeMonoQueue(cirDeque *Q, QElemType e);
Status EnMonoQueue(cirDeque *Q, QElemType e);
QElemType maxMonoQueue(cirDeque *Q);
int * maxSlidingWindow(cirDeque *Q, int *nums, int numsSize, int k);

void main()
{
	char c;
	int i,e;
	int nums[] = { 1, 3, -1, -3, 5, 3, 6, 7 };
	int numsSize=8;
	int k = 3;
	int *maxWindow;
	cirDeque Q1;

	while(1){
	printf("Circular Queue Implementation by Sequence(char type)\n");
    printf("===========================================\n");
    printf("1. initialize;    2.traverseDisp;\n");
	printf("3. insertFront;   4. insertRear;\n");
	printf("5. deleteFront;   6. deleteRear;\n");
	printf("7. getFront;      8. getRear;\n");
	printf("9. isEmpty;       a. isFull;\n");
	printf("b. maxWindow;     0. Exit;\n");
	printf("===========================================\n");
 
    scanf(" %c",&c);
	

	switch(c){
	  case '1':
		  InitQueue(&Q1);
		  break;
	  case '2':
		  QueueTraverse(&Q1);
		  break;
	  case '3':
		  printf("Input an element:\n");
		  scanf(" %d", &e);
		  if (insertFront(&Q1, e))
			  printf("insertFront successfully!\n");
		  else
			  printf("insertFront failure!\n");
		  break;
	  case '4':
		  printf("Input an element:\n");
		  scanf(" %d", &e);
		  if (insertRear(&Q1, e))
			  printf("insertRear successfully!\n");
		  else
			  printf("insertRear failure!\n");
		  break;
	  case '5':
		  if (deleteFront(&Q1))
			  printf("deleteFront successfully!\n");
		  else
			  printf("deleteFront failure!\n");
		  break;
	  case '6':
		  if (deleteRear(&Q1))
			  printf("deleteRear successfully!\n");
		  else
			  printf("deleteRear failure!\n");
		  break;
	  case '7':
		  if (!isEmpty(&Q1))
			  printf("Front is %d!\n", getFront(&Q1));
		  else
			  printf("Empty!\n");
		  break;
	  case '8':
		  if (!isEmpty(&Q1))
			  printf("Rear is %d!\n", getRear(&Q1));
		  else
			  printf("Empty!\n");
		  break;
		  
	  case '9':
		  if (isEmpty(&Q1))
			  printf("Empty!\n");
		  else
			  printf("Not Empty!\n");
		  break;		   
	  case 'a':
		  if (isFull(&Q1))
			  printf("Full!\n");
		  else
			  printf("Not Full!\n");
		  break;	
	  case 'b':
		  maxWindow = maxSlidingWindow(&Q1, nums, numsSize, k);
		  for (i = 0; i < numsSize - k + 1; i++){
			  printf("%d ", maxWindow[i]);
		  }
		  printf("\n");
		  break;
	  case '0':exit(0);
	  default:
		  printf("Print an incorrect letter;\n");
		  break;	
	}

	}
   
	system("PAUSE");
}

Status InitQueue(cirDeque *Q)
{
	Q->base = (QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
	if (!Q->base ) exit(OVERFLOW);
	Q->front = Q->rear = 0;

	return OK;
}

Status insertFront(cirDeque *Q, QElemType e)
{

	if ((Q->front - 1) % MAXQSIZE == Q->rear)
		return ERROR;
	Q->front = (Q->front-1) % MAXQSIZE;
	Q->base[Q->front] = e;

	return OK;
}

Status insertRear(cirDeque *Q, QElemType e)
{   if ((Q->rear - 1) % MAXQSIZE == Q->front)
		return ERROR;
		Q->base[Q->rear] = e;
Q->rear = (Q->rear+1) % MAXQSIZE;


               return  OK;
}


Status deleteFront(cirDeque *Q)
{
	if (Q->front == Q->rear)
		return ERROR;
	Q->front = (Q->front+1) % MAXQSIZE;
	return  OK;
}


Status deleteRear(cirDeque *Q){
    if (Q->front == Q->rear)
		return ERROR;
	Q->rear = (Q->rear-1) % MAXQSIZE;
	return  OK;
}

QElemType getFront(cirDeque *Q){
	if (isEmpty(Q)){
		printf("This is an empty queue!");
		return ERROR;
	}
	else
		return Q->base[Q->front];
}

QElemType getRear(cirDeque *Q){
	if (isEmpty(Q)){
		printf("This is an empty queue!");
		return ERROR;
	}
	else         //Q->rear前一个位置是最后一个元素
		return Q->base[Q->rear-1];
}


Status isEmpty(cirDeque *Q)
{
	if(Q->front == Q->rear)
		return TRUE;
	else return FALSE;
}

Status isFull(cirDeque *Q)
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
		return TRUE;
	else return FALSE;
}


Status QueueTraverse(cirDeque *Q)
{
	int p;
	p=Q->front;
	if (isEmpty(Q)){
	  printf("This is an empty queue!");
      return ERROR;	
	}
	while((p)%MAXQSIZE!=Q->rear){
		printf(" %d\t", Q->base[(p) % MAXQSIZE]);
	    	p++;	
	}
    printf("\n");
	return OK;
}

// 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
// 同时pop之前判断队列当前是否为空。
Status DeMonoQueue(cirDeque *Q, QElemType e){
	if (Q->front!=Q->rear&&e==Q->base[Q->front])
		deleteFront(Q);
		return OK;
}

// 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
// 这样就保持了队列里的数值是单调从大到小的了。
Status EnMonoQueue(cirDeque *Q, QElemType e){
	while (Q->front!=Q->rear&& e>Q->base[Q->rear-1] ){
        deleteRear(Q);
	}
	insertRear(Q, e);
	return OK;
}

// 查询当前队列里的最大值，如果窗口移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作直接返回队列前端也就是front就可以了。
QElemType maxMonoQueue(cirDeque *Q){
	return getFront(Q);
}

int * maxSlidingWindow(cirDeque *Q, int *nums, int numsSize, int k){
	int i;
	int *result;
	result = (int *)malloc(MAXQSIZE * sizeof(int));
	// 先将前k的元素放进队列	
	for (i = 0; i < k; i++) {
		EnMonoQueue(Q, nums[i]);
	}
	result[0] = maxMonoQueue(Q); // result 记录前k的元素的最大值

	for (i = k; i < numsSize; i++) {
		// 窗口开始向前滑动
		DeMonoQueue(Q,nums[i-k]); // 窗口后端
		EnMonoQueue(Q, nums[i]);// 窗口前端
		result[i-k+1] = maxMonoQueue(Q); // 记录对应的最大值，第几个结果
	}
	return result;
}

