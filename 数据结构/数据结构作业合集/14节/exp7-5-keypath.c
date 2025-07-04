/*邻接表存储表示，关键路径查找*/
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
#define _CRT_SECURE_NO_WARNINGS

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

typedef struct SNode{
	ElemType data;
	struct SNode *next;
}SNode, *Stack;

ALGraph G;
int visted[MAX_NUM];//定义为全局变量，存放各顶点是否已被访问标志
int VE[MAX_NUM], VL[MAX_NUM];//事件（顶点）的最早发生时间,最迟发生时间
int E[MAX_NUMA], L[MAX_NUMA];//活动的最早开始时间,最迟开始时间

/*栈的实现*/

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
	SNode *p;
	ElemType elem;

	if (S->next == NULL)
	{
	   return 0;
	}
	p = S->next;
	elem = p->data;
	S->next = p->next;
	free(p);
	return elem;
}

Status IsEmpty(Stack S)
{
	if(S->next==NULL){
		return 1;
	}

	else 
		return 0;
}

void CreatGraph_DN(ALGraph *G);
int TopologicalSortPath(ALGraph G, Stack T);
void CriticalPath(ALGraph G, Stack T);
void VistGraph(VertexNode V);
void DFS(ALGraph G, int v);
void CountVerNum_DN(ALGraph *G, int D[]);

void main()
{
	int *p;
	int i=0;
	int D[MAX_NUM] = { 0 };
 	
	Stack T;
	T = (Stack)malloc(sizeof(SNode));
	T->next = NULL;


    CreatGraph_DN(&G);
	printf("\n");
	printf("关键路径序列为: \n");
	CriticalPath(G, T);

	CountVerNum_DN(&G, D);
	for (i = 0; i<G.Vexnum; i++){
       printf("The degrees of %d Vex is %d\n", i, D[i]);
	}

 	system("PAUSE");
}
/*
创建一个图，输入示例：请输入该有向网的顶点数目和弧的数目：7 8
请初始化这%d个顶点，空格或回车分隔：a b c d e f g
*/
void CreatGraph_DN(ALGraph *G)
{
	Acnode *p, *q;
	int i, j, sign1,sign2,Value=0;
	VertexNode v1, v2;//弧头弧尾
	G->kind = DN;
	printf("请输入该有向网的顶点数目和弧的数目：");
	scanf("%d%d", &G->Vexnum, &G->Arcnum);
	printf("请初始化%d个顶点，空格或回车分隔：", G->Vexnum);
	for (i = 0; i < G->Vexnum; i++) {
		scanf(" %c", &G->Vertex[i].data);
		G->Vertex[i].firstarc = NULL;
	}  //头结点第一个邻接点赋空
	printf("请初始化顶点之间的关系（%d条弧）：\n", G->Arcnum);
	printf("形式：顶点1 顶点2 权值（表示顶点1邻接到顶点2），如a b 1,回车下一条弧\n");
	fflush(stdin);
	for (i = 0; i < G->Arcnum; i++) { //插入每个弧
		sign1 = -1; sign2 = -1;
		fflush(stdin);
		scanf("%c %c %d",&v1.data,&v2.data,&Value);
		for (j = 0; j < G->Vexnum; j++) {//定位输入顶点在顶点数组中的位置
			if (G->Vertex[j].data == v1.data)	sign1 = j;
			if (G->Vertex[j].data == v2.data)	sign2 = j;
		}
		if (sign1 == -1 || sign2 == -1)   printf("信息输入有误！\n");
		else {
			p = (Acnode*)malloc(sizeof(Acnode));  //申请空间
			p->next = NULL;
			
			p->adjvex = sign2;
			p->value = Value;//构造弧表结点
			q = G->Vertex[sign1].firstarc;
			if (q == NULL)//链入弧表结点至顶点链表中
				G->Vertex[sign1].firstarc = p;
			else {
				while (q->next != NULL) //找到最后一个结点
					q = q->next;
				q->next = p;
			}
		}
	}
}

/*拓扑排序、求得各顶点的最早发生时间，并把逆拓扑排序顺序的顶点存入栈T中*/
int TopologicalSortPath(ALGraph G, Stack T)
{
	int indegree[MAX_NUM], count = 0, k, i;
	Acnode *p;
	Acnode e,e1;
	Stack s;
	
	s = (Stack)malloc(sizeof(SNode));
	s->next = NULL;
    
	//初始化顶点入度信息
	for (i = 0; i<G.Vexnum; i++)
		indegree[i]=0;
	
	//遍历邻接表求得图中每个顶点的入度
	for (i = 0; i<G.Vexnum; i++)
	{
		p = G.Vertex[i].firstarc;
		while (p)
		{
			indegree[p->adjvex]++;
			p=p->next;
		}
	}
   
	//找到indegree数组中入度为0的顶点然后入栈
	for (i = 0; i<G.Vexnum; i++)
	   	if (!indegree[i]){
		   e.adjvex = i;
		   push(s,e.adjvex);
	   	}
	for(i=0; i<20; i++)
		VE[i] = 0;//初始化最早发生时间}
		
		
	while (!IsEmpty(s))
	{
		e.adjvex=pop(s);
		push(T, e.adjvex);
		count++;//对输出的顶点计数
		
		//拓扑排序求得每个顶点的最早发生时间
		for (p = G.Vertex[e.adjvex].firstarc ; p != NULL; p = p->next )
		{
			k =p->adjvex;
			e1.value=p->value;
			indegree[k]--;
			if (!indegree[k]){
				e1.adjvex = k;
				push(s,e1.adjvex);
			}
			if ((VE[e.adjvex] + e1.value) > VE[k]) { //计算顶点最早发生时间
				VE[k] = (VE[e.adjvex] + e1.value);
			}
		}
	}
	return count;
}

/*关键路径的求取*/
void CriticalPath(ALGraph G, Stack T)
{

	int i, j, min;
	Acnode e;
	Acnode *p;

	if (TopologicalSortPath(G, T) < G.Vexnum)
		printf("图G中存在环，无法求取关键路径！\n");
	else
	{
		for (i = 0; i < G.Vexnum; i++)
		{  
			VL[i] = VE[i];//初始化每个顶点的最迟发生时间 
		}
	 printf("\n");
		while (!IsEmpty(T))
		{
			e.adjvex = pop(T);//出栈T
			if (G.Vertex[e.adjvex].firstarc != NULL)
			{
				p = G.Vertex[e.adjvex].firstarc;
				e.value=p->value;
				min = VL[p->adjvex]-e.value;
				for (p = G.Vertex[e.adjvex].firstarc;p!=NULL;p=p->next)
				{
					e.value=p->value;
					if (min>(VL[p->adjvex] -e.value))
						min = (VL[p->adjvex] -e.value);
				}
				VL[e.adjvex] = min;//求得各顶点的最迟发生时间
				//最迟发生时间为该顶点邻接点的最迟发生时间减去该顶点到其邻接点的活动所用时间的最小值
			}
		}
		VL[0]=0;
		
		for(j=0; j<G.Vexnum;j++)
		{
			visted[j]=0;
		}
		j=0;
		if (visted[j] == 0)
		   DFS(G, j);
		printf("关键路径上的顶点为：");
		for (j = 0; j < G.Vexnum; j++)
			if (visted[j] ==1)
			   printf("%c ",G.Vertex[j].data);
	//DFS经过改进输出图G中的关键路径上的顶点.若E[i]==L[i]则i是关键路径上的顶点,深度优先遍历次序
		printf("\n");
	}
}
//访问顶点操作
void VistGraph(VertexNode V)
{
	printf("%c ", V.data);
}
//深度优先搜索核心过程。参数v表示从图中第v个结点开始深度优先遍历，计算每个活动是最早、最晚发生时间。
void DFS(ALGraph G, int v)
{
	Acnode *p;
	static j=0;
	int w;
	VertexNode V, V1;
	V = G.Vertex[v];
	visted[v] =1;
	for (p = G.Vertex[v].firstarc; p != NULL; p=p->next)
	{
        w = p->adjvex;
		E[j] =VE[v];
		L[j] = VL[p->adjvex] - p->value;
		if (E[j] == L[j]) {//关键路径条件
			VistGraph(V);
			V1 = G.Vertex[w];
			VistGraph(V1);
			printf(",");
			j++;
			if (!visted[w])
				DFS(G, w);
		}

	}
}

/*计算各结点的度
邻接表存储的有向网，当计算顶点的度时，出度为顶点链表中弧表结点的数目
入度则需遍历整个邻接表求得相应的顶点的入度，然后与出度相加得到个顶点的度
int D[MAX_NUM] = {0}, ID[MAX_NUM], OD[MAX_NUM]; int i;*/
void CountVerNum_DN(ALGraph *G, int D[])
{
	int ID[MAX_NUM], OD[MAX_NUM]; int i;
	Acnode* p;
	for (i = 0; i < G->Vexnum; i++)
	{
		D[i] = 0;
		ID[i] = 0;
		OD[i] = 0;
	}
	for (i = 0; i < G->Vexnum; i++)
	{
		p = G->Vertex[i].firstarc;
		if (p == NULL)
			OD[i] = 0;
		else
			while (p!=NULL)
			{
				OD[i]++;
				ID[p->adjvex]++;
				p = p->next;
			}
	}
	for (i = 0; i < G->Vexnum; i++)
		D[i] = OD[i] + ID[i];
}
