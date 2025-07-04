/*exp7-4 QuickSortSherwood
舍伍德快速排序。虽然快速排序平均复杂度可以看做nlogn.
但算法复杂度与输入实例之间有关系，未必都是平均时间复杂度。
这是采用舍伍德快速排序的原因，消除掉算法复杂度与输入实例之间的关系。
*/
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<cstdio>
#include<algorithm>
#define MAX 100
using namespace std;

int Partition(int a[], int low, int high)
{
	int key = a[low];
	int i = low, j = high + 1;
	while (1)
	{	while (a[++i]<key&&i <= high);
		while (a[--j]>key&&j >= low);
		if (i >= j) break;
		if (a[i] != a[j]) 
			swap(a[i], a[j]);
	}
	if ((j != low) && (a[low] != a[j]))
		swap(a[low], a[j]);
	return j;
}

//随机得到一个位置进行划分操作
int RandPartition(int a[], int low, int  high)
{
	srand(time(NULL));
	//随机生成一个low,high之间的位置k

	int k1 = rand() % (high - low + 1) + low;
	int k2 = rand() % (high - low + 1) + low;
	int k3 = rand() % (high - low + 1) + low;
	cout <<"k1 = "<< k1 << " k2 = "<< k2 << " k3 = " << k3 << endl;
	int k;
	int q[3] = {k1, k2, k3};
	sort(q, q + 3);
	k = q[1];
	cout <<"k = "<< k << endl;

	//int k = rand() % (high - low + 1) + low;
	cout << k << ":" << a[k] <<", " << endl;
	//将a[k]作为pivot
	swap(a[k], a[low]);
	k = Partition(a, low, high);
	return k;
}
void Quick_sort(int a[], int low, int high)
{
	if (low<high)
	{
		int k = RandPartition(a, low, high);
		Quick_sort(a, low, k - 1);
		Quick_sort(a, k + 1, high);
	}
}

// 随机洗牌算法
void random_shuffle(int a[]) {
	
	srand(time(NULL));
	for (int i = MAX - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}


int main()
{
	int i;
	int a[MAX];
	for (i = 0; i < MAX; i++)
		a[i] = i + 1;
	cout << "原次序：";
	cout << endl;
	for (i = 0; i < MAX; i++)
		cout << a[i] << " ";
	cout << endl;
	random_shuffle(a); //To randomize the array
	//cout << "排序前：" ;
	cout << "第一次洗牌：";
	cout << endl;
	for (i = 0; i < MAX; i++)
		cout << a[i] << " ";
	cout << endl;
	random_shuffle(a); //To randomize the array
	//cout << "排序前：" ;
	cout << "第二次洗牌：";
	cout << endl;
	for (i = 0; i < MAX; i++)
		cout << a[i] << " ";
	cout << endl;
	
	cout << "选择的pivot位置，值序列为：";
	cout << endl;
	
	Quick_sort(a, 0, MAX-1);
	cout << endl;

	cout << "排序后：";
	cout << endl;
	for (i = 0; i < MAX; i++)
		cout << a[i] << " ";
	cout << endl;
	
	
	system("PAUSE");
	return 0;
}


