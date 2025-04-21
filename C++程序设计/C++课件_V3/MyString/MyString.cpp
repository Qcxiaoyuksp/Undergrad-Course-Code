// MyString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

class MyString {
	char * ptr;
	int len;
public:
	MyString(){
		ptr = NULL;
		len = 0;
	};
	MyString( const char * Str );
	MyString( const MyString &copy );
	~MyString(){
		if( !ptr )
			delete ptr;
	};
	MyString * Copy( MyString * Str );
	MyString * Connect( MyString * Str );

	int Find( const char );
	int Find( const char * Str );
	int Find( const MyString * str );
	void MakeReserve();
	void print();
};

MyString::MyString(const char * Str)
{
	int	i, k;
	k = 0;
	while ( Str[k] != NULL ){
		k++;
	}
	len = k + 1;
	ptr = new char[len];
	if( !ptr ){
		cout<< "MEMORY ERROR " << endl;
		exit( 0 );
	}
	for(i = 0; i < len; i++ )
		ptr[i] = Str[i];
};

MyString::MyString( const MyString &copy )
{
	int	i;

	len = copy.len;
	ptr = new char[len];
	if( !ptr ){
		cout<< "MEMORY ERROR " << endl;
	}
	for(i = 0; i < len; i++ )
		ptr[i] = copy.ptr[i];
};

MyString * MyString::Copy( MyString * Str )
{
	int	i;

	if( !ptr )
		delete ptr;
	
	len = Str->len;
	ptr = new char[len];
	if( !ptr ){
		cout<< "MEMORY ERROR " << endl;
		exit( 0 );
	}

	for(i = 0; i < len; i++ )
		ptr[i] = Str->ptr[i];

	return this;
};

MyString * MyString::Connect( MyString * Str )
{
	int	i, k;
	char * ptemp;

	ptemp = ptr;
	len = len + Str->len - 1 ;
	ptr = new char[len];
	if( !ptr ){
		cout<< "MEMORY ERROR " << endl;
		exit( 0 );
	}

	i = 0;
	while( ptemp[i] ) 
		ptr[i++] = ptemp[i];

	k = 0;
	while( Str->ptr[k] ){
		ptr[i++] = Str->ptr[k++];
	}
	ptr[i] = NULL;

	delete ptemp;
	return this;
};

int MyString::Find( const char ch )
{
	int i;

	for(i = 0; i < len; i++ )
		if( ptr[i] == ch )
			break;
	if( len == i ){
		return 0;
	}
	return i+1;

};

int MyString::Find( const char * Str )
{
	int	i, k, strlen;

	k = 0;
	while ( Str[k] )
		k++;
	strlen = k;

	if( len < strlen )
		return 0;

	for(i = 0; i < len - 1; i++ ){
		k = 0;
		while( ptr[i+k] == Str[k] && k < strlen ){
			k++;
		}
		if( k == strlen  )
			return i + 1;
	}
	return 0;
};

int MyString::Find( const MyString * Str )
{
	int	i, k, strlen;

	strlen = Str->len - 1;

	if( len < strlen )
		return 0;

	for(i = 0; i < len - 1; i++ ){
		k = 0;
		while( ptr[i+k] == Str->ptr[k] && k < strlen ){
			k++;
		}
		if( k == strlen  )
			return i + 1;
	}
	return 0;
};

void MyString::MakeReserve()
{
	int i, j;
	char temp;
	i = 0;
	j = len - 2;
	while( i < j ){
		temp = ptr[i];
		ptr[i] = ptr[j];
		ptr[j] = temp;
		i++;
		j--;
	}
	
};

void MyString::print()
{
	cout << "len = " << len << endl;
	cout << ptr << endl;
};

int main(int argc, char* argv[])
{
	int i;
	MyString stest("abcdef"), test( "HIZKLMN" ), scopy;

	stest.print();

	scopy.Copy( &stest );
	stest.print();

	stest.Connect( &test );
	stest.print();

	char ch = 'N';

	i = stest.Find( ch );
	if( i != 0 ){
		stest.print();
		cout << ch << " position is " << i << endl;
	}else
		cout << "Find Not! " << endl;

	char *str = "abc";
	i = stest.Find( "abc" );
	if( i != 0 ){
		stest.print();
		cout << str;
		cout << " str position is " << i << endl;
	}else
		cout << "Find Not! " << endl;

	str = "LMN";
	i = stest.Find( str );
	if( i != 0 ){
		stest.print();
		cout << str;
		cout << " str position is " << i << endl;
	}else
		cout << "Find Not! " << endl;

	str = "gHI";
	i = stest.Find( str );
	if( i != 0 ){
		stest.print();
		cout << str;
		cout << " str postion is " << i << endl;
	}else
		cout << "Find Not! " << endl;

	i = stest.Find( &test );
	if( i != 0 ){
		stest.print();
		test.print();;
		cout << " str postion is " << i << endl;
	}else
		cout << "Find Not! " << endl;

	stest.print();
	stest.MakeReserve();
	stest.print();

	return 0;
}

