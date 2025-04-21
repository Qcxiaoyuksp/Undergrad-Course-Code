#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class CTString
{
	char *m_pData; // 保存字符数据 的指针 
	int m_nLen; // 记录字符长度 
	static int number; // 记录 对象的个数  
	
	public:
		// 构造函数 
		CTString();
		CTString(const char*);
		CTString(const CTString&); // 拷贝构造函数 
		// 析构函数 
		~CTString();
		
		// 其他成员函数
		CTString* Copy(CTString*); // 拷贝
		CTString* Connect(CTString*); // 连接
		char* Find(CTString*);
		//char* Find(char);
		void Print(); 
		
		// 静态成员函数 
		static int GetNumber();
};

int CTString::number = 0; // 静态成员变量初始化

// 无参构造函数
CTString::CTString()
{
	m_nLen = 0;
	m_pData = NULL;
	number++; 
} 

// 有参构造函数 
CTString::CTString(const char *pString)
{
	if (pString == NULL)
	{
		m_nLen = 0;
		m_pData = NULL;
	}
	else
	{
		m_nLen = strlen(pString);
		m_pData = new char[m_nLen + 1]; // 数组下标从1开始，要+1
		assert(m_pData != NULL);
		strcpy(m_pData, pString); 
	}
	number++; 
}

// 拷贝构造函数
CTString::CTString(const CTString &srcString)
{
	m_nLen = srcString.m_nLen;
	if (m_nLen == 0)
		m_pData = NULL;
	else
	{
		m_pData = new char[m_nLen + 1];
		assert(m_pData != NULL);
		strcpy(m_pData, srcString.m_pData);
	}
	number++; 
 } 

// 析构函数
CTString::~CTString()
{
	if (m_pData != NULL)
		delete []m_pData;
	number--; 
}

// 成员函数 
// connect
CTString* CTString::Connect(CTString *pString)
{
	assert(pString != NULL);
	if (pString->m_nLen == 0)
	{
		return this;
	}
	
	char* pStrTemp = m_pData;
	
	m_nLen = m_nLen + pString->m_nLen;
	m_pData = new char[m_nLen+1];
	assert(m_pData != NULL);
	
	strcpy(m_pData, pStrTemp);
	strcat(m_pData, pString->m_pData);
	delete pStrTemp;

	return this;
}

// copy
CTString* CTString::Copy(CTString *pString)
{
	assert(pString != NULL);

	if (m_pData != NULL) 
		delete m_pData;
	if (pString->m_nLen == 0)
	{
		m_pData = NULL;
		return this;
	}
	
	m_nLen = pString->m_nLen;
	m_pData = new char[m_nLen+1];
	assert(m_pData != NULL);
	strcpy(m_pData, pString->m_pData);

	return this;
} 

// find 字符串 
char* CTString::Find(CTString* pSubString)
{
	assert(pSubString != NULL);
	if (pSubString->m_nLen == 0)
	{
		return NULL;
	}
	char *pRet = NULL;
	pRet = strstr(m_pData, pSubString->m_pData);
	return pRet;
}

// 如果这样编写Print函数，思考题是有运行时错误的
void CTString::Print()
{
	cout<<"-------------------------------------------"<<endl;
	cout<<"该字符串的值："<<m_pData<<endl;	// 思考...
	cout<<"该字符串的长度："<<m_nLen<<endl;
	cout<<"-------------------------------------------"<<endl;
	cout<<endl;
}

// 获取对象个数
int CTString::GetNumber() 
{
	return number;
}

int main()
{
	CTString s1; 
	CTString *s5,*s7;
	CTString s2("Hello"); 
	CTString s4("ZhangQingChen"); 	 
	CTString s6("Chen"); 
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
		cout << pstr << endl;
	} 
	
	cout << "###" << endl;
	cout << "当前对象数量：" << CTString::GetNumber() << endl; // 输出对象数量
	cout << "###" << endl;

	return 0;
	  
}
