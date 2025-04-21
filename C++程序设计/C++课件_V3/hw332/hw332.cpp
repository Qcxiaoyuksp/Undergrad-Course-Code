// hw332.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class cylinder {
private:
	double r, h;
public:
	cylinder( double r1 = 0, double h1 = 0 )
	{
		r = r1;
		h = h1;
	}
	double vol()
	{
		return ( 3.14 * r * r * h );
	}
};

int main(int argc, char* argv[])
{
	cylinder c1(3, 5), c2;
	cout << "r = 3 and h = 5" << "    vol of c1 = " << c1.vol() << endl;

	cout << "r = 0 and h = 0" << "    vol of c2 = " << c2.vol() << endl;
	
	return 0;
}

