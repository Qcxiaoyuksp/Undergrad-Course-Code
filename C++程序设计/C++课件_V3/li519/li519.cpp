// li519.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class My_base {
public:
	My_base( int x, int y )
	{
		a = x;
		b = y;
	}
	void show()
	{
		cout << "���û���My_base��show()����" << endl;
		cout << a << " " << b << endl;
	}
private:
	int a, b;
};

class My_class: public My_base {
public:
	My_class( int x, int y, int z ) : My_base( x, y )
	{
		c = z;
	}	void show()
	{
		cout << "����������My_class��show()����" << endl;
		cout << "c =  " << c << endl;
	}
private:
	int c;
};

int main(int argc, char* argv[])
{
	My_base mb( 50, 50 ), *mp;
	My_class mc( 10, 20, 30 );
	mp = &mb;
	mp->show();

	mp = &mc;
	mp->show();

	return 0;
}
