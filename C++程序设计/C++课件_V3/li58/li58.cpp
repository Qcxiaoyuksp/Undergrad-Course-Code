// li58.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Three {
public:
	Three( int I1 = 0, int I2 = 0, int I3 = 0 );
	void print();
	Three operator --();
	Three operator --( int );
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
Three Three::operator --()
{
	--i1;
	--i2;
	--i3;
	return *this;
}
Three Three::operator --( int )
{
	Three temp( *this );
	--i1;
	--i2;
	--i3;
	return temp;
}

int main(int argc, char* argv[])
{
	Three obj1( 4, 5, 6 ), obj2, obj3( 11, 12, 13 ), obj4;
	obj1.print();
	--obj1;
	obj1.print();
	obj2 = obj1--;
	obj2.print();
	obj1.print();
	cout << endl;
	obj3.print();
	obj3.operator --();
	obj3.print();
	obj4 = obj3.operator --( 0 );
	obj4.print();
	obj3.print();
	return 0;
}

