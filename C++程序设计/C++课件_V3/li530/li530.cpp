// li530.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Shape {
public:
	Shape( double x )
	{
		r = x;
	}
	virtual void area() = 0;
	virtual void perimeter() = 0;
protected:
	double r;
};

class Circle: public Shape {
public:
	Circle( double x ): Shape( x )
	{
	}
	void area()
	{
		cout << "这个圆的面积是：" << 3.14 * r * r << endl;
	}
	void perimeter()
	{
		cout << "这个圆的周长是：" << 2 * 3.14 * r << endl;
	}
};

class In_square: public Shape {
public:
	In_square( double x ): Shape( x )
	{
	}
	void area()
	{
		cout << "这个圆内接正方形的面积是：" << 2 * r * r << endl;
	}
	void perimeter()
	{
		cout << "这个圆内接正方形的周长是：" << 4 * 1.414 * r << endl;
	}
};

class Ex_square: public Shape {
public:
	Ex_square( double x ): Shape( x )
	{
	}
	void area()
	{
		cout << "这个圆外切正方形的面积是：" << 4 * r * r << endl;
	}
	void perimeter()
	{
		cout << "这个圆外切正方形的周长是：" << 8 * r << endl;
	}
};


int main(int argc, char* argv[])
{
	Shape *ptr;

	Circle ob1( 5 );
	In_square ob2( 5 );
	Ex_square ob3( 5 );

	ptr = &ob1;
	ptr->area();
	ptr->perimeter();

	ptr = &ob2;
	ptr->area();
	ptr->perimeter();

	ptr = &ob3;
	ptr->area();
	ptr->perimeter();

	return 0;
}
