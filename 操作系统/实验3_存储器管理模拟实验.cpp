#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <windows.h>
#include <fstream>

using namespace std;
//以下是页面信息类的定义
class PageInformation
{
protected:
	int pid;			  //页号
	int count;		      //统计驻留在物理块中的次数（时间）,初始为0
public:
	PageInformation() { count = 0; }			  //默认构造函数，驻留在页面的时间初始化为0
	PageInformation(PageInformation& p)
	{
		p.pid = pid;
		p.count = count;
	}
	virtual ~PageInformation() {}
	void setpid(PageInformation* headptrblock, int pid)//修改物理块对象数组成员pid
	{
		headptrblock->pid = pid;
	}
	void setpidrand(PageInformation* headptr, int pid)//修改页面对象数组成员pid
	{
		headptr->pid = pid; cout << pid << " ";
	}
	void display()
	{
		cout << pid << " ";
		//cout<<pid;
	}
	void setpid()//选择从键盘输入时设置对象数组成员pid
	{
		int pidtemp;
		cout << "请输入您的页号（范围1-9）：";
		cin >> pidtemp;
		this->pid = pidtemp;
	}
	void counter()
	{
		count++;
	}
	void resetcount()
	{
		count = 0;
	}
	int getpid()
	{
		return pid;
	}
	int getcount()
	{
		return count;
	}
};//PageInformation

void Directloading(PageInformation*& headptr, PageInformation*& headptrblock, int pagenum)//直接将前三个页面装入物理块中
{
	int temp;
	for (int i = 0; i < pagenum; i++)//直接将符合物理块数大小的页面装入物理块中
	{
		(headptrblock + i)->setpid((headptrblock + i), (headptr + i)->getpid());
		temp = i + 1;
		for (int j = 0; j < temp; j++)
			(headptrblock + j)->counter();//对应物理块驻留时间++
	}
	cout << "原始页号为：" << "";
	for (int i = 0; i < pagenum; i++)
	{
		(headptrblock + i)->display();
	}
	cout << endl;
}//Directloading


void FIFO(PageInformation* headptr, PageInformation* headptrblock, int pagenum, int pagenumber, int& pagecounter)
{
	Directloading(headptr, headptrblock, pagenum);
	pagecounter = 0;//置0
	int status = 1;
	int temp = 0;
	for (int i = pagenum; i < pagenumber; i++)//如果有缺页现象发生，就将存入物理块时间最久的一个页面取出，装入新的页面
	{
		for (int j = 0; j < pagenum; j++)
		{
			(headptrblock + j)->counter();//对应物理块驻留时间++

		}
		for (int j = 0; j < pagenum; j++)//无缺页跳出循环进行下一页面判断，缺页寻找驻留时间最长的页面置换之
		{
			if ((headptrblock + j)->getpid() == (headptr + i)->getpid())
			{
				status = 0;
				pagecounter++;
			}
		}
		for (int j = 0; j < pagenum; j++)
		{
			if ((headptrblock + j)->getcount() > (headptrblock + temp)->getcount())
				temp = j;
		}
		if (status)
		{
			(headptrblock + temp)->setpid((headptrblock + temp), (headptr + i)->getpid());//将新页面装入物理块置换掉temp页面
			(headptrblock + temp)->resetcount();
		}
		cout << "第" << setw(2) << i + 1 << "页所持有的页号为：";
		for (int j = 0; j < pagenum; j++)
		{
			(headptrblock + j)->display();
		}
		if (status)
		{
			cout << "未命中！";
		}
		cout << endl;
		//将临时暂存变量更新
		temp = 0;
		status = 1;
	}
	int pagecounterrate = ((17 - pagecounter) * 100 / 20);
	cout << "使用FIFO算法的缺页数为：" << 17 - pagecounter << "\n缺页率为：" << "\%" << pagecounterrate << endl;
}//fifo

int pagenum = 3;				//页框数-物理块数
int pagenumber = 20;		    //页面数量
int pagecounter = 0;

//以下是主函数
int main(int argc, char** argv)
{
	time_t Time;
	time(&Time);
	int control;
	PageInformation* headptr = new PageInformation[pagenumber];    //生成页面序列
	PageInformation* headptrblock = new PageInformation[pagenum];  //生成页框
	if (argc == 1)//是否向main函数传入参数
	{
		cout << "随机生成的页地址流为：" << endl;
		srand((unsigned)time(&Time));//srand((unsigned) time (NULL));也可以传入空指针
		for (int i = 0; i < pagenumber; i++)
		{
				(headptr + i)->setpidrand((headptr + i), (int)rand() % 10);
		}
		cout << endl;

	}
	else//从文件中读入数据
	{
		cout << "(文件读入数据)" << endl;
		ifstream in(argv[1]);
		if (in.is_open())
		{
			cout << "文件打开成功！" << endl;
		}
		else
		{
			cout << "文件打开失败！";
			exit(0);
		}
		cout << "所读取的页面序列为：";
		int j = 0;
		for (int p; in >> p; )
		{
			(headptr + j)->setpidrand((headptr + j), p);//将文件数据读入
			j++;
		}
		in.close();
		cout << endl;
	}
	
		cout << "输入2使用FIFO替换算法进行替换：";
		cin >> control;
		system("cls");
		cout << "（FIFO先进先出置换算法）" << endl;
		FIFO(headptr, headptrblock, pagenum, pagenumber, pagecounter);
	delete[] headptr;
	return 0;
}

