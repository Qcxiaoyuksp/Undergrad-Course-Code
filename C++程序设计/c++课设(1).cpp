#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include <cstring>
#define MAX 500 
using namespace std;

                     //用户类 
class user{
	public:
		int id; 
		int type;
		double balance;
		string name;
		string idcard;
}u[MAX];

                      //用户类型类
class user_type{
	public:
		string type;//用户类型 
		double discount;//折扣  
		double money;
		user_type(){} 
		user_type(string type,double discount,double money){
			this->type=type;
			this->discount=discount;
			this->money=money; 
		}
}ut[4]; 

//购票类 
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

//地铁线路类
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


void read()                //读取文件 
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

void save()                 //存储文件 
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
//用户 
 void init()
 {
	ut[1]= user_type("普通用户",1.0,0);
	ut[2]= user_type("月卡用户",0.9,60);
	ut[3]= user_type("年卡用户",0.8,120);
	
	read(); 
}
int find_index_of_user(int id){
	for(int i=1;i<=n1;i++){
		if(id==u[i].id) return i;
	}
	return -1;
}
void disp_user()     //显示用户信息 
{
	cout<<"用户信息："<<endl;
	for(int i=1;i<=n1;i++){
	cout<<"用户编号："<<u[i].id<<"  姓名："<<u[i].name<<" 身份证号："<<u[i].idcard<<" 用户类型："<<ut[u[i].type].type<<" 余额："<<u[i].balance<<"元"<<endl;
	}
}
void user_menu()      //用户管理 
{
	int k,id,index,type;
	double money;
	while(1){
		system("cls");
		cout<<" \n\n\t\t*************************************用户管理业务***************************************"<<endl;
		cout<<" \n\t\t*******    1、创建新用户（默认普通）                 2、退卡（删除用户）        ********"<<endl;
		cout<<" \t\t*******    3、一卡通业务办理                         4、续费                    ********"<<endl;
		cout<<" \t\t*******    5、余额查询                               6、用户信息                ********"<<endl;
		cout<<" \t\t*******    0、返回上一界面"<<endl; 
		cout<<" \n\n 请输入您的选择："; 
		cin>>k;
		switch(k){
			case 1:
				n1++;
				if(n1==1) u[n1].id=1;
				else u[n1].id=u[n1-1].id+1;//保证用户编号唯一 
				u[n1].type=1;
				u[n1].balance=0.0;
				cout<<"请输入身份证号："; cin>>u[n1].idcard;
				cout<<"请输入用户姓名："; cin>>u[n1].name;
				cout<<"添加成功！";
				break;
			case 2:
				disp_user();
				cout<<"请输入要删除的编号："; cin>>id;
				index=find_index_of_user(id);
				if(index==-1){
					cout<<"此编号不存在！"<<endl;
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
				cout<<"删除成功！";
				break;
			case 3:
				disp_user();
				cout<<"请输入用户编号："; cin>>id;
				index=find_index_of_user(id);
				if(index==-1){
					cout<<"此编号不存在！"<<endl;
					break;
				}
				cout<<"请选择要卡的类型：（1、月卡50  2、年卡100）"; cin>>type;
				if(u[index].balance<ut[type+1].money){
					cout<<"您的余额不足"<<endl;
					break;
				}else{
					u[index].balance-=ut[type+1].money;
					u[index].type=type+1;
					cout<<"恭喜您升级为"<<ut[type+1].type<<endl;
				}
				break;
			case 4:
				disp_user();
				cout<<"请输入用户编号："; cin>>id;
				index=find_index_of_user(id);
				if(index==-1){
					cout<<"此编号不存在！"<<endl;
					break;
				}
				cout<<"请输入要充值的金额："; cin>>money;
				u[index].balance+=money;
				cout<<"充值成功！"<<endl;
				break;
			
			case 5:{string n;
			cout<<"请输入用户姓名"<<endl;
			cin>>n; 
			for(int i=1;i<=n1;i++){
				if(n==u[i].name)
		        cout<<"用户编号："<<u[i].id<<"  姓名："<<u[i].name<<" 身份证号："<<u[i].idcard<<" 用户类型："<<ut[u[i].type].type<<" 余额："<<u[i].balance<<"元"<<endl;
                         	}
				break;
		    	} 
			case 6:
				disp_user(); break;
			case 0:
				main_menu(); break;
			default:
				cout<<"输入错误，请重新输入！";
		}
		cout<<endl;
		save();
		system("pause");
	}
}

//车票 
string getTrain(int i,int k){
	int p=k%l[i].train_num;
	if(p==0) return l[i].train[l[i].train_num];
	else return l[i].train[p];
}
char* get_departure_time(int k){
	char time[]="06.00";
	int h,m; //小时和分钟
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
	cout<<"编号："<<t[i].id<<" 身份证号码："<<u[find_index_of_user(t[i].user_id)].idcard
	<<" 姓名："<<u[find_index_of_user(t[i].user_id)].name<<" 线路："<<t[i].line_id<<"号线 车次："<<t[i].train<<" 价格："<<t[i].price<<" 发车时间："
	<<time<<" 购票日期："<<t[i].date<<endl;
} 
void disp_departure_time(int i){
	for(int k=1;k<=52;k++){
		char time[]="06.00";
		strcpy(time,get_departure_time(k));
		cout<<k<<"、"<<time<<" "<<getTrain(i,k)<<endl;
	}
}
void ticket_menu()             //购票管理 
{
	int k,id,user_id,index=-1,line_id,begin,end,x,bdate,edate;
	while(1){
		system("cls");
		cout<<"\n\n\t\t*******************************购票管理**************************************"<<endl;
		cout<<" \n\t\t******* 1、购买地铁票                  2、查询某一时间段的购票信息  ********"<<endl;
		cout<<" \t\t******* 3、退票                        4、返回上一界面              ********"<<endl;
		cout<<" \n\n 请输入您的选择："; 
		cin>>k;
		switch(k){
			case 1:
				n2++;
				if(n2==1) t[n2].id=1;
				else t[n2].id=t[n2-1].id+1;
				cout<<endl;
				disp_user();
				cout<<"请输入您的编号："; cin>>user_id;
				index=find_index_of_user(user_id);
				if(index==-1){
					cout<<"用户编号不存在"<<endl;
					n2--;
					break;
				}
				t[n2].user_id=user_id;
				cout<<"请选择购票日期："; cin>>t[n2].date;
				cout<<endl;
				cout<<"请选择要乘坐的线路："; cin>>line_id;
				t[n2].line_id=line_id;
				cout<<endl;
				for(int i=1;i<=l[line_id].station_num;i++) cout<<i<<"、"<<l[line_id].station[i]<<endl;
				cout<<"请选择起始站点数："; cin>>begin;
				cout<<"请选择到达站点数："; cin>>end;
				cout<<endl;
				t[n2].begin=l[line_id].station[begin];
				t[n2].end=l[line_id].station[end];
				t[n2].price=fabs(end-begin)*ut[u[index].type].discount;  
				if(t[n2].price>u[index].balance)
				{
					cout<<"您的余额已不足"<<endl;
					n2--;
					break;
				}
				u[index].balance-=t[n2].price;
				disp_departure_time(line_id);
				cout<<"请选择发车时间编号："; cin>>x;
				t[n2].departure_time=x;
				t[n2].train=getTrain(line_id,x);
				cout<<"购票成功！";
				break;
			case 2:
				cout<<"请输入查询的起址日期："; cin>>bdate;
				cout<<"请输入查询的终止日期："; cin>>edate;
				cout<<"查询结果如下："<<endl;
				for(int i=1;i<=n2;i++){
					if(t[i].date>=bdate&&t[i].date<=edate)
						disp_ticket(i);
				}
				break;
			case 3:
				for(int i=1;i<=n2;i++) disp_ticket(i);
				cout<<"请输入需退还的车票编号："; cin>>id;
				for(int i=1;i<=n2;i++){
					if(t[i].id==id){
						index=i; break;
					}
				}
				if(index==-1){
					cout<<"编号不存在"<<endl;
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
				cout<<"退票成功，金额已返还您的账户";
				break;
			case 4:
				main_menu(); break;
			default:
				cout<<"输入错误，请重新输入！";
		}
		cout<<endl;
		save();
		system("pause");
	}
}

//地铁线路 
void disp_line(int i){
	char time[]="06.00";
	strcpy(time,get_departure_time(t[i].departure_time));
	cout<<" 线路："<<t[i].line_id<<"号线 车次："<<t[i].train<<" 发车时间："<<time<<" 购票日期："<<t[i].date<<endl;
} 
void line_menu(){
	int k,index,index2;
	string train;
	bool flag=false;
	while(1){
		system("cls");
		cout<<" \n\n\t\t*******************************地铁线路管理*****************************************"<<endl;
		cout<<" \n\t\t******* 1、路线添加车次                        2、路线删除车次              ********"<<endl;
		cout<<" \t\t******* 3、显示路线运行车次                    4、返回上一界面              ********"<<endl;
		cout<<" \n\n 请输入您的选择："; 
		cin>>k;
		switch(k){
			case 1:
				//for(int i=1;i<=n2;i++) cout<<l[i].id<<"、"<<l[i].name<<endl;
				cout<<"请选择线路："; cin>>index;
				cout<<"请输入添加的车次编号："; cin>>train;
				
				flag=false;
				for(int i=1;i<=l[index].train_num;i++){
					if(l[index].train[i]==train){
						cout<<"此线路已存在！"<<endl;
						flag=true;
						break;
					}
				}
				if(flag) break;
				l[index].train_num++;
				l[index].train[l[index].train_num]=train;
				cout<<"添加车次成功！"<<endl;
				break;
			case 2:
				for(int i=1;i<=n2;i++) cout<<l[i].id<<"、"<<l[i].name<<endl;
				cout<<"请选择线路："; cin>>index;
				for(int i=1;i<=l[index].train_num;i++) cout<<i<<"、"<<l[index].train[i]<<endl;
				cout<<"请输入删除的车次编号："; cin>>index2;
				if(index2<1||index2>l[index].train_num){
					cout<<"输入车次编号有误！"<<endl;
					break;
				}
				for(int j=index2;j<l[index].train_num;j++){
					l[index].train[j]=l[index].train[j+1];
				} 
				l[index].train_num--;
				cout<<"删除车次成功！"<<endl;
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
				cout<<"输入错误，请重新输入！";
		}
		cout<<endl;
		save();
		system("pause");
	}
}

//统计 
void statistics_menu(){
	int k,sum_user,sum_money,num_user[24],max_user,min_user,max_index,min_index;
	while(1){
		system("cls");
		cout<<" \n\n\t\t*******************************统计与预测管理*****************************************"<<endl;
		cout<<" \n\t\t*******    1、本月客流量统计                        2、月收入统计             ********"<<endl;
		cout<<" \t\t*******    3、 高峰期预测                           4、返回上一界面           ********"<<endl;
		cout<<" \n\n 请输入您的选择："; 
		cin>>k;
		switch(k){
			case 1:
				sum_user=0;
				cout<<endl<<"\t\t\t\t乘客数量统计:"<<endl; 
				for(int i=1;i<=30;i++){
					int sum=0;
					cout<<i<<"\t\t\t号 ";
					for(int j=1;j<=n2;j++){
						if(t[j].date==i){
							sum++; cout<<"+";
						} 
					}
					cout<<" "<<sum<<endl;
					sum_user+=sum;
				} 
				cout<<"总人数："<<sum_user;
				break;
			case 2:
				sum_money=0;
				cout<<endl<<"运行收入统计:"<<endl; 
				for(int i=1;i<=30;i++){//遍历1-30号 
					int sum=0;
					cout<<i<<"号 ";
					for(int j=1;j<=n2;j++){
						if(t[j].date==i){
							sum+=t[j].price;
						} 
					}
					cout<<" "<<sum<<endl;
					sum_money+=sum;
				} 
				cout<<"总收入："<<sum_money;
				break;
			case 3:                                             //预测函数 
				cout<<endl<<"高峰期预测结果："<<endl; 
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
					cout<<i<<"点 ";
					for(int j=0;j<num_user[i];j++)
					 cout<<"******";
					cout<<" "<<num_user[i]*1.0/10<<endl;
					if(num_user[i]>max_user)
					{
						max_user=num_user[i];
						 max_index=i;
					}
				}
				cout<<"\t\t\t\t高峰时间为"<<max_index<<"点左右";
				break;
			case 4:
				main_menu(); break;
			default:
				cout<<"输入错误，请重新输入！";
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
	    cout<<" \n\n\t<<<<<<<<<<<<<<<<<<<<<<<<<长沙市地铁售票管理与客流量预测系统（六月份)>>>>>>>>>>>>>>>>>>>>>>"<<endl;
		cout<<"  \n          请选择需要办理的业务："<<endl;
		cout<<"\n\t***********                         1、用户管理业务                              **********"<<endl;
		cout<<"\t***********                         2、购买地铁票业务                            **********"<<endl;
		cout<<"\t***********                         3、地铁线路管理                              **********"<<endl;
		cout<<"\t***********                         4、统计及预测业务                            **********"<<endl;
		cout<<"\t***********                         5、退出                                      **********"<<endl;
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
				cout<<"谢谢使用，祝您旅途愉快！"<<endl;
			default:
				cout<<"输入错误";
				
		}
		system("pause");
	}
}

int main()        //主函数 
{
	init();
	main_menu();
	return 0;
}
