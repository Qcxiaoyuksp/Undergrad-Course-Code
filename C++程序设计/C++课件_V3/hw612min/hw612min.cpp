// hw612min.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

template < class Type >
Type selectmin( Type list[], int len )
{
	int i;
	Type temp;

	temp = list[0];
	for ( i = 1; i < len; i++ )
		if( temp > list[i] )
			temp = list[i];
	
	return temp;
}

int main(int argc, char* argv[])
{
	int listint[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double listdouble[] = { 2.3, 4.5, 8.2, 1.5, 9.3, 12.4, 8.2, 23.8, 19.8 };

	cout << "min of int array  is "<< selectmin( listint, 9 ) << endl;

	cout << "min of double array is "<< selectmin( listdouble, 9 ) << endl;

	return 0;
}