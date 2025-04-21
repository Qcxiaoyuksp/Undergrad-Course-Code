// hw421.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <string.h>

class Time {
protected:
	int hours, minutes, seconds;
public:
	Time( int h, int m, int s )
	{
		hours = h;
		minutes = m;
		seconds = s;
	}
	void display()
	{
		cout << "出生时间：" << hours << "时" << minutes << "分" << seconds << "秒" << endl;
	}
};

class Date {
protected:
	int month, day, year;
public:
	Date( int m, int d, int y )
	{
		month = m;
		day = d;
		year = y;
	}
	void display()
	{
		cout << "出生日期：" << year << "年" << month << "月" << day << "日" << endl;
	}
};

class Child: public Time, public Date {
private:
	char Childname[10];
public:
	Child( int h, int m1, int s, int m2, int d, int y, char *name ): Time( h, m1, s ), Date( m2, d, y )
	{
		strcpy( Childname, name );
	}
	void display()
	{
		cout << "姓名：" << Childname << endl;
		Date::display();
		Time::display();
	}
};

int main(int argc, char* argv[])
{
	Child ch( 17, 46, 58, 8, 28, 2008, "Tom" );
	ch.display();

	return 0;
}
