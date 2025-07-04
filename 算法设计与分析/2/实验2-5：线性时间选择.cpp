/**
 *  线性时间选择
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>

#define MAX 100

void slsort(int num[], int p, int r);
void swap(int *x, int *y);
int Select(int num[], int p, int r, int k);

int main()
{
	int i = 19, k;
	int num[MAX] = { 6, 5, 9, 4, 3, 10, 2, 1, 7, 11, 8, 12, 18, 20, 13, 19, 15, 14, 17, 16};
	printf("请输入要选择第几小的元素：");
	scanf("%d", &k); // 选择第几小的元素
	if (k > i + 1)
		printf("error!\n");
	else
		printf("%d\n", Select(num, 0, i, k));
	system("pause");
	return 0;
}


/* 选择排序 */ 
void slsort(int num[], int p, int r)
{
	for (int i = p; i <= r - 1; i++)
	{
		int iMin = i;
		for (int j = i + 1; j <= r; j++) {
			if (num[j] < num[iMin]) {
				iMin = j; 
			}
		}
		if (iMin != i) {
			swap(&num[i], &num[iMin]);
		}
	}
}

void swap(int *x, int *y)
{
	int temp;

	temp = *x;
	*x = *y;
	*y = temp;
}
// 划分函数
int Partition(int num[], int p, int r, int mid)
{
	int i = p, j = r;
	while (i <= r && j >= p)
	{
		while (num[i] < mid){ i++; }
		while (num[j] > mid){ j--; }
		if (i >= j)
			break;
		else
		{
			swap(&num[i], &num[j]);
			i++, j--;
		}
	}
	return j;
}
// 选择函数
int Select(int num[], int p, int r, int k)
{   //用某个简单排序算法对数组a[p:r]排序,直接返回第k小元素
	if (r - p < 75)
	{
		slsort(num, p, r);//排序
		return num[p + k - 1];//返回
	}
	// 选出 n/5 组中每个组的中位数,将a[p+5*i]至a[p+5*i+4]的第3小元素与a[p + i]交换位置
	for (int i = 0; i <= (r - p - 4) / 5; i++)
	{
		slsort(num, p + i * 5, p + i * 5 + 4);//排序
		swap(&num[p + 5 * i + 2], &num[p + i]);//交换

	}
	// 选出各种中位数的中位数 mid, r-p-4
	int mid = Select(num, p, p + (r - p - 4) / 5, ((r - p - 4) / 5 + 1) / 2);
	// 以 mid 为基准进行分解
	int mid_id = Partition(num, p, r, mid);
	int mid_rank = mid_id - p + 1;
	// 递归条件判断
	if (k == mid_rank)
	{
		return num[mid_id];
	}
	else if (k < mid_rank)
	{
		return Select(num, p, mid_id, k);
	}
	else
	{
		return Select(num, mid_id + 1, r, k - mid_rank);
	}
}

