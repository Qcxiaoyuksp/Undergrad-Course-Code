// li51_complex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Complex {
	double real;
	double imag;
public:
	Complex( double r = 0, double i = 0 )
	{
		real = r;
		imag = i;
	}
	void print( )
	{
		cout << "real = " << real << ", imag = " << imag << endl;
	}
	Complex operator+( Complex );
};
Complex Complex::operator+( Complex c )
{
	Complex temp;
	temp.real = real + c.real;
	temp.imag = imag + c.imag;

	return temp;
}

int main(int argc, char* argv[])
{
	Complex c1( 1.0, 2.0 ), c2( 3.0, 4.0 ), t;

	t = c1 + c2;
	t.print();

	t = c1.operator+( c2 );
	t.print();

	return 0;
}

