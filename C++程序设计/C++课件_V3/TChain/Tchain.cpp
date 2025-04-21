#include <iostream.h>

template <class T>
class ChainNode {
public:
	T data;
	ChainNode<T> *link;
//	template <class U> friend class Chain;
};

template <class T>
class Chain {
	ChainNode<T> *first;
public:
	Chain()
	{
		first = 0;
	}
	~Chain();
	bool IsEmpty() const
	{
		return first == 0;
	}
	int Length() const;
	bool Find( int k, T &x ) const;
	int Search( const T &x ) const;
	Chain<T> & Delete( int k, T &x );
	Chain<T> & Insert( int k, const T &x );
	void Output( ostream &out) const;
	void BinSort( int range );
};

template <class T>
Chain<T>::~Chain()
{
	ChainNode<T> *next;
	while ( first ) {
		next = first->link;
		delete first;
		first = next;
	}
}
template <class T>
int Chain<T>::Length() const
{
	ChainNode<T> *current = first;
	int len = 0;

	while ( current ) {
		len++;
		current = current->link;
	}
	return len;
}
template <class T>
bool Chain<T>::Find( int k, T &x) const
{
	if ( k < 1 )
		return false;
	ChainNode<T> *current = first;
	int index = 1;

	while ( index < k && current ) {
		current = current->link;
		index++;
	}
	if ( current ) {
		x = current->data;
		return true;
	}
	return false;
}
template <class T>
int Chain<T>::Search( const T &x ) const
{
	ChainNode<T> *current = first;
	int index = 1;

	while ( current && current->data != x ) {
		current = current->link;
		index++;
	}
	if ( current )
		return index;
	return 0;
}
template <class T>
void Chain<T>::Output( ostream &out ) const
{
	ChainNode<T> *current;
	int index = 1;

	for ( current = first; current; current = current->link )
		out << " Node " << index++ << " : "<< current->data ;
	out << endl;
}

template <class T>
ostream & operator<<( ostream &out, const Chain<T> &x )
{
	x.Output( out );
	return out;
}
template <class T>
Chain<T> & Chain<T>::Delete( int k, T &x )
{
	if ( k < 1 || !first ) {
		cout << "不存在第K个元素" << endl;
		return *this;
	}
	ChainNode<T> *p = first;

	if ( k == 1 )
		first = first->link;
	else {
		ChainNode<T> *q = first;

		for ( int index = 1; index < k - 1 && q; index++ )
			q = q->link;

		if ( !q || !q->link ) {
			cout << "不存在第K个元素" << endl;
			return *this;
		}
		p = q->link;
		q->link = p->link;
	}

	x = p->data;
	delete p;
	return *this;
}

template <class T>
Chain<T> & Chain<T>::Insert( int k, const T &x )
{
	if ( k < 0 ) {
		cout << "不存在第K个元素" << endl;
		return *this;
	}

	ChainNode<T> *p = first;

	for ( int index = 1; index < k && p; index++ )
		p = p->link;

	if ( k > 0 && !p ) {
		cout << "不存在第K个元素" << endl;
		return *this;
	}

	ChainNode<T> *y = new ChainNode<T>;
	y->data = x;

	if ( k ) {
		y->link = p->link;
		p->link = y;
	} else {
		y->link = first;
		first = y;
	}
	return *this;
}
template <class T>
void Chain<T>::BinSort( int range )
{
	int b;
	ChainNode<T> **bottom, **top;

	bottom = new ChainNode<T> *[range + 1];
	top = new ChainNode<T> *[range + 1];

	for ( b = 0; b <= range; b++ )
		bottom[b] = 0;

	for ( ; first; first = first->link ){

		b = first->data;
		if ( bottom[b] ){
			top[b]->link = first;
			top[b] = first;
		} else
			bottom[b] = top[b] = first;
	}

	ChainNode<T> *y = 0;

	for ( b = 0; b <= range; b++ )
		if ( bottom[b] ){
			if ( y )
				y->link = bottom[b];
			else
				first = bottom[b];
			y = top[b];
		}
		if ( y )
			y->link = 0;
		delete [] bottom;
		delete [] top;
}

main()
{
	Chain<int> list1;
	int  index, len;

	if ( list1.IsEmpty() )
		cout << "  List is empty ! " << endl;

	list1.Insert( 0, 5 );
	cout << list1;
	if ( list1.IsEmpty() )
		cout << "  List is empty ! " << endl;
	else
		cout << "  List is not empty ! " << endl;

	list1.Insert( 1, 6 );
//	cout << list1;

	list1.Insert( 0, 8 );
//	cout << list1;

	list1.Insert( 2, 4 );
//	cout << list1;

	list1.Insert( 4, 3 );
	list1.Insert( 4, 1 );
	list1.Insert( 4, 2 );
//	cout << list1;

/*	index = list1.Search( 10 );
	cout << "  Search 10 Node Number: " << index << endl;

	int &x = index;
	if( list1.Find( 3, x ) )
		cout << "  Find 3 Node Data: " << x << endl;

	list1.Delete( 4, x );
	cout << "  Delete Node data : " << x << endl;
	cout << list1;

	len = list1.Length();
	cout << "  Length : " << len << endl;
*/


	list1.Insert( 0, 10 );
	list1.Insert( 0, 12 );
	list1.Insert( 0, 14 );
	cout << list1;

	list1.BinSort( 15 );
	cout << list1;

	return 0;
}
