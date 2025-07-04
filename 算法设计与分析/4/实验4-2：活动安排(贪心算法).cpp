#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int arrangeGreedy(vector<int> s, vector<int> f, int * a);


int main() {
	//vector<int> s = { 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
	vector<int> s = { 1, 3, 0, 5, 3, 7, 6, 8, 5, 2, 12};
	vector<int> f = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};//已按结束时间排序
	int *a = new int[s.size()];
	int ans;
	ans = arrangeGreedy(s, f, a);
	cout << "选择的活动为："<< " ";
	for (int j = 0; j < s.size(); j++) { // 输出所选活动
		if (a[j] == 1)
			cout << j + 1 << "，" ;
	}
	cout << endl;
	cout << "选择的活动数为：" << ans << endl;
	system("PAUSE");
	return 0;
}

int arrangeGreedy(vector<int> s, vector<int> f, int * a)
{
	int n = s.size(), j = 1, i, count = 1;
	a[0] = 1;//选择第1早结束的活动
	for (i = 1; i < n; i++)
	{
		if (s[i] >= f[j])
		{
			a[i] = 1;//选择ai
			j = i;
			count++;
		}
		else
			a[i] = 0;
	}
	return count;
}


