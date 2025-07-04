/*nQueen随机放置位置策略和回溯法相结合求解n皇后问题.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include<math.h> 
#include<time.h>

using namespace std;
//利用线性同余法产生的伪随机数 
const unsigned long maxshort = 65536;
const unsigned long multipliter = 1194211693L;
const unsigned adder = 12345L;
class RandomNumber{
private:
	unsigned long randSeed;
public:
	RandomNumber(unsigned long s = 0);
	unsigned short Random(unsigned long n);
	double fRandom(void);
};
RandomNumber::RandomNumber(unsigned long s){
	if (s == 0)
		randSeed = time(0);
	else
		randSeed = s;
}
unsigned short RandomNumber::Random(unsigned long n){
	randSeed = multipliter*randSeed + adder;
	return (unsigned short)((randSeed >> 16) % n);
}
double RandomNumber::fRandom(void){
	return Random(maxshort) / double(maxshort);
}


class Queen{
	friend bool nQueen(int);
private:
	bool Place(int k);
	bool Backtrack(int t);
	bool QueensLV(int stop);
	int n, *x, *y;
};
bool Queen::Place(int k){   //测试皇后k置于第x[k]列的合法性 
	for (int j = 1; j<k; j++)
	if ((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
		return false;
	return true;
}
bool Queen::Backtrack(int t){
	if (t>n){
		for (int i = 1; i <= n; i++)
			y[i] = x[i];
		return true;
	}
	else{
		for (int i = 1; i <= n; i++){
			x[t] = i;
			if (Place(t) && Backtrack(t + 1))
				return true;
		}
	}
	return false;
}
bool Queen::QueensLV(int stop){//随机放置n个皇后的拉斯维斯加算法 	
	RandomNumber rnd;    // 随机数产生器
	int k = 1;               //下一个放置的皇后的编号 
	int count = 1;
	while ((k <=stop) && (count>0)){
		count = 0;
		for (int i = 1; i <= n; i++){//遍历第k行所有可以放置的列号，用y保存，并用count记录有多少个位置可以放置
			x[k] = i;
			if (Place(k))
				y[count++] = i;
		}
		if (count>0)    //利用上面保存的可以放置的列，然后随机取其中一列来放置第k行的皇后。是Las Vegas思想			
			x[k++] = y[rnd.Random(count)];//随机位置 
	}
	return (count>0); //count>0表示放置成功	
}

bool nQueen(int n){
	Queen X;
	X.n = n;
	int *p = new int[n + 1];
	int *q = new int[n + 1];
	for (int i = 0; i <= n; i++){
		p[i] = 0;
		q[i] = 0;
	}
	X.y = p;
	X.x = q;
	// 设置随机放置皇后的个数
	int stop = 7;
	if (n>15)
		stop = n - 15;
	bool found = false;
	while (!X.QueensLV(stop));
	// 算法的回溯搜索部分
	if (X.Backtrack(stop + 1)){
		for (int i = 1; i <= n; i++)
			cout << p[i] << " ";
		found = true;
	}
	cout << endl;
	delete[] p;
	delete[] q;
	return found;
}
int  main(){
	int n = 14;
	int k=1;
	
	cout << n << "皇后问题的解为（随机放置的皇后数为7）：" << endl;
	while (!nQueen(n)){
		k++;
	}

    cout << "运行的次数为：" << k << endl;
	system("PAUSE");
	return 0;
}


