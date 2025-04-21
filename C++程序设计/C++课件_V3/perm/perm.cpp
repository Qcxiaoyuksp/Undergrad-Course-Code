// perm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

template < class Type >
void perm( Type list[], int k, int m )
{
	int i;
	if ( k == m ) {
		for ( i = 0; i <= m; i++ )
			cout << list[i] << " ";
		cout << endl;
	} else
		for ( i = k; i <= m; i++ ) {
			swap( list[k], list[i] );
			perm( list, k+1, m );
			swap( list[k], list[i] );
		}
}

template < class Type >
inline void swap( Type &a, Type &b )
{
	Type temp;
	temp = a;
	a = b;
	b = temp;
}

int main(int argc, char* argv[])
{
	int listint[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	perm( listint, 0, 3);

	return 0;
}
