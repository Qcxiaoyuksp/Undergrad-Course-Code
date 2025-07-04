/* The implemetation of binary tree. the traversal of a tree is designed by recursion function 
by Simon. Nov. 2, 2014*/

#include<stdio.h>
#include<stdlib.h>

#define OK          1
#define ERROR       0
#define TRUE        1
#define FALSE       0
#define OVERFLOW    -1

typedef int Status;
typedef int bool;

typedef char ElemType;  // node type

typedef struct BiTNode{ // Node structure
	ElemType data;            // node data
	struct BiTNode *lchild;        // left child
	struct BiTNode *rchild;        // right child
}BiTNode,*BiTree;

typedef BiTree SElemType;


//To create a binary tree.
BiTree CreateBiTree(BiTree T);
Status PreOrderRecursionTraverse(BiTree T);
Status InOrderRecursionTraverse(BiTree T);
Status PostOrderRecursionTraverse(BiTree T);
int getNodesNumber(BiTree T);
int getNodesNumber1(BiTree T); 
int getNodesNumber2(BiTree T);
int getHeight(BiTree T);
int getLeafNumber(BiTree T);
Status Visit(ElemType e);
// visit the data of one node
//int getMax(int m, int n);

int main()
{
	
	char c;
 	BiTree T=NULL;
//	BiTree T;

	while(1){
		printf("Binary Tree's Implementation\n");
		printf("===========================================\n");
		printf("1. Create a binary tree;        2. PreOrder Recursion Traverse;\n");
		printf("3. InOrder Recursion Traverse;  4. PostOrder Recursion Traverse;\n");
		printf("5. Return the number of nodes;  6. Return the height of the tree;\n");
		printf("7. Return the nubmer of leaves; 0. Exit;\n");
		printf("===========================================\n");
		
		scanf(" %c",&c);
		
		
		switch(c){
		case '1':
			printf("Please input the elements by preorder,\n");
			printf("one character for one node，a null node is '#'\n");
	        printf("For example: ABC##DE#G##F###\n");
			T=CreateBiTree(T);
			printf("\n");
			break;
		case '2':
			printf("\nPreOrder Recursion Traversal：\n");
	        PreOrderRecursionTraverse(T);
			printf("\n");
			break;
		case '3':
	    	printf("\nInOrder Recursion Traversal：\n");
	        InOrderRecursionTraverse(T);
			printf("\n");
			break;
		case '4':
			printf("\nPostOrder Recursion Traversal：\n");
	        PostOrderRecursionTraverse(T);
			printf("\n");
			break;
		case '5':
			printf("The number of nodes is :%d\n",getNodesNumber(T));   //方法1 
			//方法2  printf("The number of nodes is :%d\n",getNodesNumber1(T));
			//方法3  printf("The number of nodes is :%d\n",getNodesNumber2(T));
			break;
		case '6':
		    printf("The height of the tree is :%d\n",getHeight(T));
			break;
		case '7':
			printf("The number of leaf nodes is :%d\n",getLeafNumber(T));
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

Status Visit(ElemType e){
	if(e=='\0'){
		return ERROR;
	}else{
		printf("%c",e);
	}
	return OK;
}


BiTree CreateBiTree(BiTree T)
{
	char ch;
	scanf(" %c",&ch); //you should add a blank space before %c to filter blanks in buffer 
	if(ch=='#') 
		T=NULL;
	else{
		if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data=ch;                 // create the root
		T->lchild=CreateBiTree(T->lchild);    // create the left subtree
		T->rchild=CreateBiTree(T->rchild);    // create the right subtree
	}
	return T;
}



Status PreOrderRecursionTraverse(BiTree T)
{  
	if(T){
		if(!Visit(T->data)) return ERROR;
		PreOrderRecursionTraverse(T->lchild);
		PreOrderRecursionTraverse(T->rchild);
	}
	return OK;
}

Status InOrderRecursionTraverse(BiTree T)
{   
	if(T){
		InOrderRecursionTraverse(T->lchild);
		if(!Visit(T->data)) return ERROR;
		InOrderRecursionTraverse(T->rchild);
	}
	return OK;
}


Status PostOrderRecursionTraverse(BiTree T)
{  
	if(T){
		PostOrderRecursionTraverse(T->lchild);
		PostOrderRecursionTraverse(T->rchild);
		if(!Visit(T->data)) return ERROR;
	}
	return OK;
}

/*方法一：遍历过程中计数*/
int getNodesNumber(BiTree T)
{
	static int i=0; //为什么用static类型
	if(T){
		i++;
		getNodesNumber(T->lchild);
		getNodesNumber(T->rchild);
	}
	return i;
}

/*方法二：递归计数*/
int getNodesNumber1(BiTree T)
{
	int leftNum, rightNum, nodeNum;
	if (!T)
	nodeNum = 0;
	else {
		leftNum = getNodesNumber1(T->lchild); // 左
		rightNum = getNodesNumber1(T->rchild); // 右
		nodeNum = leftNum + rightNum + 1; // 中
	}
	return nodeNum;
}

/*方法三：递归计数优化*/
int getNodesNumber2(BiTree T)
{
	if (T == NULL) return 0;
	return 1 + getNodesNumber2(T->lchild) + getNodesNumber2(T->rchild);
}


int getHeight(BiTree T)
{ 
	int h,left,right;
	if(!T) h=0;
	else{
		left=getHeight(T->lchild);
		right=getHeight(T->rchild);
		h=left>right? left+1:right+1;
	}
	return h;
}




int getLeafNumber(BiTree T)  
{  
	int l;
	if(!T) l=0;
 	else if(T->lchild==NULL&&T->rchild==NULL){
		l=1;
	}
	else l=getLeafNumber(T->lchild)+getLeafNumber(T->rchild);
	return l;
}  

BiTree invertTree(BiTree T)
{
 	BiTree temp;
 	if (!T) return ERROR;
 	else
 	{
  		temp = T->lchild;
  		T->lchild = T->rchild;
  		T->rchild = temp;
  		invertTree(T->lchild);
  		invertTree(T->rchild);
 	}		
 	return T;
}

bool isSymmetric(BiTree T)
{
 	if (T == NULL) return FALSE;
 	return compare(T->lchild, T->rchild);
}

bool compare(BiTree left, BiTree right)
{
 	bool outside, inside, isSame;
 	if (left == NULL && right == NULL) return FALSE;
 	else if (left != NULL && right == NULL) return FALSE;
 	else if (left == NULL && right != NULL) return FALSE;
 	else if(left->data != right->data) return FALSE;
 	outside = compare(left->lchild, right->rchild);
 	inside = compare(left->rchild, right->lchild);
 	isSame = outside && inside;
 	return isSame;
}


