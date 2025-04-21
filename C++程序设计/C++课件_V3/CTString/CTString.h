//CTString.h file
/*************************************************************/
/*  ���ߣ�����                                               */  
/*  ���ܣ�C++�ַ�������ƺ�ʹ��                              */  
/*  ʱ�䣺2008-4-11                                          */  
/*************************************************************/  

class   CTString     
{   
private:   		
		char*   m_pData;                  //����ַ������ݵ�ָ��   
        int     m_nLen;                   //�ַ������ַ��ĸ���  

public:      
      //���캯��   
	  CTString();  
	  CTString(const char*);   
	  CTString(const CTString&); //�������캯��
  
      
      //��������  
      ~CTString();

	  CTString * Connect(CTString*);
	  CTString*  Copy(CTString*);
	  char*      Find(CTString*);
	  //char*		 Find(const CTString&)
 
	  void       Print();    //��ӡ����ַ�����Ϣ
 };   