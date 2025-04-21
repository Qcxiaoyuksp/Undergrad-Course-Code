// li59.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Three {
public:
	Three( int I1 = 0, int I2 = 0, int I3 = 0 );
	void print();
	friend Three operator ++( Three & );
	friend Three operator ++( Three &, int );
private:
	int i1, i2, i3;
};
Three::Three( int I1, int I2, int I3 )
{
	i1 = I1;
	i2 = I2;
	i3 = I3;
}
void Three::print()
{
	cout << "i1: " << i1 << "  i2: " << i2 << "  i3: " << i3 << endl;
}
Three operator ++( Three &op )
{
	++op.i1;
	++op.i2;
	++op.i3;
	return op;
}
Three operator ++( Three &op, int )
{
	Three temp( op );
	++op.i1;
	++op.i2;
	++op.i3;
	return temp;
}

int main(int argc, char* argv[])
{
	Three obj1( 4, 5, 6 ), obj2( 14, 15, 16 ), obj3;
	obj1.print();
	++obj1;
	obj1.print();
	obj1++;
	obj1.print();
	cout << endl;

	obj2.print();
	operator ++( obj2 );
	obj2.print();
	operator ++( obj2, 0 );
	obj2.print();
	cout << endl;

	obj3 = operator ++( obj2, 0 );
	obj2.print();
	obj3.print();

	return 0;
}


