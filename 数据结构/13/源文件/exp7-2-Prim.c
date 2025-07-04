/*exp7-2-Prim 邻接矩阵*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


#define GRAPH_H
#define MAXVEX 12
#define INFINITY 65535
typedef char VertexType; //顶点数据类型
typedef int EdgeType; //边表的权值类型
typedef struct graph{
	VertexType data[MAXVEX]; //图的顶点
	EdgeType Edge[MAXVEX][MAXVEX]; //图的边表
	int NumVertex,NumEdge; //图的顶点数与边数
}Graph;


void CreateGraph(Graph *G); //创建图
void MiniSpanTree_Prim(Graph *G); //最小生成树普利姆算法


void CreateGraph(Graph *G) //创建图
{
	int i,j,k;
	
	printf("请输入图的顶点数和边数:\n");
	scanf("%d%d",&G->NumVertex,&G->NumEdge);
	printf("请输入图的顶点信息:\n");
	for(i = 0;i < G->NumVertex;++i)
	{
		fflush(stdin); //清空输入缓冲区，为了确保不影响后面的数据读取
		scanf("%c",________________); //输入顶点的信息
	}
	for(i = 0;i < G->NumVertex;++i)  //初始化图的权值为无限大
		for(j = 0;j < G->NumVertex;++j)
			________________ = INFINITY;
	for(k = 0;k < G->NumEdge;++k)
	{
		int i,j,w;
		printf("请输入边的连接信息(vi,vj)和边的权值:\n");
		fflush(stdin);
		scanf("%d%d%d",&i,&j,&w);
		________________ = w; //边的权值
		________________ = ________________; //无向图存在反向链接,边的权值相同
	}
}
void MiniSpanTree_Prim(Graph *G)
{




}


int main()
{
	Graph G;
	CreateGraph(&G);
	MiniSpanTree_Prim(&G);
	return 0;
}