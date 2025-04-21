// mergesort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

void swap( int &a, int &b )
{
	int temp;
	
	temp = a;
	a = b;
	b = temp;

}


void merge( int c[], int d[], int l, int m, int r )
{					//合并 c[l:m] 和 c[m+1:r] 到 d[l:r]
	int i, j, k, q;

	i = l;
	j = m + 1;
	k = l;

	while( ( i <= m ) && ( j <= r ) ){
		if( c[i] <= c[j] )
			d[k++] = c[i++];
		else
			d[k++] = c[j++];
	}
	if ( i > m )
		for ( q = j; q <= r; q++)
			d[k++] = c[q];
	else
		for ( q = i; q <= m; q++)
			d[k++] = c[q];

}

void mergepass( int x[], int y[], int s, int n )
{						//合并大小为 s 的相邻子数组
	int i, j;
	
	i= 0;
	while( i <= n - 2 * s ){		//合并大小为 s 的相邻2段子数组
		merge( x, y, i, i + s - 1, i + 2 * s - 1 );
		i = i + 2 * s;
	}

	//剩余的元素个数少于2s
	if( i + s < n )
		merge( x, y, i, i + s - 1, n - 1 ); 
	else
		for( j = i; j < n; j++)
			y[j] = x[j];

}

void mergesort( int a[], int n )
{
	int i, s, *b;

	b = new int[n];

	s = 1;
	while ( s < n ){
		mergepass( a, b, s, n);		//合并到数组b
		s += s;

		for( i = 0; i < 10; i++)
			cout << b[i] << "  ";
		cout<< endl;
		
		mergepass( b, a, s, n);		//合并到数组a
		s += s;
		
		for( i = 0; i < 10; i++)
			cout << a[i] << "  ";
		cout<< endl;
	}
	delete []b;

}

int main(int argc, char* argv[])
{
	int a[10] = { 23, 45, 12, 9, 78, 96, 38, 2, 47, 39 };
	int i;

	for( i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout<< endl;
	
	mergesort( a, 10 );

	for( i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout<< endl;

	return 0;
}
