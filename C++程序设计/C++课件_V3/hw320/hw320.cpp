// hw320.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class aClass {
private:
	static int total;
public:
	aClass()
	{
		total++;
	}
	~aClass()
	{
		total--;
	}
	int gettotal()
	{
		return total;
	}
};
int aClass::total = 0;

int main(int argc, char* argv[])
{
	aClass o1, o2, o3;

	cout<< o1.gettotal() << " objects in existence" << endl;
	aClass * p;
	p = new aClass;
	if( !p ){
		cout << "Allocation error" << endl;
		return 1;
	}
	cout<< o1.gettotal() << " objects in existence after allocation" << endl;
	delete p;

	cout<< o1.gettotal() << " objects in existence after delete" << endl;
	return 0;
}

