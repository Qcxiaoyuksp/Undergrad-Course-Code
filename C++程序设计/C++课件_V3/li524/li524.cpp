// li524.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class B{
public:
//	virtual 
	~B()
	{
		cout << "调用基类B的析构函数" << endl;
	}
};
class D: public B{
public:
	~D()
	{
		cout << "调用派生类D的析构函数" << endl;
	}
};
		
int main(int argc, char* argv[])
{
	B *p;
	p = new D;

	delete p;
	return 0;
}

