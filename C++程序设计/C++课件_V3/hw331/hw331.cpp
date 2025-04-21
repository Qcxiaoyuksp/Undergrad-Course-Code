// hw331.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Date {
	int day, month, year;
public:
	void printDate();
	void setDay( int d );
	void setMonth( int m );
	void setYear(int y );
};

void Date::printDate()
{
	cout << day << "-" << month << "-" << year << endl;
}
void Date::setDay( int d )
{
	day = d;
}
void Date::setMonth( int m )
{
	month = m;
}
void Date::setYear(int y )
{
	year = y;
}

int main(int argc, char* argv[])
{
	Date testDay;

	testDay.setDay( 5 );
	testDay.setMonth( 10 );
	testDay.setYear( 2015 );
	testDay.printDate( );
	return 0;
}

