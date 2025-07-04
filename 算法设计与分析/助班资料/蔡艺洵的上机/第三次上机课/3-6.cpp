#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

//int max(int a,int b){
//	if(a>b)
//		return a;
//	else
//		return b;
//}

class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		if (nums.size() == 0) return 0;
		vector<int> dp(nums.size());
		vector<int> rec(nums.size());
		dp[0] = nums[0];
		rec[0]=0;
		int result =0;
		for (int i = 1; i < nums.size(); i++) {
			if(dp[i - 1] + nums[i]>nums[i]){
				dp[i] =dp[i - 1] + nums[i];
				rec[i]=rec[i-1];
			}
			else{
				dp[i] =nums[i];
				rec[i]=i;
			}
			//dp[i] = max(dp[i - 1] + nums[i], nums[i]); // 状态转移公式
			if (dp[i] > dp[result]) result =i; // result 保存dp[i]的最大值的下标 
		}
		for(int i=0;i<nums.size();i++){
			printf("dp[%d]:%d\n",i,dp[i]);
		}
		printf("子段下标范围为：%d-%d\n",rec[result],result);
		printf("子段范围为：");
		for(int i=rec[result];i<=result;i++){
			printf("%d  ",nums[i]);
		}
		printf("\n");
		return dp[result];
	}
};


int main() {
	int ans;
	Solution solution;
	
	vector<int> a;
	a.push_back(-3);a.push_back(2);a.push_back(-1);a.push_back(5);a.push_back(2);
	a.push_back(-1);a.push_back(4);a.push_back(-3);a.push_back(2);
	ans=solution.maxSubArray(a);
	cout << "最大和为：" ;
	cout << ans << endl;
	system("PAUSE");
	return 0;
}
