/*exp7-1-UnDiGraph 邻接矩阵存储dfs bfs*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define INFINITY 32767
#define MAX_VEX 20
#define QUEUE_SIZE (MAX_VERTEX+1)
#define DataType char  /* vertext's info  */
int *visited; /* Node: visited flag with dynamic array, good idea ! */
/* init queue for bfs */
struct _node
{
    int v_num;
    struct _node *next;
};
typedef struct _node node, *pnode;
struct _queue
{
    pnode front;
    pnode rear;
};
typedef struct _queue queue, *pqueue;

struct _graph
{
    DataType *vexs;
    int arcs[MAX_VEX][MAX_VEX];
    int vexnum, arcnum;
};
typedef struct _graph graph, *pgraph;

/* operation of queue */
queue init_queue()
{
    queue qu;
    qu.front=qu.rear=(pnode)malloc(sizeof(node));
    if(qu.front == NULL)
        exit(1);
    qu.rear->next=NULL;
    return qu;
}
void en_queue(pqueue pqu, int v_num)
{
    pnode pn;
    pn=(pnode)malloc(sizeof(node));
    if(pqu->front == NULL)
        exit(1);
    pn->v_num=v_num;
    pn->next=NULL;
    pqu->rear->next=pn;
    pqu->rear=pqu->rear->next;
}
int isempty_queue(pqueue pqu)
{
    if(pqu->front == pqu->rear)
        return 1;
    else
        return 0;
}
int de_queue(pqueue pqu)
{
    pnode pn;
	int d;
    if(isempty_queue(pqu))
        return -1;
	pn=pqu->front;
    d=pn->v_num;
    pqu->front=pn->next;
	free(pn);
    return d;
}
int locate(graph g, DataType data)
{
    int i;
    for(i=0;i<g.vexnum;i++)
        if(g.vexs[i] == data)
            return i;
     return -1;
}
graph create_graph()
{
    int i,j,w, s1,s2;
    DataType ch1,ch2,tmp;
    graph g;
	printf("g sizeof: %d\n", sizeof(g));
    printf("Enter vexnum arcnum:");
    scanf("%d %d", &g.vexnum, &g.arcnum);
    tmp=getchar();
    g.vexs=(DataType *)malloc(g.vexnum*sizeof(DataType));
	if(g.vexs == NULL)
		exit(1);
    printf("Enter %d vertext,please.../n", g.vexnum);
    for(i=0;i<g.vexnum;i++) /* 输入顶点*/
    {
        printf("vex %d: ", i);
        scanf("%c", &g.vexs[i]);
        tmp=getchar();
        //visited[i]=0;
    }
    for(i=0;i<g.vexnum;i++)  /* 初始化边权*/
        for(j=0;j<g.vexnum;j++)
            g.arcs[i][j]=INFINITY;
     printf("Enter %d arcs:(e.g. a b 1)/n", g.arcnum);
     for(i=0;i<g.arcnum;i++)/* 输入边*/
     {
        printf("arc %d: ", i);
        scanf("%c %c %d", &ch1, &ch2, &w);
        tmp=getchar();
        s1=locate(g,ch1);
        s2=locate(g,ch2);
        g.arcs[s1][s2]=g.arcs[s2][s1]=w; /* 边赋权值*/
     }
	 return g;
}
int firstvex_graph(graph g, int k)//返回k的第1个邻接点
{
    int i;
    if(k>=0 && k<g.vexnum)
        for(i=0;i<g.vexnum;i++)
            if(g.arcs[k][i] != INFINITY)
                return i;
     return -1;
}
int nextvex_graph(graph g, int i, int j)//返回i的第j个邻接点的下一个邻接点
{
    int k;
    if(i>=0 && i<g.vexnum && j>=0 && j<g.vexnum)
        for(k=j+1;k<g.vexnum;k++)
            if(g.arcs[i][k]!=INFINITY)
                return k;
     return -1;
}
void dfs(graph g, int k)
{
    int i;
    if(k == -1)
    {
        for(i=0;i<g.vexnum;i++)
            if(!visited[i])
                dfs(g,i);
     }
     else
     {
        visited[k]=1;
        printf("%c ", g.vexs[k]);
        for(i=firstvex_graph(g,k);i>=0;i=nextvex_graph(g,k,i))
            if(!visited[i])
                dfs(g,i);
     }
}
void bfs(graph g)//you are needed to finish the function.
{
    int i,j,k;
    queue qu;
    qu=init_queue();
    for(i=0;i<g.vexnum;i++)
        if(!visited[i])
        {
            visited[i] =1;
            printf("%c ", g.vexs[i]);
            en_queue(&qu,i);//i入队
            while(!isempty_queue(&qu))//qu非空
            {
                k=de_queue(&qu);//出队
                for(j = firstvex_graph(g,k); j >= 0;j = nextvex_graph(g,k,j))
                    if(!visited[j])
                    {
                        visited[j]=1;
                        printf("%c ", g.vexs[j]);
                        en_queue(&qu,j);//j入队
                    }
            }
        }   
}


void main()
{
	int i;
    graph g;
    g=create_graph();
	visited=(int *)malloc(g.vexnum*sizeof(int));

	for(i=0;i<g.vexnum;i++)
		visited[i]=0;
    printf("\n\n dfs:");

    dfs(g,-1);
	for(i=0;i<g.vexnum;i++)
		visited[i]=0;
    printf("\n bfs:");
    bfs(g);
	
	if(visited)
		free(visited);
	printf("\n");

	system("PAUSE");
}
