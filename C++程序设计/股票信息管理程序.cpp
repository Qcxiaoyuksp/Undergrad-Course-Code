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
		//��Ʊ��Ϣ�����ļ���ȡ���û�ֻ���޸�ѡ��Ĺ�Ʊ
		string s_num;
		string s_name;
		float open_pri[30];
		float close_pri[30];
		float highest_pri_d[30];	//������߼�
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

		float pri_pre() const;    //����Ԥ�⺯��
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
		string s_num[50];  //��¼�û�ѡ��Ĺ�Ʊ����,��get��������
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
		/*void sets_num(const int&);  //���ļ� ͳ��  */
		void setnick_name(string&);
		void setpassword(string&);
		void setu_name(string&);
		void setphone_num(string&);
		void setu_stock_num(int&);



		int add();
		int change();
		int logout();   //ע���û�
		int user_menu(int) ;
		void display() const;  //��ʾ�û����Ѿ�ѡ��Ĺ�Ʊ

};
//�û�����͹�Ʊ��������ֺ�����s
const int MAX_NUM=50;
user users[MAX_NUM];
stock stocks[MAX_NUM];
int user_num=0,empty_file=0;
int login();
void display__all();
void write_user();

void menu1()      //�����
{
	while(1)
	{
		//��
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN|FOREGROUND_RED);
		cout<<"            ***********************************************************************"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_GREEN);
		cout << "             ***                  "<<"��ӭʹ�ù�Ʊ����ϵͳ��                      ***" << endl;
		cout << "             ***                      1.�������û�                            ***" << endl;
		cout << "             ***                      2.�����û���¼                          *** " << endl;
		cout << "             ***                      3.����Ա��¼                            ***" << endl;
		cout << "             ***                      4.�˳�ϵͳ                              ***" << endl;
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
				cout<<"�޴�ѡ�����������!"<<endl;
			}
		}

		if (jug == 1)
		{
			if(users[user_num].add()==8);//�����Ǵ�0��ʼ��  //ѭ����������֤������ʹ��ǰ�Ѷ��壬�����  //#ifndef �����߱������ڱ���ʱ���ظ����� �����壩
			//������add�������Ѿ�����
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
			cout<<"��лʹ�ã�";
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
		cout << "�������û�����";
		cin >> nick_name;
		for(a=0; a<50; a++)
		{
			if(a==user_num)
			{
				continue;
			}
			if(nick_name==users[a].nick_name)
			{
				cout<<"�û����ѱ�ռ�ã����������룡"<<endl;
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
		cout << "���������룺";
		cin >> password;
		cout << "��ȷ�����룺";
		string temp_password;
		cin >> temp_password;
		if (temp_password == password)
		{
			break;
		}
		cout << "�������벻һ�£����������룡" << endl;
	}
	cout << "������������ʵ������";
	cin >> u_name;
	cout << "�����������ֻ��ţ�";
	cin >> phone_num;
	user_num++;  //����������
	//����������ļ�д��
	//6.3 0:36
	write_user();



	cout<<"�����û��ɹ���";   //�����һ���ļ�д���ж�

	system("pause");
	users[user_num-1].user_menu(user_num-1);   //ǰ��user_num�Ѿ�+1���������Ҫ����ȥ����������������
	return 8;
}

int user::change()
{
	int num;
	cout<<"���ĵ�ǰ������Ϣ��"<<endl;
	cout<<"1.�û�����"<<nick_name<<endl;
	cout<<"2.���룺"<<password<<endl;
	cout<<"3.��ʵ������"<<u_name<<endl;
	cout<<"4.�ֻ����룺"<<phone_num<<endl;
	cout<<"5.�˳��޸�"<<endl;
	cout<<endl;

	while(1)
	{
		cout<<"�����������޸ĵ���Ϣǰ����ţ�";
		cin>>num;
		if(num>=1&&num<=5)
		{
			break;
		}
		else
		{
			cout<<"�޴�ѡ�"<<endl;
		}
	}
	if(num==1)
	{
		string temp_nick_name;
		int a;
		while(1)
		{
			cout<<"�������µ��û�����";
			cin >>temp_nick_name;
			for(a=0; a<50; a++)
			{
				if(temp_nick_name==users[a].nick_name)
				{
					cout<<"���û����ѱ�ռ�ã����������룡"<<endl;
					break;
				}
			}
			if(a==50)
			{
				break;
			}
		}
		nick_name=temp_nick_name;
		//д���ļ�
		write_user();
		cout<<"�޸ĳɹ���"<<endl;
		system("pause");
	}

	if(num==2)
	{
		string temp1_password;
		string temp2_password;
		while (1)
		{
			cout << "�����������룺";
			cin >> temp1_password;
			cout << "��ȷ�������룺";
			cin >> temp2_password;
			if (temp1_password == temp2_password)
			{
				break;
			}
			cout << "�������벻һ�£����������룡" << endl;
		}
		password=temp1_password;
		write_user();
		//д���ļ�
		cout<<"�޸ĳɹ���"<<endl;
		system("pause");
	}

	if(num==3)
	{
		cout<<"�������޸ĺ����ʵ������";
		cin>>u_name;
		write_user();//д���ļ�
		cout<<"�޸ĳɹ���"<<endl;
		system("pause");
	}

	if(num==4)
	{
		cout<<"�������޸ĺ���ֻ����룺";
		cin>>phone_num;
		write_user();//д���ļ�
		cout<<"�޸ĳɹ���"<<endl;
		system("pause");
	}

	if(num==5)
	{
		system("cls");
		return 0;
	}
}

int user::logout()  //ע��
{
	string verify_password;
	while (1)
	{
		cout<<"�������������룺";
		cin >> verify_password;
		if (verify_password == password)
		{
			cout << "������ȷ��" << endl;
			break;
		}
		else
		{
			cout << "����������������룡" << endl;
		}
	}
	string  verify;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //��
	cout<<"ȷ��ע�������˻���ע�����޷��ָ�����y/n��"<<endl;
	while(1)
	{
		cin>>verify;
		if(verify=="y")
		{
			while(1)
			{
				cout<<"���ٴ�ȷ��ע�������˻�����y/n��"<<endl;
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

					write_user();//д���ļ�
					user_num=user_num-1;
					cout<<"ע���ɹ���"<<endl;
					cout<<"��л����ʹ�ã�"<<endl;
					system("pause");
					return 8;

				}
				if(verify=="n")
				{
					cout<<"��ȡ��ע����"<<endl;
					system("pause");
					return 0;
				}
				if(verify!="y"&&verify!="n")
				{
					cout<<"�޴�ѡ�"<<endl;
				}
			}
		}
		if(verify=="n")
		{
			cout<<"��ȡ��ע����"<<endl;
			system("pause");
			return 0;
		}
		if(verify!="y"&&verify!="n")
		{
			cout<<"�޴�ѡ�"<<endl;
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
		cout << "�������û�����";
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
			cout << "�޴��û������������������û������ǳƣ���" << endl;
		}
	}
	while (1)
	{
		cout << "���������룺";    //����һ�������û��������ѡ��
		cin >> temp_password;
		if (temp_password == users[i].getpassword())
		{
			cout << "������ȷ��" << endl;
			break;
		}
		else
		{
			cout << "����������������룡" << endl;
		}
	}


	if(users[i].user_menu(i)==8)
	{
		return 8; //header.h�������� ,��δ����
	}
}

int admin_login()
{
	string admin_password,flag,search;
	int jug2,x,i;
	while(1)
	{
		cout<<"���������Ա���룺";
		cin>>admin_password;
		if(admin_password=="adminpassword")
		{
			break;
		}
		else
		{
			cout<<"����������������룡"<<endl;
		}
	}
	while(1)
	{
		system("cls");
		cout<<"1.�鿴���й�Ʊ��Ϣ"<<endl;
		cout<<"2.�鿴�����û���ϸ��Ϣ"<<endl;
		cout<<"3.�˳�����Ա�˻�"<<endl;


		while(1)
		{
			cin>>jug2;
			if(jug2!=1&&jug2!=2&&jug2!=3)
			{
				cout<<"�޴�ѡ�"<<endl;
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
			cout<<"�Ƿ�����鿴�û�ѡ��Ĺ�Ʊ����y/n��";
			while(1)
			{
				cin>>flag;
				if(flag!="y"&&flag!="n")
				{
					cout<<"�޴�ѡ�"<<endl;
				}
				if(flag=="y")
				{
					cout<<"�����Ӧ�û��ǳƣ��鿴���û�ѡ��Ĺ�Ʊ��";
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
							cout << "�޴��û������������������û������ǳƣ���" << endl;
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

stock::stock()     //��ʼ��Ϊ0ֵ�����ж��Ƿ������
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



void setstock()   //���ļ���ȡ���й�Ʊ��Ϣ
{
	fstream fs;
	string t_s_num,t_s_name;
	float t_open_pri,t_close_pri,t_highest_pri_d;
	fs.open("stock_data.txt",ios::in);
	if(!fs)
	{
		cout<<"��Ʊ��Ϣ��ȡʧ�ܣ�"<<endl;
		system("pause");
		exit(0);
	}
	for(int num=0; num<50; num++)                                         //��һ�������ȡ���ļ�β������������������Ϊ0�����ʱΪ0��ֹ
	{

		fs>>t_s_num>>t_s_name;
		if(fs.eof())     //��ȡ�����ѵ��ļ�β���Ͳ��ٸ�ֵ
		{
			break;
		}
		stocks[num].sets_name(t_s_name);
		stocks[num].sets_num(t_s_num);
		for(int num1=0; num1<30; num1++)    //һ֧��Ʊ��30��ļ۸�����30��ļ۸�����
		{
			fs>>t_open_pri>>t_close_pri>>t_highest_pri_d;
			stocks[num].setopen_pri(num1,t_open_pri);
			stocks[num].setclose_pri(num1,t_close_pri);
			stocks[num].sethighest_pri_d(num1,t_highest_pri_d);
		}
	}

	fs.close();

}

float stock::pri_pre() const //��С���˷�
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

ostream& operator<<(ostream& out,stock A)   //��ʽ���ĳһ֧��Ʊ��������Ϣ
{
	cout<<"�����Ǹù�Ʊ�Ľ�30��۸��¼��"<<endl;
	out<<A.s_num<<"  "<<A.s_name<<"��"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN|FOREGROUND_BLUE);   //��
	out<<"          "<<"����"<<"  "<<"����"<<"    "<<"���"<<"  "<<"Ԥ��"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);   //��
	for(int a=0; a<30; a++)
	{
		if(A.close_pri[a]>A.close_pri[a+1]&&a!=29)
		{

			out<<"���"<<a+1<<"�죺";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //��
			out<<setiosflags(ios::left)<<setprecision(4)<<A.open_pri[a]<<"  "<<A.close_pri[a]<<"  "<<A.highest_pri_d[a]<<"  "<<A.pri_pre()<<"  "<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��
		}
		if(A.close_pri[a]<A.close_pri[a+1]&&a!=29)
		{
			out<<"���"<<a+1<<"�죺";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //��
			out<<setiosflags(ios::left)<<setprecision(4)<<setiosflags(ios::showpoint)<<A.open_pri[a]<<"  "<<A.close_pri[a]<<"  "<<A.highest_pri_d[a]<<"  "<<A.pri_pre()<<"  "<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��
		}
		if(A.close_pri[a]==A.close_pri[a+1]||a==29)
		{
			out<<"���"<<a+1<<"�죺";
			out<<setiosflags(ios::left)<<setprecision(4)<<setiosflags(ios::showpoint)<<A.open_pri[a]<<"  "<<A.close_pri[a]<<"  "<<A.highest_pri_d[a]<<"  "<<A.pri_pre()<<"  "<<endl;
		}
		//����4λ��Ч���֣�������λ��ǿ�Ʋ� 0��С���㣬ǿ�������
	}
	return out;
}

void write_user()
{
	string const_name="user";
	string name=const_name;
	fstream fs[user_num+empty_file];   //��һ�α���user_num==0�������ﱨ��
	int file_num,z;
	for(file_num=1; file_num<=user_num+empty_file; file_num++)       //ѭ�����û��������ļ�
	{
		//cout<<"flag";
		name=const_name+" "+to_string(file_num)+".txt";
		fs[file_num-1].open(name.c_str(),ios::out);     //���������ļ�
		if(!(fs[file_num-1]))
		{
			cout<<"user"<<" "<<file_num<<"��ʧ�ܣ�"<<endl;
			system("pause");
			exit(0);
		}
	}

	for(file_num=1,z=0; file_num<=user_num+empty_file&&z<50; file_num++)
	{
		if(users[z].getnick_name()!="0"||users[z].getpassword()!="0")   //д�벻Ϊ0���û������� ���û���
		{
			fs[file_num-1]<<users[z].getnick_name()<<" "<<users[z].getpassword()<<endl<<users[z].getu_name()<<" "<<users[z].getphone_num()<<endl<<users[z].getu_stock_num()<<endl;
			for(int x=0; x<50; x++)
			{
				if(users[z].gets_num(x)!="0")   //д����еĹ�Ʊ
				{
					fs[file_num-1]<<users[z].gets_num(x)<<endl;
				}
			}
			z++;
		}
		else
		{
			z++;
			continue;  //Ϊ�յ�ʱ���ļ�����������,�ļ������ƶ�һ��
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
	fstream fs[50];   //��һ�α���user_num==0�������ﱨ��
	int file_num,z,t_u_stock_num;
	string t_nick_name,t_password,t_u_name,t_phone_num,t_s_num[50];
	int flag=50;
	bool jump;
	int empty[50],e=0;//��¼���ļ�
	for(int o=0; o<50; o++)
	{
		empty[o]=100;
	}
	for(file_num=1; file_num<=50; file_num++)       //ѭ�����û��������ļ�
	{
		name=const_name+" "+to_string(file_num)+".txt";
		fs[file_num-1].open(name.c_str(),ios::in);     //���������ļ�
		//cout<<"file_num "<<file_num<<endl;
		if(!fs[file_num-1])
		{
			//cout<<"flag";
			flag=file_num-1;      //��¼�޶�Ӧ�ļ��ĵ�һ�������������
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
//cout<<"����flag"<<flag;

	for(file_num=1,z=0; file_num<=flag; z++,file_num++)   //��ȡ
	{
		//cout<<flag<<endl;
		fs[file_num-1]>>t_nick_name>>t_password>>t_u_name>>t_phone_num>>t_u_stock_num;
		////cout<<"t_nick_name"<<t_nick_name<<endl;
		////cout<<"user"<<file_num<<" "<<"eof="<<fs[file_num-1].eof()<<endl;
		//cout<<"1.file_num:"<<file_num<<endl;
		if(fs[file_num-1].eof())
		{
			//cout<<"2.file_num:"<<file_num<<endl;
			empty_file=empty_file+1;                //��¼���ļ�������д��ʱ�ഴ���ĸ���
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
			//cout<<"��ֵ";
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
			user_num=user_num+1;   //ͳ��������
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
	cout<<"�����ǳ��е�"<<u_stock_num<<"֧��Ʊ�͵���Ԥ��۸�"<<"               ***"<<endl;

	//������������� ������������ʺ��ټ�����
	cout<<setiosflags(ios::left)<<setprecision(4)<<setw(4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE);
	cout<<"              ***             ���̼�"<<"  "<<"���̼�"<<"  "<<"Ԥ�����ռ۸�"<<"                    ***"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

	for(int i=0; i<50; i++)
	{
		for(int t=0; t<50; t++)
		{
			if(s_num[i]==stocks[t].gets_num()&&stocks[t].gets_num()!="0")
			{
				if(stocks[t].getclose_pri(0)>stocks[t].getclose_pri(1))
				{
					cout<<"              ***             " ;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //��
					cout<<stocks[t].gets_num()<<"  "<<stocks[t].gets_name()<<"  "<<stocks[t].pri_pre();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��
					cout<<"                         ***"<<endl;
				}
				if(stocks[t].getclose_pri(0)<stocks[t].getclose_pri(1))
				{
					cout<<"              ***             " ;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
					cout<<stocks[t].gets_num()<<"  "<<stocks[t].gets_name()<<"  "<<stocks[t].pri_pre();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��
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

void display_all(int i)   //��ʾ���й�Ʊ
{
	int b;
	for(b=0; b<50; b++)
	{
		if((stocks[b].gets_num())!="0")
		{
			//cout<<stocks[b].gets_num()<<"  "<<stocks[b].gets_name()<<"  "<<stocks[b].pri_pre()<<endl;
			if(stocks[b].getclose_pri(0)>stocks[b].getclose_pri(1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //��
				cout<<stocks[b].gets_num()<<"  "<<stocks[b].gets_name()<<endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��
			}
			if(stocks[b].getclose_pri(0)<stocks[b].getclose_pri(1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //��
				cout<<stocks[b].gets_num()<<"  "<<stocks[b].gets_name()<<endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

			}
			if(stocks[b].getclose_pri(0)==stocks[b].getclose_pri(1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��
				cout<<stocks[b].gets_num()<<"  "<<stocks[b].gets_name()<<endl;
			}
		}

	}
}

void add_stock(int i)   //ѡ���¹�Ʊ
{
	cout<<"���������д���Ĺ�Ʊ"<<endl;
	display_all(i);
	cout<<endl;
	cout<<"����������Ҫѡ��Ĺ�Ʊ���ţ�";
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
			cout<<"�޴˹�Ʊ�����������룡"<<endl;
		}
		else
		{
			for(f=0; f<50; f++)
			{
				if(temp_num==users[i].gets_num(f))
				{
					cout<<"����ѡ��˹�Ʊ��"<<endl;
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //��

		cout<<"����Ԥ�⣬����Ʊ������ܻ����ǣ�ȷ��ѡ�񣿣�y/n��";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"��ȡ����"<<endl;
			system("pause");
			return;
		}
	}
	if(stocks[d].getclose_pri(0)>stocks[d].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //��

		cout<<"����Ԥ�⣬����Ʊ������ܻ��µ���ȷ��ѡ�񣿣�y/n��";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"��ȡ����"<<endl;
			system("pause");
			return;
		}
	}
	if(stocks[d].getclose_pri(0)==stocks[d].pri_pre())
	{
		cout<<"����Ԥ�⣬����Ʊ������ܻᱣ���ȶ���ȷ��ѡ�񣿣�y/n��";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"��ȡ����"<<endl;
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
	//�ļ�д�벿��

	cout<<"��ӳɹ���";
	system("pause");

}

void delete_stock(int i)
{
	string t_jug;
	if(!users[i].getu_stock_num())
	{
		cout<<"��δѡ���κι�Ʊ��";
		system("pause");
		return;
	}
	users[i].display();
	cout<<"��������Ҫɾ���Ĺ�Ʊ���룺";
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
			cout<<"�޴˹�Ʊ�����������룡"<<endl;
		}
		else
		{
			break;
		}
	}
	if(stocks[c].getclose_pri(0)<stocks[c].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);   //��

		cout<<"����Ԥ�⣬����Ʊ������ܻ����ǣ�ȷ��ѡ�񣿣�y/n��";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"��ȡ����"<<endl;
			system("pause");
			return;
		}
	}
	if(stocks[c].getclose_pri(0)>stocks[c].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //��

		cout<<"����Ԥ�⣬����Ʊ������ܻ��µ���ȷ��ѡ�񣿣�y/n��";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"��ȡ����"<<endl;
			system("pause");
			return;
		}
	}
	if(stocks[c].getclose_pri(0)==stocks[c].pri_pre())
	{
		cout<<"����Ԥ�⣬����Ʊ������ܻᱣ���ȶ���ȷ��ѡ�񣿣�y/n��";
		cin>>t_jug;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

		if(t_jug=="y")
		{

		}
		else
		{
			cout<<"��ȡ����"<<endl;
			system("pause");
			return;
		}
	}
	string jug2;
	cout<<"ȷ��ɾ����(y/n)";
	while(1)
	{
		cin>>jug2;
		if(jug2=="y")
		{
			users[i].sets_num(c,"0");
			users[i].setu_stock_num_add(-1);

			//д���ļ�
			write_user();

			cout<<"ɾ���ɹ���"<<endl;
			break;
		}
		if(jug2=="n")
		{
			cout<<"��ȡ����"<<endl;
			system("pause");
			break;
		}
		if(jug2!="n"&&jug2!="y")
		{
			cout<<"�޴�ѡ�"<<endl;
		}
	}
}




void search(int i)
{
	display_all(i);
	cout<<"��������Ҫ��ѯ��ʷ�۸�Ĺ�Ʊ��������ƣ�";
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
			cout<<"�޴˹�Ʊ�����������룡"<<endl;
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
		cout<<"����Ԥ�⣬����Ʊ������ܻ�����"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��
	}
	if(stocks[c].getclose_pri(0)>stocks[c].pri_pre())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);                                                                                          //��
		cout<<"����Ԥ�⣬����Ʊ������ܻ��µ�"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��

	}
	if(stocks[c].getclose_pri(0)==stocks[c].pri_pre())
	{
		cout<<"����Ԥ�⣬����Ʊ������ܻᱣ���ȶ�"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//��
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
		cout<< "              ***                  ��ӭʹ�ù�Ʊ����ϵͳ��                     ***" <<endl;
		cout<<"              ***             ϵͳ��һ����"<<user_num<<"���û�                             ***"<<endl;
		display();
		cout<<"              ***             ��ѡ������Ҫ�Ĺ���                              ***"<<endl;
		cout<<"              ***             1.ѡ��һ֧�¹�Ʊ����                            ***"<<endl;
		cout<<"              ***             2.ɾ��һ֧��ѡ��Ĺ�Ʊ                          ***"<<endl;
		cout<<"              ***             3.��ѯһ֧��Ʊ�Ľ�30��۸���Ϣ                  ***"<<endl;
		cout<<"              ***             4.�޸��˻���Ϣ                                  ***"<<endl;
		cout<<"              ***             5.ע���û���ɾ�������û���Ϣ��                  ***"<<endl;
		cout<<"              ***             6.�˳�ϵͳ                                      ***"<<endl;
		cout<<"            ***********************************************************************"<<endl;
		while(1)
		{
			cin>>jug1;
			if(jug1<1||jug1>6)
			{

				cout<<"�޴�ѡ����������룡"<<endl;
				//���������ж�
			}
			else
			{
				break;
			}
		}


		if(jug1==1)
		{
			void display_all();   //����   ��ʾ���й�Ʊ
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
			return 8;//����8�����ϼ��˵��û��˳�����
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
	//��ͷ�ļ���ȡ����ʼ��ͳ��ֵ
	void menu1();
	menu1();

	return 0;
}



