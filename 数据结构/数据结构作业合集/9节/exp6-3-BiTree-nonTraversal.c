   //二叉树遍历
//作者：sun
//时间：2011年12月1日
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define OK          1
#define ERROR       0
#define TRUE        1
#define FALSE       0
#define OVERFLOW    -1

#define STACK_INIT_SIZE     100
#define STACKINCREMENT      10

typedef int Status;

typedef char ElemType;  // 二叉树结点元素类型

typedef struct BiTNode{ // 二叉树结点结构
	char data;            // 结点数据
	struct BiTNode *lchild;        // 左孩子
	struct BiTNode *rchild;        // 右孩子
}BiTNode,*BiTree;

typedef BiTree SElemType;

typedef struct{//栈结构定义
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;


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

int main()
{
	BiTree T=NULL;
	
	printf("请按先序遍历输入二叉树元素（每个结点一个字符，空结点为'#'）:\n");//如ABC##DE#G##F###
	T=CreateBiTree(T);
	printf("\n递归先序遍历：\n");
	PreOrderRecursionTraverse(T);
	printf("\n递归中序遍历：\n");
	InOrderRecursionTraverse(T);
	printf("\n递归后序遍历：\n");
	PostOrderRecursionTraverse(T);
	printf("\n非递归先序遍历：\n");
	PreOrderNonRecursionTraverse(T);
	printf("\n非递归中序遍历：\n");
	InOrderNonRecursionTraverse(T);
	printf("\n非递归后序遍历：\n");
	PostOrderNonRecursionTraverse(T);
	printf("\nEnd of main.\n");
	system("PAUSE");
	return 0;
}


BiTree CreateBiTree(BiTree T){
	// 按先后次序输入二叉树中结点的值（一个字符），空格表示空树
	// 构造二叉链表表示的二叉树T
	char ch;
	scanf("%c",&ch);
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

Status PreOrderRecursionTraverse(BiTree T)
{   // 先序遍历递归算法

	if(T){
		if(!Visit(T->data)) return ERROR;
		PreOrderRecursionTraverse(T->lchild);
		PreOrderRecursionTraverse(T->rchild);
	}
	return OK;
}

Status InOrderRecursionTraverse(BiTree T)
{   // 中序遍历递归算法
	if(T){
		InOrderRecursionTraverse(T->lchild);
		if(!Visit(T->data)) return ERROR;;
		InOrderRecursionTraverse(T->rchild);
	}
	return OK;
}


Status PostOrderRecursionTraverse(BiTree T)
{   //后序遍历递归算法
	if(T){
		PostOrderRecursionTraverse(T->lchild);
		PostOrderRecursionTraverse(T->rchild);
		if(!Visit(T->data)) return ERROR;;
	}
	return OK;
}

Status PreOrderNonRecursionTraverse(BiTree T){
	SqStack S;
    SElemType p;
    InitStack(&S); Push(&S,T); // 根指针入栈
    while(!StackEmpty(S)){
        Pop(&S,&p); //访问根节点
        if(!Visit(p->data)) return ERROR;
        if(p->rchild)
        {
            Push(&S,p->rchild);
		}
        if(p->lchild)
        {
            Push(&S,p->lchild);
		}
}//while
DestroyStack(&S);
	
	return OK;
}



Status InOrderNonRecursionTraverse(BiTree T){//ABDF###E##C##
	SqStack S;
    SElemType p;
    InitStack(&S); p=T;
    while (p||!StackEmpty(S) ){
        if (p){
      Push(&S,p);
	  p=p->lchild;
   
    }
        else{//根指针退栈，访问根节点，指向右子树
            Pop(&S,&p); 
          Visit(p->data);
            p=p->rchild;
    }//else
}//while
DestroyStack(&S);
return OK;  

}



Status PostOrderNonRecursionTraverse(BiTree T){
 // 后序遍历二叉树T的非递归算法
 SqStack S;
 SElemType p=T,q= NULL;
 InitStack(&S);
 while (p)
 {
  // 当p不为空时，将其入栈，并令p指向其左孩子
  while (p)
  {
   Push(&S,p);
   p = p->lchild;
  }
  while(!StackEmpty(S))
  {
   // 当栈不为空时，取出栈顶元素
   GetTop(S,&p);
   // 若栈顶元素的右孩子为空或已被访问，则访问当前栈顶元素，并将栈顶元素出栈
   if (p->rchild==NULL
    || p->rchild==q)
   {
    printf("%c",p->data);
    Pop(&S,&p);
    q = p; // 设置q为前一个访问的结点
    // 设置p为空，表示p及其左右子树均已访问完毕，访问下
    // 一个栈中元素
     p = NULL;
   }
   // 否则，应先访问栈顶元素的右孩子
   else
   {
    p = p->rchild;
    break;
   }
  }
 }
 DestroyStack(&S);
 return OK;
}


Status Visit(ElemType e){
	// 对二叉树中的数据元素访问
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
