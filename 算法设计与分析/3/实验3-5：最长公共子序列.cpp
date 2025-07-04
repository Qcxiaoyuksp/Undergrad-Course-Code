/**
 * 最长公共子序列。
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 
#include <cstring>

using namespace std;

int LCSLength(char* str1, char* str2, int** rec);
void PrintLCS(int** rec, char* str1, int i, int j);

int main()
{
	
	//双指针的方法申请动态二维数组
	//char str1[50]="ABCBDAB";
	//char str2[50]="BDCABA";
	char str1[50] = "AABCDD";
	char str2[50] = "BBCCDD";
	
	int length1 = strlen(str1);
	int length2 = strlen(str2);

	int** rec = new int*[length1 + 1]; //共有length1+1行
	for (int i = 0; i < length1 + 1; i++)
		rec[i] = new int[length2 + 1];//共有length2+1列

	printf("公共最长子序列长度为：%d\n", LCSLength(str1, str2, rec));
	printf("追踪为：\n");

	PrintLCS(rec, str1, length1, length2);

	printf("\n");
	for (int i = 0; i < length1 + 1; i++)    //释放动态申请的二维数组
		delete[] rec[i];
	delete[] rec;

	system("PAUSE");
	return 0;
}

int LCSLength(char* str1, char* str2, int** rec)
{
	int i, j, length1, length2, len;
	length1 = strlen(str1);
	length2 = strlen(str2);

	//双指针的方法申请动态二维数组
	int** c = new int*[length1 + 1]; //共有length1+1行
	for (i = 0; i < length1 + 1; i++)
		c[i] = new int[length2 + 1];//共有length2+1列

	for (i = 0; i < length1 + 1; i++)
		c[i][0] = 0;        //第0列都初始化为0
	for (j = 0; j < length2 + 1; j++)
		c[0][j] = 0;        //第0行都初始化为0

	for (i = 1; i < length1 + 1; i++)
	{
		for (j = 1; j < length2 + 1; j++)
		{
			if (str1[i - 1] == str2[j - 1])//由于c[][]的0行0列没有使用，c[][]的第i行元素对应str1的第i-1个元素
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				rec[i][j] = 0;    //搜索方向为左上LU
			}
			else if (c[i - 1][j] > c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				rec[i][j] = 1; //搜索方向为上U
			}
			else
			{
				c[i][j] = c[i][j - 1];
				rec[i][j] = -1; //搜索方向为左L
			}
		}
	}
	//打印c[i][j]数组
	printf("dp数组：\n");
	for (i = 0; i < length1 + 1; i++)
	{
		for (int j = 0; j < length2 + 1; j ++)
			printf("dp[%d][%d]=%d ", i, j, c[i][j]);
		printf("\n");
	}
               //打印rec[i][j]数组
    printf("rec数组：\n");
	for (i = 1; i < length1 + 1; i++)
	{
		for (int j = 1; j < length2 + 1; j ++)
			printf("rec[%d][%d]=%d ", i, j, rec[i][j]);
		printf("\n");
	}
	
	len = c[length1][length2];
	for (i = 0; i < length1 + 1; i++)    //释放动态申请的二维数组
		delete[] c[i];
	delete[] c;
	return len;
}
void PrintLCS(int** rec, char* str1, int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (rec[i][j] == 0)
	{
		PrintLCS(rec, str1, i - 1, j - 1);//从后面开始递归，所以要先递归到子串的前面，然后从前往后开始输出子串
		printf("%c", str1[i - 1]);//c[][]的第i行元素对应str1的第i-1个元素
	}
	else if (rec[i][j] == 1)
		PrintLCS(rec, str1, i - 1, j);
	else
		PrintLCS(rec, str1, i, j - 1);
}

