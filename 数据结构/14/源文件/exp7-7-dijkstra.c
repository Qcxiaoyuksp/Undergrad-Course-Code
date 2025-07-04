/*exp7-7-dijkstra求单源最短路径*/
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

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack, *PSqStack;

Status InitStack(PSqStack S)
{
	S->base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S) exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(PSqStack S, SElemType e)
{
	if (S->top - S->base >= S->stacksize){
		S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT)*sizeof(SElemType));
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
typedef struct graph{
	VertexType data[MAXVEX]; //图的顶点
	EdgeType Edge[MAXVEX][MAXVEX]; //图的边表
	int NumVertex, NumEdge; //图的顶点数与边数
}Graph;

void CreateGraph(Graph *G);
int locate(Graph *G, VertexType data);
void DijkstraPath(Graph G, int *dist, int *pre, int v0);
int showPath(Graph *G, int *pre, int v0, int v);

int main()
{
	int i, j;
	Graph g;
	int v0;
	int *dist ;
	int *pre ;
		
	CreateGraph(&g);

	dist = (int *)malloc(sizeof(int)*g.NumVertex);
	pre = (int *)malloc(sizeof(int)*g.NumEdge);

	printf("输入源顶点\n");
	fflush(stdin);
	scanf("%d", &v0);
	DijkstraPath(g, dist, pre, v0);
	for (i = 0; i<g.NumVertex; i++)
	{
		if (i != v0)
		{
			if (!showPath(&g, pre, v0, i)){
				printf("%c到%c不可达\n", g.data[v0], g.data[i]);
			}else
				printf("%c到%c的距离：%d\n", g.data[v0], g.data[i], dist[i]);
		}
	}
	system("PAUSE");
	return 0;
}

void CreateGraph(Graph *G) //创建图
{
	int i, j, k, w;
	char ch1,ch2,tmp;
	int s1;
	int s2;
	printf("请输入图的顶点数和边数:\n");
	scanf("%d%d", &G->NumVertex, &G->NumEdge);
	printf("请输入图的顶点信息,顶点为单个字符，回车分隔:\n");
	for (i = 0; i < G->NumVertex; ++i)
	{
		fflush(stdin); //清空输入缓冲区，为了确保不影响后面的数据读取
		scanf("%c", &G->data[i]); //输入顶点的信息
	}
	for (i = 0; i < G->NumVertex; ++i)  //初始化图的权值为无限大
	for (j = 0; j < G->NumEdge; ++j){
		if (i == j){
			G->Edge[i][j] = 0;
		}
		else  G->Edge[i][j] = INFINITY;
	}

	printf("请输入弧的连接信息<vi,vj>和弧的权值，矩阵下标及权值，如a b 1:\n");
	fflush(stdin);
	for (i = 0; i<G->NumEdge; i++)
	{
		printf("弧 %d: ", i);
		scanf("%c %c %d", &ch1, &ch2, &w);
		tmp = getchar();
		s1 = locate(G, ch1);
		s2 = locate(G, ch2);
		G->Edge[s1][s2] = w; /* 有向边权重 */
	}
}

int locate(Graph *G, VertexType data)
{
	int i;
	for (i = 0; i<G->NumVertex; i++)
	if (G->data[i] == data)
		  return i;
	return -1;
}

 //v0表示源顶点，dist存放最短路径长度，pre存放路径
void DijkstraPath(Graph G, int *dist, int *pre, int v0)  
{
	int i, j, k;
	int min;
	int u;
	int *visited;
	visited = (int *)malloc(sizeof(int)*G.NumVertex);

	for (i = 0; i<G.NumVertex; i++)  //初始化v0顶点到其它各顶点的距离
	{
		if (G.Edge[v0][i] != INFINITY && i != v0) //若i与v0直接相邻
		{
			dist[i] = ____________;
			pre[i] = ____________;     //pre记录最短路径上从v0到i的前一个顶点
		}
		else
		{
			dist[i] = ____________;    //若i不与v0直接相邻，则权值置为无穷大
			pre[i] = -1;
		}
		visited[i] = FALSE;
		pre[v0] = v0;
		dist[v0] = 0;
	}
	visited[v0] = TRUE;
	for (i = 1; i<G.NumVertex; i++) //循环扩展n-1次
	{
		min = INFINITY;
		for (j = 0; j<G.NumVertex; j++) //寻找未被扩展的权值最小的顶点
		{
			if (visited[j] == FALSE && dist[j]<min)
			{
				min = ____________;
				u = ____________; //用u记录选择的顶点下标
			}
		}
		visited[u] = TRUE;    //加入已经访问过的集合，被访问过的集合里的点的距离都是到源点距离最近的
		for (k = 0; k<G.NumVertex; k++)   //更新dist数组的值和路径的值
		{
			//当访问过集合变化的时候，检查这个集合中新顶点相邻点到源点的距离是否缩短
			if (visited[k] == FALSE && G.Edge[u][k]>0 && (__________ + ___________)<dist[k])
			{				dist[k] = ____________ + ___________;//路径有更新就记录一下这一步加入访问集合的顶点
				pre[k] = ___________;
			}
		}
	}
}

//打印最短路径上的各个顶点,将pre数组中的路径存入栈，逆序输出
int showPath(Graph *G, int *pre, int v0, int v)  
{
	SqStack s;
	InitStack(&s);

	while (v != v0)
	{
		if (pre[v] == -1){  //不可达
			return 0;
		}
		else
		{
			Push(&s, ________);
			v = ____________;
		}
	}
	Push(&s, v);
	while (!StackEmpty(&s))
	{
		printf("%c,", G->data[____________]);
	}
}
