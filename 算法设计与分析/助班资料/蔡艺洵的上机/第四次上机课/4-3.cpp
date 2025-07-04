#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
	int maxSubArray(vector<int>& nums,int *begin, int *end) {
		int result = 0;
		int sum = 0;

		*begin = 0;
		for (int i = 0; i < nums.size(); i++) {
			sum += nums[i];
			if (sum > result) { // 取区间累计的最大值（相当于不断确定最大子序终止位置）
				result = sum;
				*end=i;
			}
			if (sum <= 0) {
				sum = 0; // 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
				*begin=i+1;//起始位置从下一个数开始 
			}
		}
		return result;
	}
};


int main() {
	int ans;
	Solution solution;
	
	vector<int> a = {1};
	int begin=0, end=0;
	

	ans=solution.maxSubArray(a,&begin,&end);
	cout << "最大和为：" ;
	cout << ans << endl;
	cout << "起止位置为：";
	cout << begin << "," << end << endl;
	system("PAUSE");
	return 0;
}
