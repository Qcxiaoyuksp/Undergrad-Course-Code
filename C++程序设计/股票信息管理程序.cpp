using namespace std;
#include <iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<windows.h>

class stock
{
	private:
		//股票信息均从文件获取，用户只能修改选择的股票
		string s_num;
		string s_name;
		float open_pri[30];
		float close_pri[30];
		float highest_pri_d[30];	//当天最高价
	public:
		stock();

		string gets_num() const;
		string gets_name() const;
		float getopen_pri(const int&) const;
		float getclose_pri(const int&) const;
		float gethighest_pri_d(const int&) const;

		void sets_num(string&);
		void sets_name(string&);
		void setopen_pri(int& ,float&);
		void setclose_pri(int& ,float&);
		void sethighest_pri_d(int& ,float&);

		float pri_pre() const;    //开盘预测函数
		friend ostream& operator<<(ostream& ,stock);
};

class user
{
	private:
		string nick_name;
		string password;
		string u_name;
		string phone_num;
		int u_stock_num;
		string s_num[50];  //记录用户选择的股票代码,用get函数访问
	public:
		user();

		string getnick_name() const;
		string getpassword() const;
		string getu_name() const;
		string getphone_num() const;
		string gets_num(const int&) const;
		int getu_stock_num() const;




		void setu_stock_num_add(int);
		void sets_num(const int&,string);
		/*void sets_num(const int&);  //从文件 统计  */
		void setnick_name(string&);
		void setpassword(string&);
		void setu_name(string&);
		void setphone_num(string&);
		void setu_stock_num(int&);



		int add();
		int change();
		int logout();   //注销用户
		int user_menu(int) ;
		void display() const;  //显示用户的已经选择的股票

};
//用户数组和股票数组的名字后面有s
const int MAX_NUM=50;
user users[MAX_NUM];
stock stocks[MAX_NUM];
int user_num=0,empty_file=0;
int login();
void display__all();
void write_user();

void menu1()      //初入口
{
	while(1)
	{
		//红
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN|FOREGROUND_RED);
		cout<<"            ***********************************************************************"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_GREEN);
		cout << "             ***                  "<<"欢迎使用股票管理系统！                      ***" << endl;
		cout << "             ***                      1.创建新用户                            ***" << endl;
		cout << "             ***                      2.已有用户登录                          *** " << endl;
		cout << "             ***                      3.管理员登录                            ***" << endl;
		cout << "             ***                      4.退出系统                              ***" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN|FOREGROUND_RED);
		cout <<"           ************************************************************************"<<endl ;
		int jug;

		while(1)
		{
			cin >> jug;
			if(jug>=1&&jug<=4)
			{
				break;
			}
			else
			{
				cout<<"无此选项！请重新输入!"<<endl;
			}
		}

		if (jug == 1)
		{
			if(users[user_num].add()==8);//数组是从0开始的  //循环包括来保证对象在使用前已定义，过检查  //#ifndef 即告诉编译器在编译时不重复包括 （定义）
			//人数在add函数里已经增加
			{
				jug=4;
			}
		}
		if (jug == 2)
		{
			if(login()==8);
			{
				jug=4;
			}
		}
		if (jug == 3)
		{
			int admin_login();
			admin_login();
		}
		if(jug==4)
		{
			system("cls");
			cout<<"感谢使用！";
			system("pause");
			exit(0);
		}
		system("cls");
	}

}


int user::add()
{
	int a;
	while(1)
	{
		cout << "请输入用户名：";
		cin >> nick_name;
		for(a=0; a<50; a++)
		{
			if(a==user_num)
			{
				continue;
			}
			if(nick_name==users[a].nick_name)
			{
				cout<<"用户名已被占用，请重新输入！"<<endl;
				break;
			}
		}
		if(a==50)
		{
			break;
		}

	}

	while (1)
	{
		cout << "请输入密码：";
		cin >> password;
		cout << "请确认密码：";
		string temp_password;
		cin >> temp_password;
		if (temp_password == password)
		{
			break;
		}
		cout << "两次密码不一致，请重新输入！" << endl;
	}
	cout << "请输入您的真实姓名：";
	cin >> u_name;
	cout << "请输入您的手机号：";
	cin >> phone_num;
	user_num++;  //总人数增加
	//这里后面做文件写入
	//6.3 0:36
	write_user();



	cout<<"创建用户成功！";   //这里加一个文件写入判断

	system("pause");
	users[user_num-1].user_menu(user_num-1);   //前面user_num已经+1，这里调用要减回去！！！！！！！！
	return 8;
}

int user::change()
{
	int num;
	cout<<"您的当前个人信息："<<endl;
	cout<<"1.用户名："<<nick_name<<endl;
	cout<<"2.密码："<<password<<endl;
	cout<<"3.真实姓名："<<u_name<<endl;
	cout<<"4.手机号码："<<phone_num<<endl;
	cout<<"5.退出修改"<<endl;
	cout<<endl;

	while(1)
	{
		cout<<"请输入您想修改的信息前的序号：";
		cin>>num;
		if(num>=1&&num<=5)
		{
			break;
		}
		else
		{
			cout<<"无此选项！"<<endl;
		}
	}
	if(num==1)
	{
		string temp_nick_name;
		int a;
		while(1)
		{
			cout<<"请输入新的用户名：";
			cin >>temp_nick_name;
			for(a=0; a<50; a++)
			{
				if(temp_nick_name==users[a].nick_name)
				{
					cout<<"该用户名已被占用，请重新输入！"<<endl;
					break;
				}
			}
			if(a==50)
			{
				break;
			}
		}
		nick_name=temp_nick_name;
		//写入文件
		write_user();
		cout<<"修改成功！"<<endl;
		system("pause");
	}

	if(num==2)
	{
		string temp1_password;
		string temp2_password;
		while (1)
		{
			cout << "请输入新密码：";
			cin >> temp1_password;
			cout << "请确认新密码：";
			cin >> temp2_password;
			if (temp1_password == temp2_password)
			{
				break;
			}
			cout << "两次密码不一致，请重新输入！" << endl;
		}
		password=temp1_password;
		write_user();
		//写入文件
		cout<<"修改成功！"<<endl;
		system("pause");
	}

	if(num==3)
	{
		cout<<"请输入修改后的真实姓名：";
		cin>>u_name;
		write_user();//写入文件
		cout<<"修改成功！"<<endl;
		system("pause");
	}

	if(num==4)
	{
		cout<<"请输入修改后的手机号码：";
		cin>>phone_num;
		write_user();//写入文件
		cout<<"修改成功！"<<endl;
		system("pause");
	}

	if(num==5)
	{
		system("cls");
		return 0;
	}
}

int user::logout()  //注销
{
	string verify_password;
	while (1)
	{
		cout<<"请输入您的密码：";
		cin >> verify_password;
		if (verify_password == password)
		{
			cout << "密码正确！" << endl;
			break;
		}
		else
		{
			cout << "密码错误，请重新输入！" << endl;
		}
	}
	string  verify;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //红
	cout<<"确认注销您的账户？注销后将无法恢复！（y/n）"<<endl;
	while(1)
	{
		cin>>verify;
		if(verify=="y")
		{
			while(1)
			{
				cout<<"请再次确认注销您的账户？（y/n）"<<endl;
				cin>>verify;
				if(verify=="y")
				{
					nick_name="0";
					password="0";
					u_name="0";
					phone_num="0";
					u_stock_num=0;
					for(int x=0; x<50; x++)
					{
						s_num[x]="0";
					}

					write_user();//写入文件
					user_num=user_num-1;
					cout<<"注销成功！"<<endl;
					cout<<"感谢您的使用！"<<endl;
					system("pause");
					return 8;

				}
				if(verify=="n")
				{
					cout<<"已取消注销！"<<endl;
					system("pause");
					return 0;
				}
				if(verify!="y"&&verify!="n")
				{
					cout<<"无此选项！"<<endl;
				}
			}
		}
		if(verify=="n")
		{
			cout<<"已取消注销！"<<endl;
			system("pause");
			return 0;
		}
		if(verify!="y"&&verify!="n")
		{
			cout<<"无此选项！"<<endl;
		}
	}

}



int login()
{
	string temp_name;
	string temp_password;
	int i;
	while (1)
	{
		cout << "请输入用户名：";
		cin >> temp_name;
		for (i = 0; i < 50; i++)
		{
			if (temp_name == users[i].getnick_name())
			{
				break;
			}

		}
		if (i!=50)
		{
			break;
		}
		else
		{
			cout << "无此用户，请重新输入您的用户名（昵称）！" << endl;
		}
	}
	while (1)
	{
		cout << "请输入密码：";    //加入一个返回用户名输入的选择
		cin >> temp_password;
		if (temp_password == users[i].getpassword())
		{
			cout << "密码正确！" << endl;
			break;
		}
		else
		{
			cout << "密码错误，请重新输入！" << endl;
		}
	}


	if(users[i].user_menu(i)==8)
	{
		return 8; //header.h里已声明 ,还未定义
	}
}

int admin_login()
{
	string admin_password,flag,search;
	int jug2,x,i;
	while(1)
	{
		cout<<"请输入管理员密码：";
		cin>>admin_password;
		if(admin_password=="adminpassword")
		{
			break;
		}
		else
		{
			cout<<"密码错误，请重新输入！"<<endl;
		}
	}
	while(1)
	{
		system("cls");
		cout<<"1.查看所有股票信息"<<endl;
		cout<<"2.查看所有用户详细信息"<<endl;
		cout<<"3.退出管理员账户"<<endl;


		while(1)
		{
			cin>>jug2;
			if(jug2!=1&&jug2!=2&&jug2!=3)
			{
				cout<<"无此选项！"<<endl;
			}
			else
			{
				break;
			}
		}

		if(jug2==1)
		{
			void display_all(int);
			display_all(0);
			system("pause");
		}
		if(jug2==2)
		{

			for(x=0; x<50; x++)
			{
				if(users[x].getnick_name()!="0")
				{
					cout<<users[x].getnick_name()<<"  "<<users[x].getpassword()<<"  "<<users[x].getu_name()<<" "<<users[x].getphone_num()<<"  "<<users[x].getu_stock_num()<<endl;
				}
			}
			cout<<"是否继续查看用户选择的股票？（y/n）";
			while(1)
			{
				cin>>flag;
				if(flag!="y"&&flag!="n")
				{
					cout<<"无此选项！"<<endl;
				}
				if(flag=="y")
				{
					cout<<"输入对应用户昵称，查看该用户选择的股票：";
					while (1)
					{
						cin >> search;
						for (i = 0; i < 50; i++)
						{
							if (search == users[i].getnick_name())
							{
								break;
							}

						}
						if (i!=50)
						{
							break;
						}
						else
						{
							cout << "无此用户，请重新输入您的用户名（昵称）！" << endl;
						}
					}
					users[i].display();
					system("pause");
					break;
				}
				if(flag=="n")
				{
					system("pause");
					break;
				}
			}

		}
		if(jug2==3)
		{
			return 0;
		}

	}
}

stock::stock()     //初始化为0值后续判断是否存在用
{
	s_num="0";
	//cout<<s_num;
	s_name="0";
	for(int t=0; t<30; t++)
	{
		open_pri[t]=0;
		close_pri[t]=0;
		highest_pri_d[t]=0;
	}

}

user::user()
{
	nick_name="0";
	password="0";
	u_name="0";
	phone_num="0";
	u_stock_num=0;
	for(int x=0; x<50; x++)
	{
		s_num[x]="0";
	}
}

float stock::getclose_pri(const int& num) const
{
	return close_pri[num];
}

float stock::gethighest_pri_d(const int& num) const
{
	return highest_pri_d[num];
}

float stock::getopen_pri(const int& num) const
{
	return open_pri[num];
}

string stock::gets_name() const
{
	return s_name;
}

string stock::gets_num() const
{
	return s_num;
}

void stock::sets_num(string& s_num)
{
	this->s_num=s_num;
}

void stock::sets_name(string& s_name)
{
	this->s_name=s_name;
}

void stock::setopen_pri(int& num,float& open_pri)
{
	this->open_pri[num]=open_pri;
}

void stock::setclose_pri(int& num,float& close_pri)
{
	this->close_pri[num]=close_pri;
}

void stock::sethighest_pri_d(int& num,float& highest_pri_d)
{
	this->highest_pri_d[num]=highest_pri_d;
}



void setstock()   //从文件读取所有股票信息
{
	fstream fs;
	string t_s_num,t_s_name;
	float t_open_pri,t_close_pri,t_highest_pri_d;
	fs.open("stock_data.txt",ios::in);
	if(!fs)
	{
		cout<<"股票信息读取失败！"<<endl;
		system("pause");
		exit(0);
	}
	for(int num=0; num<50; num++)                                         //加一个如果读取到文件尾，则令后面的所有数据为0，输出时为0截止
	{

		fs>>t_s_num>>t_s_name;
		if(fs.eof())     //读取后发现已到文件尾，就不再赋值
		{
			break;
		}
		stocks[num].sets_name(t_s_name);
		stocks[num].sets_num(t_s_num);
		for(int num1=0; num1<30; num1++)    //一支股票存30天的价格数据30天的价格数据
		{
			fs>>t_open_pri>>t_close_pri>>t_highest_pri_d;
			stocks[num].setopen_pri(num1,t_open_pri);
			stocks[num].setclose_pri(num1,t_close_pri);
			stocks[num].sethighest_pri_d(num1,t_highest_pri_d);
		}
	}

	fs.close();

}

float stock::pri_pre() const //最小二乘法
{
	float m,n,x_ave,y_ave,t1,t2;
	x_ave=((1+20)*20/2)/20;
	for(int t=0; t<20; t++)
	{
		y_ave=y_ave+close_pri[t];
	}
	y_ave=y_ave/20;
	for(int t=0; t<20; t++)
	{
		t1=t1+(t+1)*close_pri[t];
		t2=t2+(t+1)*(t+1);
	}
	n=(t1-20*x_ave*y_ave)/(t2-20*x_ave*x_ave);
	m=y_ave-n*x_ave;
	return (n*21+m);
}


string user::getnick_name() const
{
	return nick_name;
}

string user::getpassword() const
{
	return password;
}
string user::getu_name() const
{
	return u_name;
}
string user::getphone_num() const
{
	return phone_num;
}
int user::getu_stock_num() const
{
	return u_stock_num;
}

string user::gets_num(const int& n) const
{
	return s_num[n];
}

void user::setu_stock_num_add(int num)
{
	u_stock_num=u_stock_num+num;
}

void user::sets_num(const int& num,string s_num)
{
	this->s_num[num]=s_num;
}

/*void user::sets_num(const int& s_num)
{
	this->s_num=s_num;
}  */

void user::setnick_name(string& nick_name)
{
	this->nick_name=nick_name;
}

void user::setpassword(string& password)
{
	this->password=password;
}

void user::setphone_num(string& phone_num)
{
	this->phone_num=phone_num;
}

void user::setu_name(string& u_name)
{
	this->u_name=u_name;
}

void user::setu_stock_num(int& u_stock_num)
{
	this->u_stock_num=u_stock_num;
}

ostream& operator<<(ostream& out,stock A)   //格式输出某一支股票的所有信息
{
	cout<<"以下是该股票的近30天价格记录："<<endl;
	out<<A.s_num<<"  "<<A.s_name<<"："<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN|FOREGROUND_BLUE);   //红
	out<<"          "<<"开盘"<<"  "<<"收盘"<<"    "<<"最高"<<"  "<<"预测"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);   //红
	for(int a=0; a<30; a++)
	{
		if(A.close_pri[a]>A.close_pri[a+1]&&a!=29)
		{

			out<<"距今"<<a+1<<"天：";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //红
			out<<setiosflags(ios::left)<<setprecision(4)<<A.open_pri[a]<<"  "<<A.close_pri[a]<<"  "<<A.highest_pri_d[a]<<"  "<<A.pri_pre()<<"  "<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白
		}
		if(A.close_pri[a]<A.close_pri[a+1]&&a!=29)
		{
			out<<"距今"<<a+1<<"天：";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //绿
			out<<setiosflags(ios::left)<<setprecision(4)<<setiosflags(ios::showpoint)<<A.open_pri[a]<<"  "<<A.close_pri[a]<<"  "<<A.highest_pri_d[a]<<"  "<<A.pri_pre()<<"  "<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白
		}
		if(A.close_pri[a]==A.close_pri[a+1]||a==29)
		{
			out<<"距今"<<a+1<<"天：";
			out<<setiosflags(ios::left)<<setprecision(4)<<setiosflags(ios::showpoint)<<A.open_pri[a]<<"  "<<A.close_pri[a]<<"  "<<A.highest_pri_d[a]<<"  "<<A.pri_pre()<<"  "<<endl;
		}
		//锁定4位有效数字，不足四位的强制补 0和小数点，强制左对齐
	}
	return out;
}

void write_user()
{
	string const_name="user";
	string name=const_name;
	fstream fs[user_num+empty_file];   //第一次编译user_num==0所以这里报错
	int file_num,z;
	for(file_num=1; file_num<=user_num+empty_file; file_num++)       //循环打开用户总数个文件
	{
		//cout<<"flag";
		name=const_name+" "+to_string(file_num)+".txt";
		fs[file_num-1].open(name.c_str(),ios::out);     //批量生成文件
		if(!(fs[file_num-1]))
		{
			cout<<"user"<<" "<<file_num<<"打开失败！"<<endl;
			system("pause");
			exit(0);
		}
	}

	for(file_num=1,z=0; file_num<=user_num+empty_file&&z<50; file_num++)
	{
		if(users[z].getnick_name()!="0"||users[z].getpassword()!="0")   //写入不为0的用户（存在 的用户）
		{
			fs[file_num-1]<<users[z].getnick_name()<<" "<<users[z].getpassword()<<endl<<users[z].getu_name()<<" "<<users[z].getphone_num()<<endl<<users[z].getu_stock_num()<<endl;
			for(int x=0; x<50; x++)
			{
				if(users[z].gets_num(x)!="0")   //写入持有的股票
				{
					fs[file_num-1]<<users[z].gets_num(x)<<endl;
				}
			}
			z++;
		}
		else
		{
			z++;
			continue;  //为空的时候，文件对象不往后跳,文件往后移动一个
		}
	}
	for(file_num=1; file_num<=user_num+empty_file; file_num++)
	{
		fs[file_num-1].close();
	}
}

void read_user()
{
	string const_name="user";
	string name=const_name;
	fstream fs[50];   //第一次编译user_num==0所以这里报错
	int file_num,z,t_u_stock_num;
	string t_nick_name,t_password,t_u_name,t_phone_num,t_s_num[50];
	int flag=50;
	bool jump;
	int empty[50],e=0;//记录空文件
	for(int o=0; o<50; o++)
	{
		empty[o]=100;
	}
	for(file_num=1; file_num<=50; file_num++)       //循环打开用户总数个文件
	{
		name=const_name+" "+to_string(file_num)+".txt";
		fs[file_num-1].open(name.c_str(),ios::in);     //批量生成文件
		//cout<<"file_num "<<file_num<<endl;
		if(!fs[file_num-1])
		{
			//cout<<"flag";
			flag=file_num-1;      //记录无对应文件的第一个对象数组序号
			break;
		}
		/*if(fs[file_num-1].eof()==1)
		{
			cout<<"eof";
			empty[e]=file_num-1;
			e++;
		}*/
	}
//cout<<file_num<<endl;
//cout<<"这是flag"<<flag;

	for(file_num=1,z=0; file_num<=flag; z++,file_num++)   //读取
	{
		//cout<<flag<<endl;
		fs[file_num-1]>>t_nick_name>>t_password>>t_u_name>>t_phone_num>>t_u_stock_num;
		////cout<<"t_nick_name"<<t_nick_name<<endl;
		////cout<<"user"<<file_num<<" "<<"eof="<<fs[file_num-1].eof()<<endl;
		//cout<<"1.file_num:"<<file_num<<endl;
		if(fs[file_num-1].eof())
		{
			//cout<<"2.file_num:"<<file_num<<endl;
			empty_file=empty_file+1;                //记录空文件个数，写入时多创建的个数
			continue;
		}
		for(int e1=0; e1<50; e1++)
		{
			//cout<<"file_num="<<file_num<<endl;
			/*if((file_num-1)==empty[e1])
			{
				jump=1;
				//cout<<"jump==1";
			    //cout<<"file_num-1="<<file_num-1<<" "<<"empty="<<empty[e1];
			}

			}*/
			/*if(jump==1)
			{
				//cout<<"continue";
				continue;
			}*/
			//cout<<"赋值";
			users[z].setnick_name(t_nick_name);
			users[z].setpassword(t_password);
			users[z].setu_name(t_u_name);
			users[z].setphone_num(t_phone_num);
			users[z].setu_stock_num(t_u_stock_num);
			//cout<<"3.file_num:"<<file_num<<endl;
			//cout<<users[z].getnick_name()<<endl;
			for(int x=0; x<50; x++)
			{
				fs[file_num-1]>>t_s_num[x];
				if(fs[file_num-1].eof())
				{
					continue;
				}
				users[z].sets_num(x,t_s_num[x]);
			}
		}
	}

	for(int x=0; x<50; x++)
	{
		//cout<<"for";
		if(users[x].getnick_name()!="0"&&users[x].getpassword()!="0")
		{
			//cout<<"+1";
			//cout<<users[x].getnick_name()<<endl;
			user_num=user_num+1;   //统计总人数
		}
	}

	for(file_num=1; file_num<=user_num+empty_file; file_num++)
	{
		fs[file_num-1].close();
	}
}


void user::display() const
{
	cout<<"              ***             " ;
	cout<<"以下是持有的"<<u_stock_num<<"支股票和当日预测价格"<<"               ***"<<endl;

	//这里做表格首列 ，最终主体合适后再加这里
	cout<<setiosflags(ios::left)<<setprecision(4)<<setw(4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE);
	cout<<"              ***             开盘价"<<"  "<<"收盘价"<<"  "<<"预测明日价格"<<"                    ***"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

	for(int i=0; i<50; i++)
	{
		for(int t=0; t<50; t++)
		{
			if(s_num[i]==stocks[t].gets_num()&&stocks[t].gets_num()!="0")
			{
				if(stocks[t].getclose_pri(0)>stocks[t].getclose_pri(1))
				{
					cout<<"              ***             " ;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //红
					cout<<stocks[t].gets_num()<<"  "<<stocks[t].gets_name()<<"  "<<stocks[t].pri_pre();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白
					cout<<"                         ***"<<endl;
				}
				if(stocks[t].getclose_pri(0)<stocks[t].getclose_pri(1))
				{
					cout<<"              ***             " ;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
					cout<<stocks[t].gets_num()<<"  "<<stocks[t].gets_name()<<"  "<<stocks[t].pri_pre();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白
					cout<<"                       ***"<<endl;
				}
				if(stocks[t].getclose_pri(0)==stocks[t].getclose_pri(1))
				{
					cout<<"                      ***             " ;

					cout<<stocks[t].gets_num()<<"  "<<stocks[t].gets_name()<<"  "<<stocks[t].pri_pre();
					cout<<"                         ***"<<endl;
				}
			}
		}
	}
}

void display_all(int i)   //显示所有股票
{
	int b;
	for(b=0; b<50; b++)
	{
		if((stocks[b].gets_num())!="0")
		{
			//cout<<stocks[b].gets_num()<<"  "<<stocks[b].gets_name()<<"  "<<stocks[b].pri_pre()<<endl;
			if(stocks[b].getclose_pri(0)>stocks[b].getclose_pri(1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //红
				cout<<stocks[b].gets_num()<<"  "<<stocks[b].gets_name()<<endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白
			}
			if(stocks[b].getclose_pri(0)<stocks[b].getclose_pri(1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //绿
				cout<<stocks[b].gets_num()<<"  "<<stocks[b].gets_name()<<endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

			}
			if(stocks[b].getclose_pri(0)==stocks[b].getclose_pri(1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白
				cout<<stocks[b].gets_num()<<"  "<<stocks[b].gets_name()<<endl;
			}
		}

	}
}

void add_stock(int i)   //选择新股票
{
	cout<<"以下是所有储存的股票"<<endl;
	display_all(i);
	cout<<endl;
	cout<<"请输入您想要选择的股票代号：";
	string temp_num,t_jug;
	int f;
	int d;
	while(1)
	{
		cin>>temp_num;

		for(d=0; d<50; d++)
		{
			if(temp_num==stocks[d].gets_num())
			{
				break;
			}
		}
		if(d==50)
		{
			cout<<"无此股票，请重新输入！"<<endl;
		}
		else
		{
			for(f=0; f<50; f++)
			{
				if(temp_num==users[i].gets_num(f))
				{
					cout<<"您已选择此股票！"<<endl;
					break;
				}
			}
			if(f==50)
			{
				break;
			}
		}
	}
	if(stocks[d].getclose_pri(0)<stocks[d].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //红

		cout<<"根据预测，本股票明天可能会上涨，确认选择？（y/n）";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"已取消！"<<endl;
			system("pause");
			return;
		}
	}
	if(stocks[d].getclose_pri(0)>stocks[d].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //绿

		cout<<"根据预测，本股票明天可能会下跌，确认选择？（y/n）";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"已取消！"<<endl;
			system("pause");
			return;
		}
	}
	if(stocks[d].getclose_pri(0)==stocks[d].pri_pre())
	{
		cout<<"根据预测，本股票明天可能会保持稳定，确认选择？（y/n）";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"已取消！"<<endl;
			system("pause");
			return;
		}
	}
	for(f=0; f<50; f++)
	{
		if(users[i].gets_num(f)=="0")
		{
			users[i].sets_num(f,temp_num);
			users[i].setu_stock_num_add(1);
			break;
		}
	}

	write_user();
	//文件写入部分

	cout<<"添加成功！";
	system("pause");

}

void delete_stock(int i)
{
	string t_jug;
	if(!users[i].getu_stock_num())
	{
		cout<<"您未选择任何股票！";
		system("pause");
		return;
	}
	users[i].display();
	cout<<"请输入您要删除的股票代码：";
	string temp_num;
	int c;
	while(1)
	{
		cin>>temp_num;
		for(c=0; c<50; c++)
		{
			if(temp_num==users[i].gets_num(c))
			{
				break;
			}
		}
		if(c==50)
		{
			cout<<"无此股票，请重新输入！"<<endl;
		}
		else
		{
			break;
		}
	}
	if(stocks[c].getclose_pri(0)<stocks[c].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //红

		cout<<"根据预测，本股票明天可能会上涨，确认选择？（y/n）";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"已取消！"<<endl;
			system("pause");
			return;
		}
	}
	if(stocks[c].getclose_pri(0)>stocks[c].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //绿

		cout<<"根据预测，本股票明天可能会下跌，确认选择？（y/n）";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"已取消！"<<endl;
			system("pause");
			return;
		}
	}
	if(stocks[c].getclose_pri(0)==stocks[c].pri_pre())
	{
		cout<<"根据预测，本股票明天可能会保持稳定，确认选择？（y/n）";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"已取消！"<<endl;
			system("pause");
			return;
		}
	}
	string jug2;
	cout<<"确认删除？(y/n)";
	while(1)
	{
		cin>>jug2;
		if(jug2=="y")
		{
			users[i].sets_num(c,"0");
			users[i].setu_stock_num_add(-1);

			//写入文件
			write_user();

			cout<<"删除成功！"<<endl;
			break;
		}
		if(jug2=="n")
		{
			cout<<"已取消！"<<endl;
			system("pause");
			break;
		}
		if(jug2!="n"&&jug2!="y")
		{
			cout<<"无此选项！"<<endl;
		}
	}
}




void search(int i)
{
	display_all(i);
	cout<<"请输入您要查询历史价格的股票代码或名称：";
	string temp_num;
	int c;
	while(1)
	{
		cin>>temp_num;
		for(c=0; c<50; c++)
		{
			if(temp_num==stocks[c].gets_num())
			{
				break;
			}
		}
		if(c==50)
		{
			cout<<"无此股票，请重新输入！"<<endl;
		}
		else
		{
			break;
		}
	}

	cout<<stocks[c];
	//cout<<stocks[c].getclose_pri(0)<<" "<<stocks[c].pri_pre();
	if(stocks[c].getclose_pri(0)<stocks[c].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout<<"根据预测，本股票明天可能会上涨"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白
	}
	if(stocks[c].getclose_pri(0)>stocks[c].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //绿
		cout<<"根据预测，本股票明天可能会下跌"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白

	}
	if(stocks[c].getclose_pri(0)==stocks[c].pri_pre())
	{
		cout<<"根据预测，本股票明天可能会保持稳定"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//白
	}
	system("pause");
	system("cls");

}

int user::user_menu(int i)
{
	int jug1;

	while(1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		system("cls");
		cout<<"            ***********************************************************************"<<endl;
		cout<< "              ***                  欢迎使用股票管理系统！                     ***" <<endl;
		cout<<"              ***             系统中一共有"<<user_num<<"个用户                             ***"<<endl;
		display();
		cout<<"              ***             请选择您需要的功能                              ***"<<endl;
		cout<<"              ***             1.选择一支新股票管理                            ***"<<endl;
		cout<<"              ***             2.删除一支已选择的股票                          ***"<<endl;
		cout<<"              ***             3.查询一支股票的近30天价格信息                  ***"<<endl;
		cout<<"              ***             4.修改账户信息                                  ***"<<endl;
		cout<<"              ***             5.注销用户（删除所有用户信息）                  ***"<<endl;
		cout<<"              ***             6.退出系统                                      ***"<<endl;
		cout<<"            ***********************************************************************"<<endl;
		while(1)
		{
			cin>>jug1;
			if(jug1<1||jug1>6)
			{

				cout<<"无此选项，请重新输入！"<<endl;
				//输入正误判断
			}
			else
			{
				break;
			}
		}


		if(jug1==1)
		{
			void display_all();   //声明   显示所有股票
			//cout<<stocks[0].gets_num()<<endl;
			//cout<<users[i].gets_num(0);
			add_stock(i);
		}

		if(jug1==2)
		{
			delete_stock(i);
		}

		if(jug1==3)
		{
			search(i);
		}

		if(jug1==4)
		{
			change();
		}
		if(jug1==5)
		{
			if(logout()==8)
			{
				return 0;
			}

		}
		if(jug1==6)
		{
			return 8;//返回8告诉上级菜单用户退出程序
		}
	}

	system("cls");
}

int main()
{
	//cout<<endl<<stocks[0].gets_num()<<endl;
	setstock();
	read_user();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	//开头文件读取，初始化统计值
	void menu1();
	menu1();

	return 0;
}



