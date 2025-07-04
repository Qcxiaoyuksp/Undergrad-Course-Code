#include <math.h>
#include <tchar.h>
#include<iostream>
using namespace std;

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

		int ac = IntegerMultiply(a,c,N / 2);
		int bd = IntegerMultiply(b,d,N / 2);
		int ambdmc = IntegerMultiply(a-b,d-c,N / 2) + ac + bd;
		return (ac * (int)pow(10., N) + ambdmc * (int)pow(10., N / 2) + bd);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int x = 2304;//输入值 
	int y = 1520;//输入值 
	cout << "x * y = " << IntegerMultiply(x, y, 4) << endl;
	cout << "x * y = " << x*y << endl;
	x=1101;y=1010;
	cout << "x * y = " << IntegerMultiply(x, y, 4) << endl;
	cout << "x * y = " << x*y << endl;
	x=1234;y=4321;
	cout << "x * y = " << IntegerMultiply(x, y, 4) << endl;
	cout << "x * y = " << x*y << endl;
	system("pause");
	return 0;
}
