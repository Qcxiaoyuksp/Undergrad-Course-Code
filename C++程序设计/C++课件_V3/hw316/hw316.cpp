// hw316.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>

class Sample {
private:
	int x, y;
public:
	Sample( int i, int j )
	{
		x = i;
		y = j;
	}
	void disp()
	{
		cout << "disp1" << endl;
	}
	void disp() const
	{
		cout << "disp2" << endl;
	}
};

int main(int argc, char* argv[])
{
	const Sample a(1, 2);
	a.disp();
	
	Sample b(1, 2);
	b.disp();
	a.disp();
	
	Sample c(1, 2);
	c.disp();
	a.disp();

	return 0;
}

