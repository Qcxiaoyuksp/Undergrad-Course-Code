/* 修改值的方法有3种：(1) 全局变量，尽量少用；(2)  函数返回值；(3)  地址传递。
此程序变量为指针型，把此值修改从函数带回用到了二级指针，如bst_p *root；
或者用函数返加值，BiTree T=NULL; T = CreateBiTree(T);
思考什么情况下用二级指针？指针用作传出参数时，对需要对BST进行修改时，写操作。也可用返回值。
*/

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
#define MAXNUM 100

typedef int data_type;

typedef struct bst_node {
	data_type data;
	 struct bst_node *lchild, *rchild;	
}bst_t, *bst_p;

bst_p search_bst_for_insert(bst_p *root, data_type key);
Status insert_bst_node(bst_p *root, data_type data);
int print(data_type data);
Status pre_order_traverse(bst_p T);
Status in_order_traverse(bst_p T);
Status post_order_traverse(bst_p T);
Status search_bst_node(bst_p T, data_type key);
Status delete_bst_node(bst_p *root, data_type data);

int main()
{
	int i, num, item;
	bst_p root = NULL;
	char c;
	data_type arr[MAXNUM];


	while (1){
		printf("Binary Search Tree's Implementation\n");
		printf("===========================================\n");
		printf("1. Create a binary search tree;2. PreOrder Recursion Traverse;\n");
		printf("3. InOrder Recursion Traverse; 4. PostOrder Recursion Traverse;\n");
		printf("5. Delete a node; 6. Search a node; \n");
		printf("7. Insert a node; 0. Exit;\n");
		printf("===========================================\n");

		scanf(" %c", &c);


		switch (c){
		case '1':
			printf("Please enter the number of nodes:\n");
			scanf("%d", &num);
			printf("Please enter %d of integer:\n", num);

			for (i = 0; i < num; i++) {
				scanf("%d", &arr[i]);
				insert_bst_node(&root, arr[i]);
			}
			printf("\n");
			break;
		case '2':
			printf("\npre order traverse: ");
			pre_order_traverse(root);
			printf("\n");
			break;
		case '3':
			printf("\nin order traverse: ");
			in_order_traverse(root);
			printf("\n");
			break;
		case '4':
			printf("\npost order traverse: ");
			post_order_traverse(root);
			printf("\n");
			break;
		case '5':
			printf("Input the value of deleted node :\n");
			scanf(" %d", &item);
			if (delete_bst_node(&root, item))
				printf("The node with %d is deleted successfully.\n", item);
			else
				printf("The node with %d is not found.\n", item);

			break;
		case '6':
			printf("Input the value of searching node :\n");
			scanf(" %d", &item);
			if (search_bst_node(root, item))
				printf("The node with %d is found.\n", item);
			else 
				printf("The node with %d is not found.\n", item);
			
			break;
		case '7':
			printf("Input the value of inserted node :\n");
			scanf(" %d", &item);
			if (insert_bst_node(&root, item))
				printf("The node with %d is inserted successfully.\n", item);
			else
				printf("The node with %d is not inserted.\n", item);
			break;
		case '0':
                        exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;
		}

	}

	system("PAUSE");

	return 0;


}

bst_p search_bst_for_insert(bst_p *root, data_type key)
{
	bst_p s, p = *root;
	s = malloc(sizeof(struct bst_node));

	while (p) {
		s = p;

		if (p->data == key)
			return NULL;

		p = (key < p->data) ? p->lchild : p->rchild;
	}

	return s;
}

Status insert_bst_node(bst_p *root, data_type data)
{
	bst_p s, p;

	s = malloc(sizeof(struct bst_node));


	s->data = data;
	s->lchild = s->rchild = NULL;

	if (*root == NULL)
		*root = s;
	else {
		p = search_bst_for_insert(root, data);
		if (p == NULL) {
			printf("The %d already exists.\n", data);
			free(s);
			return ERROR;
		}

		if (data < p->data)
			insert_bst_node(s->lchild,data);
		else
			insert_bst_node(s->rchild,data);
	}
	return OK;
}

int print(data_type data)
{
	printf("%d ", data);

	return 1;
}



Status pre_order_traverse(bst_p T)
{
	if (T) {
		if (!print(T->data)) return ERROR;
		pre_order_traverse(T->lchild);
		pre_order_traverse(T->rchild);
	}
	return OK;
}

Status in_order_traverse(bst_p T)
{
	if (T) 
 	{
  		in_order_traverse(T->lchild);
  		if (!print(T->data)) return ERROR;
  		in_order_traverse(T->rchild);
 	}
 	return OK;
}

Status post_order_traverse(bst_p T)
{
	if (T)
 	{
  		post_order_traverse(T->lchild);
  		post_order_traverse(T->rchild);
  		if (!print(T->data)) return ERROR;
 	}
 	return OK;

}

Status delete_bst_node(bst_p *root, data_type data)
{
	bst_p p = *root, parent, s;

	parent = malloc(sizeof(struct bst_node));
	s = malloc(sizeof(struct bst_node));

	if (!p) {
		printf("Not found.\n");
		return ERROR;
	}

	if (p->data == data) {
		/* It's a leaf node */
		if (!p->rchild && !p->lchild) {
			*root = NULL;
			free(p);
		}
		/* the right child is NULL */
		else if (!p->rchild) {
			*root = p->lchild;
			free(p);
		}
		/* the left child is NULL */
		else if (!p->lchild) {
			*root = p->rchild;
			free(p);
		}
		/* the node has both children */
		else {
			s = p->rchild;
			/* the s without left child */
			if (!s->lchild)
				s->lchild=p->lchild;
			/* the s have left child */
			else {
		/* find the smallest node in the right subtree of s 与课上讲的不同*/
				while (s->lchild) {
					/* record the parent node of s */
					parent=s;
					s=s->lchild;
				}
                            /* swap */
				parent->lchild=s->rchild;
				s->lchild=p->lchild;
				s->rchild=p->rchild;
			}
			*root = s;
			free(p);
		}
	}
	else if (data > p->data) {
		delete_bst_node(&(p->rchild), data);
	}
	else if (data < p->data) {
		delete_bst_node(&(p->lchild), data);
	}
	return OK;
}


Status search_bst_node(bst_p T, data_type key)
{
	bst_p p = T;
 	while (p) 
 	{
  		if (p->data == key)
   		return OK;
  		p = (key < p->data) ? p->lchild : p->rchild;
 	}
 	return ERROR;

	
}
