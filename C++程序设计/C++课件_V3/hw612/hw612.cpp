// hw612.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

template < class Type >
Type selectmax( Type list[], int len )
{
	int i;
	Type temp;

	temp = list[0];
	for ( i = 1; i < len; i++ )
		if( temp < list[i] )
			temp = list[i];
	
	return temp;
}

int main(int argc, char* argv[])
{
	int listint[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double listdouble[] = { 2.3, 4.5, 8.2, 1.5, 9.3, 12.4, 8.2, 23.8, 19.8 };

	cout << "max of int array  is "<< selectmax( listint, 9 ) << endl;

	cout << "max of double array is "<< selectmax( listdouble, 9 ) << endl;

	return 0;
}