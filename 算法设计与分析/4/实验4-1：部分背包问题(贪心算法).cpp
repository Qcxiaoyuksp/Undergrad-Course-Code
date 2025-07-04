/*部分背包问题*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;


void knapsack(int n, float m, float profit[], float weight[], float *x);

int main(){
	//假设已按单位价值降序排序
	float  profit[5] = { 0, 10, 16, 6, 1};
	float  weight[5] = { 0, 3, 5, 2, 1};
	int n = 4;
	float c = 9;
	
	
	float  x[5] = { 0, 0, 0, 0, 0 };

	float sumWeight = 0, sumProfit = 0;

	knapsack(n, c, profit, weight, x);
	
    printf("放入背包的物品为：\n");
	for (int i = 1; i <= n ; i++)
	{
		
		if (x[i] != 0){
			printf("第%d个，重量为：%f, 价值为：%f\n", i, weight[i], profit[i]);
			printf("选择的重量为：%f, 其价值为：%f\n", x[i],x[i]*(profit[i]/weight[i]));
			sumWeight += x[i];
			sumProfit += x[i]*(profit[i]/weight[i]); 
		}
		//printf("%f ", x[i]);
	}
	printf("总重量为：%f, 总价值为：%f\n", sumWeight, sumProfit);

	system("PAUSE");
	return 0;
} 

void knapsack(int n, float m, float profit[], float weight[], float	*x)
{
	int i=0;
	
	float c = m;
	
	for (i = 1; i <= n; i++)
	{
		if (weight[i] > c)
			break;
		x[i] = weight[i];
		c -= weight[i];
	}
	
	if (i <= n)
	{
		x[i] = c;
		c = 0;
	}
		
}


