#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include <cstring>
#define MAX 500 
using namespace std;

                     //�û��� 
class user{
	public:
		int id; 
		int type;
		double balance;
		string name;
		string idcard;
}u[MAX];

                      //�û�������
class user_type{
	public:
		string type;//�û����� 
		double discount;//�ۿ�  
		double money;
		user_type(){} 
		user_type(string type,double discount,double money){
			this->type=type;
			this->discount=discount;
			this->money=money; 
		}
}ut[4]; 

//��Ʊ�� 
class ticket{
	public:
		int id;
		int user_id;  
		int line_id;
		string train;
		string begin;
		string end; 
		double price; 
		int departure_time;  
		int date;  
}t[MAX]; 

int n1,n2,s;
void main_menu();

//������·��
class line{
	public:
		int id; 
		string name;
		int station_num;
		string station[MAX]; 
		int train_num;
		string train[MAX]; 
		int carrying_num; 
}l[MAX];


void read()                //��ȡ�ļ� 
{
	ifstream f("data.txt");
	f>>n1;
	for(int i=1;i<=n1;i++){
		f>>u[i].id>>u[i].type>>u[i].balance>>u[i].name>>u[i].idcard;
	}
	
	f>>n2;
	for(int i=1;i<=n2;i++){
		f>>t[i].id>>t[i].user_id>>t[i].line_id>>t[i].train>>t[i].begin>>t[i].end
		>>t[i].price>>t[i].departure_time>>t[i].date;
	}
	f.close();
}

void save()                 //�洢�ļ� 
 {
	ofstream f("data.txt");
	f<<n1<<endl;
	for(int i=1;i<=n1;i++){
		f<<u[i].id<<" "<<u[i].type<<" "<<u[i].balance<<" "<<u[i].name<<" "<<u[i].idcard<<endl;
	}
	
	f<<n2<<endl;
	for(int i=1;i<=n2;i++){
		f<<t[i].id<<" "<<t[i].user_id<<" "<<t[i].line_id<<" "<<t[i].train<<" "<<t[i].begin
		<<" "<<t[i].end<<" "<<t[i].price<<" "<<t[i].departure_time<<" "<<t[i].date<<endl;
	}
	f.close();
} 
//�û� 
 void init()
 {
	ut[1]= user_type("��ͨ�û�",1.0,0);
	ut[2]= user_type("�¿��û�",0.9,60);
	ut[3]= user_type("�꿨�û�",0.8,120);
	
	read(); 
}
int find_index_of_user(int id){
	for(int i=1;i<=n1;i++){
		if(id==u[i].id) return i;
	}
	return -1;
}
void disp_user()     //��ʾ�û���Ϣ 
{
	cout<<"�û���Ϣ��"<<endl;
	for(int i=1;i<=n1;i++){
	cout<<"�û���ţ�"<<u[i].id<<"  ������"<<u[i].name<<" ���֤�ţ�"<<u[i].idcard<<" �û����ͣ�"<<ut[u[i].type].type<<" ��"<<u[i].balance<<"Ԫ"<<endl;
	}
}
void user_menu()      //�û����� 
{
	int k,id,index,type;
	double money;
	while(1){
		system("cls");
		cout<<" \n\n\t\t*************************************�û�����ҵ��***************************************"<<endl;
		cout<<" \n\t\t*******    1���������û���Ĭ����ͨ��                 2���˿���ɾ���û���        ********"<<endl;
		cout<<" \t\t*******    3��һ��ͨҵ�����                         4������                    ********"<<endl;
		cout<<" \t\t*******    5������ѯ                               6���û���Ϣ                ********"<<endl;
		cout<<" \t\t*******    0��������һ����"<<endl; 
		cout<<" \n\n ����������ѡ��"; 
		cin>>k;
		switch(k){
			case 1:
				n1++;
				if(n1==1) u[n1].id=1;
				else u[n1].id=u[n1-1].id+1;//��֤�û����Ψһ 
				u[n1].type=1;
				u[n1].balance=0.0;
				cout<<"���������֤�ţ�"; cin>>u[n1].idcard;
				cout<<"�������û�������"; cin>>u[n1].name;
				cout<<"��ӳɹ���";
				break;
			case 2:
				disp_user();
				cout<<"������Ҫɾ���ı�ţ�"; cin>>id;
				index=find_index_of_user(id);
				if(index==-1){
					cout<<"�˱�Ų����ڣ�"<<endl;
					break;
				}
				for(int j=index;j<n1;j++){
					u[j].id=u[j+1].id;
					u[j].type=u[j+1].type;
					u[j].balance=u[j+1].balance;
					u[j].name=u[j+1].name;
					u[j].idcard=u[j+1].idcard;
				}
				n1--; 
				cout<<"ɾ���ɹ���";
				break;
			case 3:
				disp_user();
				cout<<"�������û���ţ�"; cin>>id;
				index=find_index_of_user(id);
				if(index==-1){
					cout<<"�˱�Ų����ڣ�"<<endl;
					break;
				}
				cout<<"��ѡ��Ҫ�������ͣ���1���¿�50  2���꿨100��"; cin>>type;
				if(u[index].balance<ut[type+1].money){
					cout<<"��������"<<endl;
					break;
				}else{
					u[index].balance-=ut[type+1].money;
					u[index].type=type+1;
					cout<<"��ϲ������Ϊ"<<ut[type+1].type<<endl;
				}
				break;
			case 4:
				disp_user();
				cout<<"�������û���ţ�"; cin>>id;
				index=find_index_of_user(id);
				if(index==-1){
					cout<<"�˱�Ų����ڣ�"<<endl;
					break;
				}
				cout<<"������Ҫ��ֵ�Ľ�"; cin>>money;
				u[index].balance+=money;
				cout<<"��ֵ�ɹ���"<<endl;
				break;
			
			case 5:{string n;
			cout<<"�������û�����"<<endl;
			cin>>n; 
			for(int i=1;i<=n1;i++){
				if(n==u[i].name)
		        cout<<"�û���ţ�"<<u[i].id<<"  ������"<<u[i].name<<" ���֤�ţ�"<<u[i].idcard<<" �û����ͣ�"<<ut[u[i].type].type<<" ��"<<u[i].balance<<"Ԫ"<<endl;
                         	}
				break;
		    	} 
			case 6:
				disp_user(); break;
			case 0:
				main_menu(); break;
			default:
				cout<<"����������������룡";
		}
		cout<<endl;
		save();
		system("pause");
	}
}

//��Ʊ 
string getTrain(int i,int k){
	int p=k%l[i].train_num;
	if(p==0) return l[i].train[l[i].train_num];
	else return l[i].train[p];
}
char* get_departure_time(int k){
	char time[]="06.00";
	int h,m; //Сʱ�ͷ���
	h=(k-1)/3+6;
	if(k%3==1) m=0;
	else if(k%3==2) m=20;
	else m=40;
	if(h<10){
		time[1]=h+'0';
	}else{
		time[0]='0'+h/10; time[1]=h%10+'0';
	}
	if(m!=0){
		time[3]=m/10+'0'; 
	}
	return time;
}
void disp_ticket(int i){
	char time[]="06.00";
	strcpy(time,get_departure_time(t[i].departure_time));
	cout<<"��ţ�"<<t[i].id<<" ���֤���룺"<<u[find_index_of_user(t[i].user_id)].idcard
	<<" ������"<<u[find_index_of_user(t[i].user_id)].name<<" ��·��"<<t[i].line_id<<"���� ���Σ�"<<t[i].train<<" �۸�"<<t[i].price<<" ����ʱ�䣺"
	<<time<<" ��Ʊ���ڣ�"<<t[i].date<<endl;
} 
void disp_departure_time(int i){
	for(int k=1;k<=52;k++){
		char time[]="06.00";
		strcpy(time,get_departure_time(k));
		cout<<k<<"��"<<time<<" "<<getTrain(i,k)<<endl;
	}
}
void ticket_menu()             //��Ʊ���� 
{
	int k,id,user_id,index=-1,line_id,begin,end,x,bdate,edate;
	while(1){
		system("cls");
		cout<<"\n\n\t\t*******************************��Ʊ����**************************************"<<endl;
		cout<<" \n\t\t******* 1���������Ʊ                  2����ѯĳһʱ��εĹ�Ʊ��Ϣ  ********"<<endl;
		cout<<" \t\t******* 3����Ʊ                        4��������һ����              ********"<<endl;
		cout<<" \n\n ����������ѡ��"; 
		cin>>k;
		switch(k){
			case 1:
				n2++;
				if(n2==1) t[n2].id=1;
				else t[n2].id=t[n2-1].id+1;
				cout<<endl;
				disp_user();
				cout<<"���������ı�ţ�"; cin>>user_id;
				index=find_index_of_user(user_id);
				if(index==-1){
					cout<<"�û���Ų�����"<<endl;
					n2--;
					break;
				}
				t[n2].user_id=user_id;
				cout<<"��ѡ��Ʊ���ڣ�"; cin>>t[n2].date;
				cout<<endl;
				cout<<"��ѡ��Ҫ��������·��"; cin>>line_id;
				t[n2].line_id=line_id;
				cout<<endl;
				for(int i=1;i<=l[line_id].station_num;i++) cout<<i<<"��"<<l[line_id].station[i]<<endl;
				cout<<"��ѡ����ʼվ������"; cin>>begin;
				cout<<"��ѡ�񵽴�վ������"; cin>>end;
				cout<<endl;
				t[n2].begin=l[line_id].station[begin];
				t[n2].end=l[line_id].station[end];
				t[n2].price=fabs(end-begin)*ut[u[index].type].discount;  
				if(t[n2].price>u[index].balance)
				{
					cout<<"��������Ѳ���"<<endl;
					n2--;
					break;
				}
				u[index].balance-=t[n2].price;
				disp_departure_time(line_id);
				cout<<"��ѡ�񷢳�ʱ���ţ�"; cin>>x;
				t[n2].departure_time=x;
				t[n2].train=getTrain(line_id,x);
				cout<<"��Ʊ�ɹ���";
				break;
			case 2:
				cout<<"�������ѯ����ַ���ڣ�"; cin>>bdate;
				cout<<"�������ѯ����ֹ���ڣ�"; cin>>edate;
				cout<<"��ѯ������£�"<<endl;
				for(int i=1;i<=n2;i++){
					if(t[i].date>=bdate&&t[i].date<=edate)
						disp_ticket(i);
				}
				break;
			case 3:
				for(int i=1;i<=n2;i++) disp_ticket(i);
				cout<<"���������˻��ĳ�Ʊ��ţ�"; cin>>id;
				for(int i=1;i<=n2;i++){
					if(t[i].id==id){
						index=i; break;
					}
				}
				if(index==-1){
					cout<<"��Ų�����"<<endl;
					break;
				}
				u[find_index_of_user(t[index].user_id)].balance+=t[index].price;
				 for(int j=index;j<n2;j++){
					t[j].id=t[j+1].id; 
					t[j].user_id=t[j+1].user_id; 
					t[j].line_id=t[j+1].line_id; 
					t[j].train=t[j+1].train; 
					t[j].begin=t[j+1].begin; 
					t[j].end=t[j+1].end; 
					t[j].price=t[j+1].price; 
					t[j].departure_time=t[j+1].departure_time; 
					t[j].date=t[j+1].date; 
				}
				n2--; 
				cout<<"��Ʊ�ɹ�������ѷ��������˻�";
				break;
			case 4:
				main_menu(); break;
			default:
				cout<<"����������������룡";
		}
		cout<<endl;
		save();
		system("pause");
	}
}

//������· 
void disp_line(int i){
	char time[]="06.00";
	strcpy(time,get_departure_time(t[i].departure_time));
	cout<<" ��·��"<<t[i].line_id<<"���� ���Σ�"<<t[i].train<<" ����ʱ�䣺"<<time<<" ��Ʊ���ڣ�"<<t[i].date<<endl;
} 
void line_menu(){
	int k,index,index2;
	string train;
	bool flag=false;
	while(1){
		system("cls");
		cout<<" \n\n\t\t*******************************������·����*****************************************"<<endl;
		cout<<" \n\t\t******* 1��·����ӳ���                        2��·��ɾ������              ********"<<endl;
		cout<<" \t\t******* 3����ʾ·�����г���                    4��������һ����              ********"<<endl;
		cout<<" \n\n ����������ѡ��"; 
		cin>>k;
		switch(k){
			case 1:
				//for(int i=1;i<=n2;i++) cout<<l[i].id<<"��"<<l[i].name<<endl;
				cout<<"��ѡ����·��"; cin>>index;
				cout<<"��������ӵĳ��α�ţ�"; cin>>train;
				
				flag=false;
				for(int i=1;i<=l[index].train_num;i++){
					if(l[index].train[i]==train){
						cout<<"����·�Ѵ��ڣ�"<<endl;
						flag=true;
						break;
					}
				}
				if(flag) break;
				l[index].train_num++;
				l[index].train[l[index].train_num]=train;
				cout<<"��ӳ��γɹ���"<<endl;
				break;
			case 2:
				for(int i=1;i<=n2;i++) cout<<l[i].id<<"��"<<l[i].name<<endl;
				cout<<"��ѡ����·��"; cin>>index;
				for(int i=1;i<=l[index].train_num;i++) cout<<i<<"��"<<l[index].train[i]<<endl;
				cout<<"������ɾ���ĳ��α�ţ�"; cin>>index2;
				if(index2<1||index2>l[index].train_num){
					cout<<"���복�α������"<<endl;
					break;
				}
				for(int j=index2;j<l[index].train_num;j++){
					l[index].train[j]=l[index].train[j+1];
				} 
				l[index].train_num--;
				cout<<"ɾ�����γɹ���"<<endl;
				break;
			case 3:
				for(int i=1;i<=n2;i++){
					disp_line(i); 
					cout<<endl;
				}
				break;
			case 4:
				main_menu(); break;
			default:
				cout<<"����������������룡";
		}
		cout<<endl;
		save();
		system("pause");
	}
}

//ͳ�� 
void statistics_menu(){
	int k,sum_user,sum_money,num_user[24],max_user,min_user,max_index,min_index;
	while(1){
		system("cls");
		cout<<" \n\n\t\t*******************************ͳ����Ԥ�����*****************************************"<<endl;
		cout<<" \n\t\t*******    1�����¿�����ͳ��                        2��������ͳ��             ********"<<endl;
		cout<<" \t\t*******    3�� �߷���Ԥ��                           4��������һ����           ********"<<endl;
		cout<<" \n\n ����������ѡ��"; 
		cin>>k;
		switch(k){
			case 1:
				sum_user=0;
				cout<<endl<<"\t\t\t\t�˿�����ͳ��:"<<endl; 
				for(int i=1;i<=30;i++){
					int sum=0;
					cout<<i<<"\t\t\t�� ";
					for(int j=1;j<=n2;j++){
						if(t[j].date==i){
							sum++; cout<<"+";
						} 
					}
					cout<<" "<<sum<<endl;
					sum_user+=sum;
				} 
				cout<<"��������"<<sum_user;
				break;
			case 2:
				sum_money=0;
				cout<<endl<<"��������ͳ��:"<<endl; 
				for(int i=1;i<=30;i++){//����1-30�� 
					int sum=0;
					cout<<i<<"�� ";
					for(int j=1;j<=n2;j++){
						if(t[j].date==i){
							sum+=t[j].price;
						} 
					}
					cout<<" "<<sum<<endl;
					sum_money+=sum;
				} 
				cout<<"�����룺"<<sum_money;
				break;
			case 3:                                             //Ԥ�⺯�� 
				cout<<endl<<"�߷���Ԥ������"<<endl; 
				for(int i=6;i<=22;i++) 
				num_user[i]=0;
				for(int i=1;i<=n2;i++){
					if(t[i].date>=1&&t[i].date<=10){
						int hour=(t[i].departure_time-1)/3+6; 
						num_user[hour]++;
					}
				}
				num_user[22]+=num_user[23]; 
				max_user=num_user[6]; 
				min_user=num_user[6]; 
				max_index=6;
				for(int i=6;i<=22;i++)
				{
					cout<<i<<"�� ";
					for(int j=0;j<num_user[i];j++)
					 cout<<"******";
					cout<<" "<<num_user[i]*1.0/10<<endl;
					if(num_user[i]>max_user)
					{
						max_user=num_user[i];
						 max_index=i;
					}
				}
				cout<<"\t\t\t\t�߷�ʱ��Ϊ"<<max_index<<"������";
				break;
			case 4:
				main_menu(); break;
			default:
				cout<<"����������������룡";
		}
		cout<<endl;
		system("pause");
	}
}
void main_menu(){
	int k;
	system("color F0"); 
	while(1){
		system("cls");
	    cout<<" \n\n\t<<<<<<<<<<<<<<<<<<<<<<<<<��ɳ�е�����Ʊ�����������Ԥ��ϵͳ�����·�)>>>>>>>>>>>>>>>>>>>>>>"<<endl;
		cout<<"  \n          ��ѡ����Ҫ�����ҵ��"<<endl;
		cout<<"\n\t***********                         1���û�����ҵ��                              **********"<<endl;
		cout<<"\t***********                         2���������Ʊҵ��                            **********"<<endl;
		cout<<"\t***********                         3��������·����                              **********"<<endl;
		cout<<"\t***********                         4��ͳ�Ƽ�Ԥ��ҵ��                            **********"<<endl;
		cout<<"\t***********                         5���˳�                                      **********"<<endl;
		 cin>>k; 
		switch(k){
			case 1:
				user_menu(); break;
			case 2:
				ticket_menu(); break;
			case 3:
				line_menu(); break;
			case 4:
				statistics_menu(); break;
			case 5: 
				exit(1);
				cout<<"ллʹ�ã�ף����;��죡"<<endl;
			default:
				cout<<"�������";
				
		}
		system("pause");
	}
}

int main()        //������ 
{
	init();
	main_menu();
	return 0;
}
