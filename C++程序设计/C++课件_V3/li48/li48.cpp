// li48.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Base {
public:
	Base( int i )
	{
		x = i;
		cout << "Constructing base class" << endl;
	}
	~Base()
	{
		cout << "Destructing base class" << endl;
	}
	void show()
	{
		cout << "x = " << x << endl;
	}
private:
	int x;
};
class Derived: public Base {
public:
	Derived( int i ):Base(i),d(i)
	{
		cout << "Constructing derived class" << endl;
	}
	~Derived()
	{
		cout << "Destructing derived class" << endl;
	}
private:
	Base d;
};

int main(int argc, char* argv[])
{
	Derived obj( 5 );
	obj.show();
	return 0;
}

