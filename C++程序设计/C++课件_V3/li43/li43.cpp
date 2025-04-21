// li43.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Base {
public:
	void setxy( int m, int n )
	{
		x = m;
		y = n;
	}
	void showxy( )
	{
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
	}
private:
	int x;
protected:
	int y;
};
class Derived: public Base {
public:
	void setxyz( int m, int n, int l )
	{
		setxy ( m, n );
		z = l;
	}
	void showxyz( )
	{
//		cout << "x = " << x << endl;
//		cout << "y = " << y << endl;
		showxy( );
		cout << "z = " << z << endl;
	}
private:
	int z;
};

int main(int argc, char* argv[])
{
	Derived obj;
	obj.setxyz( 30, 40, 50 );
	obj.showxy();

//	obj.y = 60;
	obj.showxyz();
	return 0;
}

