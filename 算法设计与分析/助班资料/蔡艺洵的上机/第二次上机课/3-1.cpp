/**
 *  使用最小花费爬楼梯，增加了轨迹输出。
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int min(int a,int b){
		if(a<b)
			return a;
		else
			return b;
	}
 int minCostClimbingStairs(vector<int>& cost, vector<int>& rec) {
  vector<int> dp(cost.size());
  dp[0] = cost[0];
  dp[1] = cost[1];
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
  // 注意最后一步可以理解为不用花费，所以取倒数第一步，第二步的最少值
return min(dp[cost.size() - 1], dp[cost.size() - 2]);
 }
};

int main()
{
vector<int> cost;
//cost.push_back(1);cost.push_back(80);
//cost.push_back(1);cost.push_back(2);
//cost.push_back(1);cost.push_back(90);
//cost.push_back(1);cost.push_back(1);
//cost.push_back(100);cost.push_back(1);
 cost.push_back(1);cost.push_back(2);
 cost.push_back(1);cost.push_back(3);
 cost.push_back(6);cost.push_back(9);
 cost.push_back(1);cost.push_back(1);
 cost.push_back(10);cost.push_back(10);
 cost.push_back(2);cost.push_back(1);
vector<int> rec;
 for(int k=0;k<12;k++){
	 rec.push_back(0);
 } Solution solution;

 cout << solution.minCostClimbingStairs(cost,rec) << endl;
 for (int i = 0; i < rec.size(); i++){
  cout << rec[i] << " ";
 }
 cout << endl;
 cout << "轨迹是：" ;
 int j = rec.size()-1;
 cout << j << " ";
 while ( j!= 0){
 cout << rec[j] << " ";
 j = rec[j];       
 }
 printf("\n");
 system("PAUSE");
 return 0;
}
