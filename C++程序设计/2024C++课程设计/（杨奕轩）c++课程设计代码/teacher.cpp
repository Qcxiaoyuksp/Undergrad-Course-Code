#include "teacher.h"

//���캯������ȱʡ������ȱʡֵΪundefined����0����������ָ��
Teacher::Teacher(string id, string name, string unit, string phone, int basic_salary,
	int allowence, int income_tax, int accumulation_fund):m_id(id), m_name(name), m_unit(unit),
	m_phone(phone),m_basic_salary(basic_salary), m_allowence(allowence), m_income_tax(income_tax),
	m_accumulation_fund(accumulation_fund){}  

string Teacher::id()
{
	return this->m_id;
}

string Teacher::name()
{
	return this->m_name;
}

string Teacher::unit()
{
	return this->m_unit;
}

string Teacher::phone()
{
	return this->m_phone;
}

int Teacher::basic_salary()
{
	return this->m_basic_salary;
}

int Teacher::allowence()
{
	return this->m_allowence;
}

int Teacher::income_tax()
{
	return this->m_income_tax;
}

int Teacher::accumulation_fund()
{
	return this->m_accumulation_fund;
}

int Teacher::due_salary()
{
	return this->m_basic_salary + m_allowence;
}

int Teacher::total_deduction()
{
	return this->m_income_tax + m_accumulation_fund;
}

int Teacher::actual_salary()
{
	return this->m_basic_salary + m_allowence - m_income_tax - m_accumulation_fund;
}

Teacher & Teacher::operator=(const Teacher & s)
{
	if (&s == this) return *this;  //������Լ���ֵ
	m_id = s.m_id;
	m_name = s.m_name;
	m_unit = s.m_unit;
	m_phone = s.m_phone;
	m_basic_salary = s.m_basic_salary;
	m_allowence = s.m_allowence;
	m_income_tax = s.m_income_tax;
	m_accumulation_fund = s.m_accumulation_fund;
	return *this;
}

ostream & operator<<(ostream & os, Teacher & s)  //setw���������ֶγ���С��n��ʱ���ڸ��ֶ�ǰ���ÿո���,������ֶγ��ȴ���nʱ��ȫ�����������
{
	os << s.m_id << setw(10) << s.m_name << setw(10) << s.m_unit << setw(14) << s.m_phone << setw(10)
		<< s.m_basic_salary << setw(10) << s.m_allowence << setw(10) << s.m_income_tax << setw(10)
		<< s.m_accumulation_fund << setw(10) << s.due_salary() << setw(10) << s.total_deduction()   //������д�ɺ��������и��¡�
		<< setw(10) << s.actual_salary();
	return os;
}

bool operator==(Teacher & left, Teacher & right)
{
	return (left.id() == right.id() && right.name() == left.name() && right.unit() == left.unit()
		&& left.phone() == right.phone() && right.basic_salary() == left.basic_salary() && right.allowence() == left.allowence()
		&& left.income_tax() == right.income_tax() && right.accumulation_fund() == left.accumulation_fund());
}

void Management::swap(int i, int j)   //swap���� 
{
	Teacher t = m_teachers[i];
	m_teachers[i] = m_teachers[j]; 
	m_teachers[j] = t;             //ֻ�����˹��캯���İ˸�������û�ı�Ӧ�����ʡ��ϼƿۿʵ������
}

Management & Management::operator=(const Management & s)
{
	if (&s == this) //������Լ���ֵ
		return *this;  
	m_teachers = s.m_teachers;
	return *this;
}

void Management::displaysys() //��ʾϵͳ�����н�ʦ��Ϣ��setw���������ֶγ���С��n��ʱ���ڸ��ֶ�ǰ���ÿո���,������ֶγ��ȴ���nʱ��ȫ�����������
{
	cout << "��ʦϵͳ��Ϣ���£�" << endl;
	cout << "��ʦ��" << setw(10) << "����" << setw(10) << "ѧԺ" << setw(10) << "�绰" << setw(14) << "��������"
		<< setw(10) << "����" << setw(10) << "����˰" << setw(10) << "������" << setw(10) << "Ӧ������" << setw(10) << "�ϼƿۿ�"
		<< setw(10) << "ʵ������" << endl;
	
	for (int i = 0; i < m_teachers.size(); i++)
	{
		cout << m_teachers[i] << endl;
	}
}

//void Management::displayfile()  //��ʾdata.txt�ļ��Ľ�ʦ��Ϣ
//{
//	ifstream in("data.txt");  //�򿪵�ǰĿ¼�µ��ļ�
//	if (!in.is_open())
//		cout << "���ļ�ʧ�ܡ�" << endl;
//	if (in) //�ļ���
//	{  
//		cout << "�ļ���Ϣ���£�" << endl;
//		while (!in.eof())  //��Ա����eof�ж��ļ����Ƿ����
//		{ 
//			string str;
//			getline(in, str);   //������ʾ
//			cout << str << endl;
//		}
//		in.close();  //�ر��ļ�
//	}
//}

void Management::displayone(int i, int k)  //��ʾvector�е�i+1����ʦ��Ϣ,k=0ʱ�����һ��string��Ϊ1�����
{
	if (i < m_teachers.size())
	{
		if (k == 0)
			cout << "��ʦ��" << setw(10) << "����" << setw(10) << "ѧԺ" << setw(10) << "�绰" << setw(14) << "��������"
				<< setw(10) << "����" << setw(10) << "����˰" << setw(10) << "������" << setw(10) << "Ӧ������" << setw(10) << "�ϼƿۿ�"
				<< setw(10) << "ʵ������" << endl;
		cout << m_teachers[i] << endl;
	}
	else
		cout << "������ʦvector����" << endl;
}

void Management::outfile()    //����д��ԭ�ļ�,����ʾӦ�����ʵ�����
{
	int i;
	ofstream out("data.txt");       //�ڵ�ǰĿ¼�����ļ�,��Ϊ�Ѿ�����data����������д
	if (out) //�ж��ļ��Ƿ�ɹ���
	{                                                 
		out << "��ʦ��" << setw(10) << "����" << setw(10) << "ѧԺ" << setw(10) << "�绰" << setw(14) << "��������"
			<< setw(10) << "����" << setw(10) << "����˰" << setw(10) << "������" << endl;
		for (i = 0; i < m_teachers.size() - 1; i++)            //����д��Ӧ�����ʡ��ϼƿۿʵ�����ʣ������ȡ���ݻ���Ҫ��
		{
			out << m_teachers[i].id() << setw(10) << m_teachers[i].name() << setw(10) << m_teachers[i].unit() << setw(14) <<
				m_teachers[i].phone() << setw(10) << m_teachers[i].basic_salary() << setw(10) << m_teachers[i].allowence()
				<< setw(10) << m_teachers[i].income_tax() << setw(10) << m_teachers[i].accumulation_fund() << endl;
		}
		i = m_teachers.size() - 1;
		out << m_teachers[i].id() << setw(10) << m_teachers[i].name() << setw(10) << m_teachers[i].unit() << setw(14) <<
			m_teachers[i].phone() << setw(10) << m_teachers[i].basic_salary() << setw(10) << m_teachers[i].allowence()
			<< setw(10) << m_teachers[i].income_tax() << setw(10) << m_teachers[i].accumulation_fund();   //�������endl�����һ�С���
		out.close(); //�ر��ļ�
	}
}

void Management::sortfile()  //���������ļ�����ʾӦ�����ʵ�����
{
	int i;
	ofstream out("SortData.txt");
	if (out) //�ж��ļ��Ƿ�ɹ���
	{                                                 
		out << "��ʦ��" << setw(10) << "����" << setw(10) << "ѧԺ" << setw(10) << "�绰" << setw(14) << "��������"
			<< setw(10) << "����" << setw(10) << "����˰" << setw(10) << "������" << setw(10) << "Ӧ������" << setw(10) << "�ϼƿۿ�"
			<< setw(10) << "ʵ������" << endl;
		for (i = 0; i < m_teachers.size() - 1; i++)           
		{
			out << m_teachers[i] << endl;
		}
		i = m_teachers.size() - 1;
		out << m_teachers[i];   //�������endl�����һ��
		out.close(); //�ر��ļ�
	}
}

vector<Teacher> Management::add_from_file()  //��ȡ�ļ�����Ϣ������vector������
{
	string id, name, unit, phone;  //��ʦ�š�������ѧԺ���ơ���ϵ�绰
	int basic_salary, allowence, income_tax, accumulation_fund;  //�������ʡ�����������˰��������
	m_teachers.clear();   //�������
	ifstream in("data.txt");  //�򿪵�ǰĿ¼�µ��ļ�
	if (!in.is_open())
		cout << "error opening file.";
	if (in) //�ļ��� 
	{  
		string str;
		getline(in, str); //ֻ��ȡ��һ�����ݣ����֣��������в���
		while (!in.eof()) //��Ա����eof�ж��ļ����Ƿ����
		{  
			in >> id >> name >> unit >> phone >> basic_salary >> allowence >> income_tax >> accumulation_fund;  //��������
			Teacher t(id, name, unit, phone, basic_salary, allowence, income_tax, accumulation_fund);   //����teacher��ʹ���˹��캯��
			m_teachers.push_back(t);
		}
		in.close();  //�ر��ļ�
	}
	return m_teachers;
}

vector<Teacher> Management::find() //��ȷ���ң�ͨ���������߽�ʦ�Ų���,���ؽ�ʦ����Ϣ������deletionɾ����
{
	vector<Teacher> s;
	string str;
	int i, k = 0, is_exist = 0;
	cout << "�������������ʦ�ţ�";
	cin >> str;
	for (i = 0; i < m_teachers.size(); i++)
	{
		if (str == m_teachers[i].id())   //���Ψһ
		{
			is_exist = i + 1;             //��i+1����ʦ ��1��ʼ
			s.push_back(m_teachers[i]);   //��ӽ�s��
			displayone(i, 0);             //��ʾ��Ϣ ��0��ʼ
			break;                        //����forѭ������Ϊ��ʦ��Ψһ
		}
		else if (str == m_teachers[i].name())  //��Ψһ
		{
			k++;
			is_exist = i + 1;                 //��i+1����ʦ ��1��ʼ
			s.push_back(m_teachers[i]);       //��ӽ�s��
			if (k == 1)
				displayone(i, 0);             //��ʾ��Ϣ �е�һ��string
			else
				displayone(i, 1);             //��ʾ��Ϣ �����ϴ���ʾ������Ҫ����ʾ��һ��string
		}
	}
	if (is_exist == 0)
		cout << "û�иý�ʦ��Ϣ��";
	return s;
}

vector<int> Management::find_seq()  //ͨ���������߽�ʦ�Ų���,���ؽ�ʦ��λ����Ϣ������ţ�����modify�༭��
{
	vector<int> s;
	string str;
	int i, k = 0, is_exist = 0;
	cout << "�������������ʦ�ţ�";
	cin >> str;
	for (i = 0; i < m_teachers.size(); i++)
	{
		if (str == m_teachers[i].id())   //���Ψһ
		{
			is_exist = i + 1;             //��i+1����ʦ ��1��ʼ
			s.push_back(i);				  //��ӽ�s��,0-size-1
			displayone(i, 0);             //��ʾ��Ϣ ��0��ʼ
			break;                        //����forѭ������Ϊ��ʦ��Ψһ
		}
		else if (str == m_teachers[i].name())  //��Ψһ
		{
			k++;
			is_exist = i + 1;                 //��i+1����ʦ ��1��ʼ
			s.push_back(i);					  //��ӽ�s��
			if (k == 1)
				displayone(i, 0);             //��ʾ��Ϣ �е�һ��string
			else
				displayone(i, 1);             //��ʾ��Ϣ �����ϴ���ʾ������Ҫ����ʾ��һ��string
		}
	}
	if (is_exist == 0)
		cout << "û�иý�ʦ��Ϣ��";
	return s;
}

vector<int> Management::find_range()  //��Χ����, ����Ӧ�����ʡ�ʵ�����ʡ���������ָ����Χ�ڵĽ�ʦ����,���ص�ַ
{
	int min, max, mark, i, money, is_exist = 0, k = 0;
	vector<int> s;
	cout << "��������������Ϣ��Ӧ�����֣�1��Ӧ������ 2��ʵ������ 3��������";
	cin >> mark;
	cout << "��������������Ϣ��Ӧ�Ľ����С�����ֵ���м��ÿո��������";
	cin >> min >> max;
	for (i = 0; i < m_teachers.size(); i++)
	{
		switch (mark)
		{
		case 1: 
			money = m_teachers[i].due_salary(); 
			break;
		case 2: 
			money = m_teachers[i].actual_salary(); 
			break;
		case 3: 
			money = m_teachers[i].accumulation_fund(); 
			break;
		default: 
			cout << "�������ִ����˳���ѯ��" << endl; 
			return vector<int>();
		}
		if (money <= max && money >= min)   //�����Ψһ
		{
			k++;
			is_exist = i + 1;             //��i+1����ʦ ��1��ʼ
			s.push_back(i);				  //��ӽ�s��
			if (k == 1)
				displayone(i, 0);             //��ʾ��Ϣ �е�һ��string
			else
				displayone(i, 1);             //��ʾ��Ϣ �����ϴ���ʾ������Ҫ����ʾ��һ��string
		}
	}
	if (is_exist == 0)
		cout << "û�д��ڸ÷�Χ�Ľ�ʦ��Ϣ��" << endl;
	return s;
}

int Management::fuzzyfind()  //ģ������,�����������֡�ѧԺ��Ϣ���绰��һ���֣������г��������������м�¼,����λ����Ϣ
{
	string str;
	vector<int> s;
	int i, j, k, m, n, sequence = 0;
	cout << "ִ��ģ�������������������֡�ѧԺ��Ϣ��绰�Ĳ�����Ϣ: " << endl;
	cin >> str;
	for (i = 0; i < m_teachers.size(); i++)
	{
		for (j = 0; j < str.size(); j++) //id��ѯ
		{          
			if (str[j] != (m_teachers[i].id())[j])
				break;
		}
		if (j == str.size()) //���λ����Ϣ
		{
			s.push_back(i);           
		}

		for (k = 0; k < str.size(); k++) //name��ѯ
		{                 
			if (str[k] != (m_teachers[i].name())[k])
				break;
		}
		if (k == str.size()) //���λ����Ϣ
		{
			s.push_back(i);           
		}

		for (m = 0; m < str.size(); m++) //ѧԺ��ѯ
		{          
			if (str[m] != (m_teachers[i].unit())[m])
				break;
		}
		if (m == str.size()) //���λ����Ϣ
		{
			s.push_back(i);           
		}

		for (n = 0; n < str.size(); n++) //�绰��ѯ
		{          
			if (str[n] != (m_teachers[i].phone())[n])
				break;
		}
		if (n == str.size()) //���λ����Ϣ
		{
			s.push_back(i);           
		}
	}
	//��ʾģ����ѯ����Ϣ
	if (s.size() == 0) {
		cout << "δ��ѯ��������Ϣ��" << endl;
		return 0;
	}
	else if (s.size() == 1) {
		displayone(s[0], 0);             //��ʾ��Ϣ �е�һ��string
	}
	else {
		displayone(s[0], 0);             //��ʾ��Ϣ �е�һ��string
		for (i = 1; i < s.size(); i++)
			displayone(s[i], 1);         //����ʾstring 
	}
	//���ж���ѡ��
	if (s.size() == 1);              //ϵͳ��һλ���������Ľ�ʦ
	else {                         //ϵͳ�ж�λ���������Ľ�ʦ
		cout << "������1-" << s.size() << "��������Ŵ���ѡ���ʦ��Ϣ��" << endl;
		cin >> sequence;
		sequence--;       //��ɴ�0��ʼ��λ����Ϣ
		cout << "��ѡ��Ľ�ʦ��Ϣ���£�" << endl;
		displayone(s[sequence], 0);
	}
	return sequence;
}

void Management::modify()  //�޸Ľ�ʦ��Ϣ
{
	string id, name, unit, phone;  //��ʦ�š�������ѧԺ���ơ���ϵ�绰
	int basic_salary, allowence, income_tax, accumulation_fund, mark, dir, sequence = 0;  //�������ʡ�����������˰��������
	cout << "����ѡ���޸Ľ�ʦ��Ϣ��";
	vector<int> s = find_seq();
	int num = s.size();            //��ȡ���������Ľ�ʦ����
	if (num == 0)                  //��ѯ�޴���
		cout << "�޷��޸ġ�" << endl;
	else                           //�н�ʦ��Ϣ
	{
		if (num == 1);												//ϵͳ��һλ���������Ľ�ʦ
		else                                                        //ϵͳ�ж�λ���������Ľ�ʦ
		{
			cout << "������1-" << num << "��������Ŵ�������Ҫ�޸ĵĽ�ʦ��Ϣ��" << endl;
			cin >> sequence;
			sequence--;       //��ɴ�0��ʼ��λ����Ϣ
		}
		dir = s[sequence];  //���ֻ��һ�ˣ�s[0]λ�õ����־��Ǹý�ʦ��m_teachers�����е�λ�ã�
		cout << "��Ҫ�޸���һ��Ϣ��(1.��ʦ�� 2.���� 3.ѧԺ 4.�绰 5.�������� 6.���� 7.����˰ 8.������ 0.����)" << endl;
		cin >> mark;
		if (mark == 0) {
			cout << "��ѡ���˳��޸ģ��޸�ʧ�ܡ�" << endl;
			return;
		}
		cout << "�������޸���Ϣ��";
		switch (mark)
		{
			case 1: 
				cin >> id; 
				m_teachers[dir].change_id(id); 
				break;
			case 2: 
				cin >> name; 
				m_teachers[dir].change_name(name); 
				break;
			case 3: 
				cin >> unit; 
				m_teachers[dir].change_unit(unit); 
				break;
			case 4: 
				cin >> phone; 
				m_teachers[dir].change_phone(phone); 
				break;
			case 5: 
				cin >> basic_salary; 
				m_teachers[dir].change_basic_salary(basic_salary); 
				break;
			case 6: 
				cin >> allowence; 
				m_teachers[dir].change_allowence(allowence); 
				break;
			case 7: 
				cin >> income_tax; m_teachers[dir].change_income_tax(income_tax); 
				break;
			case 8: 
				cin >> accumulation_fund; m_teachers[dir].change_accumulation_fund(accumulation_fund); 
				break;
			default:
				break;
		}
		outfile();     //�����ļ�
		cout << "�޸ĳɹ�!�޸ĺ�ĸý�ʦ��Ϣ��ʾ���£�" << endl;
		displayone(dir, 0);
	}	
}

void Management::addition()  //���ӽ�ʦ��Ϣ
{
	string id, name, unit, phone;  //��ʦ�š�������ѧԺ���ơ���ϵ�绰
	int basic_salary, allowence, income_tax, accumulation_fund, k, is_exist = 0;  //�������ʡ�����������˰��������
	while (1)
	{
		cout << "�������ʦ��Ϣ����ʦ�š�������ѧԺ���ơ���ϵ�绰���������ʡ�����������˰��������" << endl;
		cin >> id >> name >> unit >> phone >> basic_salary >> allowence >> income_tax >> accumulation_fund;
		for (int i = 0; i < m_teachers.size(); i++)
		{
			if (id == m_teachers[i].id() && name == m_teachers[i].name()) {
				cout << "�Ѿ����ڸý�ʦ��Ϣ" << endl;
				is_exist = 1;
			}
		}
		if (is_exist == 0)         //vector��û�н�ʦ��Ϣ�������
		{
			Teacher t(id, name, unit, phone, basic_salary, allowence, income_tax, accumulation_fund);   //����teacher��ʹ���˹��캯��
			m_teachers.push_back(t);
			cout << "���ӳɹ����¼ӽ�ʦ��Ϣ����" << endl;
			displayone(m_teachers.size() - 1, 0);
			outfile();     //�����ļ�
		}
		is_exist = 0;   //������0���Ա�����´��ж�
		cout << "�Ƿ�������ӽ�ʦ��Ϣ�������밴1���˳��밴0��" << endl;
		cin >> k;
		if (k == 0)
			break;
	}
}

void Management::deletion()   //ɾ����ʦ��Ϣ
{
	int m, n, sequence, count = 0;	//m��ʾ��ȷ���Ƿ�ɾ����n��ʾѡ��ɾ����λorһλ��ʦ��//sequence��ʾɾ��һλ��ʦʱ��Ӧ��š�count��ʾɾ�����н�ʦ��Ӧ���Լ�
	cout << "����ѡ��ɾ����ʦ��Ϣ��" ;
	vector<Teacher> s = find();
	vector<Teacher>::iterator itor;
	int num = s.size();            //��ȡ���������Ľ�ʦ����
	if (num == 0)
		cout << "�޷�ɾ����" << endl;
	else if (num == 1)                                           //ϵͳ��һλ���������Ľ�ʦ
	{
		cout << "�Ƿ�ȷ��ɾ���ý�ʦ��Ϣ�������밴1���˳��밴0��" << endl;
		cin >> m;
		if (m == 1) {
			for (itor = m_teachers.begin(); itor != m_teachers.end();)
			{
				if (*itor == s[0])   //s����һ����ʦ��Ϣ����s[0]
				{
					itor = m_teachers.erase(itor);	  //��Ϊɾ��һ��Ԫ��֮�󣬵������Ѿ�ָ���˱�ɾ��Ԫ�ص���һ��Ԫ��
					break;           //��Ϊ��ֻ��һ�����ҵ���������������治����itorʱ��û��break�ᱨ��
				}
				else itor++;
			}
			cout << "ɾ���ɹ���" << endl;
			outfile();     //�����ļ�
		}
		if (m == 0)
			cout << "����ȡ��ɾ���ý�ʦ��Ϣ��ɾ��ʧ�ܡ�" << endl;		
	}	
	else   //ϵͳ�ж�λ���������Ľ�ʦ
	{
		cout << "������������Ϣ�Ľ�ʦ�ж�λ��ɾ��ȫ���밴1��ɾ��һλ�밴0��" << endl;
		cin >> n;
		if (n == 1) {                                          //ɾ���������������н�ʦ 
			cout << "�Ƿ�ȷ��ɾ��ȫ����ʦ��Ϣ�������밴1���˳��밴0��" << endl;
			cin >> m;
			if (m == 1) {
				for (itor = m_teachers.begin(); itor != m_teachers.end();)       
				{
					if (count < num) {
						if (*itor == s[0 + count])  //i++���ؼ�1ǰ��ֵ��
						{
							count++;
							itor = m_teachers.erase(itor);
						}
						else  itor++;
					}
					else 
						break;
				}
				cout << "ɾ���ɹ���" << endl;
				outfile();     //�����ļ�
			}
			if (m == 0)
				cout << "����ȡ��ɾ���ý�ʦ��Ϣ��ɾ��ʧ�ܡ�" << endl;
		}
		else 
		{
			cout << "������1-" << num << "��������Ŵ�������Ҫɾ���Ľ�ʦ��Ϣ��" << endl;
			cin >> sequence;
			cout << "�Ƿ�ȷ��ɾ���ý�ʦ��Ϣ�������밴1���˳��밴0��" << endl;
			cin >> m;
			if (m == 1) {
				for (itor = m_teachers.begin(); itor != m_teachers.end();)
				{
					if (*itor == s[sequence - 1])
					{
						itor = m_teachers.erase(itor);
						break;                      //ɾ��һλ
					}
					else itor++;
				}
				cout << "ɾ���ɹ���" << endl;
				outfile();     //�����ļ�
			}
			if (m == 0)
				cout << "����ȡ��ɾ���ý�ʦ��Ϣ��ɾ��ʧ�ܡ�" << endl;
		}
	}
}

double Management::average(string & str, string &u)   //�����ַ����ж�������ƽ������,����ƽ�������
{
	int i, num = 0;
	double money = 0;
	for (i = 0; i < m_teachers.size(); i++)
	{
		if (m_teachers[i].unit() != u)
			continue;                 
		num++;
		if (str == "basic_salary") 
			money += m_teachers[i].basic_salary();
		else if (str == "allowence") 
			money += m_teachers[i].allowence();
		else if (str == "income_tax") 
			money += m_teachers[i].income_tax();
		else if (str == "accumulation_fund") 
			money += m_teachers[i].accumulation_fund();
		else if (str == "due_salary") 
			money += m_teachers[i].due_salary();
		else if (str == "total_deduction") 
			money += m_teachers[i].total_deduction();
		else if (str == "actual_salary") 
			money += m_teachers[i].actual_salary();
	}
	if (num != 0)
		money = money / num;
	return money;
}

double Management::deviation(string & str, string &u)  //���׼��
{
	int i, num = 0;
	double avg, money = 0;
	avg = average(str, u);
	for (i = 0; i < m_teachers.size(); i++)
	{
		if (m_teachers[i].unit() != u)
			continue;
		num++;
		if (str == "basic_salary") 
			money += pow(m_teachers[i].basic_salary() - avg, 2);
		else if (str == "allowence") 
			money += pow(m_teachers[i].allowence() - avg, 2);
		else if (str == "income_tax") 
			money += pow(m_teachers[i].income_tax() - avg, 2);
		else if (str == "accumulation_fund") 
			money += pow(m_teachers[i].accumulation_fund() - avg, 2);
		else if (str == "due_salary") 
			money += pow(m_teachers[i].due_salary() - avg, 2);
		else if (str == "total_deduction") 
			money += pow(m_teachers[i].total_deduction() - avg, 2);
		else if (str == "actual_salary") 
			money += pow(m_teachers[i].actual_salary() - avg, 2);
	}
	if (num != 0)
		money = sqrt(money / num);
	return money;
}

void Management::average()   //����ƽ�����ʣ���������ʱ�׼��
{
	int mark;
	double avg, std;  //ƽ��ֵ����׼��
	string str, u;
	cout << "��������ѧԺ���ƣ�";
	cin >> u;
	cout << "��������������Ӧ��ƽ�����ʣ�1���������� 2������ 3������˰ 4�������� 5��Ӧ������ 6���ϼƿۿ� 7��ʵ������" << endl;
	cin >> mark;
	switch (mark)
	{
		case 1: 
			str = "basic_salary"; 
			break;
		case 2: 
			str = "allowence"; 
			break;
		case 3: 
			str = "income_tax"; 
			break;
		case 4: 
			str = "accumulation_fund"; 
			break;
		case 5: 
			str = "due_salary"; 
			break;
		case 6: 
			str = "total_deduction"; 
			break;
		case 7: 
			str = "actual_salary"; 
			break;
		default:
			break;
	}
	avg = average(str,u); 
	std = deviation(str,u);
	if (avg == 0.0) cout << "ѧԺ�������" << endl;
	else
		cout << "ƽ��ֵΪ" << avg << setw(10) << "��׼��Ϊ" << std << endl;
}

void Management::SectionSort()  //ѡ������
{
	int num = m_teachers.size();
	for (int i = 0; i < num - 1; i++) //iȡֵ���Ϊǰn-1������jȡֵΪ��i+1-n
	{				 
		int max = i;								 //��¼���������������Ԫ��λ�� 
		for (int j = i + 1; j < num; j++) {
			int m1 = m_teachers[max].actual_salary(), n1 = m_teachers[j].actual_salary();
			int m2 = m_teachers[max].accumulation_fund(), n2 = m_teachers[j].accumulation_fund();
			string m3 = m_teachers[max].id(), n3 = m_teachers[j].id();
			if (m1 < n1)
				max = j;							 //�������Ԫ��λ�� 
			else if (m1 == n1)
			{
				if (m2 < n2)
					max = j;
				else if (m2 == n2) 
				{
					if (m3 < n3)   //��ʦ��Ψһ�����������
						max = j;
				}
			}
		}
		swap(i, max);		 // ����swap����,�����Ԫ�طŵ�λ��i
	}
	sortfile();        //���������ļ���"SortData.txt"
}

