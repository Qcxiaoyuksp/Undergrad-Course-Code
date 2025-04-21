// li319.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class A {
public:
	A(int x1){
		x = x1;
	}
	void disp(){
		cout << "this = " << this << "  when x = " << this->x << endl;
	}
private:
	int x;
};

int main()
{
	A a( 1 ), b( 2 ), c( 3 );
	
	a.disp();
	b.disp();
	c.disp();
	
	return 0;
}

