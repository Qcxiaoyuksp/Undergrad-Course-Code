#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void Knapsack(int profit[], int weight[], int c, int n, int **dp, int **rec);
void Traceback(int **dp, int weight[], int c, int n, int *x, int **rec);

int main(){
	//int profit[5] = { 0, 1, 6, 10, 16 };//第一个数没用
	//int weight[5] = { 0, 1, 2, 3, 5 };//第一个数没用
	//int c = 7, n = 4;
	int profit[5] = {0, 1, 9, 10, 16};
	int weight[5] = {0, 1, 5, 2, 3};
	int c = 7, n = 4;
	
	int ** dp = new int*[n + 1]; //共有length1+1行
	int ** rec = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		dp[i] = new int[c + 1];//共有length2+1列
		rec[i] = new int[c + 1];
	}		
	for (int j = 0; j < n + 1; j ++)
		dp[0][j] = 0;
	int *x=new int[c + 1];

	int sumWeight=0, sumProfit=0;

	Knapsack(profit, weight, c, n, dp, rec);
	Traceback(dp, weight, c, n, x, rec);
    printf("放入背包的物品为：\n");
	for (int i = 1; i < c ; i++)
	{
		
		if (x[i] == 1){
           printf("第%d个，重量为：%d, 价值为：%d\n", i, weight[i], profit[i]);
		   sumWeight += weight[i] ;
		   sumProfit += profit[i] ;
		}
		//printf("%d ", x[i]);
	}
	printf("总重量为：%d, 总价值为：%d\n", sumWeight, sumProfit);
	
	//打印dp数组和rec数组 
	printf("dp数组为：\n");
	for (int i = 1; i <= n; i ++)
	{
		for (int j = 0; j <= c; j ++) 
		{
			printf("dp[%d][%d]=%d\t", i, j, dp[i][j]);
		}
		printf("\n");
	}
	printf("rec数组为：\n");
	for (int i = 1; i <= n; i ++)
	{
		for (int j = 0; j <= c; j ++)
		{
			printf("rec[%d][%d]=%d\t", i, j, rec[i][j]);
		}
		printf("\n");
	}

	system("PAUSE");
	return 0;
} 

void Knapsack(int profit[], int weight[], int c, int n, int **dp, int **rec)
{
	int jMax = min(weight[1] - 1, c);//背包剩余容量上限 范围[0~w[n]-1]  
	for (int j = 0; j <= jMax; j++)
	{
		dp[1][j] = 0; //第一行初始化
		rec[1][j] = 0; 
	}

	for (int j = weight[1]; j <= c; j++)//限制范围[w[n]~c]  
	{
		dp[1][j] = profit[1];///**
		rec[1][j] = 1;
	}

	for (int i = 2; i <= n; i ++)
	{
		jMax = min(weight[i] - 1, c);
		for (int j = 0; j <= jMax; j++)//背包不同剩余容量j<=jMax<c  
		{
			dp[i][j] = dp[i - 1][j] ;//没产生任何效益 
			rec[i][j] = 0; 
		}

		for (int j = weight[i]; j <= c; j++) //背包不同剩余容量j-wi >c  
		{
			dp[i][j] = max(dp[i - 1][j] , dp[i -1][j - weight[i]] + profit[i] );//效益值增长vi
			if (dp[i - 1][j] >= dp[i - 1][j - weight[i]] + profit[i])
				rec[i][j] = 0;
			else rec[i][j] = 1;   
		}
	}
	
}

//x[]数组存储对应物品0-1向量,0不装入背包，1表示装入背包  
void Traceback(int **dp, int weight[], int c, int n, int *x, int **rec)
{
	for (int i = n; i >= 1; i--)
	{
		if (dp[i][c] == dp[i - 1][c])
		{
			x[i] = 0 ;
		}
		else
		{
			x[i] = 1 ;
			c -= weight[i];
		}
	}
	//x[n] = (dp[n][c]) ? 1 : 0;
}

