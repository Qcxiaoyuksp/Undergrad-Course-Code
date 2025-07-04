#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef char ElemType;
//----------------二叉树中序线索化及遍历-----------
typedef  enum {link, thread } PointTag;//link=0表示指针，thread=1表示线索

typedef struct BiTNode{ // Node structure
	ElemType data;            // node data
	struct BiTNode *lchild;        // left child
	struct BiTNode *rchild;        // right child
	PointTag ltag, rtag;
}BiTNode, *BiTree;//线索二叉树的定义

BiTree pre;//定义其为全局变量


BiTree  CreateBiTree(BiTree T);
void InThreading(BiTree p);
BiTree InOrderThreading(BiTree Thr, BiTree T);
void VistTree(BiTree T);
void InOrderTraverse(BiTree T);

int main()
{

	char c;
	//	BiTree T=NULL;
	BiTree Thr=NULL, T=NULL;

	while (1){
		printf("Binary Tree's Implementation\n");
		printf("===========================================\n");
		printf("1. Create a binary tree;  2. InOrder Threading;\n");
		printf("3. InOrder Traverse;      0. Exit;\n");
		printf("===========================================\n");

		scanf(" %c", &c);


		switch (c){
		case '1':
			printf("Please input the elements by preorder,\n");
			printf("one character for one node，a null node is '#'\n");
			printf("For example: ABC##DE#G##F###\n");
			T = CreateBiTree(T);
			printf("\n");
			break;
		case '2':
			Thr = InOrderThreading(Thr, T);
			printf("\n");
			break;
		case '3':
			printf("\nInOrder Threading Traversal：\n");
			InOrderTraverse(Thr);
			printf("\n");
			break;
		case '0':exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;
		}

	}

	system("PAUSE");

	return 0;
}


BiTree CreateBiTree(BiTree T)
{
	char ch;
	scanf(" %c", &ch); //you should add a blank space before %c to filter blanks in buffer 
	if (ch == '#')
		T = NULL;
	else{
		if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch;                 // create the root
		T->ltag = link; T->rtag = link;//线索二叉树的构造
		T->lchild = CreateBiTree(T->lchild);    // create the left subtree
		T->rchild = CreateBiTree(T->rchild);    // create the right subtree
	}
	return T;
}

void InThreading(BiTree p)
{//中序线索化核心过程
	
    if (p != NULL)
{
    InThreading( p->lchild);//递归线索左子树
    if (p->lchild == NULL) { 
        p->lchild = pre; //指向前驱
        p->ltag = thread; 
    }
if (pre->rchild == NULL) { 
pre->rchild =p ; //指向后继
pre->rtag = thread; 
}
pre = p;
InThreading(p->rchild );//递归线索右子树
}

}

BiTree InOrderThreading(BiTree Thr, BiTree T)
{//线索化二叉树
	Thr = (BiTree)malloc(sizeof(BiTNode));//建立头结点
	if (!Thr)
		exit(1);
	Thr->ltag = link;
	Thr->rchild = Thr;
	Thr->rtag = thread;
	if (T == NULL) { Thr->lchild = Thr; }
	else
	{
		Thr->lchild = T;//令头结点的左指针指向非空的根结点
		pre = Thr;
		InThreading(T);
		pre->rchild = Thr;
		pre->rtag = thread;
		Thr->rchild = pre;
	}
	return Thr;
}
void VistTree(BiTree T)
{
	if (T != NULL)
		printf(" %c ", T->data);
}

void InOrderTraverse(BiTree T)
{//遍历中序线索二叉树
	BiTree p;
p = T->lchild;//p指向根
while ( p!=T)//当p不为头结点时
{//线索化的二叉树就像一个双向循环链表
while (p->ltag ==link )
    {p=p->lchild;}//向左到底
     VistTree(p);
while (p->rtag ==thread &&p->rchild != T)
{
p = p->rchild; VistTree(p);
}
//若p的右指针为线索则p->rchild为p的后继
//因此可以直接令p=p->rchild然后访问
p = p->rchild;
//后继访问完毕则遍历右子树
}


}

