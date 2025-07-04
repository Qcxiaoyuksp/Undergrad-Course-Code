/*nQueen回溯法,排列树。*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Queens(vector<int>& q, int i, int length);
bool place(vector<int>& q, int i);
void swap(vector<int>& q, int i, int j);
int cnt = 0; //解的数量
int sum = 0; //分支个数 

int main()
{
	//int n = 4;
	int n = 8;
	vector<int> q(n);//存放最优解向量
	for (int i = 0; i < n; i++)
	{
		q[i] = i + 1; //下标表示行/列，值表示列/行
	}
	Queens(q, 0, n);
	
	cout << "解的个数：" << cnt << endl;
	cout << "分支的个数：" << sum << endl;
	
	system("PAUSE");
	return 0;
}

void Queens(vector<int>& q, int i, int length)
{
	if (i == length) //找到一个解
	{
		cout << "解序号" << cnt << "：";
		for (int j = 0; j < length; j++)
		{
			cout << q[j] << " ";
		}
		cout << endl;
		cnt++;
	}
	else
	{
		for (int k = i; k < length; k++)
		{
			swap(q, k, i);
			if (place(q, i)) //是否可放置
				Queens(q, i + 1, length);
			swap(q, k, i); //回溯还原
		}
	}
}
//测试第i行的q[i]列上能否摆放皇后
bool place(vector<int>& q, int i)
{
	sum++; 
	for (int j = 0; j < i; j++)
	{
		if (i == j || q[i] == q[j] || abs(i - j) == abs(q[i] - q[j]))	//同行或同列或在同一斜线上
		{
			return false;
		}
	}
	return true;
}

void swap(vector<int>& q, int i, int j)
{
	int tmp = q[i];
	q[i] = q[j];
	q[j] = tmp;
}


