// li45.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Base {
public:
	Base()
	{
		cout << "Constructing base class" << endl;
	}
	~Base()
	{
		cout << "Destructing base class" << endl;
	}
};

class Derived : public Base {
public:
	Derived()
	{
		cout << "Constructing derived class" << endl;
	}
	~Derived()
	{
		cout << "Destructing derived class" << endl;
	}
};


int main(int argc, char* argv[])
{
	Derived obj;

	return 0;
}

