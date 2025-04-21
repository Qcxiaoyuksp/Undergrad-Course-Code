// tempstack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdlib.h>
template <class T> class stack {
private:
	T data[100];
	int top;
public:
	stack();
	push( T a );
	T pop();
};

template <class T> stack<T>::stack()
{
	top = 0;
}

template <class T> stack<T>::push( T a )
{
	if( top != 100 )
		data[top++] = a;
	else {
		cout << " stack is full! " << endl;
		exit( 0 );
	}
}

template <class T> T stack<T>::pop()
{
	T temp;

	if( top !=0 )
		temp = data[--top];
	else {
		cout << " stack is empty! " << endl;
	}
	return temp;
}

int main(int argc, char* argv[])
{
	stack<int> intstack;

	intstack.push( 2 );
	intstack.push( 4 );
	intstack.push( 6 );

	cout << intstack.pop() << endl;
	cout << intstack.pop() << endl;
	cout << intstack.pop() << endl;

	stack<char> charstack;

	charstack.push( 'a' );
	charstack.push( 'c' );
	charstack.push( 'e' );

	cout << charstack.pop() << endl;
	cout << charstack.pop() << endl;
	cout << charstack.pop() << endl;
	
	return 0;
}


