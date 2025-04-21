// li57.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Complex{
public:
	Complex( int real1 = 0, int imag1 = 0 );
	friend Complex operator +( Complex com, int a )
	{
		return Complex( com.real + a, com.imag );
	}
	friend  Complex operator +( int a, Complex com )
	{
		return Complex( a + com.real, com.imag );
	} 
	void show();
private:
	int real, imag;
};
Complex::Complex( int real1, int imag1 )
{
	real = real1;
	imag = imag1;
}
void Complex::show()
{
	cout << "real = " << real << "  imag = " <<imag << endl;
}

int main(int argc, char* argv[])
{
	Complex com1( 30, 40 ), com2;
	com2 = com1 + 30;
	com2.show();
	com2 = 50 + com1;
	com2.show();
	return 0;
}

