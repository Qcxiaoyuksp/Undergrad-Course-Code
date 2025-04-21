#include "teacher.h"

//构造函数，带缺省参数，缺省值为undefined或者0，在声明中指定
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
	if (&s == this) return *this;  //避免给自己赋值
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

ostream & operator<<(ostream & os, Teacher & s)  //setw后面的输出字段长度小于n的时候，在该字段前面用空格补齐,当输出字段长度大于n时，全部整体输出。
{
	os << s.m_id << setw(10) << s.m_name << setw(10) << s.m_unit << setw(14) << s.m_phone << setw(10)
		<< s.m_basic_salary << setw(10) << s.m_allowence << setw(10) << s.m_income_tax << setw(10)
		<< s.m_accumulation_fund << setw(10) << s.due_salary() << setw(10) << s.total_deduction()   //后三个写成函数，进行更新。
		<< setw(10) << s.actual_salary();
	return os;
}

bool operator==(Teacher & left, Teacher & right)
{
	return (left.id() == right.id() && right.name() == left.name() && right.unit() == left.unit()
		&& left.phone() == right.phone() && right.basic_salary() == left.basic_salary() && right.allowence() == left.allowence()
		&& left.income_tax() == right.income_tax() && right.accumulation_fund() == left.accumulation_fund());
}

void Management::swap(int i, int j)   //swap函数 
{
	Teacher t = m_teachers[i];
	m_teachers[i] = m_teachers[j]; 
	m_teachers[j] = t;             //只交换了构造函数的八个变量，没改变应发工资、合计扣款、实发工资
}

Management & Management::operator=(const Management & s)
{
	if (&s == this) //避免给自己赋值
		return *this;  
	m_teachers = s.m_teachers;
	return *this;
}

void Management::displaysys() //显示系统内已有教师信息，setw后面的输出字段长度小于n的时候，在该字段前面用空格补齐,当输出字段长度大于n时，全部整体输出。
{
	cout << "教师系统信息如下：" << endl;
	cout << "教师号" << setw(10) << "姓名" << setw(10) << "学院" << setw(10) << "电话" << setw(14) << "基本工资"
		<< setw(10) << "津贴" << setw(10) << "所得税" << setw(10) << "公积金" << setw(10) << "应发工资" << setw(10) << "合计扣款"
		<< setw(10) << "实发工资" << endl;
	
	for (int i = 0; i < m_teachers.size(); i++)
	{
		cout << m_teachers[i] << endl;
	}
}

//void Management::displayfile()  //显示data.txt文件的教师信息
//{
//	ifstream in("data.txt");  //打开当前目录下的文件
//	if (!in.is_open())
//		cout << "打开文件失败。" << endl;
//	if (in) //文件打开
//	{  
//		cout << "文件信息如下：" << endl;
//		while (!in.eof())  //成员函数eof判断文件流是否结束
//		{ 
//			string str;
//			getline(in, str);   //按行显示
//			cout << str << endl;
//		}
//		in.close();  //关闭文件
//	}
//}

void Management::displayone(int i, int k)  //显示vector中第i+1个教师信息,k=0时输出第一行string，为1不输出
{
	if (i < m_teachers.size())
	{
		if (k == 0)
			cout << "教师号" << setw(10) << "姓名" << setw(10) << "学院" << setw(10) << "电话" << setw(14) << "基本工资"
				<< setw(10) << "津贴" << setw(10) << "所得税" << setw(10) << "公积金" << setw(10) << "应发工资" << setw(10) << "合计扣款"
				<< setw(10) << "实发工资" << endl;
		cout << m_teachers[i] << endl;
	}
	else
		cout << "超出教师vector容量" << endl;
}

void Management::outfile()    //重新写入原文件,不显示应发工资等三项
{
	int i;
	ofstream out("data.txt");       //在当前目录创建文件,因为已经有了data，所以是重写
	if (out) //判断文件是否成功打开
	{                                                 
		out << "教师号" << setw(10) << "姓名" << setw(10) << "学院" << setw(10) << "电话" << setw(14) << "基本工资"
			<< setw(10) << "津贴" << setw(10) << "所得税" << setw(10) << "公积金" << endl;
		for (i = 0; i < m_teachers.size() - 1; i++)            //不能写入应发工资、合计扣款、实发工资，否则读取数据还需要改
		{
			out << m_teachers[i].id() << setw(10) << m_teachers[i].name() << setw(10) << m_teachers[i].unit() << setw(14) <<
				m_teachers[i].phone() << setw(10) << m_teachers[i].basic_salary() << setw(10) << m_teachers[i].allowence()
				<< setw(10) << m_teachers[i].income_tax() << setw(10) << m_teachers[i].accumulation_fund() << endl;
		}
		i = m_teachers.size() - 1;
		out << m_teachers[i].id() << setw(10) << m_teachers[i].name() << setw(10) << m_teachers[i].unit() << setw(14) <<
			m_teachers[i].phone() << setw(10) << m_teachers[i].basic_salary() << setw(10) << m_teachers[i].allowence()
			<< setw(10) << m_teachers[i].income_tax() << setw(10) << m_teachers[i].accumulation_fund();   //如果加了endl，会多一行。。
		out.close(); //关闭文件
	}
}

void Management::sortfile()  //存放排序后文件，显示应发工资等三项
{
	int i;
	ofstream out("SortData.txt");
	if (out) //判断文件是否成功打开
	{                                                 
		out << "教师号" << setw(10) << "姓名" << setw(10) << "学院" << setw(10) << "电话" << setw(14) << "基本工资"
			<< setw(10) << "津贴" << setw(10) << "所得税" << setw(10) << "公积金" << setw(10) << "应发工资" << setw(10) << "合计扣款"
			<< setw(10) << "实发工资" << endl;
		for (i = 0; i < m_teachers.size() - 1; i++)           
		{
			out << m_teachers[i] << endl;
		}
		i = m_teachers.size() - 1;
		out << m_teachers[i];   //如果加了endl，会多一行
		out.close(); //关闭文件
	}
}

vector<Teacher> Management::add_from_file()  //读取文件的信息并加入vector容器中
{
	string id, name, unit, phone;  //教师号、姓名、学院名称、联系电话
	int basic_salary, allowence, income_tax, accumulation_fund;  //基本工资、津贴、所得税、公积金
	m_teachers.clear();   //清空容器
	ifstream in("data.txt");  //打开当前目录下的文件
	if (!in.is_open())
		cout << "error opening file.";
	if (in) //文件打开 
	{  
		string str;
		getline(in, str); //只读取第一行数据（汉字），不进行操作
		while (!in.eof()) //成员函数eof判断文件流是否结束
		{  
			in >> id >> name >> unit >> phone >> basic_salary >> allowence >> income_tax >> accumulation_fund;  //读入数据
			Teacher t(id, name, unit, phone, basic_salary, allowence, income_tax, accumulation_fund);   //构造teacher，使用了构造函数
			m_teachers.push_back(t);
		}
		in.close();  //关闭文件
	}
	return m_teachers;
}

vector<Teacher> Management::find() //精确查找，通过姓名或者教师号查找,返回教师的信息，用于deletion删除中
{
	vector<Teacher> s;
	string str;
	int i, k = 0, is_exist = 0;
	cout << "请输入姓名或教师号：";
	cin >> str;
	for (i = 0; i < m_teachers.size(); i++)
	{
		if (str == m_teachers[i].id())   //情况唯一
		{
			is_exist = i + 1;             //第i+1个教师 从1开始
			s.push_back(m_teachers[i]);   //添加进s中
			displayone(i, 0);             //显示信息 从0开始
			break;                        //跳出for循环，因为教师号唯一
		}
		else if (str == m_teachers[i].name())  //不唯一
		{
			k++;
			is_exist = i + 1;                 //第i+1个教师 从1开始
			s.push_back(m_teachers[i]);       //添加进s中
			if (k == 1)
				displayone(i, 0);             //显示信息 有第一行string
			else
				displayone(i, 1);             //显示信息 接着上次显示，不需要在显示第一行string
		}
	}
	if (is_exist == 0)
		cout << "没有该教师信息。";
	return s;
}

vector<int> Management::find_seq()  //通过姓名或者教师号查找,返回教师的位置信息，即序号，用于modify编辑中
{
	vector<int> s;
	string str;
	int i, k = 0, is_exist = 0;
	cout << "请输入姓名或教师号：";
	cin >> str;
	for (i = 0; i < m_teachers.size(); i++)
	{
		if (str == m_teachers[i].id())   //情况唯一
		{
			is_exist = i + 1;             //第i+1个教师 从1开始
			s.push_back(i);				  //添加进s中,0-size-1
			displayone(i, 0);             //显示信息 从0开始
			break;                        //跳出for循环，因为教师号唯一
		}
		else if (str == m_teachers[i].name())  //不唯一
		{
			k++;
			is_exist = i + 1;                 //第i+1个教师 从1开始
			s.push_back(i);					  //添加进s中
			if (k == 1)
				displayone(i, 0);             //显示信息 有第一行string
			else
				displayone(i, 1);             //显示信息 接着上次显示，不需要在显示第一行string
		}
	}
	if (is_exist == 0)
		cout << "没有该教师信息。";
	return s;
}

vector<int> Management::find_range()  //范围查找, 查找应发工资、实发工资、公积金处于指定范围内的教师名单,返回地址
{
	int min, max, mark, i, money, is_exist = 0, k = 0;
	vector<int> s;
	cout << "请输入您查找信息对应的数字：1、应发工资 2、实发工资 3、公积金。";
	cin >> mark;
	cout << "请输入您查找信息对应的金额最小、最大值（中间用空格隔开）。";
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
			cout << "输入数字错误，退出查询。" << endl; 
			return vector<int>();
		}
		if (money <= max && money >= min)   //情况不唯一
		{
			k++;
			is_exist = i + 1;             //第i+1个教师 从1开始
			s.push_back(i);				  //添加进s中
			if (k == 1)
				displayone(i, 0);             //显示信息 有第一行string
			else
				displayone(i, 1);             //显示信息 接着上次显示，不需要在显示第一行string
		}
	}
	if (is_exist == 0)
		cout << "没有处于该范围的教师信息。" << endl;
	return s;
}

int Management::fuzzyfind()  //模糊查找,根据输入名字、学院信息、电话的一部分，可以列出满足条件的所有记录,返回位置信息
{
	string str;
	vector<int> s;
	int i, j, k, m, n, sequence = 0;
	cout << "执行模糊搜索，请您输入名字、学院信息或电话的部分信息: " << endl;
	cin >> str;
	for (i = 0; i < m_teachers.size(); i++)
	{
		for (j = 0; j < str.size(); j++) //id查询
		{          
			if (str[j] != (m_teachers[i].id())[j])
				break;
		}
		if (j == str.size()) //存放位置信息
		{
			s.push_back(i);           
		}

		for (k = 0; k < str.size(); k++) //name查询
		{                 
			if (str[k] != (m_teachers[i].name())[k])
				break;
		}
		if (k == str.size()) //存放位置信息
		{
			s.push_back(i);           
		}

		for (m = 0; m < str.size(); m++) //学院查询
		{          
			if (str[m] != (m_teachers[i].unit())[m])
				break;
		}
		if (m == str.size()) //存放位置信息
		{
			s.push_back(i);           
		}

		for (n = 0; n < str.size(); n++) //电话查询
		{          
			if (str[n] != (m_teachers[i].phone())[n])
				break;
		}
		if (n == str.size()) //存放位置信息
		{
			s.push_back(i);           
		}
	}
	//显示模糊查询的信息
	if (s.size() == 0) {
		cout << "未查询到此人信息。" << endl;
		return 0;
	}
	else if (s.size() == 1) {
		displayone(s[0], 0);             //显示信息 有第一行string
	}
	else {
		displayone(s[0], 0);             //显示信息 有第一行string
		for (i = 1; i < s.size(); i++)
			displayone(s[i], 1);         //不显示string 
	}
	//进行二次选择
	if (s.size() == 1);              //系统仅一位满足条件的教师
	else {                         //系统有多位满足条件的教师
		cout << "请输入1-" << s.size() << "，输入序号代表选择教师信息。" << endl;
		cin >> sequence;
		sequence--;       //变成从0开始的位置信息
		cout << "您选择的教师信息如下：" << endl;
		displayone(s[sequence], 0);
	}
	return sequence;
}

void Management::modify()  //修改教师信息
{
	string id, name, unit, phone;  //教师号、姓名、学院名称、联系电话
	int basic_salary, allowence, income_tax, accumulation_fund, mark, dir, sequence = 0;  //基本工资、津贴、所得税、公积金
	cout << "您已选择修改教师信息。";
	vector<int> s = find_seq();
	int num = s.size();            //读取满足条件的教师个数
	if (num == 0)                  //查询无此人
		cout << "无法修改。" << endl;
	else                           //有教师信息
	{
		if (num == 1);												//系统仅一位满足条件的教师
		else                                                        //系统有多位满足条件的教师
		{
			cout << "请输入1-" << num << "，输入序号代表您想要修改的教师信息。" << endl;
			cin >> sequence;
			sequence--;       //变成从0开始的位置信息
		}
		dir = s[sequence];  //如果只有一人，s[0]位置的数字就是该教师在m_teachers数组中的位置，
		cout << "您要修改哪一信息？(1.教师号 2.姓名 3.学院 4.电话 5.基本工资 6.津贴 7.所得税 8.公积金 0.返回)" << endl;
		cin >> mark;
		if (mark == 0) {
			cout << "您选择退出修改，修改失败。" << endl;
			return;
		}
		cout << "请输入修改信息：";
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
		outfile();     //更改文件
		cout << "修改成功!修改后的该教师信息显示如下：" << endl;
		displayone(dir, 0);
	}	
}

void Management::addition()  //增加教师信息
{
	string id, name, unit, phone;  //教师号、姓名、学院名称、联系电话
	int basic_salary, allowence, income_tax, accumulation_fund, k, is_exist = 0;  //基本工资、津贴、所得税、公积金
	while (1)
	{
		cout << "请输入教师信息：教师号、姓名、学院名称、联系电话、基本工资、津贴、所得税、公积金" << endl;
		cin >> id >> name >> unit >> phone >> basic_salary >> allowence >> income_tax >> accumulation_fund;
		for (int i = 0; i < m_teachers.size(); i++)
		{
			if (id == m_teachers[i].id() && name == m_teachers[i].name()) {
				cout << "已经存在该教师信息" << endl;
				is_exist = 1;
			}
		}
		if (is_exist == 0)         //vector中没有教师信息，则加入
		{
			Teacher t(id, name, unit, phone, basic_salary, allowence, income_tax, accumulation_fund);   //构造teacher，使用了构造函数
			m_teachers.push_back(t);
			cout << "增加成功，新加教师信息如下" << endl;
			displayone(m_teachers.size() - 1, 0);
			outfile();     //更改文件
		}
		is_exist = 0;   //重新置0，以便进入下次判断
		cout << "是否继续增加教师信息，继续请按1，退出请按0。" << endl;
		cin >> k;
		if (k == 0)
			break;
	}
}

void Management::deletion()   //删除教师信息
{
	int m, n, sequence, count = 0;	//m表示再确认是否删除，n表示选择删除多位or一位教师，//sequence表示删除一位教师时对应序号。count表示删除所有教师对应的自加
	cout << "您已选择删除教师信息。" ;
	vector<Teacher> s = find();
	vector<Teacher>::iterator itor;
	int num = s.size();            //读取满足条件的教师个数
	if (num == 0)
		cout << "无法删除。" << endl;
	else if (num == 1)                                           //系统仅一位满足条件的教师
	{
		cout << "是否确定删除该教师信息？继续请按1，退出请按0。" << endl;
		cin >> m;
		if (m == 1) {
			for (itor = m_teachers.begin(); itor != m_teachers.end();)
			{
				if (*itor == s[0])   //s仅有一个教师信息，即s[0]
				{
					itor = m_teachers.erase(itor);	  //因为删除一个元素之后，迭代器已经指向了被删除元素的下一个元素
					break;           //因为就只有一个，找到即跳出，如果上面不返回itor时，没有break会报错
				}
				else itor++;
			}
			cout << "删除成功。" << endl;
			outfile();     //更改文件
		}
		if (m == 0)
			cout << "您已取消删除该教师信息，删除失败。" << endl;		
	}	
	else   //系统有多位满足条件的教师
	{
		cout << "满足您输入信息的教师有多位，删除全部请按1，删除一位请按0。" << endl;
		cin >> n;
		if (n == 1) {                                          //删除满足条件的所有教师 
			cout << "是否确定删除全部教师信息？继续请按1，退出请按0。" << endl;
			cin >> m;
			if (m == 1) {
				for (itor = m_teachers.begin(); itor != m_teachers.end();)       
				{
					if (count < num) {
						if (*itor == s[0 + count])  //i++返回加1前的值。
						{
							count++;
							itor = m_teachers.erase(itor);
						}
						else  itor++;
					}
					else 
						break;
				}
				cout << "删除成功。" << endl;
				outfile();     //更改文件
			}
			if (m == 0)
				cout << "您已取消删除该教师信息，删除失败。" << endl;
		}
		else 
		{
			cout << "请输入1-" << num << "，输入序号代表您想要删除的教师信息。" << endl;
			cin >> sequence;
			cout << "是否确定删除该教师信息？继续请按1，退出请按0。" << endl;
			cin >> m;
			if (m == 1) {
				for (itor = m_teachers.begin(); itor != m_teachers.end();)
				{
					if (*itor == s[sequence - 1])
					{
						itor = m_teachers.erase(itor);
						break;                      //删除一位
					}
					else itor++;
				}
				cout << "删除成功。" << endl;
				outfile();     //更改文件
			}
			if (m == 0)
				cout << "您已取消删除该教师信息，删除失败。" << endl;
		}
	}
}

double Management::average(string & str, string &u)   //根据字符串判断求哪项平均工资,返回平均单项工资
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

double Management::deviation(string & str, string &u)  //求标准差
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

void Management::average()   //总项平均工资，并输出工资标准差
{
	int mark;
	double avg, std;  //平均值，标准差
	string str, u;
	cout << "请您输入学院名称：";
	cin >> u;
	cout << "请您输入序号求对应的平均工资：1、基本工资 2、津贴 3、所得税 4、公积金 5、应发工资 6、合计扣款 7、实发工资" << endl;
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
	if (avg == 0.0) cout << "学院输入错误。" << endl;
	else
		cout << "平均值为" << avg << setw(10) << "标准差为" << std << endl;
}

void Management::SectionSort()  //选择法排序
{
	int num = m_teachers.size();
	for (int i = 0; i < num - 1; i++) //i取值最大为前n-1个数，j取值为后i+1-n
	{				 
		int max = i;								 //记录待排序数据中最大元素位置 
		for (int j = i + 1; j < num; j++) {
			int m1 = m_teachers[max].actual_salary(), n1 = m_teachers[j].actual_salary();
			int m2 = m_teachers[max].accumulation_fund(), n2 = m_teachers[j].accumulation_fund();
			string m3 = m_teachers[max].id(), n3 = m_teachers[j].id();
			if (m1 < n1)
				max = j;							 //更新最大元素位置 
			else if (m1 == n1)
			{
				if (m2 < n2)
					max = j;
				else if (m2 == n2) 
				{
					if (m3 < n3)   //教师号唯一，不存在相等
						max = j;
				}
			}
		}
		swap(i, max);		 // 调用swap函数,把最大元素放到位置i
	}
	sortfile();        //存放排序后文件到"SortData.txt"
}

