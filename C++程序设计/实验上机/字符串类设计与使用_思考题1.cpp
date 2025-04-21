#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class CTString
{
	char *m_pData; // �����ַ����� ��ָ�� 
	int m_nLen; // ��¼�ַ����� 
	
	public:
		// ���캯�� 
		CTString();
		CTString(const char*);
		CTString(const CTString&); // �������캯�� 
		// �������� 
		~CTString();
		
		// ������Ա����
		CTString* Copy(CTString*); // ����
		CTString* Connect(CTString*); // ����
		char* Find(CTString*);
		//char* Find(char);
		void Print(); 
};

// �޲ι��캯��
CTString::CTString()
{
	m_nLen = 0;
	m_pData = NULL;
} 

// �вι��캯�� 
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
		m_pData = new char[m_nLen + 1]; // �����±��1��ʼ��Ҫ+1
		assert(m_pData != NULL);
		strcpy(m_pData, pString); 
	}
}

// �������캯��
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

// ��������
CTString::~CTString()
{
	if (m_pData != NULL)
		delete []m_pData;
}

// ��Ա���� 
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

// find �ַ��� 
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

// ���������дPrint������˼������������ʱ�����
void CTString::Print()
{
	cout<<"-------------------------------------------"<<endl;
	cout<<"���ַ�����ֵ��"<<m_pData<<endl;	// ˼��...
	cout<<"���ַ����ĳ��ȣ�"<<m_nLen<<endl;
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
���� 145	20	E:\C++�������\ʵ���ϻ�\�ַ����������ʹ��_˼����1.cpp	[Error] no matching function for call to 'CTString::Copy(const char [6])'
ԭ�򣺴���Ĳ������Ͳ���ȷ����Ҫ������� CTString��ʵ�����Ķ��󣬲������ַ��������� Copy("hello") ���� 
*/
