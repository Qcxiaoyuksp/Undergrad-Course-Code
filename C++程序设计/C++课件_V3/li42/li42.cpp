// li42.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Base {
public:
	void seta( int sa )
	{
		a = sa;
	}
	void showa()
	{
		cout << "a = " << a << endl;
	}
protected:
	int a;
};
class Derive1: private Base {
public:
	void setab( int sa, int sb )
	{
		a = sa;
		b = sb;
	}
	void showab()
	{
		cout << "a = " << a << endl;
		cout << "b = " << b << endl;
	}
protected:
	int b;
};
class Derive2: private Derive1 {
public:
	void setabc( int sa, int sb, int sc )
	{
		setab( sa, sb );
		c = sc;
	}
	void showabc()
	{
//		cout << "a = " << a << endl;
//		cout << "b = " << b << endl;
		showab();
		cout << "c = " << c << endl;
	}
private:
	int c;
};

int main(int argc, char* argv[])
{
	Base op1;
	op1.seta( 1 );
	op1.showa( );

	Derive1 op2;
	op2.setab( 2, 3 );
	op2.showab( );

	Derive2 op3;
	op3.setabc( 4, 5, 6 );
	op3.showabc( );

	return 0;
}

