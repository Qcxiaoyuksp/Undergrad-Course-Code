// binarytree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>


template <class Type>
struct treenode {
	Type data;
	int flag;
	treenode *left;
	treenode *right;
};

const int size = 100;
template <class Type>
class TreeStack {
	private:
		treenode <Type> *stck[size];
		int tos;
	public:
		TreeStack()
		{
			tos = 0;
		}
		int isempty()
		{
			return tos;
		}
		void push ( treenode <Type> * );
		treenode <Type> * pop(  );
};

template <class Type>
void TreeStack <Type> ::push( treenode <Type> *tpt )
{
	if( tos == size )
		cout << "stack is full" <<endl;
	
	stck[tos] = tpt;

	tos++;
}

template <class Type>
treenode <Type> * TreeStack <Type> ::pop(  )
{

	if ( tos == 0 )
		cout << "stack is empty" << endl;

	tos--;
	return stck[tos];
}
	
template <class Type>
class BinaryTree {
	private:
		treenode <Type> *root;
		TreeStack <Type> tstack;
	public:
		BinaryTree()
		{
			root = 0;
		}
		treenode <Type> * isroot()
		{
			return root;
		}
		void sample( );
		void delsample();
		void PreOrder ( );
		void InOrder ( );
		void PostOrder ( );
		void PreOrder1 ( treenode <Type> *p )
		{
			if ( p != 0 ) {
				cout << "  " << p->data;
				PreOrder1 ( p->left );
				PreOrder1 ( p->right );
			}
		}
		void InOrder1 ( treenode <Type> *p )
		{
			if ( p != 0 ) {
				InOrder1 ( p->left );
				cout << "  " << p->data;
				InOrder1 ( p->right );
			}
		}
		void PostOrder1 ( treenode <Type> *p )
		{
			if ( p != 0 ) {
				PostOrder1 ( p->left );
				PostOrder1 ( p->right );
				cout << "  " << p->data;
			}
		}

};

template <class Type>
void BinaryTree <Type> ::sample( )
{
	treenode <Type> *p1, *p2, *p3, *p4, *p5;
	root = new treenode <Type>;
	p1 = new treenode <Type>;
	p2 = new treenode <Type>;
	p3 = new treenode <Type>;
	p4 = new treenode <Type>;
	p5 = new treenode <Type>;

	root->data = 'A';
	root->flag = 2;
	root->left = p1;
// creat left tree
	p1->data = 'B';
	p1->flag = 2;
	p1->left = p2;
	p1->right = p3;

	p2->data = 'D';
	p2->flag =  2;
	p2->left = p4;
	p2->right = 0;

	p3->data = 'E';
	p3->flag =  2;
	p3->left = 0;
	p3->right = p5;

	p4->data = 'H';
	p4->flag =  2;
	p4->left = 0;
	p4->right = 0;

	p5->data = 'I';
	p5->flag =  2;
	p5->left = 0;
	p5->right = 0;

	p1 = new treenode <Type>;
	p2 = new treenode <Type>;
	p3 = new treenode <Type>;
	p4 = new treenode <Type>;
	p5 = new treenode <Type>;

	root->right = p1;
// creat right tree
	p1->data = 'C';
	p1->flag =  2;
	p1->left = p2;
	p1->right = p3;

	p2->data = 'F';
	p2->flag =  2;
	p2->left = 0;
	p2->right = p4;

	p3->data = 'G';
	p3->flag =  2;
	p3->left = p5;
	p3->right = 0;

	p4->data = 'J';
	p4->flag =  2;
	p4->left = 0;
	p4->right = 0;

	p5->data = 'K';
	p5->flag =  2;
	p5->left = 0;
	p5->right = 0;

}

template <class Type>
void BinaryTree <Type> ::delsample( )
{
	treenode <Type> *p1, *p2, *p3, *p4, *p5;

// delete  left tree
	p1 = root->left;
	p2 = p1->left;
	p3 = p1->right;
	p4 = p2->left;
	p5 = p3->right;
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete p5;

// delete right tree
	p1 = root->right;
	p2 = p1->left;
	p3 = p1->right;
	p4 = p2->right;
	p5 = p3->left;
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete p5;

}

template <class Type>
void BinaryTree <Type> ::PreOrder( )
{
	int i = 1;
	treenode <Type> *p;
	p = root;

	while ( p != 0 ){

		cout << " node " << i++ << ":" << p->data;
		if ( ( i - 1 ) % 4 == 0 )
			cout << endl;

		if ( p->right != 0 )
			tstack.push( p->right );

		if ( p->left != 0 )
			p = p->left;
		else {
			if ( !tstack.isempty() )
				p = 0;
			else 
				p = tstack.pop();
		}
	}
	cout << endl;
}

template <class Type>
void BinaryTree <Type> ::InOrder( )
{
	int i = 1;
	treenode <Type> *p;
	p = root;

	while ( p != 0 ){

		tstack.push( p );

		if ( p->left != 0 )
			p = p->left;
		else {
			p = tstack.pop();
			cout << " node " << i++ << ":" << p->data;
			if ( ( i - 1 ) % 4 == 0 )
				cout << endl;

			while ( tstack.isempty() && p->right == 0 ){
				p = tstack.pop();
				cout << " node " << i++ << ":" << p->data;
				if ( ( i - 1 ) % 4 == 0 )
					cout << endl;
			}
			p = p->right;
		}

	}
	cout << endl;
}

template <class Type>
void BinaryTree <Type> ::PostOrder( )
{
	int i = 1;
	treenode <Type> *p;
	p = root;

	while ( p != 0 ){

		switch ( p->flag ) {
		case 2:
			p->flag--;
			tstack.push( p );
			if ( p->left == 0 )
				p = tstack.pop();
			else 
				p = p->left;
			break;
		case 1:
			p->flag--;
			tstack.push( p );
			if ( p->right == 0 )
				p = tstack.pop();
			else 
				p = p->right;
			break;
		case 0:
			cout << "  node " << i++ << ": " << p->data ;
			if ( ( i - 1 ) % 4 == 0 )
				cout << endl;
			if( !tstack.isempty() )
				p = 0;
			else
				p = tstack.pop();
			break;
		default:
			cout << " flag error" << endl;
		}

	}

	cout << endl;
}

int main(int argc, char* argv[])
{
	BinaryTree <char> bt;

	bt.sample();

	cout << "PreOrder tree \n";
	bt.PreOrder1( bt.isroot() );
	cout << endl;
	bt.PreOrder();

	cout << "InOrder tree \n";
	bt.InOrder1( bt.isroot() );
	cout << endl;
	bt.InOrder();

	cout << "PostOrder tree \n";
	bt.PostOrder1( bt.isroot() );
	cout << endl;
	bt.PostOrder();
	
	bt.delsample();

	return 0;
}
