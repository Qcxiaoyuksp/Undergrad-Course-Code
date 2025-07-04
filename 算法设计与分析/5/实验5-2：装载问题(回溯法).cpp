/*MaxLoading,回溯法。*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 
#include <cstring>

using namespace std;

//问题表示
int w[] = { 0, 10, 40, 40 };	//各集装箱重量,不用下标0的元素
//int w[] = { 0, 20, 40, 40 };	//各集装箱重量,不用下标0的元素
int n = 3;
int c1 = 50, c2 = 50;

//求解结果表示
int maxw;		//存放最优解的总重量
int x[6];		//存放最优解向量
int minnum = 999999;	//存放最优解的集装箱个数,初值为最大值


void dfs(int tw, int rw, int op[], int i); //求第一艘轮船的最优解
bool solve();			//求解复杂装载问题

int main(){
	//假设已按单位价值降序排序
	int op[6];			//存放临时解

	//memset(op, 0, sizeof(op));
	int rw = 0;
	for (int i = 1; i <= n; i++)
		rw += w[i];
	dfs(0, rw, op, 1);			//求第一艘轮船的最优解
	
	if (solve())			//输出结果
	{
		printf(" 装载方案\n");
		for (int i = 1; i <= n; i++)
		{
			printf("%d ",x[i]);
		}
	
	}
	else printf("    没有合适的装载方案\n");

	system("PAUSE");
	return 0;
} 

void dfs(int tw, int rw, int op[], int i) //求第一艘轮船的最优解
{
	if (i>n)				//找到一个叶子结点
	{
		if (tw <= c1 && tw>maxw)
		{
			maxw = tw;			//找到一个满足条件的更优解
			for (int j = 1; j <= n; j++)	//复制最优解
				x[j] = op[j];
		}
	}
	else				//尚未找完所有集装箱
	{
		op[i] = 1;			//选取第i个集装箱
		if (tw + w[i] <= c1)	//左孩子结点剪枝
			dfs(tw + w[i], rw - w[i], op, i + 1);
		op[i] = 0;			//不选取第i个集装箱,回溯
		if (tw + rw>c1)		//右孩子结点剪枝
			dfs(tw, rw - w[i], op, i + 1);
	}
}

bool solve()			//求解复杂装载问题
{
	int sum = 0;			//累计第一艘轮船装完后剩余的集装箱重量
	for (int j = 1; j <= n; j++)
	if (x[j] == 0)
		sum += w[j];
	if (sum <= c2)		//第二艘轮船可以装完
		return true;
	else				//第二艘轮船不能装完
		return false;
}

