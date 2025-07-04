/*--------------------------------------------------------------------
图用邻接表存储，实现图的拓扑排序，深度优先搜索与广度优先搜索。
包含图结构、链栈、顺序循环队列三种数据结构。
------------------------------------------------------2015年09月*/
#define _CRT_SECURE_NO_WARNINGS

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX_NUM 20//最大顶点数目
#define MAX_NUMA 40//最大弧数目

typedef enum {DG,DN,UDG,UDN} GraphKind;//图类型
typedef struct Acnode{
	int adjvex;//存放顶点在数组中的位置
	int value;//权值，这里定义为整型
	struct Acnode *next;
	char *info;//存放弧的信息
}Acnode;//弧的定义
typedef struct {
	char data;
	Acnode *firstarc;
}VertexNode;//顶点定义

typedef struct{
	VertexNode Vertex[MAX_NUM];
	int Vexnum,Arcnum;//当前顶点数目、弧数目
	GraphKind kind;//图的类型
}ALGraph;//图的定义

typedef int Status;
typedef int ElemType;
typedef int Bool;
Bool visited[MAX_NUM];  //全局数组,存放各顶点是否已被访问标志
int visted[MAX_NUM];//定义为全局变量，存放各顶点是否已被访问标志
//int VE[MAX_NUM], VL[MAX_NUM];//事件的最早发生时间,最迟发生时间
//int E[MAX_NUMA], L[MAX_NUMA];//活动的最早开始时间,最迟开始时间

/* 队列定义及相关操作，广度优先搜索用到此循环队列 */
typedef int Status;
typedef int QElemType;

typedef struct{
	QElemType *base;
	int front; //头指针，队非空时指向队头元素 
	int rear; //尾指针，队非空时指向队尾元素的下一位置 
} SqQueue;


Status InitQueue(SqQueue *Q)
{

	Q->base = (QElemType *)malloc(MAX_NUM*sizeof(QElemType));
	if (!Q->base) exit(OVERFLOW);
	Q->front = Q->rear = 0;

	return OK;
}

Status EnQueue(SqQueue *Q, QElemType e)
{

	if ((Q->rear + 1) % MAX_NUM == Q->front)
		return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAX_NUM;

	return OK;
}

QElemType DeQueue(SqQueue *Q)
{

	QElemType e;
	if (Q->front == Q->rear)
		return ERROR;
	e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAX_NUM;
	return  e;
}


Status QueueEmpty(SqQueue *Q)
{
	if (Q->front == Q->rear)
		return TRUE;
	else return FALSE;
}


/* 链栈定义及相关操作，拓扑排序用到栈的操作 */
typedef struct SNode{
	ElemType data;
	struct SNode *next;
}SNode, *Stack;

Stack CreatStack(Stack S)
{
    S = (Stack )malloc(sizeof(SNode));
	S->next = NULL;
	return S;
}
Status push(Stack S, ElemType e)
{
 SNode *TmpCell;
 TmpCell = (Stack)malloc(sizeof(SNode));
TmpCell->data=e;
 TmpCell->next = S->next;
  S->next = TmpCell;
return 1;
}
ElemType pop(Stack S)
{
	SNode *t;
	ElemType e;
	if(S->next==NULL){
		return 0;
	}
	t=S->next;
	S->next=S->next->next;
	e=t->data;
	free(t);
	return e;
}
Status IsEmpty(Stack S)
{
	if(S->next==NULL){
		return 1;
	}

	else 
		return 0;
}

void VistGraph(VertexNode V);
int FirstAdjvex(ALGraph G, int v);
int NextAdjvex(ALGraph G, int v, int w);
void DFS1(ALGraph G, int v);
void DFSTraverse1(ALGraph G);
void BFSTraverse(ALGraph *G);
void CreatGraph_DN(ALGraph *G);
void TopologicalSort1(ALGraph G);
//void DFS(ALGraph G, int v);
//int TopologicalSortPath(ALGraph G, Stack T);
//void CriticalPath(ALGraph G, Stack T);
void CountVerNum_DN(ALGraph *G, int D[]);


void main()
{
	int *p;
	int i=0;
	int D[MAX_NUM] = { 0 };

    ALGraph G;
  	char c;
	int e;
	Stack T;//用于关键路径计算
	T = (Stack)malloc(sizeof(SNode));
	T->next = NULL;

	while (1){
		printf("------------------------------------\n");
		printf("      图的邻接表实现相关算法\n");
		printf("====================================\n");
		printf("1. 创建一个图;     2. 深度优先搜索;\n");
		printf("3. 广度优先搜索;   4. 拓扑排序;\n");
		printf("5. 关键路径计算;   6. 顶点度计算;\n");
		printf("0. Exit;\n");
		printf("====================================\n");

		scanf(" %c", &c);

		switch (c){
		case '1':
			CreatGraph_DN(&G);
			printf("创建成功!");
			printf("\n");
			break;
		case '2':
			printf("\n图的深度优先搜索序列为: ");
			DFSTraverse1(G);
			printf("\n");
			break;
		case '3':
			printf("\n图的广度优先搜索序列为: ");
			BFSTraverse(&G);
			printf("\n");
			break;
		case '4':
			printf("\n图的拓扑排序序列为: ");
			TopologicalSort1(G);
			printf("\n");
			break;
		case '5':
			//printf("\n关键路径为： \n");
			//CriticalPath(G, T);
			//printf("\n");
			break;
		case '6':
			CountVerNum_DN(&G, D);
			for (i = 0; i<G.Vexnum; i++){
				printf("The degrees of %d Vex is %d\n", i, D[i]);
			}
			break;

		case '0':exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;
		}

	}
 	system("PAUSE");
}
/*
创建一个图，输入示例：请输入该有向网的顶点数目和弧的数目：7 8
请初始化这%d个顶点，空格或回车分隔：a b c d e f g
请初始化顶点之间的关系（%d条弧）：
a b 1
a c 3
b d 2
c d 4
d e 1
d f 3
e g 2
f g 4
*/
void CreatGraph_DN(ALGraph *G)
{
	

}

/*深度优先搜索*/
void VistGraph(VertexNode V)
{//访问顶点操作
	printf("%c ", V.data);
}
int FirstAdjvex(ALGraph G, int v)
{//得到图G中第v个顶点的第一个邻接顶点所在位置
	Acnode *p; 
	p = G.Vertex[v].firstarc;
	if (p == NULL)
		return -1;
	return p->adjvex;
}
int NextAdjvex(ALGraph G, int v, int w)
{//得到w顶点下一邻接点的位置
	Acnode *p; 
	p = G.Vertex[v].firstarc;
	while (p->adjvex != w&&p != NULL)
		p = p->next;
	p = p->next;
	if (p == NULL)
		return -1;
	return p->adjvex;
}
void DFS1(ALGraph G, int v)
{//深度优先搜索核心过程。参数v表示从图中第v个结点开始深度优先遍历
	int w;
	VertexNode V; 
	V = G.Vertex[v];
	visited[v] = 1; 
	VistGraph(V);//令该顶点所在标志为1表示已访问，然后访问该顶点
	for (w =____________; w >= 0; w = ____________)
	    if (!visited[w]) 
		    DFS1(______, _____);
}
void DFSTraverse1(ALGraph G)
{//深度优先搜索
	int i;
	for (i = 0; i<G.Vexnum; i++) visited[i] = 0;//首先初始化访问标志
	for (i = 0; i<G.Vexnum; i++)
	   if (!visited[i])
		  DFS1(______, _____);
}

/*广度优先搜索*/
void BFSTraverse(ALGraph *G){
	int i;
	SqQueue Q;
	int w;
	Acnode *p;

	for (i = 0; i<G->Vexnum; ++i){
		visited[i] = FALSE;
	}
	InitQueue(&Q);
	
	for (i = 0; i<G->Vexnum; ++i){
		if (!visited[i]){
			visited[i] = TRUE;
			VistGraph(G->Vertex[i]);
			EnQueue(&Q, i);

			while (!____________){ //队列非空
				i=____________;//出队
				p = G->Vertex[i].____________; //p指向G->Vertex[i]第一个弧
				while (p){
					if (!visited[p->adjvex]){
						visited[p->adjvex] = TRUE; 
							printf("%c ", G->Vertex[p->adjvex].data);
						EnQueue(&Q, ____________);//p的顶点编号入队
					}
					p = ____________;//指向下一个弧
				}
			}
		}
	}
}

/*AOV网拓扑排序，拓扑排序输出AOV网中所有顶点*/
void TopologicalSort1(ALGraph G)
{	

}




/*计算各结点的度
邻接表存储的有向网，当计算顶点的度时，出度为顶点链表中弧表结点的数目
入度则需遍历整个邻接表求得相应的顶点的入度，然后与出度相加得到个顶点的度
int D[MAX_NUM] = {0}, ID[MAX_NUM], OD[MAX_NUM]; int i;*/
void CountVerNum_DN(ALGraph *G, int D[])
{
	int ID[MAX_NUM], OD[MAX_NUM]; int i;
	Acnode *p;
	for (i = 0; i<G->Vexnum; i++)
	{
		D[i] = 0;
		ID[i] = 0;
		OD[i] = 0;
	}
	for (i = 0; i<G->Vexnum; i++)
	{
		p = G->Vertex[i].____________;
		if (p == NULL)
			OD[i] = 0;
		else
		while (____________)
		{
			OD[i]++;
			ID[____________]++;
			p = ____________;
		}
	}
	for (i = 0; i<G->Vexnum; i++)
		D[i] = ____________ + ____________;
}
