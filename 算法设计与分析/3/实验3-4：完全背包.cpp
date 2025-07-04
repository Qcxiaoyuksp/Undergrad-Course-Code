#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void completeKnapsack();

int main() {
	completeKnapsack();
	system("PAUSE");
	return 0;
}

void completeKnapsack()
{
	//vector<int> weight = { 1, 2, 3, 5 };
	//vector<int> profit = { 1, 6, 10, 16 };
	//int c = 7;//背包容量
	vector<int> weight = {1, 2, 3, 4};
	vector<int> profit = {1, 9, 6, 16};
	int c = 6;
	vector<int> dp(c + 1, 0);
	vector<int> rec(c + 1, 0);
	for (int i = 0; i < weight.size(); i++) { // 遍历物品
        cout << "i=" << i <<" ";
		for (int j = 1; j <= c; j++) { // 遍历背包容量
			if (j < weight[i]) 
			{
				dp[j] = dp[j];
				rec[j] = 0;
			}				
			else  
			{
				//dp[j] = max(dp[j], dp[j - weight[i]] + profit[i]);
				if (dp[j] > dp[j - weight[i]] + profit[i])
				{
					dp[j] = dp[j];
					rec[j] = 0;
				}					
				else 
				{
					dp[j] = dp[j - weight[i]] + profit[i];
					rec[j] = 1;
				}
			}	
				
			cout << "dp[" << j << "]=" << dp[j] << " rec[" << j << "]=" << rec[j] << "\t";
			//cout << "j=" << j << " rec[j]=" << rec[j] << "\t";
		}
		cout << endl;
	}
	cout << "最大价值总和：" << endl;
	cout << dp[c] << endl;
}

