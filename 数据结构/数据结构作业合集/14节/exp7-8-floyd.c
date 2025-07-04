/*Floyd求最短路径*/
#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXVEX 20
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define INFINITY 65535

#include<stdlib.h>
#include <stdio.h>

typedef int Status;
typedef int SElemType;
typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack, *PSqStack;

Status InitStack(PSqStack S)
{
	S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S) exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(PSqStack S, SElemType e)
{
	if (S->top - S->base >= S->stacksize) {
		S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S->base) exit(OVERFLOW);
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return OK;
}

SElemType Pop(PSqStack S)
{
	if (S->top == S->base) return ERROR;
	return *--S->top;
}

Status StackEmpty(PSqStack S)
{
	if (S->top == S->base)
		return TRUE;
	else return FALSE;
}


typedef char VertexType; //顶点数据类型
typedef int EdgeType; //边表的权值类型
typedef struct graph {
	VertexType data[MAXVEX]; //图的顶点
	EdgeType Edge[MAXVEX][MAXVEX]; //图的边表
	int NumVertex, NumEdge; //图的顶点数与边数
}Graph;

void CreateGraph(Graph *G);
int locate(Graph *G, VertexType data);
void Floyd(Graph g, int **path, int **length);
int showPath(Graph *g, int **path, int v0, int v);

int main()
{

	int i, j;
	Graph g;
	int v0;
	int **path;//二维数组存储路径
	int **length;//二维数组存储最短路径长度

	CreateGraph(&g);

	path = (int **)malloc(sizeof(int)*g.NumVertex);
	for (i = 0; i < g.NumVertex; i++) {
		path[i] = (int *)malloc(sizeof(int)*g.NumVertex);
	}
	length = (int **)malloc(sizeof(int)*g.NumVertex);
	for (i = 0; i < g.NumVertex; i++) {
		length[i] = (int *)malloc(sizeof(int)*g.NumVertex);
	}

	Floyd(g, path, length);

	for (i = 0; i < g.NumVertex; i++)
	{
		for (j = 0; j < g.NumVertex; j++) {
			printf("%c到%c的距离：%d\n", g.data[i], g.data[j], length[i][j]);
			if (i != j)
			{
				showPath(&g, path, i, j);
			}
		}
		printf("\n");
	}
	system("PAUSE");
	return 0;
}

void CreateGraph(Graph *G) //创建图
{
	int i, j, k, w;
	char ch1, ch2, tmp;
	int s1;
	int s2;
	printf("请输入图的顶点数和边数:\n");
	scanf("%d%d", &G->NumVertex, &G->NumEdge);
	printf("请输入图的顶点信息,顶点为单个字符:\n");
	for (i = 0; i < G->NumVertex; ++i)
	{
		fflush(stdin); //清空输入缓冲区，为了确保不影响后面的数据读取
		scanf(" %c", &G->data[i]); //输入顶点的信息
	}
	for (i = 0; i < G->NumVertex; ++i)  //初始化图的权值为无限大
		for (j = 0; j < G->NumEdge; ++j) {
			if (i == j) {
				G->Edge[i][j] = 0;
			}
			else  G->Edge[i][j] = INFINITY;
		}

	printf("请输入弧的连接信息<vi,vj>和弧的权值，矩阵下标及权值，如a b 1:\n");
	fflush(stdin);
	for (i = 0; i < G->NumEdge; i++)
	{
		printf("弧 %d: ", i);
		scanf(" %c %c %d", &ch1, &ch2, &w);
		tmp = getchar();
		s1 = locate(G, ch1);
		s2 = locate(G, ch2);
		G->Edge[s1][s2] = w; /* 有向边权重 */
	}
}

int locate(Graph *G, VertexType data)
{
	int i;
	for (i = 0; i < G->NumVertex; i++)
		if (G->data[i] == data)
			return i;
	return -1;
}

//打印最短路径上的各个顶点
int showPath(Graph *g, int **path, int v0, int v)
{
	SqStack s;
	InitStack(&s);

	while (v != v0)
	{
		if (path[v0][v] == -1) {//不可达
			return 0;
		}
		else {
			Push(&s,v);
			v =path[v0][v];
		}
	}
	Push(&s, v);
	while (!StackEmpty(&s))
	{
		printf("%c,", g->data[Pop(&s)]);
	}
	return 1;
}

void Floyd(Graph g, int **path, int **length)
{
	int i, j, k, n = g.NumVertex;
	for (i = 0; i < n; i++) { //初始化两两顶点的距离
		for (j = 0; j < n; j++)
		{
			length[i][j] = g.Edge[i][j];
			if (length[i][j] <INFINITY) { //两顶点的相连
				path[i][j] =i;
			}
			else
				path[i][j] = -1;  //两顶点的不相连
		}
	}
	for (k = 0; k < n; k++)  //分别加入每个顶点k检查最短径变化
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (length[i][j] > (length[i][k]+length[k][j]))
				{
					length[i][j] = length[i][k] + length[k][j];
					path[i][j] = k;
				}
	}
}
