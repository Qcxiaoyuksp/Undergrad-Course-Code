#include<fstream>
#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<string>
#include<cstring>
#include<stdio.h>
#include<iomanip>  
#include<sstream>
#pragma warning(disable:4996)
using namespace std;
int d = 0, n = 0, m = 0, k = 0, l = 0, g = 0, s1 = 0, s2 = 0, i = 0, v = 1;
class room
{
public:
	char number[15];
	float price;
	int grade;
	string a;
	char sell_time[30];
	void input();
	void show();
	void change();
	void delete1();
	void readfrom();
	void writeto();
};
class customer
{
public:
	char num[15];
	char ID[20];
	char sex[10];
	char name[20];
	char phone[20];
	char intime[30];
	char outtime[30];
	char room_number[3];
	void show();
	void input();
	void change();
	void delete1();
	void forsee();
	void readfrom();
	void writeto();


}; room* p = new room[20];
customer* q = new customer[20];
void room::input()
{
	cout << "房号"; cin >> number; cout << endl;
	cout << "价格"; cin >> price; cout << endl;
	cout << "等级（高1低2"; cin >> grade;
	if (grade != 1 && grade != 2)
	{
		cout << "输入错误，请重新输入" << endl;
		cin >> grade;
	}
	cout << "是否出售（已出售1/未出售2" << endl; cin >> a;
	if (a == "1")
	{
		cout << "请输入出售时间" << endl; cin >> sell_time;
	}
	else if (a == "2")
		cout << "  " << endl;
	else if (a != "1" && a != "2")
	{
		cout << "输入错误，请重新输入"; cin >> a;
	}
}
void room::show()
{
	cout << "___________________________________________________|" << endl;
	cout << number << "    " << price << "    " << a << "       ";
	if (a == "2")
		cout << "未售出" << endl;
	if (a == "1")
		cout << sell_time << endl;

}
void room::change()
{
	int chiose;
	cout << "请输入要修改的信息（1：编号  2：价格  3：等级   4：出售情况   5：出售时间"; cin >> chiose;
	if (chiose == 1)
	{
		cout << "请输入修改后的编号"; cin >> number; cout << "修改成功";
	}
	if (chiose == 2)
	{
		cout << "请输入修改后的价格"; cin >> price; cout << "修改成功";
	}
	if (chiose == 3)
	{
		cout << "请输入修改后的等级"; cin >> grade; cout << "修改成功";
	}
	if (chiose == 4)
	{
		cout << "请输入修改后的出售情况"; cin >> a;
		if (a == "未出售")
		{
			strcpy(sell_time, 0);
		}
	}
	if (chiose == 5)
	{
		cout << "请输入修改后的出售时间"; cin >> sell_time; cout << "修改成功";
	}
}
void room::delete1()
{


	strcpy(number, "0");
	price = 0;
	grade = 0;
	a = "0";
	strcpy(sell_time, "0");
}
void room::readfrom()
{
	ifstream infile("room2.txt", ios::in);
	if (!infile)
	{
		cerr << "2open error!" << endl;
		exit(1);
	}

	infile >> number >> price >> grade >> a;
	if (a == "2")
		cout << "未出售" << endl;
	else if (a == "1")
		infile >> sell_time; cout << endl;
	infile.close();

}
void room::writeto()
{
	ofstream outfile("room2.txt", ios::out);
	if (!outfile)
	{
		cerr << "1open error!" << endl;
		exit(1);
	}


	outfile << number << " " << price << " " << grade << " " << a << " ";
	if (a == "1")
		outfile << sell_time << endl;
	if (a == "2")
		outfile << "未售出" << endl;

	outfile.close();
}


void customer::input()
{
	cout << "请输入顾客的信息" << endl;
	cout << "请输入顾客编号"; cin >> num;
	cout << "请输入顾客姓名"; cin >> name;
	cout << "请输入顾客性别"; cin >> sex;
	cout << "请输入顾客身份证号"; cin >> ID;
	cout << "请输入顾客联系方式"; cin >> phone;
	cout << "请输入顾客的入住时间"; cin >> intime;
	cout << "请输入顾客的离开时间"; cin >> outtime;
	cout << "请输入所住房间号"; cin >> room_number;
	for (i = 1; i <= n; i++)
	{
		while (strcmp(room_number, p[i].number) == 0)
		{
			cout << "该房间不存在，请重新输入" << endl; cin >> room_number;
		}
	}

}
void customer::change()
{
	int chiose1;
	cout << "请输入要修改的内容(1:编号  2:姓名  3:性别   4：身份证号  5：联系方式  6：入住时间   7：离开时间  8：房间号)"; cin >> chiose1;
	if (chiose1 == 1)
	{
		cout << "请输入新的编号"; cin >> num; cout << "修改成功";
	}
	if (chiose1 == 2)
	{
		cout << "请输入新的姓名"; cin >> name; cout << "修改成功";
	}
	if (chiose1 == 3)
	{
		cout << "请输入新的性别"; cin >> sex; cout << "修改成功";
	}
	if (chiose1 == 4)
	{
		cout << "请输入新的身份证号"; cin >> ID; cout << "修改成功";
	}
	if (chiose1 == 5)
	{
		cout << "请输入新的联系方式"; cin >> phone; cout << "修改成功";
	}
	if (chiose1 == 6)
	{
		cout << "请输入新的入住时间"; cin >> intime; cout << "修改成功";
	}
	if (chiose1 == 7)
	{
		cout << "请输入新的离开时间"; cin >> outtime; cout << "修改成功";
	}
	if (chiose1 == 8)
	{
		cout << "请输入新的房间号"; cin >> room_number; cout << "修改成功";
	}
}
void customer::delete1()
{

	strcpy(num, "0");
	strcpy(name, "0");
	strcpy(ID, "0");
	strcpy(sex, "0");
	strcpy(phone, "0");
	strcpy(intime, "0");
	strcpy(outtime, "0");
	strcpy(room_number, "0");

}
void customer::show()
{
	cout << num << "       " << name << "   " << sex << "   " << ID << "           " << phone << "           " << intime << "      " << outtime << "         " << room_number << endl;
}

void customer::readfrom()
{
	ifstream infile("customer.txt", ios::in);
	if (!infile)
	{
		cerr << "2open error!" << endl;
		exit(1);
	}
	infile >> num >> ID >> sex >> name >> phone >> intime >> outtime >> room_number; cout << endl;
	infile.close();
}
void customer::writeto()
{
	ofstream outfile("customer.txt", ios::out);
	if (!outfile)
	{
		cerr << "1open error!" << endl;
		exit(1);
	}

	outfile << num << " " << ID << " " << sex << " " << name << " " << phone << " " << intime << " " << outtime << " " << room_number << endl;

	outfile.close();
}




int main()

{
	int w, i = 0;	int chiose = 1;
	room* p = new room[20];
	customer* q = new customer[20];
	int ab;
	char password[15];
	char password1[15];
	cout << "____________________________________________________" << endl;
	cout << "|              欢迎来到酒店信息管理界面            |" << endl;
	cout << "____________________________________________________" << endl;

loop:
	cout << "（1:设置初始密码          2：登录        3:修改密码）" << endl; cin >> ab;
	if (ab == 1)
	{
		string username;
		cout << "请输入账户名及初始密码" << endl; 
cin >> username >> password;

ofstream outfile("users.txt", ios::app); //打开输出文件，追加写入
if (outfile.is_open())
{
    outfile << username << " " << password << endl; //写入到文件中
    cout << "账户注册成功" << endl;
    outfile.close(); //关闭文件
}
else
{
    cout << "文件打开失败" << endl;
}

system("pause");
system("cls");
goto loop;

	}
	if (ab == 3)
	{
		string account;
		cout << "请输入账户信息" << endl;
cin >> account;
cout << "请输入修改后的密码" << endl; 
cin >> password;

ifstream infile("users.txt");
ofstream outfile("temp.txt");

string line;
while (getline(infile, line))
{
    istringstream iss(line);
    string a, p;
    if (!(iss >> a >> p)) break;
    if (a == account)
    {
        outfile << account << " " << password << endl;
        continue;
    }
    outfile << line << endl;
}

infile.close();
outfile.close();

remove("users.txt");
rename("temp.txt", "users.txt");

cout << "密码修改成功" << endl;
system("pause");
system("cls");
goto loop;

	}
	if (ab == 2)
	{
		string username;
		cout << "请输入账户名及登录密码" << endl; 
cin >> username >> password1;
	
ifstream infile("users.txt"); //打开输入文件，读取数据
if (infile.is_open())
{
    string line;
    bool success = false;
    while(getline(infile, line))
    {
        string u, p;
        stringstream ss(line);
        ss >> u >> p;
        if (u == username && p == password1)
        {
            success = true;
            break;
        }
    }
    if(!success)
    {
    	cout << "用户名或密码错误，系统即将返回" << endl;
        system("pause");
        system("cls");
	}
		else
		{     cout << "登录成功" << endl;
		rerun:

			cout << "------------------------------------------------------" << endl;
			cout << " *                       酒店信息管理                  * " << endl;
			cout << " *                    1:客房基本信息输入               *" << endl;
			cout << " *                    2:客房基本信息的查询             *" << endl;
			cout << " *                    3:客房基本信息的修改             *" << endl;
			cout << " *                    4:客房基本信息的删除             *" << endl;
			cout << " *                    5:酒店房间的浏览                 *" << endl;
			cout << " *                    6：保存客房信息                  *" << endl;
			cout << " *------------------------------------------------------" << endl;
			cout << " *                        顾客信息管理                 *" << endl;
			cout << " *                    7：顾客基本信息的输入            *" << endl;
			cout << " *                    8：顾客基本信息的输出            *" << endl;
			cout << " *                    9：顾客基本信息的修改            *" << endl;
			cout << " *                   10: 顾客信息的删除                *" << endl;
			cout << " *                   11：顾客信息浏览                  *" << endl;
			cout << " *                   12: 保存顾客信息                  *" << endl;
			cout << " *                   13：客流量预测                    *" << endl;
			cout << " -------------------------------------------------------" << endl;
			cout << " *                   14: 退出系统                      *" << endl;
			cout << "请选择功能"; cin >> w;
			switch (w)
			{
			case 1:
				cout << "------------------------------------" << endl;
				cout << "|        客房基本信息输入功能      | " << endl;
				cout << "------------------------------------" << endl;
				cout << "                                    " << endl;
				if (d == 0)
				{
					cout << "首次录入客房信息，请输入客房数量"; cin >> n;
					for (i = 1; i <= n; i++)
						p[i].input();
					d = 1;
					s1 = n;

				}
				else if (d == 1)
				{
					cout << "添加客房信息，请输入客房数量"; cin >> m; n = n + m;
					for (i = s1 + 1; i <= n; i++)
					{
						p[i].input();
						s1 = s1 + m;
					}
				}
				system("pause");
				system("cls");
				goto rerun;
				break;
			case 2:
			{   int flag3 = 0;
			char num1[15];
			int yu;
			cout << "-------------------------------------" << endl;
			cout << "|        客房基本信息的查询功能      |" << endl;
			cout << "-------------------------------------" << endl;
			cout << "                                    " << endl;
			cout << "请输入查询方式（1：所有客房信息  2：单个客房信息"; cin >> yu;
			if (yu == 1)
			{
				cout << "___________________________________________________" << endl;
				cout << "房号" << "  " << "价格" << "  ""出售情况" << "       " << "出售时间" << "|" << endl;
				for (i = 1; i <= n; i++)
				{
					p[i].show();
				}

			}
			else
			{
				cout << "请输入客房编号，系统将为您查询客房信息" << endl; cin >> num1;
				cout << "客房基本信息预览表" << endl;


				for (i = 1; i <= n; i++)
				{
					if (strcmp(num1, p[i].number) == 0)
					{
						cout << "___________________________________________________" << endl;
						cout << "房号" << "  " << "价格" << "  ""出售情况" << "       " << "出售时间" << "|" << endl;
						p[i].show();
						flag3 = 1;
					}
				}
				if (flag3 == 0)
					cout << "此客房信息不存在" << endl;
			}

			system("pause");
			system("cls");
			goto rerun;
			break;
			}
			case 3:
				char num2[15];
				cout << "---------------------------------------" << endl;
				cout << "|       客房基本信息的修改功能         |" << endl;
				cout << "----------------------------------------" << endl;
				cout << "请输入要修改客房的房号"; cin >> num2;
				for (i = 1; i <= n; i++)
				{
					if (strcmp(num2, p[i].number) == 0)
						p[i].change();
				}
				system("pause");
				system("cls");
				goto rerun;
				break;
			case 4:
			{

				char number2[15];
				cout << "------------------------------------------" << endl;
				cout << " |            客房信息删除功能           |  " << endl;
				cout << "------------------------------------------" << endl;
				cout << "请输入要删除客房的编号"; cin >> number2;
				for (i = 1; i <= n; i++)
				{
					if (strcmp(number2, p[i].number) == 0)
					{
						p[i].delete1();
						cout << "删除成功" << endl;
					}
				}

				system("pause");
				system("cls");
				goto rerun;
				break;
			}
			case 5:
				cout << "------------------------------------------" << endl;
				cout << " |            酒店房间浏览表              |" << endl;
				cout << "------------------------------------------" << endl;
				cout << "___________________________________________________" << endl;
				cout << "房号" << "  " << "价格" << "  ""出售情况" << "       " << "出售时间" << "|" << endl;
				for (i = 1; i <= n; i++)
				{
					p[i].show();


				}

				system("pause");
				system("cls");
				goto rerun;
				break;
			case 6:

				cout << "------------------------------------------" << endl;
				cout << " |            酒店房间浏览表              |" << endl;
				cout << "------------------------------------------" << endl;

				cout << "客房信息（编号，价格，等级，是否出售 出售时间)" << endl;
				for (i = 1; i <= n; i++)
				{
					p[i].writeto();
					cout << "信息保存成功" << endl; cout << n;
				}

				system("pause");
				system("cls");
				goto rerun;
				break;

			case 7:
				cout << "-------------------------------------------" << endl;
				cout << "|         顾客基本信息输入功能             |" << endl;
				cout << "-------------------------------------------" << endl;

				if (g == 0)
				{
					cout << "请输入要录入信息的顾客人数"; cin >> k;
					for (i = 1; i <= k; i++)
					{
						q[i].input();
						g = 1;
						s2 = k;
					}
				}

				else if (g == 1)
				{
					cout << "增添顾客人数"; cin >> l; k = k + l;
					for (i = s2 + 1; i <= k; i++)
					{
						q[i].input();
						s2 = s2 + l;
					}
				}
				system("pause");
				system("cls");
				goto rerun;
				break;
			case 8:
				int chiose, chiose2;
				char num3[15], ID1[20], room_number1[15];

				cout << "---------------------------------------------" << endl;
				cout << "           顾客基本信息的查询功能             |" << endl;
				cout << "----------------------------------------------" << endl;
				cout << "请输入查询方式（1：单个顾客的基本信息  2：某一天内所有顾客的基本信息）" << endl; cin >> chiose2;
				if (chiose2 == 1)
				{
					cout << "请选择查询方式（1:顾客编号，2：身份证号  3：房间号 "; cin >> chiose;
					if (chiose == 1)
					{
						cout << "请输入顾客编号"; cin >> num3;

						cout << "编号,姓名,性别,身份证号,联系方式,入住时间,离开时间,所住房间 " << endl;
						for (i = 1; i <= k; i++)
						{
							if (strcmp(num3, q[i].num) == 0)
							{
								q[i].show();
								v = 1;
								break;
							}
							else
								v = 0;
						}
						if (v == 0)
						{
							cout << "该用户未录入" << endl;
						}

					}
					else
						if (chiose == 2)
						{
							cout << "请输入顾客身份证号"; cin >> ID1;
							cout << "编号    姓名     性别      身份证号                         联系方式                    入住时间            离开时间         所住房间 " << endl;
							for (i = 1; i <= k; i++)
							{
								if (strcmp(ID1, q[i].ID) == 0)
								{
									q[i].show();
									v = 1;
									break;
								}
								else
									v = 0;
							}
							if (v == 0)
							{
								cout << "该用户未录入" << endl;
							}
						}
						else if (chiose == 3)
						{
							cout << "请输入顾客的房间号"; cin >> room_number1;
							cout << "编号    姓名     性别      身份证号                         联系方式                    入住时间            离开时间         所住房间 " << endl;
							for (i = 1; i <= k; i++)
							{
								if (strcmp(room_number1, q[i].room_number) == 0)

								{
									q[i].show();
									v = 1;
									break;
								}
								else
									v = 0;
							}
							if (v == 0)
							{
								cout << "该用户未录入" << endl;
							}
						}
				}
				if (chiose2 == 2)
				{
					char d[30];
					cout << "--------------------------------------------" << endl;
					cout << "|               某日期内所有顾客信息       | " << endl;
					cout << "---------------------------------------------" << endl;
					cout << "请输入日期"; cin >> d;
					cout << "编号    姓名     性别      身份证号                         联系方式                    入住时间            离开时间         所住房间 " << endl;
					for (i = 1; i <= k; i++)
					{
						if (((strcmp(q[i].intime, d) < 0) || (strcmp(q[i].intime, d) == 0)) && ((strcmp(q[i].outtime, d) > 0) || (strcmp(q[i].outtime, d) == 0)))
						{
							if (q[i].num != 0 || q[i].ID != 0 || q[i].sex != 0 || q[i].name != 0 || q[i].phone != 0 || q[i].intime != 0 || q[i].outtime != 0 || q[i].room_number != 0);
							q[i].show();
						}

					}

				}
				system("pause");
				system("cls");
				goto rerun;
				break;

			case 9:

				char name1[15], ID2[20], room_number2[15];
				cout << "----------------------------------------------" << endl;
				cout << "|         顾客基本信息修改功能                 |" << endl;
				cout << "-----------------------------------------------" << endl;
				cout << "请输入客户信息（1：姓名 2：身份证号 3：房间号）";
				if (chiose == 1)
				{
					cout << "请输入姓名"; cin >> name1;
					for (i = 1; i <= k; i++)
					{
						if (strcmp(name1, q[i].name) == 0)
						{
							q[i].change(); cout << "修改成功" << endl;
							break;
						}
					}


				}
				else
					if (chiose == 2)
					{
						cout << "请输入顾客身份证号"; cin >> ID2;
						for (i = 1; i <= k; i++)
						{
							if (strcmp(ID2, q[i].ID) == 0)
							{
								q[i].change(); cout << "修改成功" << endl;
								break;

							}

						}
					}
					else
						if (chiose == 3)
						{
							cout << "请输入顾客的房间号"; cin >> room_number2;
							for (i = 1; i <= k; i++)
							{
								if (strcmp(room_number2, q[i].room_number) == 0)
								{
									q[i].change(); cout << "修改成功" << endl;
									break;
								}

							}
						}
				system("pause");
				system("cls");
				goto rerun;
				break;
			case 10:

				char name3[20];
				cout << "------------------------------------------" << endl;
				cout << " |            顾客信息删除功能           |  " << endl;
				cout << "------------------------------------------" << endl;
				cout << "请输入要删除顾客的姓名"; cin >> name3;
				for (i = 1; i <= k; i++)
				{
					if (strcmp(name3, q[i].name) == 0)
					{
						q[i].delete1();
						cout << "删除成功" << endl;
					}
				}


				system("pause");
				system("cls");
				goto rerun;
				break;

			case 11:
				cout << "--------------------------------------------" << endl;
				cout << "|               顾客信息浏览功能             |" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "编号    姓名     性别      身份证号                         联系方式                    入住时间            离开时间         所住房间 " << endl;
				for (i = 1; i <= k; i++)
				{
					if (q[i].num != 0 || q[i].ID != 0 || q[i].sex != 0 || q[i].name != 0 || q[i].phone != 0 || q[i].intime != 0 || q[i].outtime != 0 || q[i].room_number != 0);
					q[i].show();
				}
				system("pause");
				system("cls");
				goto rerun;
				break;
			case 12:

				cout << "顾客信息（编号     姓名    性别     身份证号     联系方式      入住时间     离开时间   所住房间 )" << endl;
				for (i = 1; i <= k; i++)
					q[i].writeto();
				cout << "顾客信息保存成功" << endl;
				system("pause");
				system("cls");
				goto rerun;
				break;
			case 13:
			{
				int gy, n = 0; char time[30];
				cout << "--------------------------------------------" << endl;
				cout << "|       客流量统计/预测                     |" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "1:客流量统计              2：客流量预测" << endl; cin >> gy;
				if (gy == 1)
				{
					cout << "请输入要统计的时间段" << endl; cin >> time;
					for (i = 1; i < k; i++)
					{
						if (((strcmp(q[i].intime, time) < 0) || (strcmp(q[i].intime, time) == 0)) && ((strcmp(q[i].outtime, time) > 0) || (strcmp(q[i].outtime, time) == 0)))
							n++;
					}
					cout << "此时间段内实际入住人数为" << n;
				}
				else if (gy == 2)
				{
					double i[20]{}, q[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
					double aver, sum = 0, q0 = static_cast<double> (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12 + 13 + 14 + 15 + 16 + 17 + 18 + 19 + 20) / 20, z0 = 0, m0 = 0;
					double 	b, a;
					int y;
					fstream infile("forsee.txt", ios::in);
					if (!infile)
					{
						cout << "错误，找不到文件" << endl;
					}
					else
					{
						for (int m = 0; m < 20; m++)
						{
							infile >> i[m];//从文件中读入前20天数据
							sum += i[m];
						}
						aver = sum / 20;//计算平均值
					}
					infile.close();

					for (int j = 0; j < 20; j++)
					{
						z0 = z0 + (q[j] - q0) * (i[j] - aver);//斜率的分子
						m0 = m0 + (q[j] - q0) * (q[j] - q0);//斜率的分母
					}
					b = z0 / m0;
					a = aver - b * q0;//根据公式计算线性回归系数
					cout << "\t\t\t\t\t\t\t\n\n前20天人数:" << endl;
					for (int m = 0; m < 20; m++)
						cout << i[m] << "\t";
					cout << "\t\t\t\t\t\t\t\t\n\n- - - - - 预测人数为：";
					y = b * 21 + a; //人数预测
					cout << y;


				}
				system("pause");
				system("cls");
				goto rerun;
				break;
			}
			case 14:
				int gg;
				cout << "--------------------------------------------" << endl;
				cout << "|               退出                        |" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "是否要退出（1：是  2否）" << endl; cin >> gg;
				if (g == 2)
				{
					system("pause");
					system("cls");
					goto rerun; 
				}
				if (g == 1)
					break;

			}
		}
	}else
{
    cout << "文件打开失败" << endl;
}
	}
	delete[]p;
	delete[]q;
}
