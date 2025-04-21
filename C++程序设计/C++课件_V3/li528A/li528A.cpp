// li528A.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Figure {
public:
	Figure( double a, double b )
	{
		x = a;
		y = b;
	}
	virtual void area()
	{
		cout << "基类的虚函数" << endl;
	}
protected:
	double x, y;
};

class Triangle:public Figure{
public:
	Triangle( double a, double b) : Figure( a, b)
	{
	}
	void area()
	{
		cout << "三角形的高是 " << x << "，底是 " << y;
		cout << "，面积是 " << 0.5 * x * y << endl;
	}
};

class Square:public Figure{
public:
	Square( double a, double b) : Figure( a, b)
	{
	}
	void area()
	{
		cout << "矩形的长是 " << x << "，  宽是 " << y;
		cout << "，面积是 " << x * y << endl;
	}
};

int main(int argc, char* argv[])
{
	Figure *p;
	Triangle t( 10.0, 6.0 );
	Square s( 10.0, 6.0 );

	p = &t;
	p->area();

	p = &s;
	p->area();
	return 0;
}
