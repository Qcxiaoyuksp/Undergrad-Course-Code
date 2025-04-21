// Li411.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class A {
public:
	A( int x1 )
	{
		x = x1;
	}
	void print()
	{
		cout << "x = " << x << endl;
	}
private:
	int x;
};

class B : private A {
public:
	B( int x1, int y1 ) : A ( x1 )
	{
		y = y1;
	}
	void print2()
	{
		print();
	}
private:
	int y;
};

int main(int argc, char* argv[])
{
	B b( 10, 20 );
	b.print2();

	return 0;
}

