#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void Knapsack(int profit[], int weight[], int c, int n, int **dp);
void Traceback(int **dp, int weight[], int c, int n, int *x);

int main(){
	int profit[5] = { 0, 1, 6, 10, 16 };
	int weight[5] = { 0, 1, 2, 3, 5 };
	int c = 7, n = 4;
	
	int ** dp = new int*[n + 1]; //共有length1+1行
	for (int i = 0; i < n + 1; i++)
		dp[i] = new int[c + 1];//共有length2+1列
	int *x=new int[c + 1];

	int sumWeight=0, sumProfit=0;

	Knapsack(profit, weight, c, n, dp);
	Traceback(dp, weight, c, n, x);
     printf("放入背包的物品为：\n");
	for (int i = 1; i < c ; i++)
	{
		
		if (x[i] == 1){
           printf("第%d个，重量为：%d, 价值为：%d\n", i, weight[i], profit[i]);
		   sumWeight += weight[i];
		   sumProfit += profit[i];
		}
		//printf("%d ", x[i]);
	}
	printf("总重量为：%d, 总价值为：%d\n", sumWeight, sumProfit);
	
	for (int j = 0; j < weight[1]; j++)
	{
		dp[0][j] = 0;
	}
	for (int j = weight[1]; j <= c; j++)
	{
		dp[0][j] = profit[0];///**
	}
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 0; j <= c; j++) 
		{
			if(j<weight[i]) dp[i][j]=dp[i-1][j];
			else{
				dp[i][j]=max(dp[i - 1][j], dp[i - 1][j - weight[i]] + profit[i]);
			}  
		}
	}
	printf("dp数组(二维)为：\n");
	for(int i=1;i<=n;i++){
		for(int j=0;j<=c;j++){
			printf("dp[%d][%d]:%d  ",i,j,dp[i][j]);
		}
		printf("\n");
	}
	printf("rec数组(一维)为：\n");
	for(int i=1;i<=n;i++){
		printf("rec[%d]:%d  ",i,x[i]);
	}
	system("PAUSE");
	return 0;
} 

void Knapsack(int profit[], int weight[], int c, int n, int **dp)
{
	int jMax = min(weight[n] - 1, c);//背包剩余容量上限 范围[0~w[n]-1]  
	for (int j = 0; j <= jMax; j++)
	{
		dp[n][j] = 0;
	}

	for (int j = weight[n]; j <= c; j++)//限制范围[w[n]~c]  
	{
		dp[n][j] = profit[n];///**
	}

	for (int i = n - 1; i > 1; i--)
	{
		jMax = min(weight[i] - 1, c);
		for (int j = 0; j <= jMax; j++)//背包不同剩余容量j<=jMax<c  
		{
			dp[i][j] = dp[i + 1][j];//没产生任何效益  
		}

		for (int j = weight[i]; j <= c; j++) //背包不同剩余容量j-wi >c  
		{
			dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - weight[i]] + profit[i]);//效益值增长vi   
		}
	}
	dp[1][c] = dp[2][c];
	if (c >= weight[1])
	{
		dp[1][c] = max(dp[1][c], dp[2][c - weight[1]] + profit[1]);
	}
}

//x[]数组存储对应物品0-1向量,0不装入背包，1表示装入背包  
void Traceback(int **dp, int weight[], int c, int n, int *x)
{
	for (int i = 1; i < n; i++)
	{
		if (dp[i][c] == dp[i + 1][c])
		{
			x[i] = 0;
		}
		else
		{
			x[i] = 1;
			c -= weight[i];
		}
	}
	x[n] = (dp[n][c]) ? 1 : 0;
}
