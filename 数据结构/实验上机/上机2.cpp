/*
数据结构上机2  2023-6-15  计算机2101张清晨 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define OK          1
#define ERROR       0
#define TRUE        1
#define FALSE       0
#define OVERFLOW    -1

#define STACK_INIT_SIZE     100  //栈初始开辟长度
#define STACKINCREMENT      10  //栈空间满时的增量

#define INFINITY 32767
#define MAXVEX 60
int visited[MAXVEX]; /* Node: visited flag with dynamic array, good idea ! */

typedef int Status;
typedef char ElemType;  // 二叉树结点元素类型
typedef int QElemType;
typedef int VertexType; //顶点数据类型
typedef int EdgeType; //边表的权值类型


typedef struct BiTNode{ // 二叉树结点结构
	char data;            // 结点数据
	struct BiTNode *lchild;        // 左孩子
	struct BiTNode *rchild;        // 右孩子
}BiTNode,*BiTree;
typedef BiTree SElemType;

typedef struct{//栈结构定义
	SElemType *base;  //栈底指针 
	SElemType *top;  //栈顶指针 
	int stacksize;
}SqStack;


typedef struct QNode{
   QElemType data;
   struct QNode *next;
 }QNode, *QueuePtr;
 
typedef struct{
   QueuePtr front;
   QueuePtr rear;
} LinkQueue;

typedef struct graph{
	VertexType data[MAXVEX]; //图的顶点
	EdgeType Edge[MAXVEX][MAXVEX]; //图的边表
	int NumVertex,NumEdge; //图的顶点数与边数
}Graph;

Status InitStack(SqStack *S);
//构造一个空栈S
Status DestroyStack(SqStack *S);
//销毁栈S，S不再存在
Status ClearStack(SqStack *S);
//把栈S置为空栈
Status StackEmpty(SqStack S);
//若栈S为空栈，则返回TRUE，否则返回FALSE
int StackLength(SqStack S);
//返回S元素的个数，即栈的长度
Status GetTop(SqStack S,SElemType *e);
//若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
Status Push(SqStack *S,SElemType e);
//插入元素e为新的栈顶元素
Status Pop(SqStack *S,SElemType *e);
//若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
Status StackTraverse(const SqStack *S);
//从栈底到栈顶依次对每个元素进行访问
void tree(); 
BiTree CreateBiTree(BiTree T);
// 按先后次序输入二叉树中结点的值（一个字符），空格表示空树
// 构造二叉链表表示的二叉树T
Status PreOrderRecursionTraverse(BiTree T);
// 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
// 先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
Status InOrderRecursionTraverse(BiTree T);
// 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
// 中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
Status PostOrderRecursionTraverse(BiTree T);
// 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
// 后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
Status PreOrderNonRecursionTraverse(BiTree T);
// 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
// 先序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
Status InOrderNonRecursionTraverse(BiTree T);
// 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
// 中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
Status PostOrderNonRecursionTraverse(BiTree T);
// 采用二叉链表存储结结构，Visit是对数据元素操作的应用函数
// 后序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
Status Visit(ElemType e);
// 对二叉树中的数据元素访问


void DFS_BFS();  //图的两种遍历 
void CreateGraph(Graph *G);  //创建图
int Firstvex_Graph(Graph G, int k);  //返回k的第1个邻接点
int Nextvex_Graph(Graph G, int i, int j);  //返回i的第j个邻接点的下一个邻接点
void DFS(Graph G, int k);  //DFS遍历 
void BFS(Graph G);  //BFS遍历 
Status InitQueue(LinkQueue *Q);//Initialize an empty list
Status QueueEmpty(LinkQueue *Q);
Status EnQueue(LinkQueue *Q, QElemType e);
QElemType DeQueue(LinkQueue *Q);

int main()
{
	char c;

	while(1){  //主菜单 
		printf("请选择以下三种操作之一：\n");
		printf("a.二叉树的遍历\n");
		printf("b.图的遍历\n");
		printf("c.离开\n");
		
		scanf(" %c",&c);
		
		switch(c)
		{
			case 'a':
				tree();  //二叉树的遍历 
				break;
			case 'b':
				DFS_BFS();  //图的遍历 
				break;
			case 'c':
				exit(0);
			default:
		   		printf("Print an incorrect letter;\n");
		   		break;
				 
		}
		system("PAUSE");
		return 0;
		
	}
}

//二叉树的遍历
void tree()
{
	BiTree T=NULL;
	char c;
	
	while(1){
		printf("二叉树的遍历\n");
		printf("===============================================\n");
		printf("1. 建立二叉树;    2. 先序遍历;\n");
		printf("3. 中序遍历;      4. 后序遍历;    0.离开程序；\n");
		printf("===============================================\n");
		
		scanf(" %c",&c); 
	//	getchar();
		
		switch(c){
			case '1':
				printf("请按先序遍历输入二叉树元素（每个结点一个字符，空结点为'#'，如ABC##DE#G##F###）:\n");//如ABC##DE#G##F###
				T=CreateBiTree(T);
				if(T) printf("创建成功！\n\n");
				else printf("创建失败！\n\n");
				break;
			case '2':
				printf("递归先序遍历：");
				PreOrderRecursionTraverse(T);
				printf("\n非递归先序遍历：");
				PreOrderNonRecursionTraverse(T);
				printf("\n\n");
				break;
			case '3':
				printf("递归中序遍历：");
				InOrderRecursionTraverse(T);
				printf("\n非递归中序遍历：");
				InOrderNonRecursionTraverse(T);
				printf("\n\n");
				break;
			case '4':
				printf("递归后序遍历：");
				PostOrderRecursionTraverse(T);
				printf("\n非递归后序遍历：");
				PostOrderNonRecursionTraverse(T);
				printf("\n\n");
				break;
			case '0':
				exit(0);
			default:
		   		printf("Print an incorrect letter;\n");
		   		break;
		}
		
		
	}	
	system("PAUSE");
 } 

// 按先后次序输入二叉树中结点的值（一个字符），空格表示空树
// 构造二叉链表表示的二叉树T
BiTree CreateBiTree(BiTree T)
{
	char ch;
	scanf(" %c",&ch);
	if(ch=='#') T=NULL;
	else{
		if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data=ch;                 // 生成根节点
		T->lchild=CreateBiTree(T->lchild);    // 构造左子树
		T->rchild=CreateBiTree(T->rchild);    // 构造右子树
	}
	return T;
}

// 先序遍历递归算法
Status PreOrderRecursionTraverse(BiTree T)
{   

	if(T){
		if(!Visit(T->data)) return ERROR;
		PreOrderRecursionTraverse(T->lchild);
		PreOrderRecursionTraverse(T->rchild);
	}
	return OK;
}

// 中序遍历递归算法
Status InOrderRecursionTraverse(BiTree T)
{   
	if(T){
		InOrderRecursionTraverse(T->lchild);
		if(!Visit(T->data)) return ERROR;;
		InOrderRecursionTraverse(T->rchild);
	}
	return OK;
}

//后序遍历递归算法
Status PostOrderRecursionTraverse(BiTree T)
{   
	if(T){
		PostOrderRecursionTraverse(T->lchild);
		PostOrderRecursionTraverse(T->rchild);
		if(!Visit(T->data)) return ERROR;;
	}
	return OK;
}

// 先序遍历二叉树T的非递归算法
Status PreOrderNonRecursionTraverse(BiTree T)
{
	SqStack S;
 	SElemType p;
 	InitStack(&S);
 	Push(&S, T);
 	while (!StackEmpty(S))
 	{
 		Pop(&S, &p);
  		if (!Visit(p->data)) return ERROR;
  		if (p->rchild) Push(&S, p->rchild);
  		if (p->lchild) Push(&S, p->lchild);
 	}
	return OK;
}

// 中序遍历二叉树T的非递归算法
Status InOrderNonRecursionTraverse(BiTree T)
{
	SqStack S;
 	SElemType p;
 	InitStack(&S);
 	p = T;
 	while (p || !StackEmpty(S))
 	{
  		if (p)
  		{
   			Push(&S, p);
   			p = p->lchild;
  		}
  		else
  		{
   			Pop(&S, &p);
   			Visit(p->data);
   			p = p->rchild;
  		}
 	}
	return OK;

}

// 后序遍历二叉树T的非递归算法
Status PostOrderNonRecursionTraverse(BiTree T)
{
	SqStack S;
	SElemType p,q;
	InitStack(&S);      Push(&S,T); // 根指针入栈
	while(!StackEmpty(S)){
		while(GetTop(S, &p) && p && (p -> lchild || p -> rchild)){
			Push(&S, p -> rchild);
			Push(&S, p -> lchild);
		} 
		if (!StackEmpty(S)){
			Pop(&S, &p);
			if (p){
				if (!Visit(p -> data)) return ERROR;
			}
			else{
				Pop(&S, &p);
				if (!Visit(p -> data)) return ERROR;
			}
			while (GetTop(S, &q) && q && p == q -> rchild){
				Pop(&S, &p);
				if (!Visit(p -> data)) return ERROR;
				GetTop(S, &q);
			}
		}
	}//while
	DestroyStack(&S);
	return OK;

}

// 对二叉树中的数据元素访问
Status Visit(ElemType e)
{
	if(e=='\0'){
		return ERROR;
	}else{
		printf("%c",e);
	}
	return OK;
}

//-----------顺序栈操作-------------

Status InitStack(SqStack *S){
	//构造一个空栈S
	S->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S->base)//分配失败
	{
		printf("分配内存失败.\n");
		exit(0);
	}
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack(SqStack *S){
	//销毁栈S，S不再存在
	if(!S)//S为空
	{
		printf("指针为空，释放失败.\n");
		exit(0);
	}
	free(S->base);
	return OK;
}

Status ClearStack(SqStack *S){
	//把栈S置为空栈
	if(!S)//S不存在
		return FALSE;
	S->top=S->base;//直接将栈顶指针指向栈底
	return OK;
}

Status StackEmpty(SqStack S){
	//若栈S为空栈，则返回TRUE，否则返回FALSE
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;
}

int StackLength(SqStack S){
	//返回S元素的个数，即栈的长度
	return S.stacksize;
}

Status GetTop(SqStack S,SElemType *e){
	//若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
	if(S.top==S.base){
		return FALSE;
	}else{
		*e=*(S.top-1);
		return OK;
	}
}

Status Push(SqStack *S,SElemType e){
	//插入元素e为新的栈顶元素
	if(S->top-S->base>=S->stacksize){//栈已满，追加存储空间
		S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S->base)
		{
			printf("重新申请空间失败.\n");
			exit(0);
		}
		S->top=S->base+S->stacksize;//更改栈顶指针
		S->stacksize+=STACKINCREMENT;
	}
	*S->top++=e;
	return OK;
}


Status Pop(SqStack *S,SElemType *e){
	//若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
	if(S->top==S->base){//栈为空
		return ERROR;
	}
	*e=*(--S->top);
	return OK;
}


//-----------遍历图操作-------------
void DFS_BFS(){
	Graph G;   //visited = (int *)malloc(G.NumVertex * sizeof(int));
	char c;    
	
	while(1){
		printf("图的遍历\n");
		printf("=================================================\n");
		printf("1. 建立图；              2. DFS深度优先遍历图；\n");
		printf("3. BFS广度优先遍历图；   0. 离开程序；\n");
		printf("=================================================\n");
		
		scanf(" %c",&c);//fflush(stdin);
		
		if (c == '1'){
				CreateGraph(&G);     
				printf("建图完成！\n"); 
		}
		else if (c == '2'){
				for(int i = 0; i < G.NumVertex; i++) visited[i] = 0;
				printf("Dfs:");     
				DFS(G, -1);
		}
		else if (c == '3'){
				for(int i = 0; i < G.NumVertex; i++) visited[i] = 0;
				printf("Bfs:");      
				BFS(G);
		}
		else if (c == '0') 
			return;
		else 
			printf("Print an incorrect letter;\n");
		printf("\n\n");
	}
}

//创建图
void CreateGraph(Graph *G) 
{
	int i,j,k;
	
	printf("请输入图的顶点数和边数:\n");
	scanf("%d %d", &G -> NumVertex, &G -> NumEdge);
	printf("请输入图的顶点信息:\n");
	for(i = 0;i < G->NumVertex; ++i)
	{
		//fflush(stdin); //清空输入缓冲区，为了确保不影响后面的数据读取
		scanf("%d", &G -> data[i]); //输入顶点的信息
	}
	for(i = 0;i < G->NumVertex; ++i)  //初始化图的权值为无限大
		for(j = 0;j < G->NumVertex; ++j)
			G -> Edge[i][j] = INFINITY;
	for(k = 0;k < G->NumEdge;++k)
	{
		int i, j, w;
		printf("请输入边的连接信息(vi,vj)和边的权值:\n");
		//fflush(stdin);
		scanf("%d%d%d", &i, &j, &w);
		G -> Edge[i-1][j-1] = w; //边的权值
		G -> Edge[j-1][i-1]= G -> Edge[i-1][j-1]; //无向图存在反向链接,边的权值相同
	}
}

//返回k的第1个邻接点
int Firstvex_Graph(Graph G, int k)
{
    int i;
    if(k >= 0 && k < G.NumVertex)
        for(i = 0;i < G.NumVertex; i++)
            if(G.Edge[k][i] != INFINITY)
                return i;
     return -1;
}

//返回i的第j个邻接点的下一个邻接点
int Nextvex_Graph(Graph G, int i, int j)
{
    int k;
    if(i >= 0 && i < G.NumVertex && j >= 0 && j < G.NumVertex)
	    for (k = j + 1;k < G.NumVertex; k++){
	    	if (G.Edge[i][k] != INFINITY)
	    		return k;
		}
     return -1;
}

//DFS遍历 
void DFS(Graph G, int k)
{
	//printf("%d\n", k);
    int i;
    if(k == -1)
    {
        for(i = 0; i < G.NumVertex; i++)
            if(!visited[i])
                DFS(G, i);
     }
     else
     {
        visited[k] = 1;
        printf("%d ", G.data[k]);
    	for(i = Firstvex_Graph(G, k);i >= 0; i = Nextvex_Graph(G, k, i))
            if(!visited[i])
                DFS(G, i);
     }
}

//BFS遍历 
void BFS(Graph G)
{
    int i, j, k;
    LinkQueue Q;
    InitQueue (&Q);
    //printf("QWQWQWQ");
    for(i = 0; i < G.NumVertex; i++)
        if(!visited[i])
        {
            visited[i] = 1;
            printf("%d ", G.data[i]);
            EnQueue(&Q, i);
            while(!QueueEmpty(&Q))//qu非空
            {
                k = DeQueue(&Q);
                for(j = Firstvex_Graph(G, k); j >= 0; j = Nextvex_Graph(G, k, j))
                    if(!visited[j])
                    {
                        visited[j] = 1;
                        printf("%d ", G.data[j]);
                        EnQueue(&Q, j);
                    }
            }
        }
}


//-----------队列操作-------------
Status InitQueue(LinkQueue *Q)
{
	Q -> front = Q -> rear = (QueuePtr)malloc(sizeof(QNode));
	if (Q -> front == NULL) exit(OVERFLOW);
	Q -> front -> next = NULL;
	
	return OK;
}

Status EnQueue(LinkQueue *Q, QElemType e)
{	
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p -> data = e;
	p -> next = NULL;
	Q -> rear -> next = p;
	Q -> rear = p;
	return OK; 
}

Status QueueEmpty(LinkQueue *Q)
{
	if (Q -> rear == Q -> front) return ERROR;
	return OK;
}

QElemType DeQueue(LinkQueue *Q)
{
	if (Q -> front == Q -> rear) return ERROR;
	
	QueuePtr p;
	p = Q -> front -> next;
	QElemType e = p -> data;
	Q -> front -> next = p -> next;
	if (Q -> rear == p) 
		Q -> rear = Q -> front;
	free(p);
	return e;
}
