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
	cout << "Complex��Ķ���com1ת����double�͵�����Ϊ��";
	cout << double( com1 ) << endl;

	Complex com2( 66.6, 4.4 );
	cout << "Complex��Ķ���com2ת����int�͵�����Ϊ��";
	cout << int( com2 ) << endl;

	return 0;
}

