// lie614.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>

template<class T>
struct quenode{
    T nodedata;
    quenode * next;
};

template<class T>
class queue{
//  private:
	protected:
		int quesize;
		quenode<T> * head;
		quenode<T> * tail;
		bool allocateerror;
		queue &copy(queue &q);
    public:
		queue();
		queue(queue &q)
		{	
			head=NULL;tail=NULL;copy(q);
//			printf("Using copy constructor\n " );
		}
		~queue()
			{	clearque();	}
	    bool getallocateerror()
			{	return allocateerror;	}
		void push(T &);
		bool pop(T &);
		bool isempty()
			{	return (quesize==0) ?true:false;	}
		void clearque();
		queue &operator= (queue &q)
		{
			copy(q);
			return * this;
		}
};

template<class T>
queue<T>::queue()
{
    quesize = 0;
    allocateerror = false;
    head = NULL;
    tail = NULL;
}

template<class T>
queue<T>& queue<T>::copy(queue<T>& que)
{
    quenode<T> * p,* q,* r;
    if (head) clearque();
    quesize = que.quesize;
    allocateerror = false;
    head = NULL;
    tail = NULL;
    if ( !que.head )
		return * this;

    head = new quenode<T>;
    if ( !head ){
        allocateerror = true;
        return * this;
    }

    head->nodedata = que.head->nodedata;
    head->next = NULL;
    tail = head;
    r = NULL;
    p = head;
    q = que.head->next;
    while( q ){
        r = new quenode<T>;
        if ( !r ){
            allocateerror = true;
            return * this;
        }

        r->nodedata = q->nodedata;
        r->next = NULL;
        p->next = r;
        tail = r;
        p = p->next;
        q = q->next;
    }
    return * this;
}

template<class T>
void queue<T>::push(T &x)
{
    quenode<T> *p;
    p = new quenode<T>;

    if( !p ){
        allocateerror=true;
        return;
    }

    p->nodedata = x;
    if(tail){
        p->next = NULL;
        tail->next = p;
        tail = p;
    }else{
        p->next = NULL;
        tail = p;
        head = p;
    }

    quesize++;
}

template<class T>
bool queue<T>::pop(T &x)
{
    quenode<T> *p;

    if( head ){
        x = head->nodedata;
        p = head;
        head = head->next;

        if (head == NULL)
			tail = NULL;

        delete p;
        quesize--;
        return true;
    }
    return false;
}

template<class T>
void queue<T>::clearque()
{
    T p;
    allocateerror = false;
    while ( pop(p) );
    head = tail = NULL;
}

class staff{
    public:
    char name[80];
    int age;
    float salary;
    char sex[8];

    void assign(char * name, int age, float salary, char * sex)
    {
        strcpy(staff::name,name);
        staff::age = age;
        staff::salary = salary;
        strcpy(staff::sex,sex);
    }

    void print()
    {
        printf("%10s%6d%10.2f%8s\n", name, age, salary, sex);
    }
};

void viewque( queue<staff> &que )
{
    int i=1;
    staff p;
    queue<staff> quecopy(que);
    system("cls");

    while( quecopy.pop(p) ){
        printf("%2d:", i++);
        p.print();
    }
}

int main() 
{
	queue<staff>que;
	staff p;

	p.assign("Chenweilin", 47, 1500, "male");
	que.push(p);

	p.assign("Wangling", 34, 850.5, "male");
	que.push(p);

	p.assign("Zhangdaling", 27, 1200, "male");
	que.push(p);

	p.assign("Fanglibida", 51, 2000, "female");
	que.push(p);

	viewque(que);

	return 0;
}