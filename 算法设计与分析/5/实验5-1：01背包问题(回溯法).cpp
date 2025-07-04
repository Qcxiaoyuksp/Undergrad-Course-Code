/*01背包问题,回溯法。*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;
//问题表示
int n = 4;			//4种物品
int W = 6;			//限制重量为6
int w[] = { 0, 5, 3, 2, 1 };		//存放4个物品重量,不用下标0元素
int v[] = { 0, 4, 4, 3, 1 };		//存放4个物品价值,不用下标0元素
//int w[] = { 0, 5, 3, 2, 1 };		//存放4个物品重量,不用下标0元素
//int v[] = { 0, 16, 10, 6, 1 };		//存放4个物品价值,不用下标0元素
//求解结果表示
int x[5];			//存放最终解
int maxv; 			//存放最优解的总价值

void dfs(int i, int tw, int tv, int rw, int op[]); //求解0/1背包问题

int main(){
	//假设已按单位价值降序排序
	int sumWeight=0, sumProfit=0;
	int rw=0;
	int op[5] = {0};

	for (int i = 1; i <= n; i++)
	{
		rw+= w[i];
	}
	dfs(1, 0, 0, rw, op);

    printf("放入背包的物品为：\n");
	for (int i = 1; i <= n ; i++)
	{
		if (x[i] != 0){
			printf("第%d个，重量为：%d, 价值为：%d\n", i, w[i], v[i]);
			sumWeight += w[i];
			sumProfit += v[i];
		}
		//printf("%f ", x[i]);
	}
	printf("总重量为：%d, 总价值为：%d\n", sumWeight, maxv);
	system("PAUSE");
	return 0;
} 


void dfs(int i, int tw, int tv, int rw, int op[]) //求解0/1背包问题
{  //初始调用时rw为所有物品重量和
	int j;
	if (i>n)				//找到一个叶子结点
	{
		if (tw == W && tv>maxv) 		//找到一个满足条件的更优解,保存
		{
			maxv = tv;
			for (j = 1; j <= n; j++)		//复制最优解
				x[j] = op[j];
		}
	}
	else					//尚未找完所有物品
	{
		if (tw + w[i] <= W)			//左孩子结点剪枝
		{
			op[i] = 1;			//选取第i个物品
			dfs(i + 1, tw + w[i], tv + v[i], rw - w[i], op);
		}
		op[i] = 0;				//不选取第i个物品,回溯
		if (tw + rw>W)			//右孩子结点剪枝
			dfs(i + 1, tw, tv, rw - w[i], op);
	}
}

