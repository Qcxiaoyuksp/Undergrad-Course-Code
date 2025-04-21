// sxy04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdlib.h>

template <class Type>
struct stacknode {
	Type nodedata;
	stacknode *next;
};
template <class Type>
class linkstack {
	private:
		stacknode <Type> *top;
	public:
		void init()
		{
			top = 0;
		}
		void push( Type data );
		Type pop();
};

template <class Type>
void linkstack <Type> ::push(Type data )
{
	stacknode <Type> *p;
	p = new stacknode <Type>;
	if(p==0){
		cout << "error" << endl;
		exit( 0 );
	}
	p->nodedata = data;
	p->next = top;
	top = p;
}

template <class Type>
Type linkstack <Type> ::pop( )
{
	stacknode <Type> *p;
	Type d;
	if(top==0){
		cout << "error: stack is empty" << endl;
	   	exit( 0 );
	}
	d = top->nodedata;
	p = top;
	top = top->next;
	delete p;
	return d;
}

int main(int argc, char* argv[])
{
	linkstack <char> s1, s2;
	int i;

	s1.init();
	s2.init();
//		cout << "pop s1: "  << s1.pop() << endl;

	s1.push('a');
	s2.push('x');
	s1.push('b');
	s2.push('y');
	s1.push('c');
	s2.push('z');

	for ( i = 0; i < 3; i++)
		cout << "pop s1: "  << s1.pop() << endl;
	for ( i = 0; i < 3; i++)
		cout << "pop s2: "  << s2.pop() << endl;

	linkstack <double> ds1, ds2;

	ds1.init();
	ds2.init();

	ds1.push( 1111.111111 );
	ds2.push( 5555.555555 );
	ds1.push( 2222.222222 );
	ds2.push( 6666.666666 );
	ds1.push( 3333.333333 );
	ds2.push( 7777.777777 );

	for ( i = 0; i < 3; i++)
		cout << "pop ds1: "  << ds1.pop() << endl;
	for ( i = 0; i < 3; i++)
		cout << "pop ds2: "  << ds2.pop() << endl;

	return 0;
}
