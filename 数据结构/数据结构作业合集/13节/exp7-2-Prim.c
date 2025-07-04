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
		scanf("%c",&G->data[i]); //输入顶点的信息
	}
	for(i = 0;i < G->NumVertex;++i)  //初始化图的权值为无限大
		for(j = 0;j < G->NumVertex;++j)
		G->Edge[i][j] = INFINITY;
	for(k = 0;k < G->NumEdge;++k)
	{
		int i,j,w;
		printf("请输入边的连接信息(vi,vj)和边的权值:\n");
		fflush(stdin);
		scanf("%d%d%d",&i,&j,&w);
		G->Edge[i][j] = w; //边的权值
		G->Edge[j][i] = G->Edge[i][j]; //无向图存在反向链接,边的权值相同
	}
}

	void MiniSpanTree_Prim(Graph *G)
{    
    int adjVex[MAXVEX],i,min,k,j; //存放顶点的下标值
    EdgeType lowcost[MAXVEX]; //存放最小的权值
    adjVex[0] = 0; //选取下标为0的一个顶点
    lowcost[0] = 0; //表示此顶点已经被处理过
    for(i = 1;i < G->NumVertex;++i)
        {lowcost[i]=G->Edge[0][i];
		adjVex[i] = 0;  
		//将与下标为零的顶点邻接的边权值存放在lowcost中
    }
    for(i = 1;i < G->NumVertex;++i) //选择其余G.vexnum-1
        //全部初始化为下标为零的顶点个顶点
        {  min = INFINITY; //初始化最小值为无穷大
            k = 0; //用于记录权值最小的顶点的下标值
			for(j = 1;j < G->NumVertex;++j) //求出下一个结点，用k记录下标如果顶点没有处理过而且权值小于最小值
		    {
			    if( lowcost[j]!=0 &&lowcost[j]<min) //
           { min = lowcost[j]; //把权值赋给min
              k = j; //记录当前最小权值的顶点的下标
}}
       lowcost[k] = 0; //标记下标k的顶点为已处理
       printf("(%d %d)\n",adjVex[k],k);
       for(j = 1;j < G->NumVertex;++j) //更新V- U中顶点连接U中顶点最小边权边, 只与新加入顶点k相关
           { if(lowcost[j]!=0 && G->Edge[k][j] < lowcost[j]) //如果顶点没有处理过且权值小于此前未被加入时的顶点权值
       {
            lowcost[j] = G->Edge[k][j]; //将较小的权值存入lowcost的相应位置，与k相关。
            adjVex[j] = k;//在adjVex数组中记录下顶点的下标
}
} 
}
}
int main()
{
	Graph G;
	CreateGraph(&G);
	MiniSpanTree_Prim(&G);
	return 0;
}








