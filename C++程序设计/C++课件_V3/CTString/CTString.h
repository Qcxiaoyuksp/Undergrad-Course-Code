//CTString.h file
/*************************************************************/
/*  作者：建大                                               */  
/*  功能：C++字符串类设计和使用                              */  
/*  时间：2008-4-11                                          */  
/*************************************************************/  

class   CTString     
{   
private:   		
		char*   m_pData;                  //存放字符串数据的指针   
        int     m_nLen;                   //字符串中字符的个数  

public:      
      //构造函数   
	  CTString();  
	  CTString(const char*);   
	  CTString(const CTString&); //拷贝构造函数
  
      
      //析够函数  
      ~CTString();

	  CTString * Connect(CTString*);
	  CTString*  Copy(CTString*);
	  char*      Find(CTString*);
	  //char*		 Find(const CTString&)
 
	  void       Print();    //打印输出字符串信息
 };   