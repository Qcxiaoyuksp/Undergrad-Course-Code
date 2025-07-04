/*data[] is sorted by heap sorting algorithm*/
#include <stdio.h>

void swap(int *a, int *b);
void adjustHeap(int L[], int s, int m);
void HeapSort(int L[], int nums);
//大顶堆进行调整
void adjustHeap(int L[],int s, int m )  //由于从0开始，所以左孩子要加一 s * 2 + 1
{//调整（筛选）L使L[s....m]成为一个大顶堆
	int j;
	int temp = L[s];

	for (j = s * 2 + 1; j < m; j = j * 2 + 1)//s指向父结点，j指向子结点
	{
		//如果右边值大于左边值，指向右边
		if (j + 1 < m && L[j] < L[j + 1])
		{
			j++;
		}
		//如果子节点大于父节点，将子节点值赋给父节点,并以新的子节点作为父节点（不用进行交换）
		if (L[j] > temp)
		{
			L[s] = L[j];
			s = j;
		}
		else
			break;
	}
	//将暂存的值赋值到最后的位置
	L[s] = temp;
}
//堆排序主要算法
void HeapSort(int L[], int nums)
{
	int i,j,temp;
	//1.构建大顶堆
	for (i = nums >> 1 ; i >= 0; i--)//需要筛选的结点从0到nums/2，每次范围为i到nums
	{
		adjustHeap(L, i, nums - 1); 
	}
	printf("构建后的堆结构为：\n");
	for (i = 0; i < nums; i++)
		printf("%d ", L[i]);
	printf("\n");
	//2.调整堆结构+交换堆顶元素与末尾元素
	printf("堆排序结果为:\n");
	for (j = nums - 1; j > 0; j--)
	{
		printf("%d ", L[0]);
		//堆顶元素和末尾元素进行交换
        int temp = L[0];
		L[0] = L[j];
		L[j] = temp;

		adjustHeap(L, 0, j - 1);//重新对堆进行筛选,确定实参。
	}
	printf("%d \n", L[0]);
}
int main() {
	int i;
	int data[] = { 10, 8, 5, 7, 4, 6, 9, 3, 1, 2 };
	int len = sizeof(data) / sizeof(int);
	
	HeapSort(data, len);

	printf("排序后各元素的交换结果:\n");
	for (i = 0; i < len; i++)
		printf("%d ", data[i]);
	
	printf("\n"); 
//	system("PAUSE");
	return 0;
}
