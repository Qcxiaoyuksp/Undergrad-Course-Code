/**
随机化算法 用随机投点法计算定积分
*/

#define _CRT_SECURE_NO_WARNINGS

#include "iostream"
#include "ctime"
#include "iomanip"

using namespace std;

const unsigned long maxshort = 65536L;
const unsigned long multiplier = 1194211693L;
const unsigned long adder = 12345L;

class RandomNumber
{
private:
	unsigned long randSeed;  //当前种子
public:
	RandomNumber(unsigned long s = 0);  //构造函数，默认值0表示由系统自动产生种子
	unsigned short Random(unsigned long n);  //产生0:n-1之间的随机整数
	double fRandom(void);  //产生[0:1)之间的随机实数
};

RandomNumber::RandomNumber(unsigned long s)  //产生种子
{
	if (s == 0)
		randSeed = time(0);   //用系统时间产生种子 
	else
		randSeed = s;     //用户提供种子
}

unsigned short RandomNumber::Random(unsigned long n)  //产生0:n-1之间的随机整数
{
	randSeed = multiplier * randSeed + adder;
	return (unsigned short)((randSeed >> 16) % n);  //高16位随机性较好，右移16位后，映射到（0~n-1）范围内
}

double RandomNumber::fRandom(void)  //产生[0,1)之间的随机整数
{
	return Random(maxshort) / double(maxshort);  //产生0~(maxshort-1)间的随机整数，在除以maxshort
}

double Darts(int n, double a, double b);
double f(double x);

int main()
{
	double a = 1.0, b = 3.0;
	double integral;
	long num = 100;
    printf("用随机投点法计算定积分\n");
	//printf("f(x)=x*x,范围[0,1],真值为\n");
	printf("f(x)=1/3*x*x*x,范围[1,3],真值为\n");
	for (int i = 1; i < 7; i++){
		integral = Darts(num,a,b);
		printf("随机投掷%d个点时，", num);
		printf("定积分=%f\n", integral);
		num = num * 10;
	}

	system("PAUSE");
	return 0;
}
/*
* 基本思想是在矩形区域内随机均匀投点，求出由这些点
* 产生的函数值的算术平均值，再乘以区间宽度，即可得
* 出定积分的近似解
*/
double Darts(int n, double a, double b)
{
	static RandomNumber dart;
	double sum = 0.0;
	for (int i = 0; i<n; i++)
	{
		double x = (b - a)*dart.fRandom()+ a;//产生[a,b)之间的随机数
		sum = sum + f(x);
	}
	return (b - a)*sum / n;
}

double f(double x)
{
	//return x*x;
	return ((double)1/3)*x*x*x;
}
