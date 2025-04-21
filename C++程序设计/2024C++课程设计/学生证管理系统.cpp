#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <iomanip>  //ʹ��stew����
#include <algorithm>

using namespace std;

class Student {
public:
    int id;        // ѧ�� 
    string name;   // ���� 
    string sex;    // �Ա� 
    int classNum;  // �༶�� 
    string major;  // רҵ 

    // ���캯��
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
    
	void add();         //����¼��ѧ����Ϣ�ĺ�����
	void find();        //���尴ѧ�Ų�ѯ��Ϣ�����Ͱ��༶��ѯ��Ϣ������
	void modify();      //�����޸ĺ�����
	void del();         //����ɾ������;
	void statistics();  //����һ��ͳ�ƺ�����statistics ͳ�ƣ�
	void showAll();     //����һ����ʾ��������ʾ���м�¼�� 
};

void welcome();
void entrance();
void add_from_file();
void outfile();

Student stu;
vector<Student> vec;
int sum = 0;

/***************��ӭ************************/
void welcome()
{
	system("cls");
    cout<<"                                             �x�x�y�y�z�z�|�|�}�}�~�~�~�~�~�~�}�}�|�|�z�z�y�y�x�x"<<endl;
    cout << "<<<<<<------------------------------------------��ӭ����ѧ��֤����ϵͳ------------------------------------------>>>>>>>>" << endl;
    cout << " *******                                         1. ¼��ѧ��֤��Ϣ                                            ********" << endl;
    cout << " *******                                         2. ��ѯѧ����Ϣ��༶��Ϣ                                    ********" << endl;
    cout << " *******                                         3. �޸�ѧ��֤��Ϣ                                            ********" << endl;
    cout << " *******                                         4. ɾ��ѧ��֤��Ϣ                                            ********" << endl;
    cout << " *******                                         5. ��ѯ�༶����                                              ********" << endl;
    cout << " *******                                         6. �鿴���м�¼                                              ********" << endl;
	cout << " *******                                         7. �˳�                                                      ********" << endl;
    cout << "<<<<<<---------------------------------------------------------------------------------------------------------->>>>>>>>" << endl;
	cout << "���������ѡ��";
	entrance();
}

/***************����**************************/
void entrance()
{
	int a;
	cin >> a;
    system("cls");
	switch(a)
	{
		
		case 1:             //¼����Ϣ
			cout<<"\t\t\t��ӭ����¼����Ϣ����\n\n";
            stu.add();
			break;
		case 2:             //����ѧ�ţ���ʾĳѧ����Ϣ�͸�����ţ���ʾȫ��ѧ��
            cout<<"\t\t\t��ӭ�����ѯ����\n\n";
			stu.find();
			break;
		case 3:             //�����޸Ľ���
			cout<<"\t\t\t��ӭ�����޸ļ�¼����\n\n";
			stu.modify();
			break;
		case 4:             //����ɾ������
			cout<<"\t\t\t��ӭ����ɾ����¼����\n\n";
            stu.del();
            break;
		case 5:             //ͳ�ư༶���� 
			cout<<"\t\t\t��ӭ����ͳ�Ƽ�¼����\n\n";
			stu.statistics();
			break;
		case 6:
			stu.showAll();
			break;
		case 7:				//�˳�
			return ;
		default: 
			cout << "�������!" << endl;
			system("pause");
			welcome();
			break;
	}
}

/*************���ѧ����Ϣ********************/
void Student :: add()
{
	int figure;//����Ҫ������Ϣ��ѧ���ĸ���
	char h,m;

	cout<<"��Ҫ������ٸ�ѧ������Ϣ? " << endl;
	cin >> figure;
	cout<<"��ȷ��Ҫ����" << figure << "��ѧ������Ϣô��\n";
	fflush(stdin);
	cout<<"<��Y��ʼ N����>" << endl;
	cin >> h;
	if(h=='Y'||h=='y')
	{
		for(int j=0;j<figure;j++)
		{
			Student s;
			cout<<"�������" << j + 1 << "��ѧ������Ϣ��\n";
            cout<<"ѧ��:";
		    cin >> s.id;
			cout<<"����:";
        	cin >> s.name;
    		cout << "�Ա�:";
			cin >> s.sex; 
			cout<<"�༶:";
            cin >> s.classNum;
            cout << "רҵ:";
			cin >> s.major;
            
			sum++;
			vec.push_back(s);
		}
		
		sort(vec.begin(), vec.end()); // ��ѧ������ 
		outfile(); //�����ļ�
		
		cout<<"��ӳɹ�!\n";
		
		cout<<"�Ƿ����ڲ鿴���м�¼�� y/n" << endl;
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

/****************����ѧ�ţ���ʾĳλѧ��ѧ��֤��Ϣ********************/
/****************�����༶����ʾȫ��ѧ����Ϣ********************/
void Student :: find()
{
	int i, j;
	int sno;
	int classes;
	char t = ' ';
	
	cout<<"\t\t�����ԣ�\n";
	cout<<"\t\t1.��ѧ�Ų�ѯ!\n";
	cout<<"\t\t2.����Ų�ѯ!\n";
	
	int a;
	cin >> a;
    switch(a)
	{
		case 1:
			cout<<"������ѧ�ţ�";
			cin >> sno;
			
			for(i=0;i<sum;i++)
			{
				if(sno == vec[i].id)
				{
					cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
					cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
					cout << endl;
					break;
				}
			}
			
			if(i == sum)
			{
				cout<<"û���ҵ�!\n";
			}
			
			cout<<"�Ƿ������ѯ�� y/n\n";
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
			cout<<"������༶��";
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
				cout<<"û���ҵ�!\n";
			}
			else
			{
				cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
				for(i=0;i<sum;i++)
				{
					if(classes == vec[i].classNum)
					{
						cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
						cout<<"\n";
					}
				}
			}
			
			cout<<"�Ƿ������ѯ�� y/n\n";
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

/****************�޸���Ϣ****************/
void Student :: modify()
{
	int i;
	int numb;
	char h;
	
	cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
	for(i=0;i<sum;i++)
	{
		cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
		cout<<"\n";
	}
    printf("��������Ҫ�޸ĵ�ѧ����ѧ�ţ�");
    
	cin >> numb;
	for(i=0;i<sum;i++)
	{
		if(numb == vec[i].id)
		{
			cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
			cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
			cout << endl;
			break;
		}
	}
	
	if(i == sum)
	{
		cout<<"û���ҵ�!\n";
		cout<<"�Ƿ�����޸ģ� y/n\n";
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
		cout<<"�������ѧ��������Ϣ��\n";
		
		cout<<"ѧ��:";
		cin >> vec[i].id;
		cout<<"����:";
		cin >> vec[i].name;
		cout << "�Ա�:";
		cin >> vec[i].sex;
		cout<<"�༶:";
		cin >> vec[i].classNum;
		cout << "רҵ:";
		cin >> vec[i].major;
		
		sort(vec.begin(), vec.end()); // ��ѧ������ 
		outfile(); //�����ļ�
		
		cout<<"�޸ĳɹ�!\n";
		cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
		for(i=0;i<sum;i++)
		{
			if(vec[i].id != 0)
			{
				cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
				cout<<"\n";
			}
		}
		
		cout<<"�Ƿ�����޸ģ� y/n\n";
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

/****************ɾ����¼****************/
void Student :: del()
{
	int i;
	int numb;
	char h,k;
	
	cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
	for(i=0;i<sum;i++)
	{
		if(vec[i].id != 0)
		{
			cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
			cout<<"\n";
		}
	}
	
	cout<<"������Ҫɾ����ѧ�ţ�";
	fflush(stdin);
	cin >> numb;
	
	for(i=0;i<sum;i++)
	{
		if(numb == vec[i].id)
		{
			cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
			cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
			cout<<"\n";
			break;
		}
	}
	
	if(i == sum)
	{
		cout<<"û���ҵ�!\n";
		cout<<"�Ƿ����ɾ���� y/n\n";
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
		cout<<"�Ƿ�ȷ��ɾ���� y/n\n";
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
			
			cout<<"ɾ���ɹ�!\n";
			
			sort(vec.begin(), vec.end()); // ��ѧ������ 
			outfile(); //�����ļ� 
			
			cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
			for(i=0;i<sum;i++)
			{
				if(vec[i].id != 0)
				{
					cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
					cout<<"\n";
				}
			}
			
			cout<<"�Ƿ����ɾ���� y/n\n";
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

/****************ͳ��ĳ�����ѧ������****************/
void Student :: statistics()
{
	int count = 0;
	int s;
	cout << "������Ҫͳ�Ƶİ༶�ţ�";
	cin >> s;
	
	for (int i = 0; i < sum; i++)
	{
		if (s == vec[i].classNum) count++;
	}
	
	cout << s << "���ѧ�������ǣ�" << count << endl; 
	
	cout<<"�Ƿ����ͳ�ƣ� y/n\n";
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

/****************��ʾ���е�ѧ��֤��Ϣ****************/
void Student :: showAll()
{
	if (sum)
	{
		cout<<"ѧ��\t\t����\t�Ա�\t�༶\tרҵ\n";
		for(int i=0;i<sum;i++)
		{
			cout << vec[i].id << "\t" << vec[i].name << "\t" << vec[i].sex << "\t" << vec[i].classNum << "\t" << vec[i].major;
			cout<<"\n";
		}
		cout << endl;
	}
	cout << "����ѧ�������ǣ�" << sum << endl; 
	system("pause");
	welcome();
}

/****************���ļ������е�ѧ��֤��Ϣ���뵽vector����������****************/
void add_from_file()
{
	int id, classNum;
	string name, sex, major;
	vec.clear();
	
	ifstream in("ѧ��֤����ϵͳ.txt");
	if (!in.is_open())
	{
		cerr << "�޷����ļ�����������д������" << endl; 
		return ; 
	}
	
	string str;
	getline(in, str); //ֻ��ȡ��һ�����ݣ����֣��������в���
	
	while (in >> id >> name >> sex >> classNum >> major)
	{
//		in >> id >> name >> sex >> classNum >> major;
		Student s(id, name, sex, classNum, major);
		vec.push_back(s);
		sum++;
	}
	
	in.close();
	
	sort(vec.begin(), vec.end()); // ��ѧ������ 
}

/****************�����е�ѧ��֤��Ϣ����д�뵽txt�ļ���****************/
void outfile()
{
	ofstream out("ѧ��֤����ϵͳ.txt");
	if (!out.is_open())
	{
		cerr << "�޷����ļ�����������д���ļ�" << endl; 
		return ; 
	}
	
	out << "ѧ��" << setw(21) << "����" << setw(15) << "�Ա�" << setw(9) << "�༶��" << setw(5) << "רҵ" << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		out << vec[i].id << setw(10) << vec[i].name << setw(10) << vec[i].sex << setw(10) << vec[i].classNum << setw(10) << vec[i].major << endl;
	}
	
	out.close();
}

int main()
{
	system("COLOR f0");  //����Ϊ�׵׺��� 
	
	add_from_file();
	welcome();	//���뻶ӭ���棻
	
	return 0;
}
