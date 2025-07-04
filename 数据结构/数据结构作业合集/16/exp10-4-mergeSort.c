#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
//sourceArr[] 源数组，tempArr[]临时数组，从小到大归并排序
void Merge(int sourceArr[],int tempArr[],int startIndex,int midIndex,int endIndex)
{
	
	int i = startIndex, j = midIndex + 1, k = startIndex;//i,j归并两段的指针，临时数组中指针
	while (i != midIndex + 1 && j != endIndex + 1)
	{
		if (sourceArr[i] > sourceArr[j])
			tempArr[k++] = sourceArr[j++];
		else
			tempArr[k++] = sourceArr[i++];
	}
	while (i != midIndex + 1) //处理剩余部分
		tempArr[k++] = sourceArr[i++];
	while (j != endIndex + 1)//处理剩余部分
		tempArr[k++] = sourceArr[j++];
	for (i = startIndex; i <= endIndex; i++) //导回到源数组
	   sourceArr[i] = tempArr[i];
}

//内部使用递归
void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
	int midIndex;
	if (startIndex < endIndex)
	{
		midIndex  = startIndex + (endIndex - startIndex) / 2;//避免溢出int
		MergeSort(sourceArr, tempArr, startIndex, midIndex);//递归左半部分
		MergeSort(sourceArr, tempArr, midIndex + 1, endIndex);//递归右半部分
		Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);//归并
	}
}

int main(int argc, char * argv[])
{
	int a[8] = { 50, 10, 20, 30, 70, 40, 80, 60 };
	int i, b[8];
	MergeSort(a, b, 0, 7);
	for (i = 0; i < 8; i++)
		printf("%d ", a[i]);
	printf("\n");
	system("PAUSE");
	return 0;
}
