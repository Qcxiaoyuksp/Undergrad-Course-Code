#include <math.h>
#include <tchar.h>
#include<iostream>
using namespace std;

int q(int n, int m)  //最大加数n1 不大于m的划分个数即为q(n,m) m为n的最大划分数
{
	if (n < 1 || m < 1) return 0;  // n=0 或者m=0 均不符合题意
	if (n == 1 || m == 1) return 1; // n=1 或者m=1 都只有一种情况
	if (n < m) return q(n,n); // 因为 n>=m 为前提条件 所以这种情况q(n,m)即为q(n,n)
	if (n == m) return q(n,m-1) + 1; //n=m的情况下，即划分为n1=n和n1<=n-1的情况
	return  q(n,m-1) + q(n-m,m); //正常情况下 q(n,m)的划分由n1=m的情况和n1<=m-1的情况
}

int main() {
	cout << q(6, 6) << endl;
	cout << q(7, 7) << endl;
	cout << q(8, 8) << endl;
	cout << q(5, 5) << endl;
	cout << q(4, 4) << endl;
	system("pause");
	return 0;
}
