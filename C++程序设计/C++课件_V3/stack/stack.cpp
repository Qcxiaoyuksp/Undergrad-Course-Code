// stack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdlib.h>
class stack {
private:
	int data[100];
	int top;
public:
	stack();
	push( int a );
	int pop();
};

stack::stack()
{
	top = 0;
}

stack::push( int a )
{
	if( top != 100 )
		data[top++] = a;
	else {
		cout << " stack is full! " << endl;
		exit( 0 );
	}
}

int stack::pop()
{
	int temp;

	if( top !=0 )
		temp = data[--top];
	else {
		cout << " stack is empty! " << endl;
	}
	return temp;
}

int main(int argc, char* argv[])
{
	stack intstack;

	intstack.push( 2 );
	intstack.push( 4 );
	intstack.push( 6 );
	intstack.push( 8 );

	cout << intstack.pop() << endl;
	cout << intstack.pop() << endl;
	cout << intstack.pop() << endl;
	cout << intstack.pop() << endl;
	
	return 0;
}

