#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <iomanip>  //使用stew函数
#include <algorithm>

using namespace std;

class Student {
public:
    int id;        // 学号 
    string name;   // 姓名 
    string sex;    // 性别 
    int classNum;  // 班级号 
    string major;  // 专业 

    // 构造函数
    Student(){
		id = 0;
		name = "";
		sex = "";
		classNum = 0;
		major = "";
	}
	
    Student(int id, string name, string sex, int classNum, string major)
        : id(id), name(name), sex(sex), classNum(classNum), major(major) {}
        
    bool operator < (const Student& tmp) const 
    {
    	return id < tmp.id;
	}
    
	void add();         //定义录入学生信息的函数；
	void find();        //定义按学号查询信息函数和按班级查询信息函数；
	void modify();      //定义修改函数；
	void del();         //定义删除函数;
	void statistics();  //定义一个统计函数；statistics 统计；
	void showAll();     //定义一个显示函数，显示所有记录； 
};

void welcome();
void entrance();
void add_from_file();
void outfile();

Student stu;
vector<Student> vec;
int sum = 0;

/***************欢迎************************/
void welcome()
{
	system("cls");
    cout<<"                                             ▁▁▂▂▃▃▅▅▆▆▇▇▇▇▇▇▆▆▅▅▃▃▂▂▁▁"<<endl;
    cout << "<<<<<<------------------------------------------欢迎来到学生证管理系统------------------------------------------>>>>>>>>" << endl;
    cout << " *******                                         1. 录入学生证信息                                            ********" << endl;
    cout << " *******                                         2. 查询学生信息或班级信息                                    ********" << endl;
    cout << " *******                                         3. 修改学生证信息                                            ********" << endl;
    cout << " *******                                         4. 删除学生证信息                                            ********" << endl;
    cout << " *******                                         5. 查询班级人数                                              ********" << endl;
    cout << " *******                                         6. 查看所有记录                                              ********" << endl;
	cout << " *******                                         7. 退出                                                      ********" << endl;
    cout << "<<<<<<---------------------------------------------------------------------------------------------------------->>>>>>>>" << endl;
	cout << "请输入你的选择：";
	entrance();
}

/***************进入**************************/
void entrance()
{
	int a;
	cin >> a;
    system("cls");
	switch(a)
	{
		
		case 1:             //录入信息
			cout<<"\t\t\t欢迎进入录入信息界面\n\n";
            stu.add();
			break;
		case 2:             //给定学号，显示某学生信息和给定班号，显示全班学生
            cout<<"\t\t\t欢迎进入查询界面\n\n";
			stu.find();
			break;
		case 3:             //进入修改界面
			cout<<"\t\t\t欢迎进入修改记录界面\n\n";
			stu.modify();
			break;
		case 4:             //进入删除界面
			cout<<"\t\t\t欢迎进入删除记录界面\n\n";
            stu.del();
            break;
		case 5:             //统计班级人数 
			cout<<"\t\t\t欢迎进入统计记录界面\n\n";
			stu.statistics();
			break;
		case 6:
			stu.showAll();
			break;
		case 7:				//退出
			return ;
		default: 
			cout << "输入错误!" << endl;
			system("pause");
			welcome();
			break;
	}
}

/*************添加学生信息********************/
void Student :: add()
{
	int figure;//定义要输入信息的学生的个数
	char h,m;

	cout<<"你要输入多少个学生的信息? " << endl;
	cin >> figure;
	cout<<"您确定要输入" << figure << "个学生的信息么？\n";
	fflush(stdin);
	cout<<"<按Y开始 N返回>" << endl;
	cin >> h;
	if(h=='Y'||h=='y')
	{
		for(int j=0;j<figure;j++)
		{
			Student s;
			cout<<"请输入第" << j + 1 << "个学生的信息：\n";
            cout<<"学号:";
		    cin >> s.id;
			cout<<"姓名:";
        	cin >> s.name;
    		cout << "性别:";
			cin >> s.sex; 
			cout<<"班级:";
            cin >> s.classNum;
            cout << "专业:";
			cin >> s.major;
            
			sum++;
			vec.push_back(s);
		}
		
		sort(vec.begin(), vec.end()); // 按学号排序 
		outfile(); //更新文件
		
		cout<<"添加成功!\n";
		
		cout<<"是否现在查看所有记录？ y/n" << endl;
		fflush(stdin);
		cin >> m;
		if(m=='y'||m=='Y')
		{
			system("cls");
			stu.showAll();
		}
		else
		{
			system("cls");
			welcome();
		}
	}
	else
	{
		system("cls");
		welcome();
	}
}

/****************给定学号，显示某位学生学生证信息********************/
/****************给定班级，显示全班学生信息********************/
void Student :: find()
{
	int i, j;
	int sno;
	int classes;
	char t = ' ';
	
	cout<<"\t\t您可以：\n";
	cout<<"\t\t1.按学号查询!\n";
	cout<<"\t\t2.按班号查询!\n";
	
	int a;
	cin >> a;
    switch(a)
	{
		case 1:
			cout<<"请输入学号：";
			cin >> sno;
			
			for(i=0;i<sum;i++)
			{
				if(sno == vec[i].id)
				{
					cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
					cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
					cout << endl;
					break;
				}
			}
			
			if(i == sum)
			{
				cout<<"没有找到!\n";
			}
			
			cout<<"是否继续查询？ y/n\n";
			cin >> t;
			if (t == 'Y' || t == 'y')
			{
				stu.find();
			}
			else
			{
				welcome();
			}
			break;
		case 2:
			cout<<"请输入班级：";
			cin >> classes;
			
			for(j = 0; j < sum; j++)
			{
				if(classes == vec[j].classNum)
				{
					break;
				}
			}
			
			if(j == sum)
			{
				cout<<"没有找到!\n";
			}
			else
			{
				cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
				for(i=0;i<sum;i++)
				{
					if(classes == vec[i].classNum)
					{
						cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
						cout<<"\n";
					}
				}
			}
			
			cout<<"是否继续查询？ y/n\n";
			cin >> t;
			if (t == 'Y' || t == 'y')
			{
				stu.find();
			}
			else
			{
				welcome();
			}
			break;
		default:
			stu.find();
			break;
	}
}

/****************修改信息****************/
void Student :: modify()
{
	int i;
	int numb;
	char h;
	
	cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
	for(i=0;i<sum;i++)
	{
		cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
		cout<<"\n";
	}
    printf("请输入您要修改的学生的学号：");
    
	cin >> numb;
	for(i=0;i<sum;i++)
	{
		if(numb == vec[i].id)
		{
			cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
			cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
			cout << endl;
			break;
		}
	}
	
	if(i == sum)
	{
		cout<<"没有找到!\n";
		cout<<"是否继续修改？ y/n\n";
		cin >> h;
		if (h == 'Y' || h == 'y')
		{
			stu.modify();
		}
		else
		{
			welcome();
		}
	}
	else
	{
		cout<<"请输入该学生的新信息：\n";
		
		cout<<"学号:";
		cin >> vec[i].id;
		cout<<"姓名:";
		cin >> vec[i].name;
		cout << "性别:";
		cin >> vec[i].sex;
		cout<<"班级:";
		cin >> vec[i].classNum;
		cout << "专业:";
		cin >> vec[i].major;
		
		sort(vec.begin(), vec.end()); // 按学号排序 
		outfile(); //更新文件
		
		cout<<"修改成功!\n";
		cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
		for(i=0;i<sum;i++)
		{
			if(vec[i].id != 0)
			{
				cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
				cout<<"\n";
			}
		}
		
		cout<<"是否继续修改？ y/n\n";
		cin >> h;
		if (h == 'Y' || h == 'y')
		{
			stu.modify();
		}
		else
		{
			welcome();
		}
	} 
}

/****************删除记录****************/
void Student :: del()
{
	int i;
	int numb;
	char h,k;
	
	cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
	for(i=0;i<sum;i++)
	{
		if(vec[i].id != 0)
		{
			cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
			cout<<"\n";
		}
	}
	
	cout<<"请输入要删除的学号：";
	fflush(stdin);
	cin >> numb;
	
	for(i=0;i<sum;i++)
	{
		if(numb == vec[i].id)
		{
			cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
			cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
			cout<<"\n";
			break;
		}
	}
	
	if(i == sum)
	{
		cout<<"没有找到!\n";
		cout<<"是否继续删除？ y/n\n";
		cin >> h;
		if (h == 'Y' || h == 'y')
		{
			stu.del();
		}
		else
		{
			welcome();
		}
	}
	else
	{
		cout<<"是否确定删除？ y/n\n";
		fflush(stdin);
		cin >> h;
		
		if(h =='y'||h =='Y')
		{
			for (auto it = vec.begin(); it != vec.end(); it++)
			{
				if (it->id == vec[i].id)
				{
					it = vec.erase(it);
					break;
				}
			}
			sum--;
			
			cout<<"删除成功!\n";
			
			sort(vec.begin(), vec.end()); // 按学号排序 
			outfile(); //更新文件 
			
			cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
			for(i=0;i<sum;i++)
			{
				if(vec[i].id != 0)
				{
					cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
					cout<<"\n";
				}
			}
			
			cout<<"是否继续删除？ y/n\n";
			cin >> k;
			if (k == 'Y' || k == 'y')
			{
				stu.del();
			}
			else
			{
				welcome();
			}
		}
		else
		{
			del();
		}
	}
}

/****************统计某个班的学生人数****************/
void Student :: statistics()
{
	int count = 0;
	int s;
	cout << "请输入要统计的班级号：";
	cin >> s;
	
	for (int i = 0; i < sum; i++)
	{
		if (s == vec[i].classNum) count++;
	}
	
	cout << s << "班的学生个数是：" << count << endl; 
	
	cout<<"是否继续统计？ y/n\n";
	char k;
	cin >> k;
	if (k == 'Y' || k == 'y')
	{
		stu.statistics();
	}
	else
	{
		welcome();
	}
}

/****************显示所有的学生证信息****************/
void Student :: showAll()
{
	if (sum)
	{
		cout<<"学号\t\t姓名\t性别\t班级\t专业\n";
		for(int i=0;i<sum;i++)
		{
			cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
			cout<<"\n";
		}
		cout << endl;
	}
	cout << "所有学生个数是：" << sum << endl; 
	system("pause");
	welcome();
}

/****************将文件中所有的学生证信息加入到vector对象数组中****************/
void add_from_file()
{
	int id, classNum;
	string name, sex, major;
	vec.clear();
	
	ifstream in("学生证管理系统.txt");
	if (!in.is_open())
	{
		cerr << "无法打开文件！不能正常写入数组" << endl; 
		return ; 
	}
	
	string str;
	getline(in, str); //只读取第一行数据（汉字），不进行操作
	
	while (in >> id >> name >> sex >> classNum >> major)
	{
//		in >> id >> name >> sex >> classNum >> major;
		Student s(id, name, sex, classNum, major);
		vec.push_back(s);
		sum++;
	}
	
	in.close();
	
	sort(vec.begin(), vec.end()); // 按学号排序 
}

/****************将所有的学生证信息重新写入到txt文件中****************/
void outfile()
{
	ofstream out("学生证管理系统.txt");
	if (!out.is_open())
	{
		cerr << "无法打开文件！不能正常写入文件" << endl; 
		return ; 
	}
	
	out << "学号" << setw(21) << "姓名" << setw(15) << "性别" << setw(9) << "班级号" << setw(5) << "专业" << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		out << vec[i].id << setw(10) << vec[i].name << setw(10) << vec[i].sex << setw(10) << vec[i].classNum << setw(10) << vec[i].major << endl;
	}
	
	out.close();
}

int main()
{
	system("COLOR f0");  //设置为白底黑字 
	
	add_from_file();
	welcome();	//进入欢迎界面；
	
	return 0;
}
