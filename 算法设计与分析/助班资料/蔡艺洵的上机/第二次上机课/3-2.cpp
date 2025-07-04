/*动态规划算法之-----走方格 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int getMin(int map[4][4],int n,int m);
int Min(int a,int b);  //系统有min,max函数
int getMax(int map[4][4], int n, int m);
int Max(int a, int b);
int main()
{
	int i=0, j=0;
	int array[4][4] ={
		{2, 3, 0, 8},
		{4, 2, 7, 3},
		{5, 3, 0, 5},
		{0, 1, 2, 4}	
	 };
	printf("原数组：\n" );
	for (i = 0; i<4; i++){
		for (j = 0; j<4; j++){
			printf("%4d", array[i][j]);
		}
		printf("\n");
	}
	
	printf("最小权重为：%d\n",getMin(array, 4, 4));
	
	printf("最大权重为：%d\n", getMax(array, 4, 4));
	system("pause");
	return 0;
}

int getMin(int map[4][4], int n, int m) {
	int dp[4][4] = {0};
	int i, j;
	for (i = 0; i<n; i++){  //第一行初始化，一直向右走.
		for (j = 0; j <= i; j++){  //i=0,j=0 dp[0][0] i=0,j=0,1 dp[1][0]
			dp[i][0] += map[j][0];
		}
	}
	for (i = 1; i<m; i++){  //第一列初始化，一直向下走；如i=0，则dp[0][0]会计算两次。
		for (j = 0; j <= i; j++){
			dp[0][i] += map[0][j];
		}
	}
	for (i = 1; i<n; i++){
		for (j = 1; j<m; j++){
			dp[i][j] = Min(dp[i][j - 1] + map[i][j], dp[i - 1][j] + map[i][j]);
		}
	}

	printf("最小权重数组为：\n");
	for (i = 0; i<n; i++){
		for (j = 0; j<m; j++){
			printf("%4d", dp[i][j]);
		}
		printf("\n");
	}
	printf("最小权重路径为：\n");
	i = 3; j = 3;
	while (i != 0 || j != 0){  //反向查询路径，可用栈存储，出栈即为正向路径
		printf("(%d，%d)", j, i);
		printf("<-");
		if (dp[i][j]-map[i][j]== dp[i - 1][j] ){
			i--;
		}
		else if (dp[i][j]-map[i][j]== dp[i][j - 1]){
			j--;
		}
	}
	printf("(%d，%d)\n", j, i);

	return dp[n - 1][m - 1];
}
int Min(int a, int b){
	if (a>b){
		return b;
	}
	else{
		return a;
	}
}

int getMax(int map[4][4], int n, int m) {
	int dp[4][4] = { 0 };
	int i, j;
	for (i = 0; i<n; i++){  //第一行初始化，一直向右走
		for (j = 0; j <= i; j++){
			dp[i][0] += map[j][0];
		}
	}
	for (i = 1; i<m; i++){  //第一列初始化，一直向下走；如i=0，则dp[0][0]会计算两次。
		for (j = 0; j <= i; j++){
			dp[0][i] += map[0][j];
		}
	}
	for (i = 1; i<n; i++){
		for (j = 1; j<m; j++){
			dp[i][j] = Max(dp[i][j - 1] + map[i][j], dp[i - 1][j] + map[i][j]);
		}
	}
printf("最大权重数组为：\n");
	for (i = 0; i<n; i++){
		for (j = 0; j<m; j++){
			printf("%4d", dp[i][j]);
		}
		printf("\n");
	}
	printf("最大权重路径为：\n");
	i = 3; j = 3;
	while (i != 0 || j != 0){  //反向查询路径，可用栈存储，出栈即为正向路径
		printf("(%d，%d)", j, i);
		printf("<-");
		if (dp[i][j]-map[i][j]== dp[i - 1][j]){
			i--;
		}else if (dp[i][j]-map[i][j]== dp[i][j - 1]){
			j--;
		}
	}
	printf("(%d，%d)\n", j, i);

	return dp[n - 1][m - 1];
}
int Max(int a, int b){
	if (a>b){
		return a;
	}
	else{
		return b;
	}
}
