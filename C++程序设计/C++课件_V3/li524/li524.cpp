// li524.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class B{
public:
//	virtual 
	~B()
	{
		cout << "���û���B����������" << endl;
	}
};
class D: public B{
public:
	~D()
	{
		cout << "����������D����������" << endl;
	}
};
		
int main(int argc, char* argv[])
{
	B *p;
	p = new D;

	delete p;
	return 0;
}

