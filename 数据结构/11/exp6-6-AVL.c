#include <stdio.h>
#include <stdlib.h>
//分别定义平衡因子数  
#define LH +1
#define EH  0
#define RH -1
typedef int ElemType;
typedef enum {false,true} bool;
//定义二叉排序树
typedef struct BSTNode{
    ElemType data;
    int bf;//balance flag
    struct BSTNode *lchild,*rchild;
}*BSTree,BSTNode;

//对以 p 为根结点的二叉树做右旋处理，令 p 指针指向新的树根结点
void R_Rotate(BSTree* p);

//对以 p 为根结点的二叉树做左旋处理，令 p 指针指向新的树根结点
void L_Rotate(BSTree* p);

//对以指针 T 所指向结点为根结点的二叉树作左子树的平衡处理，令指针 T 指向新的根结点
void LeftBalance(BSTree * T);

//右子树的平衡处理同左子树的平衡处理完全类似
void RightBalance(BSTree* T);

int InsertAVL(BSTree* T,ElemType e,bool* taller);

//判断现有平衡二叉树中是否已经具有数据域为 e 的结点
bool FindNode(BSTree root,ElemType e,BSTree* pos);

//中序遍历平衡二叉树
void InorderTra(BSTree root);
int main()
{
    char c;
    int i,item,nArr[] = {1,23,45,34,98,9,4,35,23};
    BSTree root=NULL, pos;
    bool taller;
    //用 nArr查找表构建平衡二叉树（不断插入数据的过程）

    while (1){
		printf("AVL Tree's Implementation\n");
		printf("===========================================\n");
		printf("1. Create an AVL tree;  2. InOrder Traverse;\n");
		printf("3. Search a Node ;      0. Exit;\n");
		printf("===========================================\n");

		scanf(" %c", &c);

		switch (c){
		case '1':
			for (i=0;i<9;i++)
            {
               InsertAVL(&root,nArr[i],&taller);
            }
            printf("AVL tree has been created!;\n");
			printf("\n");
			break;
		case '2':
			//中序遍历输出
			printf("中序遍历序列是：\n");
            InorderTra(root);
			printf("\n");
			break;
		case '3':
			//判断平衡二叉树中是否含有数据域为某值的结点
            printf("Input the value of searching node :\n");
			scanf(" %d", &item);
			if(FindNode(root,item,&pos))
				printf("The node with %d is found.\n", item);
			else
				printf("The node with %d is not found.\n", item);
            printf("\n");
			break;
		case '0':exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;
		}

	}

    return 0;
}

//对以*p为根的二叉排序树做右旋处理，处理之后p指向新的树根结点
void R_Rotate(BSTree* p)
{
	BSTree lc;
    lc = (*p)->lchild;
    (*p)->lchild = lc->rchild;
    lc->rchild = (*p);
    (*p) = lc;
    
}

//对以 p 为根结点的二叉树做左旋处理，处理之后p指向新的树根结点
void L_Rotate(BSTree *p)
{
   	BSTree lc;
    lc = (*p)->rchild;
    (*p)->rchild = lc->lchild;
    lc->lchild = (*p);
    (*p) = lc;


}

//对以指针 T 所指向结点为根结点的二叉树作左子树的平衡处理，令指针 T 指向新的根结点
void LeftBalance(BSTree * T)
{
	BSTree lc, rd;
    lc = (*T)->lchild;
    switch (lc->bf)
    {
    case LH:
        (*T)->bf = lc->bf = EH;
        R_Rotate(&lc);
        break;
    case RH:
        rd = lc->rchild;
        switch (rd->bf)
        {
            case LH:
                (*T)->bf = RH;
                lc->bf =EH;
                break;
            case EH:
                (*T)->bf = lc->bf = EH;
                break;
            case RH:
                (*T)->bf =  EH;
                lc->bf = LH;
                break;
        }
        rd->bf = EH;
        L_Rotate(&rd);
        R_Rotate(&rd);
        break;
    } 

}
//右子树的平衡处理同左子树的平衡处理类似
void RightBalance(BSTree* T)
{
	BSTree lc, rd;
    lc = (*T)->rchild;
    switch (lc->bf)
    {
        case RH:
            (*T)->bf = lc->bf = EH;
            L_Rotate(&lc);
            break;
        case LH:
            rd = lc->lchild;
            switch (rd->bf)
            {
                case LH:
                    (*T)->bf = EH;
                    lc->bf = RH;
                    break;
                case EH:
                    (*T)->bf = lc->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    lc->bf = LH;
                    break;
            }
            rd->bf = EH;
            R_Rotate(&rd);
            L_Rotate(&rd);
            break;
    }

}

int InsertAVL(BSTree* T,ElemType e,bool* taller)
{//只填LeftBalance(T)或RightBalance(T)
    //如果本身为空树，则直接添加 e 为根结点
    if ((*T)==NULL)
    {
        (*T)=(BSTree)malloc(sizeof(BSTNode));
        (*T)->bf = EH;
        (*T)->data = e;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        *taller=true;
    }
    //如果二叉排序树中已经存在 e ，则不做任何处理
    else if (e == (*T)->data)
    {
        *taller = false;
        return 0;
    }
    //如果 e 小于结点 T 的数据域，则插入到 T 的左子树中
    else if (e < (*T)->data)
    {
        //如果插入过程，不会影响树本身的平衡，则直接结束
        if(!InsertAVL(&(*T)->lchild,e,taller))
            return 0;
        //判断插入过程是否会导致整棵树的深度 +1
        if(*taller)
        {
            //判断根结点 T 的平衡因子是多少，由于是在其左子树添加新结点的过程中导致失去平衡，所以当 T 结点的平衡因子本身为 1 时，需要进行左子树的平衡处理，否则更新树中各结点的平衡因子数
            switch ((*T)->bf)
            {
                case LH:
                    LeftBalance(T);
                    *taller = false;
                    break;
                case  EH:
                    (*T)->bf = LH;
                    *taller = true;
                    break;
                case RH:
                    (*T)->bf = EH;
                    *taller = false;
                    break;
            }
        }
    }
    //同样，当 e>T->data 时，需要插入到以 T 为根结点的树的右子树中，同样需要做和以上同样的操作
    else
    {
        if(!InsertAVL(&(*T)->rchild,e,taller))
            return 0;
        if (*taller)
        {
            switch ((*T)->bf)
            {
                case LH:
                    (*T)->bf = EH;
                    *taller = false;
                    break;
                case EH:
                    (*T)->bf = RH;
                    *taller = true;
                    break;
                case  RH:
                    RightBalance(T);
                    *taller = false;
                    break;
            }
        }
    }
    return 1;
}
//判断现有平衡二叉树中是否已经具有数据域为 e 的结点
bool FindNode(BSTree root,ElemType e,BSTree* pos)
{
    BSTree pt = root;
    (*pos) = NULL;
    while(pt)
    {
        if (pt->data == e)
        {
            //找到节点，pos指向该节点并返回true
            (*pos) = pt ;
            return true;
        }
        else if (pt->data>e)
        {
            pt = pt->lchild ;
        }
        else
            pt = pt->rchild ;
    }
    return false;
}

//中序遍历平衡二叉树
void InorderTra(BSTree root)
{
    if(root->lchild)
        InorderTra(root->lchild );

    printf("%d ",root->data);

    if(root->rchild)
        InorderTra(root->rchild );
}
