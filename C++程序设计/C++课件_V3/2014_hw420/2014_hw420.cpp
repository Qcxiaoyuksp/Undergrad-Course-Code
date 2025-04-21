// 2014_hw420.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class area_c1 {
protected:
	double height;
	double width;
public:
	area_c1(double r, double s)
	{
		height = r;
		width = s;
	}
	virtual double area() = 0;
};

class rectangle: public area_c1 {
public:
	rectangle( double r, double s ): area_c1(r, s)
	{
	}
	double area( )
	{
		return height * width;
	}
};

class isosceles: public area_c1 {
public:
	isosceles( double r, double s ): area_c1(r, s)
	{
	}
	double area( )
	{
		return height * width / 2;
	}
};


int main(int argc, char* argv[])
{
	double area;

	area_c1 *p;
	rectangle r( 10.0, 5.0 );
	isosceles i( 4.0, 6.0 );

	p = &r;
	area = p->area();
	cout << "矩形面积" << area << endl;

	p = &i;
	area = p->area();
	cout << "三角形面积" << area << endl;

	return 0;
}
