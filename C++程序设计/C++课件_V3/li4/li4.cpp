// li4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Coord {
public:
	Coord( int i = 0, int j = 0 )
	{
		x = i;
		y = j;
	}
	void print()
	{
		cout << "x: " << x << ", y: " << y << endl;
	}
	friend Coord operator++ ( Coord &op )
	{
		++op.x;
		++op.y;
		return op;
	}
/*	friend Coord operator++ ( Coord op )
	{
		++op.x;
		++op.y;
		return op;
	}
*/
private:
	int x, y;
};

int main(int argc, char* argv[])
{
	Coord ob( 10, 20 );
	ob.print();
	++ob;
	ob.print();
	operator++( ob );
	ob.print();
	return 0;
}

