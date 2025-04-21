#ifndef TEACHER_H
#define TEACHER_H
#include <math.h>   //ʹ����ѧ����
#include <vector>   //ʹ�õ����� 
#include <string>   //ʹ���ַ���
#include <iomanip>  //ʹ��stew����
#include <fstream>  //�ļ����������ifstream�����е��ļ�����, ofstream���ļ�д����, fstream ���ļ�����д
#include <iostream>   //��������� 
using namespace std;  

//��ʦ�� 
class Teacher {     
private:
	string m_id, m_name, m_unit, m_phone;                                //��ʦ�š�������ѧԺ���ơ���ϵ�绰
	int m_basic_salary, m_allowence, m_income_tax, m_accumulation_fund;  //�������ʡ�����������˰��������
	int m_due_salary = m_basic_salary + m_allowence;                     //Ӧ������
	int m_total_deduction = m_income_tax + m_accumulation_fund;          //�ϼƿۿ�
	int m_actual_salary = m_due_salary - m_total_deduction;              //ʵ������

public:
	//���캯��
	Teacher(string id = "undefined", string name = "undefined", string unit = "undefined", string phone = "undefined",
		int basic_salary = 0, int allowence = 0, int income_tax = 0, int accumulation_fund = 0);  
	//���ƹ��캯��
	Teacher(const Teacher &rhs) :m_id(rhs.m_id), m_name(rhs.m_name), m_unit(rhs.m_unit), m_phone(rhs.m_phone), 
		m_basic_salary(rhs.m_basic_salary), m_allowence(rhs.m_allowence), m_income_tax(rhs.m_income_tax),
		m_accumulation_fund(rhs.m_accumulation_fund){}
    //�����������ڴ˺�����Ϊ�� 
	~Teacher(){}       
	//���ؽ�ʦ��Ϣ��11������
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
	//�޸���Ϣ��8������
	void change_id(string m) { m_id = m; };
	void change_name(string m) { m_name = m; };
	void change_unit(string m) { m_unit = m; };
	void change_phone(string m) { m_phone = m; };
	void change_basic_salary(int m) { m_basic_salary = m; };
	void change_allowence(int m) { m_allowence = m; };
	void change_income_tax(int m) { m_income_tax = m; };
	void change_accumulation_fund(int m) { m_accumulation_fund = m; };
	Teacher& operator =(const Teacher &s);   //��ֵ�����
	friend ostream& operator<<(ostream &os, Teacher &s);
};
//��������˵��
ostream& operator<<(ostream &os, Teacher &s);
//��ͨ��������
bool operator==(Teacher &left, Teacher &right);//����==

// ������ 
class Management {
private:
	vector<Teacher> m_teachers;
	void swap(int i, int j);          //swap��������λ�õ�Teacher
public:
	Management& operator =(const Management &s);   //��ֵ�����
	void displaysys();                //��ʾϵͳ�����н�ʦ��Ϣ
//	void displayfile();               //��ʾdata�ļ��Ľ�ʦ��Ϣ
	void displayone(int i,int k);     //��ʾvector�е�i+1����ʦ��Ϣ,k=0ʱ�����һ��string��Ϊ1�����
	void outfile();                   //����д��ԭ�ļ�
	void sortfile();                  //���������ļ�
	vector<Teacher> add_from_file();  //��ȡ�ļ�����Ϣ������vector������
	vector<Teacher> find();           //ͨ���������߽�ʦ�Ų���,���ؽ�ʦ����Ϣ������deletion��
	vector<int> find_seq();			  //ͨ���������߽�ʦ�Ų���,���ؽ�ʦ��λ����Ϣ������ţ�����modify��
	vector<int> find_range();         //����Ӧ�����ʡ�ʵ�����ʡ���������ָ����Χ�ڵĽ�ʦ����,���ص�ַ
	int fuzzyfind();                  //ģ������,�����������֡�ѧԺ��Ϣ���绰��һ���֣������г��������������м�¼,����λ����Ϣ
	void modify();                    //�޸Ľ�ʦ��Ϣ
	void addition();                  //���ӽ�ʦ��Ϣ
	void deletion();                  //ɾ����ʦ��Ϣ
	double average(string &str, string &u);      //����ƽ������,����ƽ�������
	double deviation(string &str, string &u);     //���ر�׼��
	void average();                   //����ƽ�����ʣ���������ʱ�׼��
	void SectionSort();               //�����㷨��ѡ�������ҳ������ڵ�һ��λ�ã�����
};

#endif
