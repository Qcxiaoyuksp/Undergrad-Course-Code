// li327.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Point {
private:
	int x, y;
public:
	Point( int a = 0, int b = 0 );
	Point( const Point &p);
	void print(){
		cout << x << "  " << y << endl;
	}
};
Point::Point( int a, int b )
{
	x = a;
	y = b;
	cout << "Using normal constructor" << endl;
}
Point::Point( const Point &p)
{
	x = 2 * p.x;
	y = 2 * p.y;
	cout << "Using copy constructor" << endl;
}

void fun1( Point p )
{
	p.print();
}

Point fun2()
{
	Point p4( 10, 30 );
	return p4;
}

int main(int argc, char* argv[])
{
	Point p1( 30, 40 );
	p1.print();
	Point p2( p1 );

	p2.print();
	Point p3 = p1;

	p3.print();
	fun1( p1 );
	p2 = fun2();

	p2.print();
	return 0;
}

