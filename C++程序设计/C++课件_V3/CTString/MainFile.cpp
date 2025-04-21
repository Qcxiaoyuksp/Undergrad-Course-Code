#include <iostream.h>
#include "CTString.h"   

int  main(int argc, char *argv[] )
{ 
	CTString s1; 
	CTString * s5,*s7;
	CTString s2("Hello"); 
	CTString s4("Everyone!"); 	 
	CTString s6("one"); 
	CTString s3(s4); 

	s5 = &s2;
	s7 = &s4;
	s2.Print();
	//s1.Print();	// 有问题的语句
	cout<<"------连接字符串----------------"<<endl;

	s2.Connect(&s4);
	s2.Print();

	cout<<"------查找字符串----------------"<<endl;
	char *pstr = NULL;
	pstr = s2.Find(&s6);
	if (pstr != NULL)
	{
		cout<<pstr<<endl;
	} 

	return 0;
	  
}