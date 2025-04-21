// hw315.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class A {
	int x, y;
public:
	void set( int i, int j )
	{
		x = i;
		y = j;
		cout << "A::x = " << x << "  A::y = " << y << endl;
	}
	int get_y()
	{
		return y;
	}
};

class box {
	int length, width;
	A lable;
public:
	void set( int l, int w, int s, int p )
	{
		length = l;
		width = w;
		lable.set( s, p );
	}
	int get_area()
	{
		return length * width ;
	}
};

int main(int argc, char* argv[])
{
	box b;
	b.set( 4, 6, 1, 20 );
	cout << b.get_area() << endl;
	return 0;
}

