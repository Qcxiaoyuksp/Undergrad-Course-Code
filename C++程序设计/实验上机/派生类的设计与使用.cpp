#include<iostream>
#include<cstring>
using namespace std;

class CEmpoyee
{
public:
	char* m_pName;//����
	int m_nAge; //����
	float m_fSalary;//нˮ
public:
	//���캯������������
	CEmpoyee(char* pName = NULL, int age = 0, float salary = 0.0);
	CEmpoyee(const CEmpoyee&);
	virtual ~CEmpoyee();
	//������Ա����
	void SetName(char* p_name);
	char* Getname();
	void SetAge(int age);
	int GetAge();
	void SetSalary(float salary);
	float Getsalary();
	void Print();
};

//class CManager :private CEmpoyee
class CManager :public CEmpoyee
{
public: 
	int m_nlevel;//����
public:
	//���캯������������
	CManager(char* pName = NULL, int age = 0, float salary = 0.0, int nLevel = 0);
	CManager(const CEmpoyee&, int);
	~CManager();

	//������Ա����
	void SetLevel(int);
	int GetLevel();
	void Print();
};

// CEmpoyee ��Ա������ 
//���캯��
CEmpoyee::CEmpoyee(char* pName, int age, float salary)
{
	if (pName == NULL)
	{
		return;
	}
	this->m_pName = new char[strlen(pName) + 1];
	strcpy(this->m_pName, pName);
	//for (int i = 0; i <= strlen(pName); i++)
	//{
	//	this->m_pName[i] = pName[i];
	//}
	this->m_nAge = age;
	this->m_fSalary = salary;
}

//�������캯��
CEmpoyee::CEmpoyee(const CEmpoyee& empoyee)
{
	if (empoyee.m_pName != NULL)
	{
		this->m_pName = new char[strlen(empoyee.m_pName) + 1];
		strcpy(this->m_pName, empoyee.m_pName); 
	}
	else{
		this->m_pName = NULL;
	}
//	for (int i = 0; i <= strlen(empoyee.m_pName); i++)
//	{
//		this->m_pName[i] = empoyee.m_pName[i];
//	}
	this->m_nAge = empoyee.m_nAge;
	this->m_fSalary = empoyee.m_fSalary;
}

//��������
CEmpoyee::~CEmpoyee()
{
	if (this->m_pName != NULL)
	{
		delete[] this->m_pName;
		this->m_pName = NULL;
	}
}

//��������
void CEmpoyee::SetName(char* p_name)
{
	if (this->m_pName != NULL)
	{
		delete[] this->m_pName;
		this->m_pName = NULL;
	}
	if (p_name != NULL)
	{
		this->m_pName = new char[strlen(p_name) + 1];
		strcpy(this->m_pName, p_name);
	}
	else 
	{
		this->m_pName = NULL;
	}
}

//��ȡ����
char* CEmpoyee::Getname()
{
	return this->m_pName;
}

//��������
void CEmpoyee::SetAge(int age)
{
	this->m_nAge = age;
}

//��ȡ����
int CEmpoyee::GetAge()
{
	return this->m_nAge;
}

//����нˮ
void CEmpoyee::SetSalary(float salary)
{
	this->m_fSalary = salary;
}

//��ȡнˮ
float CEmpoyee::Getsalary()
{
	return this->m_fSalary;
}

//��ӡ��Ϣ
void CEmpoyee::Print()
{
	cout << "������" << this->Getname() << " ���䣺" << this->GetAge() << " ���ʣ�" << this->Getsalary() << endl;
}

// CManager ��Ա������ 
//���캯��
CManager::CManager(char* pName, int age, float salary, int nLevel) :CEmpoyee(pName, age, salary)
{
	this->m_nlevel = nLevel;
}

//�������캯��
CManager::CManager(const CEmpoyee& Empoyee, int level) :CEmpoyee(Empoyee)
{
	this->m_nlevel = level;
}

//��������
CManager::~CManager()
{}

//���ü���
void CManager::SetLevel(int level)
{
	this->m_nlevel = level;
}

//��ȡ����
int CManager::GetLevel()
{
	return this->m_nlevel;
}

//��ӡ���
void CManager::Print()
{
	cout << "������" << this->Getname() << " ���䣺" << this->GetAge() << " н�ʣ�" << this->Getsalary() << " ����" << this->GetLevel() << endl;
}


int main()
{	
	CEmpoyee one("First", 10, 10000);
	CEmpoyee two("Second", 20, 20000);
	CEmpoyee three(two);
	
	one.Print();
	two.Print();
	three.Print();
	
	CManager four("Fourth", 40, 40000, 4);
	CManager five(three, 5);
	five.SetLevel(6);
	
	four.Print();
	five.Print();
	
	cout << "Level of five: " << five.GetLevel() << endl;
	cout << "Size of CManager: " << sizeof(five) << endl;
	
	return 0;
}
