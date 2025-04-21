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
		cout << "���Բ������ǣ�" << 3.14 * r * r << endl;
	}
	void perimeter()
	{
		cout << "���Բ���ܳ��ǣ�" << 2 * 3.14 * r << endl;
	}
};

class In_square: public Shape {
public:
	In_square( double x ): Shape( x )
	{
	}
	void area()
	{
		cout << "���Բ�ڽ������ε�����ǣ�" << 2 * r * r << endl;
	}
	void perimeter()
	{
		cout << "���Բ�ڽ������ε��ܳ��ǣ�" << 4 * 1.414 * r << endl;
	}
};

class Ex_square: public Shape {
public:
	Ex_square( double x ): Shape( x )
	{
	}
	void area()
	{
		cout << "���Բ���������ε�����ǣ�" << 4 * r * r << endl;
	}
	void perimeter()
	{
		cout << "���Բ���������ε��ܳ��ǣ�" << 8 * r << endl;
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
