// li55Complex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Complex {
public:
	Complex( double r = 0.0, double i = 0.0 );
	void print();
	Complex operator+( Complex c );
	Complex operator-( Complex c );
	Complex operator*( Complex c );
	Complex operator/( Complex c );
private:
	double real;
	double imag;
};
Complex::Complex( double r, double i )
{
	real = r;
	imag = i;
}
Complex Complex::operator+( Complex c )
{
	Complex temp;
	temp.real = real + c.real;
	temp.imag = imag + c.imag;
	return temp;
}
Complex Complex::operator-( Complex c )
{
	Complex temp;
	temp.real = real - c.real;
	temp.imag = imag - c.imag;
	return temp;
}
Complex Complex::operator*( Complex c )
{
	Complex temp;
	temp.real = real * c.real - imag * c.imag;
	temp.imag = real * c.imag + imag * c.real ;
	return temp;
}
Complex Complex::operator/( Complex c )
{
	Complex temp;
	double t;
	t = 1 / ( c.real * c.real + c.imag * c.imag);
	temp.real = ( real * c.real + imag * c.imag ) * t;
	temp.imag = ( imag * c.real - real * c.imag ) * t;
	return temp;
}
void Complex::print()
{
	cout << real;
	if( imag > 0 )
		cout << " + ";
	if( imag != 0 )
		cout << imag << 'i' << endl;
}

int main(int argc, char* argv[])
{
	Complex A1( 2.3, 4.6 ), A2( 3.6, 2.8 ), A3, A4, A5, A6;
	A3 = A1 + A2;
	A4 = A1 - A2;
	A5 = A1 * A2;
	A6 = A1 / A2;
	A1.print();
	A2.print();
	A3.print();
	A4.print();
	A5.print();
	A6.print();

	return 0;
}

