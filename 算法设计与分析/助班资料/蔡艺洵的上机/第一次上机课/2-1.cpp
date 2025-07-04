#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>

using namespace std;

void perm(int list[], int k, int m);
void swap(int& a, int& b);

int main()
{
	int a[5] = {1,2,3,4};
//	perm(a, 0, 3);
//	printf("\n");

	perm(a, 0, 2);
	printf("\n");
	
//	perm(a, 0, 5);
//	printf("\n");
//	
//	int b[6] = {2,4,6,8,7,5};
//	perm(b, 0, 5);
//	printf("\n");

	system("PAUSE");
	return 0;
}
void perm(int list[], int k, int m)
{
	if (k == m)
	{
		//只剩下一个元素
		for (int i = 0; i <= m; i++)
			cout << list[i];
		cout << endl;
	}
	else
	for (int i = k; i <= m; i++)
	{
		swap(list[i], list[k]); //将第i个元素与第k个元素交换位置
		perm(list, k+1, m); //递归排列第k+1到第m个元素
		swap(list[i], list[k]); //第i和第k个交换元素的重新换回正常位置
	}
}
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
