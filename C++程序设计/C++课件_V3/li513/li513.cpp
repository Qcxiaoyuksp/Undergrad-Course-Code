// li513.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream.h>

class Vector4 {
public:
	Vector4( int a1, int a2, int a3, int a4 )
	{
		v[0] = a1;
		v[1] = a2;
		v[2] = a3;
		v[3] = a4;
	}
	int & operator[]( int bi );
private:
	int v[4];
};
int & Vector4::operator []( int bi )
{
	if( bi < 0 || bi >=4 )
	{
		cout << "Bad subscript!" << endl;
		exit( 1 );
	}
	return v[bi];
}

int main(int argc, char* argv[])
{
	Vector4 v( 1, 2, 3, 4 );
	cout << v[2] << endl;
	v[3] = v[2];
	cout << v[3] << endl;
	v[2] = 22;
	cout << v[2] << endl;
	return 0;
}

