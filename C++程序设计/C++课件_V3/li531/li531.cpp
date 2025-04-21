// li531.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdlib.h>

class list {
public:
	list *head;
	list *tail;
	list *next;
	int num;
	list()
	{
		head = tail = next = NULL;
	}
	virtual void store( int i ) = 0;
	virtual int retrieve () = 0;
};

class queue: public list {
public:
	void store( int i );
	int retrieve( );
};
void queue::store( int i )
{
	list *item;
	item = new queue;
	if( !item ){
		cout << "Allocation erroe" << endl;
		exit( 1 );
	}
	item->num = i;
	if( tail )
		tail->next = item;
	tail = item;
	item->next = NULL;
	if( !head )
		head = tail;
}
int queue::retrieve()
{
	int i;
	list *p;
	if( !head ){
		cout << "list empty" << endl;
		return 0;
	}
	i= head->num;
	p =head;
	head = head->next;
	delete p;
	return i;
}

class stack: public list {
public:
	void store( int i );
	int retrieve( );
};
void stack::store( int i )
{
	list *item;
	item = new stack;
	if( !item ){
		cout << "Allocation erroe" << endl;
		exit( 1 );
	}
	item->num = i;
	if( head )
		item->next = head;
	head = item;
	if( !tail )
		tail = head;
}
int stack::retrieve()
{
	int i;
	list *p;
	if( !head ){
		cout << "list empty" << endl;
		return 0;
	}
	i= head->num;
	p =head;
	head = head->next;
	delete p;
	return i;
}

int main(int argc, char* argv[])
{
	list *p;
	queue q_ob;
	p = &q_ob;
	p->store( 1 );
	p->store( 2 );
	p->store( 3 );
	cout << "queue: ";
	cout << p->retrieve();
	cout << p->retrieve();
	cout << p->retrieve();
	cout << endl;

	stack s_ob;
	p = &s_ob;
	p->store( 1 );
	p->store( 2 );
	p->store( 3 );
	cout << "stack: ";
	cout << p->retrieve();
	cout << p->retrieve();
	cout << p->retrieve();
	cout << endl;

	return 0;
}

