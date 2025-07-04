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
BiTree invertTree(BiTree T);
bool compare(BiTree left, BiTree right);
bool isSymmetric(BiTree T);
int Max(int leftNum,int rightNum);
BiTree CreateBiTree(BiTree T);
Status PreOrderRecursionTraverse(BiTree T);
Status InOrderRecursionTraverse(BiTree T);
Status PostOrderRecursionTraverse(BiTree T);
int getNodesNumber(BiTree T);
int getHeight(BiTree T);
int getLeafNumber(BiTree T);
Status Visit(ElemType e);
 //visit the data of one node
int getMax(int m, int n);

int main()
{
	
	char c;
 	BiTree T=NULL,W=NULL;
	//BiTree T;

	while(1){
		printf("Binary Tree's Implementation\n");
		printf("===========================================\n");
		printf("1. Create a binary tree;       2. PreOrder Recursion Traverse;\n");
		printf("3. InOrder Recursion Traverse; 4. PostOrder Recursion Traverse;\n");
		printf("5. Return the number of nodes; 6. Return the height of the tree;\n");
		printf("7. Return the nubmer of leaves; 0. Exit;\n");
		printf("8. 翻转; 9. 对称;\n");
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
			printf("The number of nodes is :%d\n",getNodesNumber(T));
			break;
		case '6':
		    printf("The height of the tree is :%d\n",getHeight(T));
			break;
		case '7':
			printf("The number of leaf nodes is :%d\n",getLeafNumber(T));
			break;
			case '8':
			
			W=invertTree(T); 
			PreOrderRecursionTraverse(W);
			printf("\n");
			break;
			case '9':
			if(isSymmetric(T))
			{
				printf("是对称\n");
			}
			else printf("不是对称\n") ;
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

int getNodesNumber(BiTree T)
{   
int leftNum, rightNum, nodeNum;
if (!T)
return 0;
else {
leftNum = getNodesNumber(T->lchild); // 左
rightNum = getNodesNumber(T->rchild); // 右
nodeNum = leftNum+rightNum + 1; // 中
}
return nodeNum;

}//ABDF###E##C##

 int Max(int leftNum,int rightNum)
{

	if(leftNum>=rightNum) return leftNum;
else return rightNum;

}


int getHeight(BiTree T)
{ 
    int leftNum, rightNum,Num;
if (!T)
return 0;
else {
leftNum = getHeight(T->lchild); // 左
rightNum = getHeight(T->rchild); // 右
Num=leftNum+rightNum+1;
}

return Max(leftNum,rightNum)+1;
}




int getLeafNumber(BiTree T)  
{  
    static int ii=0; 
    if(T){
        
        getLeafNumber(T->lchild);
        getLeafNumber(T->rchild);
		if(T->lchild==NULL&&T->rchild==NULL){
		ii++;
		}
    }
return ii;
}  


bool isSymmetric(BiTree T) {
if (T == NULL) return TRUE;
return compare(T->lchild, T->rchild);
}


bool compare(BiTree left, BiTree right) {
bool outside, inside, isSame;
// 首先排除空节点的情况
if (left==NULL&& left!=NULL) return FALSE;
else if (left!=NULL&& left==NULL) return FALSE;
else if (left==NULL&& left==NULL) return TRUE;
// 排除了空节点，再排除数值不相同的情况
else if (left->data != right->data) return FALSE;
// 左右节点都不为空，且数值相同，递归下一层
outside = compare(left->lchild, right->rchild); 
// 外侧节点：左子树左孩子，右子树右孩子
inside = compare(left->rchild, right->lchild); 
// 内侧节点：左子树右孩子，右子树左孩子
isSame = outside && inside; 
return isSame;
}


BiTree invertTree(BiTree T){
BiTree temp;
if (T==NULL){ return NULL; }//递归出口
else {
//交换结点的左右孩子
temp=T->rchild;
T->rchild=T->lchild;
T->lchild=temp;
invertTree(T->lchild);
invertTree(T->rchild);

}
return T;

}

