//CPP文件——类的实现文件   
/*************************************************************/
/*  作者：建大                                               */  
/*  功能：C++字符串类设计和使用                              */  
/*  时间：2008-4-11                                          */  
/*************************************************************/

#include <string.h>
#include <iostream.h>

#include <assert.h>
// 使用assert.h中的assert函数
// assert函数——断言函数，用来确保某一条件为真
// 标准C中该函数类似这样定义
/*
void assert(int expression)
{
	if (!(expression))
	{
		cout<<"错误信息"<<endl;
		exit(0);	// 程序退出
	}
}
*/

#include "CTString.h"

//构造函数 
CTString::CTString()
{
	m_nLen = 0; 
	m_pData = NULL;
}

CTString::CTString(const char *pString)   
{
	 if(pString == NULL)   
	 {
		 m_nLen = 0;
		 m_pData = NULL;
	 } 
	 else   
	 {
		 m_nLen = strlen(pString);      
		 m_pData = new char[m_nLen+1];  // 为什么要+1
		 assert(m_pData != NULL);
		 strcpy(m_pData, pString);                      
	 }
}   
      
//拷贝构造函数    
CTString::CTString(const CTString &srcString)  
{   
	m_nLen = srcString.m_nLen;
	if (m_nLen == 0)
		m_pData = NULL;
	else
	{
		m_pData = new char[m_nLen+1];
		assert( m_pData != NULL);
		strcpy(m_pData, srcString.m_pData);
	}	
}   

//析构函数        
CTString::~CTString()
{
	// 此处的判断是必须的
	if (m_pData != NULL) 
		delete []m_pData;
}   
    
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
CTString* CTString::Copy(CTString *pString)
{
	assert(pString != NULL);

	if (m_pData != NULL) 
		delete m_pData;
	m_nLen = pString->m_nLen;
	if (pString->m_nLen == 0)
	{
		m_pData = NULL;
		return this;
	}

	m_pData = new char[m_nLen+1];
	assert(m_pData != NULL);
	strcpy(m_pData, pString->m_pData);

	return this;
} 

char*  CTString::Find(CTString* pSubString)
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

