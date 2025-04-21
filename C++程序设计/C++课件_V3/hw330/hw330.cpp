// hw330.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class counter {
	int value;
public:
	counter( int number );
	void increment();
	void decrement();
	int getvalue();
	int print();
};
counter::counter ( int number )
{
	value = number;
}
void counter:: increment()
{
	value++;
}

void counter:: decrement()
{
	value--;
}

int counter:: getvalue()
{
	return value;
}

int counter:: print()
{
	cout << value << endl;
	return 0;
}

int main(int argc, char* argv[])
{
	counter c1( 10 );

	c1.print();

	c1.increment();
	c1.print();
	cout << c1.getvalue() << endl;

	c1.decrement();
	c1.print();

	return 0;
}

