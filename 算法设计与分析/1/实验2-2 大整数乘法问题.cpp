#include <math.h>
#include <tchar.h>
#include<iostream>
using namespace std;

//十进制的
/* 
int IntegerMultiply(int x, int y, int N)
{
		
	if ((0 == x) || (0 == y))
		return 0;
	if (1 == N)
		return x*y;
	else
	{
		int a = x / (int)pow(10., (int)N / 2);
		int b = x - a * (int)pow(10., N / 2);
		int c = y / (int)pow(10., (int)N / 2);
		int d = y - c * (int)pow(10., N / 2);

		int ac = IntegerMultiply(a, c, N/2);
		int bd = IntegerMultiply(b, d, N/2);
		int ambdmc = IntegerMultiply(a-b, d-c, N/2) + ac + bd;
		return (ac * (int)pow(10., N) + ambdmc * (int)pow(10., N / 2) + bd);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int x = 2304;
	int y = 1520;
	
	cout << "x * y = " << IntegerMultiply(x, y, 4) << endl;
	cout << "x * y = " << x*y << endl;
	
	x = 1234;
	y = 6789;
	cout << "x * y = " << IntegerMultiply(x, y, 4) << endl;
	cout << "x * y = " << x*y << endl;
	 
	system("pause");
	return 0;
}
*/

//二进制的
int IntegerMultiply(int x, int y, int N)
{
		
	if ((0 == x) || (0 == y))
		return 0;
	if (1 == N)
		return x*y;
	else
	{
		int a = x / pow(10, N / 2);
		int b = x - a * pow(10, N / 2);
		int c = y / pow(10, N / 2);
		int d = y - c * pow(10, N / 2);

		int ac = IntegerMultiply(a, c, N/2);
		int bd = IntegerMultiply(b, d, N/2);
		int ambdmc = IntegerMultiply(a-b, d-c, N/2) + ac + bd;
		return (ac * pow(2, N) + ambdmc * pow(2, N / 2) + bd);
	}
}

int bToD(int x)
{
	int i = 0, sum = 0;
	while(x > 0){
		int b = x % 10;
		sum += b * pow(2, i);
		i ++;
		x /= 10;
	
	}
	return sum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int x = 1101;
	int y = 1010;
	
	cout << "x * y = " << IntegerMultiply(x, y, 4) << endl;
	
	int x1 = bToD(x);
	int y1 = bToD(y);
	cout << "x1 * y1 = " << x1*y1 << endl;
	
	 
	system("pause");
	return 0;
}
