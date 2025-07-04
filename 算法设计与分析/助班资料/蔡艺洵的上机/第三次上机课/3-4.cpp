#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void completeKnapsack();

int max(int a,int b){
	if(a>b)
		return a;
	else
		return b;
}

int main() {
	completeKnapsack();
	system("PAUSE");
	return 0;
}

void completeKnapsack()
{
	vector<int> weight;
	vector<int> profit;
	weight.push_back(1);weight.push_back(2);weight.push_back(3);weight.push_back(5);
	profit.push_back(1);profit.push_back(6);profit.push_back(10);profit.push_back(16);
	int c = 7;//背包容量
	vector<int> dp(c + 1, 0);
	for (int i = 0; i < weight.size(); i++) { // 遍历物品
         cout << "i=" << i <<" ";
		 for (int j = 1; j <= c; j++) { // 遍历背包容量
			 if (j < weight[i]) 
				 dp[j] = dp[j];
			 else  	
				 dp[j] = max(dp[j], dp[j - weight[i]] + profit[i]);
			cout << "j=" << j << "dp[j]=" << dp[j] << " ";
		}
		cout << endl;
	}
	cout << dp[c] << endl;
}
