// lie717.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Complex{
public:
	Complex( double r, double i)
	{
		real = r;
		imag = i;
	}
	Complex()
	{
		real = 0;
		imag = 0;
	}
	friend Complex operator+(Complex, Complex);
	friend ostream &operator<<(ostream &, Complex &);
	friend istream &operator>>(istream &, Complex &);
private:
	double real, imag;
};

Complex operator+(Complex a, Complex b)
{
	Complex temp;

	temp.real = a.real + b.real;
	temp.imag = a.imag + b.imag;
	
	return temp;
}

ostream &operator<<(ostream &output, Complex &obj)
{
	output<< obj.real;
	if(obj.imag > 0)
		output << " + ";
	if( obj.imag != 0)
		output<< obj.imag << "i";
	return output;
}

istream &operator>>(istream &input, Complex &obj)
{
	cout<<"请输入复数实部和虚部的值："<< endl;

	input>>obj.real;
	input>>obj.imag;

	return input;
}

int main(int argc, char* argv[])
{
	Complex c1(2.4, 4.6), c2, c3;

	cout<< "复数 c1 的值是：" << c1 << endl;

	cin>> c2;
	cout<< "复数 c2 的值是：" << c2 << endl;

	c3 = c1 + c2;
	cout<< "复数 c3	(c3 = c1 + c2) 的值是：" << c3 << endl;

	return 0;
}
