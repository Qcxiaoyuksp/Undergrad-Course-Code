// linkstack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdlib.h>

template<class T>
struct snode{
	T sdata;
	snode * next;
};

template <class T> class stack {
private:
	snode<T> *head;
public:
	stack();
	~stack();
	push( T a );
	T pop();
};

template <class T> stack<T>::stack()
{
	head = NULL;
}
template <class T> stack<T>::~stack()
{
	snode<T> *p;

	while( head ){
		p = head;
		head = p->next;
		delete p;
	} 
}
template <class T> stack<T>::push( T a )
{
	snode<T> *p;
	p = new snode<T>;
	if( p != NULL ){
		p->sdata = a;
		p->next = head;
		head = p;
	}else{
		cout<< "allocate error!" << endl;
		exit( 0 );
	}
}
template <class T> T stack<T>::pop()
{
	T temp;
	snode<T> *p;

	if( head == NULL ){
		cout << " stack is empty! " << endl;
		return 0;
	}

	p = head;
	head = head->next;
	temp = p->sdata;
	delete p;

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



