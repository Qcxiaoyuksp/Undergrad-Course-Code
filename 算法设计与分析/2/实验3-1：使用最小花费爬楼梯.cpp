/**
 *  使用最小花费爬楼梯，增肌了轨迹输出。
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> rec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

class Solution {
public:
	int minCostClimbingStairs(vector<int>& cost) {
		vector<int> dp(cost.size());
		dp[0] = cost[0];
		dp[1] = cost[1];
		int m;
		for (int i = 2; i < cost.size(); i++) {
			//dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
			if (dp[i - 1] < dp[i - 2]){
    			dp[i] = dp[i - 1] + cost[i];
    			rec[i] = i - 1;
   			}
   			else{
    			dp[i] = dp[i - 2] + cost[i];
    			rec[i] = i - 2;
   			}
		}
		
		/*
		for(int i = rec.size() - 1; i >= 0; i --){
			for(int j = i; j >= 0; j --){
				if(dp[i] - cost[i] == dp[j]){
					m = j;
					break;
				}
			}
			rec[i] = m;	
		}
		*/
		
		// 注意最后一步可以理解为不用花费，所以取倒数第一步，第二步的最少值
		return min(dp[cost.size() - 1], dp[cost.size() - 2]);
	}
};



int main()
{
	vector<int> cost = { 1, 80, 2, 1, 90, 1, 2, 1, 100, 1 };
	//vector<int> cost = { 1, 80, 1, 2, 1, 90, 1, 1, 100, 1 };
	//vector<int> rec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Solution solution;

	cout << solution.minCostClimbingStairs(cost) << endl;
	
	for (int i = 0; i < rec.size(); i++){
		cout << rec[i] << " ";
	}
	cout << endl;
	cout << "轨迹是：" ;
	for(int i = rec.size() - 1; i > 0; i = rec[i]){
		printf("%d ", i);
	
	}
	cout << "0" ;
	
	printf("\n");
	system("PAUSE");
	return 0;
}

