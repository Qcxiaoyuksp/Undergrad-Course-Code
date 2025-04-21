#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class CTString
{
	char *m_pData; // �����ַ����� ��ָ�� 
	int m_nLen; // ��¼�ַ����� 
	static int number; // ��¼ ����ĸ���  
	
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
		
		// ��̬��Ա���� 
		static int GetNumber();
};

int CTString::number = 0; // ��̬��Ա������ʼ��

// �޲ι��캯��
CTString::CTString()
{
	m_nLen = 0;
	m_pData = NULL;
	number++; 
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
	number++; 
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
	number++; 
 } 

// ��������
CTString::~CTString()
{
	if (m_pData != NULL)
		delete []m_pData;
	number--; 
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

// ��ȡ�������
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
	//s1.Print();	// ����������
	
	cout<<"------�����ַ���----------------"<<endl;
	s2.Connect(&s4);
	s2.Print();

	cout<<"------�����ַ���----------------"<<endl;
	char *pstr = NULL;
	pstr = s2.Find(&s6);
	if (pstr != NULL)
	{
		cout << pstr << endl;
	} 
	
	cout << "###" << endl;
	cout << "��ǰ����������" << CTString::GetNumber() << endl; // �����������
	cout << "###" << endl;

	return 0;
	  
}
