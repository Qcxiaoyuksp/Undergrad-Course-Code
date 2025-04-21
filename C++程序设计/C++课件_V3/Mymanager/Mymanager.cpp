// Mymanager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <malloc.h>
class CEmpoyee {
	char * m_pName;
	int m_nAge;
	float m_fSalary;

public:
	CEmpoyee(char * _pName = NULL, int _nAge = 0, float _fSalary = 0.0);
	CEmpoyee(const CEmpoyee &);
	~CEmpoyee();

	void SetName(char*);
	char* GetName();
	void SetAge(int);
	int GetAge();
	void SetSalary(float);
	float GetSalary();
	void Print();
};

CEmpoyee::CEmpoyee(char * _pName, int _nAge, float _fSalary)
{
    //��ʼ����Ա����
	SetAge(0);
	m_pName = NULL;
	SetSalary(0.0);

	if (_fSalary > 0.0 && _nAge > 0 &&  _pName != NULL) //�ݴ���
	{
		SetAge(_nAge);
		SetName(_pName);
		SetSalary(_fSalary);
	}
}

CEmpoyee::CEmpoyee(const CEmpoyee & _CECurrent)
{
	//��ʼ����Ա����
	SetAge(0);
	SetName(NULL);
	SetSalary(0.0);

	SetAge(_CECurrent.m_nAge);
	SetName(_CECurrent.m_pName);
	SetSalary(_CECurrent.m_fSalary);
}

CEmpoyee::~CEmpoyee()
{
	if (m_pName != NULL){
		delete[] m_pName;
	}
	m_pName = NULL;
}

int CEmpoyee::GetAge()
{
	int nRet = -1;
	nRet = m_nAge;

	return nRet;
}

void CEmpoyee::SetAge(int _nAge)
{
	m_nAge = 0;
	if (_nAge > 0){
		m_nAge = _nAge;
	}
}

float CEmpoyee::GetSalary()
{
	float fRet = 0.0;
	fRet = m_fSalary;
	return fRet; 
}

void CEmpoyee::SetSalary(float _fSalary)
{
	m_fSalary = 0.0;
	if (_fSalary > 0.0){
		m_fSalary = _fSalary;
	}
}

char* CEmpoyee::GetName()
{
	char* pRet = NULL;
	pRet = m_pName;
	return pRet;
}

void CEmpoyee::SetName(char* _pName)
{
	int nNameLength = 0;
	int i = 0;
	if (_pName != NULL)	{
		for (i = 0; _pName[i] != '\0'; i++){
			nNameLength = i + 1;
		}
		if (m_pName != NULL){
			delete []m_pName;
			m_pName = NULL;
		}
		else
			m_pName = NULL;

		// copy 
		m_pName = new char [nNameLength + 1];
		memcpy(m_pName, _pName, nNameLength);
		m_pName[nNameLength] = '\0';		
	}
	else
		m_pName = NULL;
}

void CEmpoyee::Print()
{
   cout<<"Empoyee"<<endl;
   cout<<"������ "<<m_pName<<endl;
   cout<<"���䣺"<<m_nAge<<endl;
   cout<<"нˮ�� "<<m_fSalary<<endl;
}

class CManager : public CEmpoyee  
{
	int m_nLevel;

public:
	CManager(char * _pName = NULL, int _nAge = 0, float _fSalary = 0.0, int _nLevel = 0);
	CManager(CEmpoyee&, int);	
	~CManager();

	void SetLevel(int);
	int GetLevel();
	void Print();	
};

CManager::CManager(char * _pName, int _nAge, float _fSalary, int _nLevel)
{
	//�������Ա��������ֱ�ӷ��ʻ��๫�г�Ա����
	//˼��-----�������ĺô�----------(ʵ���˴��������)
	SetAge(0);
	SetName(NULL);
	SetSalary(0.0);	
	
	m_nLevel = 0;
	
	if (_fSalary > 0.0 && _nAge > 0 && _nLevel > 0 && _pName != NULL){
		SetAge(_nAge);
		SetName(_pName);
		SetSalary(_fSalary);	
		m_nLevel = _nLevel;
	}
}

CManager::CManager(CEmpoyee& _CECurrent, int _nLevel)
{
	SetAge(_CECurrent.GetAge());
	SetName(_CECurrent.GetName());
	SetSalary(_CECurrent.GetSalary());
	m_nLevel = 0;
	if (_nLevel > 0){
		m_nLevel = _nLevel;
	}
}

CManager::~CManager()
{

}

void CManager::SetLevel(int _nLevel)
{
	if (_nLevel > 0){
		m_nLevel = _nLevel;
	}
}

int CManager::GetLevel()
{
	int nRet = -1;
	nRet = m_nLevel;

	return nRet;
}

void CManager::Print()
{
   cout<<"CManager"<<endl;
   cout<<"������ "<<GetName()<<endl;
   cout<<"���䣺"<<GetAge()<<endl;
   cout<<"нˮ�� "<<GetSalary()<<endl;
   cout<<"���� "<<GetLevel()<<endl;
}

int main(int argc, char* argv[])
{
	CEmpoyee emp("WangHua",21,1200);

	cout<<"�������캯������emp����emp1--:"<<endl;	
	CEmpoyee emp1(emp);
	emp1.Print();

	cout<<"-------------------------"<<endl;
	CManager cmp(emp, 2);
	emp.Print();
	cout<<"-------------------------"<<endl;
	cmp.Print();

	return 0;
}

