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

typedef struct BTreeNode {
    char e;
	struct BTreeNode * left;
	struct BTreeNode * right;
} BTree;


BTree * createBTreeNode(char e){//创建一个结点
	BTree *nd;
	nd = (BTree *) malloc(sizeof(BTree));
	nd->e = e;
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

/*在str中,s1到s2之间查找是否存在c,如找到返回位置，否则返回-1.
*/
int findChar(const char *str, int s1, int s2, char c) {
	int i;
	if (!str || s2 < s1 || s1 < 0 || s2 >= strlen(str))
		return -1;
	for (i = s1; i <= s2; i++) {
		if (str[i] == c)
			return i;
	}
	return -1;
}

/*递归创建结点函数，每次由一个字符创建一个结点。
算法的关键是准确确定递归函数中两个字符序列的上下界。
*/
BTree *getRoot(char *pre, int p1, int p2, char *in, int i1, int i2) {
	//p1 and p2 are bounds of pre, and i1 and i2 are bounds of in;  
	char rootCh = pre[p1];//取先序序列中的第一个字符
	int tmp;
	BTree *nd;
	if (!pre || p2 < p1 || p1 < 0 || p2 >= strlen(pre) || !in || i2 < i1 || i1
		< 0 || i2 >= strlen(in)) {
		return NULL;
	}
	tmp = findChar(in, i1, i2, rootCh);
	if (tmp < 0) {
		return NULL;
	}

	nd = createBTreeNode(rootCh);//先序遍历次序创建二叉树，由rootCh创建一个结点
	nd->left = getRoot(pre, p1 + 1, p1 + tmp - i1, in, i1, tmp - 1);
	nd->right = getRoot(pre, p1 + tmp - i1 + 1, p2, in, tmp + 1, i2);
	return nd;
}
/*开始创建函数，由先序序列及中序序列递归创建二叉树*/
BTree * createBTree(char *pre, char *in) {  
	if (!pre || !in)
		return NULL;
	return getRoot(pre, 0, strlen(pre) - 1, in, 0, strlen(in) - 1);
}
int Visit(char e) {
	if (e == '\0') {
		return ERROR;
	}
	else {
		printf("%c", e);
	}
	return OK;
}

/*后序遍历二叉树，学生完成*/
int  printPostOrder(BTree * t) {   //后序遍历二叉树，学生完成
if (t) {
		printPostOrder(t->left);
		printPostOrder(t->right);
		if (!Visit(t->e)) return ERROR;
	}
	return OK;
    
}
//输出二叉树结点
void printBTreeNode(BTree *nd, int depth) {  //输出二叉树
	int i; 
	for ( i = 0; i < depth - 1; i++)
		printf("  ");
	if (depth > 0)
		printf("--");
	if (!nd) {
		printf("*\n");
		return ;
	}
	printf("%c\n", nd->e);
	printBTreeNode(nd->left, depth + 1);
	printBTreeNode(nd->right, depth + 1);
}

//输出二叉树
void printBTree(BTree *t) {  
	printBTreeNode(t, 0);
}

//计算结点数
int countBTree(BTree *t) {
	if (!t)
		return 0;
	return countBTree(t->left) + countBTree(t->right) + 1;
}

int main() {
	char pre[] = "ABDGCEFH";
	char in[] = "DGBAECHF";
	BTree *t;
	t = createBTree(pre, in);

	printf("Preorder: %s\n", pre);
	printf("Inorder: %s\n", in);
	if (countBTree(t) != strlen(pre)) {
		printf("No such a binary tree!\n");
		return 0;
	}
	printf("Postorder: ");
	printPostOrder(t);
	printf("\n");
	printf("The BTree is (* means no such node):\n");
	printBTree(t);

	system("PAUSE");

	return 0;
}	

