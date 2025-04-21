// li52_complex.cpp : Defines the entry point for the console application.
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
	friend Complex operator+( Complex& a, Complex& b );
};
Complex operator+( Complex& a, Complex& b )
{
	Complex temp;
	temp.real = a.real + b.real;
	temp.imag = a.imag + b.imag;

	return temp;
}

int main(int argc, char* argv[])
{
	Complex c1( 1.0, 2.0 ), c2( 3.0, 4.0 ), t;

	t = c1 + c2;
	t.print();

	return 0;
}

