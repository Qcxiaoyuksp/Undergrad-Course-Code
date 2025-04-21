// li718.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>

class Copy_file {
public:
	Copy_file();
	~Copy_file();
	void Copy_files();
	void in_file();
	void outfile();
private:
	fstream inf;
	fstream outf;
	char file1[20];
	char file2[20];
};

Copy_file::Copy_file()
{
	cout<<"请输入源文件名：";
	cin>>file1;
	inf.open(file1, ios::in|ios::nocreate);

	if( !inf ){
		cout<<"不能打开源文件："<<file1<<endl;
		abort();
	}

	cout<<"请输入目的文件名：";
	cin>>file2;
	outf.open(file2, ios::in| ios::out|ios::noreplace);

	if( !outf ){
		cout<<"不能打开目的文件："<<file1<<endl;
		abort();
	}

}

Copy_file::~Copy_file()
{
	inf.close();
	outf.close();
}

void Copy_file::Copy_files()
{
	char ch;
	inf.seekg( 0 );
	inf.get( ch );
	while( !inf.eof() ){
		if( ch >='a' && ch <= 'z' )
			outf.put( ch );
		inf.get( ch );
	}

}

void Copy_file::in_file()
{
	char ch;
	inf.close();
	inf.open( file1, ios::in );
	inf.get( ch );
	while( !inf.eof() ){
		cout << ch;
		inf.get( ch );
	}
	cout << endl;
}

void Copy_file::outfile()
{
	char ch;
	outf.seekg( 0 );
	outf.get( ch );
	while( !outf.eof() ){
		cout << ch;
		outf.get( ch );
	}
	cout << endl;
}


int main(int argc, char* argv[])
{
	Copy_file cf;

	cf.Copy_files();

	cout << "源文件中的内容：" << endl;
	cf.in_file();

	cout << "目的文件中的内容：" << endl;
	cf.outfile();

	return 0;
}
