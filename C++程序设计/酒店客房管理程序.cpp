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
	cout << "����"; cin >> number; cout << endl;
	cout << "�۸�"; cin >> price; cout << endl;
	cout << "�ȼ�����1��2"; cin >> grade;
	if (grade != 1 && grade != 2)
	{
		cout << "�����������������" << endl;
		cin >> grade;
	}
	cout << "�Ƿ���ۣ��ѳ���1/δ����2" << endl; cin >> a;
	if (a == "1")
	{
		cout << "���������ʱ��" << endl; cin >> sell_time;
	}
	else if (a == "2")
		cout << "  " << endl;
	else if (a != "1" && a != "2")
	{
		cout << "�����������������"; cin >> a;
	}
}
void room::show()
{
	cout << "___________________________________________________|" << endl;
	cout << number << "    " << price << "    " << a << "       ";
	if (a == "2")
		cout << "δ�۳�" << endl;
	if (a == "1")
		cout << sell_time << endl;

}
void room::change()
{
	int chiose;
	cout << "������Ҫ�޸ĵ���Ϣ��1�����  2���۸�  3���ȼ�   4���������   5������ʱ��"; cin >> chiose;
	if (chiose == 1)
	{
		cout << "�������޸ĺ�ı��"; cin >> number; cout << "�޸ĳɹ�";
	}
	if (chiose == 2)
	{
		cout << "�������޸ĺ�ļ۸�"; cin >> price; cout << "�޸ĳɹ�";
	}
	if (chiose == 3)
	{
		cout << "�������޸ĺ�ĵȼ�"; cin >> grade; cout << "�޸ĳɹ�";
	}
	if (chiose == 4)
	{
		cout << "�������޸ĺ�ĳ������"; cin >> a;
		if (a == "δ����")
		{
			strcpy(sell_time, 0);
		}
	}
	if (chiose == 5)
	{
		cout << "�������޸ĺ�ĳ���ʱ��"; cin >> sell_time; cout << "�޸ĳɹ�";
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
		cout << "δ����" << endl;
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
		outfile << "δ�۳�" << endl;

	outfile.close();
}


void customer::input()
{
	cout << "������˿͵���Ϣ" << endl;
	cout << "������˿ͱ��"; cin >> num;
	cout << "������˿�����"; cin >> name;
	cout << "������˿��Ա�"; cin >> sex;
	cout << "������˿����֤��"; cin >> ID;
	cout << "������˿���ϵ��ʽ"; cin >> phone;
	cout << "������˿͵���סʱ��"; cin >> intime;
	cout << "������˿͵��뿪ʱ��"; cin >> outtime;
	cout << "��������ס�����"; cin >> room_number;
	for (i = 1; i <= n; i++)
	{
		while (strcmp(room_number, p[i].number) == 0)
		{
			cout << "�÷��䲻���ڣ�����������" << endl; cin >> room_number;
		}
	}

}
void customer::change()
{
	int chiose1;
	cout << "������Ҫ�޸ĵ�����(1:���  2:����  3:�Ա�   4�����֤��  5����ϵ��ʽ  6����סʱ��   7���뿪ʱ��  8�������)"; cin >> chiose1;
	if (chiose1 == 1)
	{
		cout << "�������µı��"; cin >> num; cout << "�޸ĳɹ�";
	}
	if (chiose1 == 2)
	{
		cout << "�������µ�����"; cin >> name; cout << "�޸ĳɹ�";
	}
	if (chiose1 == 3)
	{
		cout << "�������µ��Ա�"; cin >> sex; cout << "�޸ĳɹ�";
	}
	if (chiose1 == 4)
	{
		cout << "�������µ����֤��"; cin >> ID; cout << "�޸ĳɹ�";
	}
	if (chiose1 == 5)
	{
		cout << "�������µ���ϵ��ʽ"; cin >> phone; cout << "�޸ĳɹ�";
	}
	if (chiose1 == 6)
	{
		cout << "�������µ���סʱ��"; cin >> intime; cout << "�޸ĳɹ�";
	}
	if (chiose1 == 7)
	{
		cout << "�������µ��뿪ʱ��"; cin >> outtime; cout << "�޸ĳɹ�";
	}
	if (chiose1 == 8)
	{
		cout << "�������µķ����"; cin >> room_number; cout << "�޸ĳɹ�";
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
	cout << "|              ��ӭ�����Ƶ���Ϣ�������            |" << endl;
	cout << "____________________________________________________" << endl;

loop:
	cout << "��1:���ó�ʼ����          2����¼        3:�޸����룩" << endl; cin >> ab;
	if (ab == 1)
	{
		string username;
		cout << "�������˻�������ʼ����" << endl; 
cin >> username >> password;

ofstream outfile("users.txt", ios::app); //������ļ���׷��д��
if (outfile.is_open())
{
    outfile << username << " " << password << endl; //д�뵽�ļ���
    cout << "�˻�ע��ɹ�" << endl;
    outfile.close(); //�ر��ļ�
}
else
{
    cout << "�ļ���ʧ��" << endl;
}

system("pause");
system("cls");
goto loop;

	}
	if (ab == 3)
	{
		string account;
		cout << "�������˻���Ϣ" << endl;
cin >> account;
cout << "�������޸ĺ������" << endl; 
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

cout << "�����޸ĳɹ�" << endl;
system("pause");
system("cls");
goto loop;

	}
	if (ab == 2)
	{
		string username;
		cout << "�������˻�������¼����" << endl; 
cin >> username >> password1;
	
ifstream infile("users.txt"); //�������ļ�����ȡ����
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
    	cout << "�û������������ϵͳ��������" << endl;
        system("pause");
        system("cls");
	}
		else
		{     cout << "��¼�ɹ�" << endl;
		rerun:

			cout << "------------------------------------------------------" << endl;
			cout << " *                       �Ƶ���Ϣ����                  * " << endl;
			cout << " *                    1:�ͷ�������Ϣ����               *" << endl;
			cout << " *                    2:�ͷ�������Ϣ�Ĳ�ѯ             *" << endl;
			cout << " *                    3:�ͷ�������Ϣ���޸�             *" << endl;
			cout << " *                    4:�ͷ�������Ϣ��ɾ��             *" << endl;
			cout << " *                    5:�Ƶ귿������                 *" << endl;
			cout << " *                    6������ͷ���Ϣ                  *" << endl;
			cout << " *------------------------------------------------------" << endl;
			cout << " *                        �˿���Ϣ����                 *" << endl;
			cout << " *                    7���˿ͻ�����Ϣ������            *" << endl;
			cout << " *                    8���˿ͻ�����Ϣ�����            *" << endl;
			cout << " *                    9���˿ͻ�����Ϣ���޸�            *" << endl;
			cout << " *                   10: �˿���Ϣ��ɾ��                *" << endl;
			cout << " *                   11���˿���Ϣ���                  *" << endl;
			cout << " *                   12: ����˿���Ϣ                  *" << endl;
			cout << " *                   13��������Ԥ��                    *" << endl;
			cout << " -------------------------------------------------------" << endl;
			cout << " *                   14: �˳�ϵͳ                      *" << endl;
			cout << "��ѡ����"; cin >> w;
			switch (w)
			{
			case 1:
				cout << "------------------------------------" << endl;
				cout << "|        �ͷ�������Ϣ���빦��      | " << endl;
				cout << "------------------------------------" << endl;
				cout << "                                    " << endl;
				if (d == 0)
				{
					cout << "�״�¼��ͷ���Ϣ��������ͷ�����"; cin >> n;
					for (i = 1; i <= n; i++)
						p[i].input();
					d = 1;
					s1 = n;

				}
				else if (d == 1)
				{
					cout << "��ӿͷ���Ϣ��������ͷ�����"; cin >> m; n = n + m;
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
			cout << "|        �ͷ�������Ϣ�Ĳ�ѯ����      |" << endl;
			cout << "-------------------------------------" << endl;
			cout << "                                    " << endl;
			cout << "�������ѯ��ʽ��1�����пͷ���Ϣ  2�������ͷ���Ϣ"; cin >> yu;
			if (yu == 1)
			{
				cout << "___________________________________________________" << endl;
				cout << "����" << "  " << "�۸�" << "  ""�������" << "       " << "����ʱ��" << "|" << endl;
				for (i = 1; i <= n; i++)
				{
					p[i].show();
				}

			}
			else
			{
				cout << "������ͷ���ţ�ϵͳ��Ϊ����ѯ�ͷ���Ϣ" << endl; cin >> num1;
				cout << "�ͷ�������ϢԤ����" << endl;


				for (i = 1; i <= n; i++)
				{
					if (strcmp(num1, p[i].number) == 0)
					{
						cout << "___________________________________________________" << endl;
						cout << "����" << "  " << "�۸�" << "  ""�������" << "       " << "����ʱ��" << "|" << endl;
						p[i].show();
						flag3 = 1;
					}
				}
				if (flag3 == 0)
					cout << "�˿ͷ���Ϣ������" << endl;
			}

			system("pause");
			system("cls");
			goto rerun;
			break;
			}
			case 3:
				char num2[15];
				cout << "---------------------------------------" << endl;
				cout << "|       �ͷ�������Ϣ���޸Ĺ���         |" << endl;
				cout << "----------------------------------------" << endl;
				cout << "������Ҫ�޸Ŀͷ��ķ���"; cin >> num2;
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
				cout << " |            �ͷ���Ϣɾ������           |  " << endl;
				cout << "------------------------------------------" << endl;
				cout << "������Ҫɾ���ͷ��ı��"; cin >> number2;
				for (i = 1; i <= n; i++)
				{
					if (strcmp(number2, p[i].number) == 0)
					{
						p[i].delete1();
						cout << "ɾ���ɹ�" << endl;
					}
				}

				system("pause");
				system("cls");
				goto rerun;
				break;
			}
			case 5:
				cout << "------------------------------------------" << endl;
				cout << " |            �Ƶ귿�������              |" << endl;
				cout << "------------------------------------------" << endl;
				cout << "___________________________________________________" << endl;
				cout << "����" << "  " << "�۸�" << "  ""�������" << "       " << "����ʱ��" << "|" << endl;
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
				cout << " |            �Ƶ귿�������              |" << endl;
				cout << "------------------------------------------" << endl;

				cout << "�ͷ���Ϣ����ţ��۸񣬵ȼ����Ƿ���� ����ʱ��)" << endl;
				for (i = 1; i <= n; i++)
				{
					p[i].writeto();
					cout << "��Ϣ����ɹ�" << endl; cout << n;
				}

				system("pause");
				system("cls");
				goto rerun;
				break;

			case 7:
				cout << "-------------------------------------------" << endl;
				cout << "|         �˿ͻ�����Ϣ���빦��             |" << endl;
				cout << "-------------------------------------------" << endl;

				if (g == 0)
				{
					cout << "������Ҫ¼����Ϣ�Ĺ˿�����"; cin >> k;
					for (i = 1; i <= k; i++)
					{
						q[i].input();
						g = 1;
						s2 = k;
					}
				}

				else if (g == 1)
				{
					cout << "����˿�����"; cin >> l; k = k + l;
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
				cout << "           �˿ͻ�����Ϣ�Ĳ�ѯ����             |" << endl;
				cout << "----------------------------------------------" << endl;
				cout << "�������ѯ��ʽ��1�������˿͵Ļ�����Ϣ  2��ĳһ�������й˿͵Ļ�����Ϣ��" << endl; cin >> chiose2;
				if (chiose2 == 1)
				{
					cout << "��ѡ���ѯ��ʽ��1:�˿ͱ�ţ�2�����֤��  3������� "; cin >> chiose;
					if (chiose == 1)
					{
						cout << "������˿ͱ��"; cin >> num3;

						cout << "���,����,�Ա�,���֤��,��ϵ��ʽ,��סʱ��,�뿪ʱ��,��ס���� " << endl;
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
							cout << "���û�δ¼��" << endl;
						}

					}
					else
						if (chiose == 2)
						{
							cout << "������˿����֤��"; cin >> ID1;
							cout << "���    ����     �Ա�      ���֤��                         ��ϵ��ʽ                    ��סʱ��            �뿪ʱ��         ��ס���� " << endl;
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
								cout << "���û�δ¼��" << endl;
							}
						}
						else if (chiose == 3)
						{
							cout << "������˿͵ķ����"; cin >> room_number1;
							cout << "���    ����     �Ա�      ���֤��                         ��ϵ��ʽ                    ��סʱ��            �뿪ʱ��         ��ס���� " << endl;
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
								cout << "���û�δ¼��" << endl;
							}
						}
				}
				if (chiose2 == 2)
				{
					char d[30];
					cout << "--------------------------------------------" << endl;
					cout << "|               ĳ���������й˿���Ϣ       | " << endl;
					cout << "---------------------------------------------" << endl;
					cout << "����������"; cin >> d;
					cout << "���    ����     �Ա�      ���֤��                         ��ϵ��ʽ                    ��סʱ��            �뿪ʱ��         ��ס���� " << endl;
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
				cout << "|         �˿ͻ�����Ϣ�޸Ĺ���                 |" << endl;
				cout << "-----------------------------------------------" << endl;
				cout << "������ͻ���Ϣ��1������ 2�����֤�� 3������ţ�";
				if (chiose == 1)
				{
					cout << "����������"; cin >> name1;
					for (i = 1; i <= k; i++)
					{
						if (strcmp(name1, q[i].name) == 0)
						{
							q[i].change(); cout << "�޸ĳɹ�" << endl;
							break;
						}
					}


				}
				else
					if (chiose == 2)
					{
						cout << "������˿����֤��"; cin >> ID2;
						for (i = 1; i <= k; i++)
						{
							if (strcmp(ID2, q[i].ID) == 0)
							{
								q[i].change(); cout << "�޸ĳɹ�" << endl;
								break;

							}

						}
					}
					else
						if (chiose == 3)
						{
							cout << "������˿͵ķ����"; cin >> room_number2;
							for (i = 1; i <= k; i++)
							{
								if (strcmp(room_number2, q[i].room_number) == 0)
								{
									q[i].change(); cout << "�޸ĳɹ�" << endl;
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
				cout << " |            �˿���Ϣɾ������           |  " << endl;
				cout << "------------------------------------------" << endl;
				cout << "������Ҫɾ���˿͵�����"; cin >> name3;
				for (i = 1; i <= k; i++)
				{
					if (strcmp(name3, q[i].name) == 0)
					{
						q[i].delete1();
						cout << "ɾ���ɹ�" << endl;
					}
				}


				system("pause");
				system("cls");
				goto rerun;
				break;

			case 11:
				cout << "--------------------------------------------" << endl;
				cout << "|               �˿���Ϣ�������             |" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "���    ����     �Ա�      ���֤��                         ��ϵ��ʽ                    ��סʱ��            �뿪ʱ��         ��ס���� " << endl;
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

				cout << "�˿���Ϣ�����     ����    �Ա�     ���֤��     ��ϵ��ʽ      ��סʱ��     �뿪ʱ��   ��ס���� )" << endl;
				for (i = 1; i <= k; i++)
					q[i].writeto();
				cout << "�˿���Ϣ����ɹ�" << endl;
				system("pause");
				system("cls");
				goto rerun;
				break;
			case 13:
			{
				int gy, n = 0; char time[30];
				cout << "--------------------------------------------" << endl;
				cout << "|       ������ͳ��/Ԥ��                     |" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "1:������ͳ��              2��������Ԥ��" << endl; cin >> gy;
				if (gy == 1)
				{
					cout << "������Ҫͳ�Ƶ�ʱ���" << endl; cin >> time;
					for (i = 1; i < k; i++)
					{
						if (((strcmp(q[i].intime, time) < 0) || (strcmp(q[i].intime, time) == 0)) && ((strcmp(q[i].outtime, time) > 0) || (strcmp(q[i].outtime, time) == 0)))
							n++;
					}
					cout << "��ʱ�����ʵ����ס����Ϊ" << n;
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
						cout << "�����Ҳ����ļ�" << endl;
					}
					else
					{
						for (int m = 0; m < 20; m++)
						{
							infile >> i[m];//���ļ��ж���ǰ20������
							sum += i[m];
						}
						aver = sum / 20;//����ƽ��ֵ
					}
					infile.close();

					for (int j = 0; j < 20; j++)
					{
						z0 = z0 + (q[j] - q0) * (i[j] - aver);//б�ʵķ���
						m0 = m0 + (q[j] - q0) * (q[j] - q0);//б�ʵķ�ĸ
					}
					b = z0 / m0;
					a = aver - b * q0;//���ݹ�ʽ�������Իع�ϵ��
					cout << "\t\t\t\t\t\t\t\n\nǰ20������:" << endl;
					for (int m = 0; m < 20; m++)
						cout << i[m] << "\t";
					cout << "\t\t\t\t\t\t\t\t\n\n- - - - - Ԥ������Ϊ��";
					y = b * 21 + a; //����Ԥ��
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
				cout << "|               �˳�                        |" << endl;
				cout << "---------------------------------------------" << endl;
				cout << "�Ƿ�Ҫ�˳���1����  2��" << endl; cin >> gg;
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
    cout << "�ļ���ʧ��" << endl;
}
	}
	delete[]p;
	delete[]q;
}
