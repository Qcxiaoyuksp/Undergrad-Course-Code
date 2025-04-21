// hw220T.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

int &f( int &i)
{
	i += 10;
	return i;
}
int main(int argc, char* argv[])
{
	int k = 0;
	int &m = f( k );
	cout << k << endl;
	m = 20;
	cout << k << endl;
	return 0;
}

