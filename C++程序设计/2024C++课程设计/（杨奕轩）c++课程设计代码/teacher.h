#ifndef TEACHER_H
#define TEACHER_H
#include <math.h>   //使用数学函数
#include <vector>   //使用迭代器 
#include <string>   //使用字符串
#include <iomanip>  //使用stew函数
#include <fstream>  //文件输入输出。ifstream从已有的文件读入, ofstream向文件写内容, fstream 打开文件供读写
#include <iostream>   //输入输出流 
using namespace std;  

//教师类 
class Teacher {     
private:
	string m_id, m_name, m_unit, m_phone;                                //教师号、姓名、学院名称、联系电话
	int m_basic_salary, m_allowence, m_income_tax, m_accumulation_fund;  //基本工资、津贴、所得税、公积金
	int m_due_salary = m_basic_salary + m_allowence;                     //应发工资
	int m_total_deduction = m_income_tax + m_accumulation_fund;          //合计扣款
	int m_actual_salary = m_due_salary - m_total_deduction;              //实发工资

public:
	//构造函数
	Teacher(string id = "undefined", string name = "undefined", string unit = "undefined", string phone = "undefined",
		int basic_salary = 0, int allowence = 0, int income_tax = 0, int accumulation_fund = 0);  
	//复制构造函数
	Teacher(const Teacher &rhs) :m_id(rhs.m_id), m_name(rhs.m_name), m_unit(rhs.m_unit), m_phone(rhs.m_phone), 
		m_basic_salary(rhs.m_basic_salary), m_allowence(rhs.m_allowence), m_income_tax(rhs.m_income_tax),
		m_accumulation_fund(rhs.m_accumulation_fund){}
    //析构函数，在此函数体为空 
	~Teacher(){}       
	//返回教师信息的11个函数
	string id();	
	string name();	
	string unit();	
	string phone();
	int basic_salary();		
	int allowence();	
	int income_tax();	
	int accumulation_fund();
	int due_salary();	
	int total_deduction();	
	int actual_salary();
	//修改信息的8个函数
	void change_id(string m) { m_id = m; };
	void change_name(string m) { m_name = m; };
	void change_unit(string m) { m_unit = m; };
	void change_phone(string m) { m_phone = m; };
	void change_basic_salary(int m) { m_basic_salary = m; };
	void change_allowence(int m) { m_allowence = m; };
	void change_income_tax(int m) { m_income_tax = m; };
	void change_accumulation_fund(int m) { m_accumulation_fund = m; };
	Teacher& operator =(const Teacher &s);   //赋值运算符
	friend ostream& operator<<(ostream &os, Teacher &s);
};
//辅助函数说明
ostream& operator<<(ostream &os, Teacher &s);
//普通函数声明
bool operator==(Teacher &left, Teacher &right);//重载==

// 管理类 
class Management {
private:
	vector<Teacher> m_teachers;
	void swap(int i, int j);          //swap交换两个位置的Teacher
public:
	Management& operator =(const Management &s);   //赋值运算符
	void displaysys();                //显示系统内已有教师信息
//	void displayfile();               //显示data文件的教师信息
	void displayone(int i,int k);     //显示vector中第i+1个教师信息,k=0时输出第一行string，为1不输出
	void outfile();                   //重新写入原文件
	void sortfile();                  //存放排序后文件
	vector<Teacher> add_from_file();  //读取文件的信息并加入vector容器中
	vector<Teacher> find();           //通过姓名或者教师号查找,返回教师的信息，用于deletion中
	vector<int> find_seq();			  //通过姓名或者教师号查找,返回教师的位置信息，即序号，用于modify中
	vector<int> find_range();         //查找应发工资、实发工资、公积金处于指定范围内的教师名单,返回地址
	int fuzzyfind();                  //模糊查找,根据输入名字、学院信息、电话的一部分，可以列出满足条件的所有记录,返回位置信息
	void modify();                    //修改教师信息
	void addition();                  //增加教师信息
	void deletion();                  //删除教师信息
	double average(string &str, string &u);      //单项平均工资,返回平均单项工资
	double deviation(string &str, string &u);     //返回标准差
	void average();                   //总项平均工资，并输出工资标准差
	void SectionSort();               //排序算法，选择法排序，找出最大放在第一个位置，依次
};

#endif
