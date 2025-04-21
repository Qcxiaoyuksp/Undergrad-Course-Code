// li56.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Coord {
public:
	Coord( int i = 0, int j = 0 );
	void print();
	Coord operator ++();
private:
	int x, y;
};
Coord::Coord( int i, int j )
{
	x = i;
	y = j;
}
void Coord::print()
{
	cout << "x: " << x << ", y: " << y << endl;
}
Coord Coord::operator ++()
{
	++x;
	++y;
	return *this;
}

int main(int argc, char* argv[])
{
	Coord ob( 10, 20 );
	ob.print();
	++ob;
	ob.print();
	ob.operator ++();
	ob.print();
	return 0;
}

