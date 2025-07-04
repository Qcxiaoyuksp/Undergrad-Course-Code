/*编辑距离*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
	int min3(int a, int b, int c){
		int m=a;
		if (m > b)
			m = b;
		if (m > c)
			m = c;
		return m;
	}
	vector<vector<int>> minEditDistance(string s, string t, vector<vector<int>> dp) {
		vector<vector<int>> rec(s.size() + 1, vector<int>(t.size() + 1, 0));
		//初始化两个数组
		for (int i = 0; i <= s.size(); i++) dp[i][0] = i ;
		for (int j = 0; j <= t.size(); j++) dp[0][j] = j ;
		//rec数组 取1表示U，dp[i][j]由dp[i-1][j]获得，即上侧U。
		//rec数组 取-1表示L，dp[i][j]由dp[i][j-1]获得，即左侧L。
		//rec数组 取0表示LU，dp[i][j]由dp[i-1][j-1]获得，即左上LU。
		rec[0][0] = 0;
		for (int i = 1; i <= s.size(); i++) rec[i][0] = 1 ;
		for (int j = 1; j <= t.size(); j++) rec[0][j] = -1 ;

		for (int i = 1; i < s.size(); i++) {
			for (int j = 1; j < t.size(); j++) {
				int c = 0;
				if (s[i] != t[j]) c = 1;
				int replaceO = dp[i - 1][j - 1] + c;
				int deleteO = dp[i - 1][j] + 1;
				int insertO = dp[i][j - 1] + 1;
				//替换操作
				if (replaceO == min3(deleteO, insertO, replaceO)){
                	dp[i][j] = dp[i - 1][j - 1] + c ;
					rec[i][j] = 0 ;   //左上LU
				}
				//插入操作
				else if (insertO == min3(deleteO, insertO, replaceO)){
					dp[i][j] = dp[i][j - 1] + 1;
					rec[i][j] = -1 ;   //左L
				}
				//删除操作
				else{
					dp[i][j] =dp[i - 1][j] + 1;
					rec[i][j] = 1 ;   //上U
				}
			}
		}
		//打印dp数组
		cout << "dp数组:" << endl;
		for (int i = 0; i < s.size() ; i++){
			for (int j = 0; j < t.size() ; j++){
				cout << "dp[i][j] = " << dp[i][j]  << ",";
			}
			cout << endl;
		}

		return rec;
	}
	//追踪最优解操作序列，递归函数后正序输出操作序列
	void PrintMED(vector<vector<int>> rec, string s, string t, int i, int j)
	{
		if (i == 0 && j == 0)
			return ;
		if (rec[i][j] == 0)
		{
			PrintMED(rec, s, t, i - 1 , j - 1 );//
			if (s[i] == t[j])
			   printf("无操作\n");//
			else
				printf("用%c替换%c\n", t[j], s[i]);//
		}
		else if (rec[i][j] == 1){
            PrintMED(rec, s, t, i - 1 ,j );
			printf("删除%c\n", s[i] );//
		}
			
		else{
            PrintMED(rec, s,t, i , j - 1 );
			printf("插入%c\n", s[j]);//
		}
	}
};


int main() {
	
	Solution solution;
	//string s = " ABCBDAB";
	//string t = " BDCABA";
	string s = " ABCDAB";
	string t = " DCABA";
	vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
	vector<vector<int>> rec(s.size() + 1, vector<int>(t.size() + 1, 0));
	rec = solution.minEditDistance(s, t, dp);
	cout << endl;
	//打印追踪数组rec
	cout << "rec数组:" << endl;
	for (int i = 0; i < s.size() ; i++){
		for (int j = 0; j < t.size() ; j++){
			cout << "rec[i][j] = " << rec[i][j]  << ",";
		}
		cout <<  endl;
	}

	solution.PrintMED(rec, s, t, s.size()-1, t.size()-1);

	system("PAUSE");
	return 0;
}

