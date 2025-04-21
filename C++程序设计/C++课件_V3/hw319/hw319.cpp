// hw319.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class example {
	int i;
public:
	example( int n )
	{
		i = n;
		cout << "Constructing" << endl;
	}
	~example()
	{
		cout << "Destructing" << endl;
	}
	int get_i()
	{
		return i;
	}
};

int sqr_it( example o )
{
	return o.get_i() * o.get_i();
}

int main(int argc, char* argv[])
{
	example x( 10 );
	cout << x.get_i() << endl;
	cout << sqr_it( x ) << endl;
	return 0;
}

