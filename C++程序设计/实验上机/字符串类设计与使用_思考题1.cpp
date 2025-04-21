#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class CTString
{
	char *m_pData; // 保存字符数据 的指针 
	int m_nLen; // 记录字符长度 
	
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
};

// 无参构造函数
CTString::CTString()
{
	m_nLen = 0;
	m_pData = NULL;
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
 } 

// 析构函数
CTString::~CTString()
{
	if (m_pData != NULL)
		delete []m_pData;
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

int main()
{ 
	CTString *pstr;
	pstr = new CTString;
	pstr->Print();
	pstr->Copy("hello");
	pstr->Print();  
	
	return 0; 
	  
}

/*
报错： 145	20	E:\C++程序设计\实验上机\字符串类设计与使用_思考题1.cpp	[Error] no matching function for call to 'CTString::Copy(const char [6])'
原因：传入的参数类型不正确，需要传入的是 CTString类实例化的对象，不能是字符串，所以 Copy("hello") 报错。 
*/
