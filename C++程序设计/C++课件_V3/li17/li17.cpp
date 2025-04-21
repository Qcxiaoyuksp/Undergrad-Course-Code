// li17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
class Complex {
public:
	Complex( double r = 0, double i = 0 )
	{
		real = r;
		imag = i;
	}
	operator double()
	{
		return real;
	}
	operator int()
	{
		return int( real );
	}
private:
	double real, imag;
};

int main(int argc, char* argv[])
{
	Complex com1( 22.2, 4.4 );
	cout << "Complex类的对象com1转换成double型的数据为：";
	cout << double( com1 ) << endl;

	Complex com2( 66.6, 4.4 );
	cout << "Complex类的对象com2转换成int型的数据为：";
	cout << int( com2 ) << endl;

	return 0;
}

