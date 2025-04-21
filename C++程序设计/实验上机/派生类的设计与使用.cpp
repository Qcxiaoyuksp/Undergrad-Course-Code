#include<iostream>
#include<cstring>
using namespace std;

class CEmpoyee
{
public:
	char* m_pName;//姓名
	int m_nAge; //年龄
	float m_fSalary;//薪水
public:
	//构造函数和析构函数
	CEmpoyee(char* pName = NULL, int age = 0, float salary = 0.0);
	CEmpoyee(const CEmpoyee&);
	virtual ~CEmpoyee();
	//其他成员函数
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
	int m_nlevel;//级别
public:
	//构造函数和析构函数
	CManager(char* pName = NULL, int age = 0, float salary = 0.0, int nLevel = 0);
	CManager(const CEmpoyee&, int);
	~CManager();

	//其他成员函数
	void SetLevel(int);
	int GetLevel();
	void Print();
};

// CEmpoyee 成员函数： 
//构造函数
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

//拷贝构造函数
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

//析构函数
CEmpoyee::~CEmpoyee()
{
	if (this->m_pName != NULL)
	{
		delete[] this->m_pName;
		this->m_pName = NULL;
	}
}

//设置名字
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

//获取名字
char* CEmpoyee::Getname()
{
	return this->m_pName;
}

//设置年龄
void CEmpoyee::SetAge(int age)
{
	this->m_nAge = age;
}

//获取年龄
int CEmpoyee::GetAge()
{
	return this->m_nAge;
}

//设置薪水
void CEmpoyee::SetSalary(float salary)
{
	this->m_fSalary = salary;
}

//获取薪水
float CEmpoyee::Getsalary()
{
	return this->m_fSalary;
}

//打印信息
void CEmpoyee::Print()
{
	cout << "姓名：" << this->Getname() << " 年龄：" << this->GetAge() << " 工资：" << this->Getsalary() << endl;
}

// CManager 成员函数： 
//构造函数
CManager::CManager(char* pName, int age, float salary, int nLevel) :CEmpoyee(pName, age, salary)
{
	this->m_nlevel = nLevel;
}

//拷贝构造函数
CManager::CManager(const CEmpoyee& Empoyee, int level) :CEmpoyee(Empoyee)
{
	this->m_nlevel = level;
}

//析构函数
CManager::~CManager()
{}

//设置级别
void CManager::SetLevel(int level)
{
	this->m_nlevel = level;
}

//获取级别
int CManager::GetLevel()
{
	return this->m_nlevel;
}

//打印输出
void CManager::Print()
{
	cout << "姓名：" << this->Getname() << " 年龄：" << this->GetAge() << " 薪资：" << this->Getsalary() << " 级别：" << this->GetLevel() << endl;
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
