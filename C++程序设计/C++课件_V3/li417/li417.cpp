// li417.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
class Base {												//声明基类Base	
public:
	Base( int sa )
	{
		a = sa;
		cout << "Constructing Base" << endl;
	}
private:
	int a;
};
class Base1: virtual public Base {							//声明类Base是Base1的虚基类
public:
	Base1( int sa, int sb ): Base( sa )						//在此，必须缀上对类Base构造函数的调用
	{
		b = sb;
		cout << "Constructing Base1" << endl;
	}
private:
	int b;
};
class Base2: virtual public Base {							//声明类Base是Base2的虚基类
public:
	Base2( int sa, int sc ): Base( sa )						//在此，必须缀上对类Base构造函数的调用
	{
		c = sc;
		cout << "Constructing Base2" << endl;
	}
private:
	int c;
};
class Derived: public Base1, public Base2{					//Derived是Base1和Base2的共同派生类，是Base的间接派生类
public:
	Derived( int sa, int sb, int sc, int sd ): Base( sa ), Base1( sa, sb ), Base2( sa, sc )			//在此，必须缀上对类Base构造函数的调用
	{
		d = sd;
		cout << "Constructing Derived" << endl;
	}
private:
	int d;
};

int main(int argc, char* argv[])
{
	Derived obj( 2, 4, 6, 8 );
	return 0;
}

