/**
回溯法-旅行商(TSP)问题
输入
4
0 30 6 4
30 0 5 10
6 5 0 20
4 10 20 0
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#define MAX 100
using  namespace std;

//问题表示
int sum=0;
int n;                               //城市个数
int a[MAX][MAX];                   //城市间距离,邻接矩阵，0表示不通
//求解结果表示
int x[MAX];                       //记录路径
int bestx[MAX] = { 0 };           //记录最优路径
int bestp = 63355;              //最短路径长
int cp = 0;                    //当前路径长

void backtrack(int t){
	if (t>n){//得到一个解 
		sum++; 
		if ((a[x[n]][1]) && (a[x[n]][1] + cp<bestp)){
			bestp =a[x[n]][1]+cp;
			for (int i = 1; i <= n; i++){
				bestx[i] =x[i];
			}
		}
	}
	else{
		for (int i = t; i <= n; i++){
			sum++;
			/*约束为当前节点到下一节点的长度不为0,限界为走过的长度+当前要走的长度之和小于最优长度*/
			if ((a[x[t - 1]][x[i]]) && (cp + a[x[t - 1]][x[i]]<bestp)){
				swap(x[t], x[i]);
				cp +=a[x[t-1]][x[t]];
				backtrack(t + 1);
				cp -= a[x[t-1]][x[t]];
				swap(x[t], x[i]);
			}
		}
	}
}
int main(){
	cout << "输入城市个数:" << endl;
	cin >> n;      //顶点数
	for (int i = 1; i <= n; i++){
		x[i] = i;
	}
	cout << "输入城市之间的距离(0表示城市间不通):" << endl;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			cin >> a[i][j];
		}
	}
	backtrack(2);
	cout << "最少旅行费用为: " << bestp << endl;
	cout << "旅行路径为:" << endl;
	for (int i = 1; i <= n; i++){
		cout << bestx[i] << " ";
	}
	cout << bestx[1]<<endl;
	cout << "解空间下的结点总数为:" <<sum--<< endl;
	cout << "解空间下的分支总数为:" <<sum<< endl;
	system("PAUSE");
	return 0;
}
