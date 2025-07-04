#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

#define number 30 //非零元素个数最大值

//矩阵结构定义
typedef struct {
	int i, j;
	ElemType e;
}triple;
typedef struct {
	triple data[number];
	int rpos[number];
	int m, n, num;
}TSMatrix;

Status createTSMatrix(TSMatrix *T);
Status printTSMatrix(TSMatrix T);
int isInMatrix(TSMatrix T, int row, int col);
int getElemInMatrix(TSMatrix T, int row, int col);
Status transposeMatrix(TSMatrix *M, TSMatrix *T);
Status  fastTransposeMatrix(TSMatrix * M, TSMatrix * T);


int main() {
	char c;
	int i;

	TSMatrix M;
	TSMatrix T;

	while (1){
		printf("List Implementation by Sequence\n");
		printf("===================================================\n");
		printf("1. Create a Matrix;     2. Display a Matrix; \n");
		printf("3. Transpose a Matrix;  4. Fast Transpose a Matrix;\n");
		printf("0. Exit;\n");
		printf("===================================================\n");

		scanf(" %c", &c);

		switch (c){

		case '1':
			if (createTSMatrix(&M)){
				printf("创建矩阵成功\n");
			}
			else{
				printf("创建矩阵失败\n");
			}
			break;
		case '2':
			printTSMatrix(T);
			break;
		case '3':
			transposeMatrix(&M, &T);
			printf("使用普通方法：\n");
			for ( i = 0;i < T.num; i++) {
				printf("(%d,%d,%d)\n", T.data[i].i, T.data[i].j, T.data[i].e);
			}
			printf("\n");
			break;
		case '4':
			fastTransposeMatrix(&M, &T);
			printf("使用快速方法：\n");
			for (i = 0; i < T.num; i++) {
				printf("(%d,%d,%d)\n", T.data[i].i, T.data[i].j, T.data[i].e);
			}
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
/* 矩阵输入
M.m = 3;
M.n = 2;
M.num = 4;

M.data[0].i = 1;
M.data[0].j = 2;
M.data[0].e = 1;

M.data[1].i = 2;
M.data[1].j = 2;
M.data[1].e = 3;

M.data[2].i = 3;
M.data[2].j = 1;
M.data[2].e = 6;

M.data[3].i = 3;
M.data[3].j = 2;
M.data[3].e = 5;
*/
Status createTSMatrix(TSMatrix *M){
	int k;
	int I,J,E;
	printf("输入矩阵的行数、列数、非零元素个数:\n");
	scanf("%d%d%d", &M->m, &M->n, &M->num);
	
	for (k = 0; k<M->num; k++)
	{
		printf("输入第%d元素,i值从1到%d,j值从1到%d:\n", k + 1, M->m, M->n);
		scanf("%d%d%d", &I, &J, &E);
		if (I<1 || I>M->m || J<1 || J>M->n){
			printf("输入了非法的i值或j值");
			return  ERROR;
		}
		M->data[k].i = I;
		M->data[k].j = J;
		M->data[k].e = E;
	}
	return OK;
}

/*输出一个矩阵*/
Status printTSMatrix(TSMatrix T)
{
	int i, j;

	for (i = 1; i<=T.m; i++)
	{
		for (j = 1; j<=T.n; j++)
		{
			if (isInMatrix(T, i, j))
				printf("%d ", getElemInMatrix(T, i, j));
			else
				printf("0 ");
		}
		printf("\n");
	}
	return OK;
}

//检查一组行列号是否为非零元
int isInMatrix(TSMatrix T, int row, int col)
{
	int counter = 0;
	while (counter < T.num)
	{
		if (T.data[counter].i == row && T.data[counter].j == col)
		{
			return 1;
		}
		counter++;
	}
	return 0;
}
//取得一组行列号对应的元素
int getElemInMatrix(TSMatrix T, int row, int col)
{
	int counter;
	
	if (!isInMatrix(T, row, col))
		exit(0);
	for (counter = 0; counter<T.num; counter++)
	{
		if (T.data[counter].i == row && T.data[counter].j == col)
		{
			return T.data[counter].e;
		}
	}
}
/*普通方法转置*/
Status transposeMatrix(TSMatrix *M, TSMatrix *T){
	int col, p, q;
    T->m = M->n; T->n = M->m; T->num = M->num;
    if (T->num) { 
	    q = 0;
        for (col = 1; col <=M->m ; col++) {
        for (p = 0; p<M->num; p++) {
            if ( M->data[p].j== col) {
                T->data[q].i = M->data[p].j;
		        T->data[q].j = M->data[p].i;
		        T->data[q].e = M->data[p].e;    
                 q++; }
} } }



	return OK;
}

/*快速方法转置*/
Status  fastTransposeMatrix(TSMatrix * M, TSMatrix * T){
	int col, t, j, p, q;
	 int *cpot,*array;
    cpot = (int *)malloc(sizeof(int)*(M->n+1));
    array = (int *)malloc(sizeof(int)*(M->n+1));
    T->m = M->n; T->n = M->m; T->num = M->num;
    if (T->num) {
        for (col = 1; col <= M->n; col++) 
		{ array[col] = 0; }
        for (t = 0; t<M->num; t++) { //统计每列非零元素个数
            j = M->data[t].j;
			 array[j]++;
    }
        cpot[1] = 1;
        for (col = 2; col <= M->n; col++) { //M中第col列第一个非零元在T中位置
            cpot[col] = cpot[col-1]+array[col-1];
    }
        for (p = 0; p<M->num; p++) {
            col = M->data[p].j;
            q = cpot[col]; //q-1为T->data数组中第col列的可插入位置
                T->data[q-1].i = M->data[p].j;
		        T->data[q-1].j = M->data[p].i;
		        T->data[q-1].e = M->data[p].e;
   cpot[col]++; //位置向下一个
} }
return OK;
}
