//CPP�ļ��������ʵ���ļ�   
/*************************************************************/
/*  ���ߣ�����                                               */  
/*  ���ܣ�C++�ַ�������ƺ�ʹ��                              */  
/*  ʱ�䣺2008-4-11                                          */  
/*************************************************************/

#include <string.h>
#include <iostream.h>

#include <assert.h>
// ʹ��assert.h�е�assert����
// assert�����������Ժ���������ȷ��ĳһ����Ϊ��
// ��׼C�иú���������������
/*
void assert(int expression)
{
	if (!(expression))
	{
		cout<<"������Ϣ"<<endl;
		exit(0);	// �����˳�
	}
}
*/

#include "CTString.h"

//���캯�� 
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
		 m_pData = new char[m_nLen+1];  // ΪʲôҪ+1
		 assert(m_pData != NULL);
		 strcpy(m_pData, pString);                      
	 }
}   
      
//�������캯��    
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

//��������        
CTString::~CTString()
{
	// �˴����ж��Ǳ����
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

// ���������дPrint������˼������������ʱ�����
void CTString::Print()
{
	cout<<"-------------------------------------------"<<endl;
	cout<<"���ַ�����ֵ��"<<m_pData<<endl;	// ˼��...
	cout<<"���ַ����ĳ��ȣ�"<<m_nLen<<endl;
	cout<<"-------------------------------------------"<<endl;
	cout<<endl;
}

