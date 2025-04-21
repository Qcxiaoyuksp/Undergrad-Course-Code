// li715.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>

struct List {
	char course[15];
	int score;
};

int main(int argc, char* argv[])
{
	List list3[4] = { {"Computer", 90}, {"Mathematics", 78}, {"English", 84}, {"C++", 86} };
	List st;
	fstream ff;

	ff.open("f6.dat", ios::out|ios::in|ios::binary);
	if( !ff ){
		cout<< "Open f6.dta error!" << endl;
		abort();
	}

	for( int i = 0; i < 4; i++ )
		ff.write( (char *) &list3[i], sizeof( List ) );
/*
	ff.seekp( sizeof( List ) * 3 );
	ff.read( (char *)&st, sizeof( List ) );
	cout<< st.course << "\t" << st.score << endl;
*/
	ff.seekp( sizeof( List ) * 2 );
	ff.read( (char *)&st, sizeof( List ) );
	cout<< st.course << "\t" << st.score << endl;

	ff.seekp( sizeof( List ) * 0 );
	ff.read( (char *)&st, sizeof( List ) );
	cout<< st.course << "\t" << st.score << endl;

	ff.seekp( sizeof( List ) , ios::cur );
	ff.read( (char *)&st, sizeof( List ) );
	cout<< st.course << "\t" << st.score << endl;

	ff.close();

	return 0;
}

