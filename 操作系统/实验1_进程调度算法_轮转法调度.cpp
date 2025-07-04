//RR时间片轮转与HPF优先级调度算法
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef struct{
	char pname;//进程名
	int arrive_t;//到达时间
	int service_t;//服务时间
	int finish_t;//完成时间
	int turnaround_t;//周转时间
	double w_turnaround_t;//带权周转时间
	char state;//进程状态: w：等待， m：就绪，r：运行
	int priority;//优先级
	int run_t;//运行时间
	int remaining_t;//剩余时间
}PCB;
PCB p[20];
int n=10;
char op;
void init()//初始化进程信息：进程名、到达时间、服务时间、状态
{
	p[0].pname = 'A';
	p[0].arrive_t = 0;
	p[0].service_t = 3;
	p[0].priority=2;

	p[1].pname = 'B';
	p[1].arrive_t = 2;
	p[1].service_t = 5;
	p[1].priority=1;

	p[2].pname = 'C';
	p[2].arrive_t = 2;
	p[2].service_t = 2;
	p[2].priority=4;

	p[3].pname = 'D';
	p[3].arrive_t = 4;
	p[3].service_t = 4;
	p[3].priority=3;

	p[4].pname = 'E';
	p[4].arrive_t = 4;
	p[4].service_t = 1;
	p[4].priority=10;

	p[5].pname = 'F';
	p[5].arrive_t = 4;
	p[5].service_t = 4;
	p[5].priority=8;

    p[6].pname = 'G';
	p[6].arrive_t = 6;
	p[6].service_t = 2;
	p[6].priority=9;

	p[7].pname = 'H';
	p[7].arrive_t = 6;
	p[7].service_t = 6;
	p[7].priority=6;

	p[8].pname = 'I';
	p[8].arrive_t = 6;
	p[8].service_t = 5;
	p[8].priority=7;

	p[9].pname = 'J';
	p[9].arrive_t = 6;
	p[9].service_t = 2;
	p[9].priority=5;


	for(int i=0;i<n;i++)
    {
        p[i].state='w';//初始状态都设为等待
        p[i].run_t=0;
        p[i].remaining_t=p[i].service_t;
    }
}
void original_HPF_P()//输出HPF的初始状态
{
	printf("进程的初始状态\n");
	printf("------------------------------------------------------------------\n");
	printf("进程名\t\t到达时间\t服务时间\t优先级(数越大优先级越高)\n");
	int i;
	for(i=0;i<n;i++)
	{
		printf("%c\t\t    %d\t\t    %d\t\t    %d\n",p[i].pname,p[i].arrive_t,p[i].service_t,p[i].priority);
	}
 }
 void original_RR_P()//输出时间片轮转调度算法各进程的初始状态
{
	printf("进程的初始状态\n");
	printf("------------------------------------------------------------------\n");
	printf("进程名\t\t到达时间\t服务时间\n");
	int i;
	for(i=0;i<n;i++)
	{
		printf("%c\t\t    %d\t\t    %d\n",p[i].pname,p[i].arrive_t,p[i].service_t);
	}
 }
//HPF非抢占式优先级调度算法
//比较后面的优先级
bool cmp1(PCB a,PCB b)//先按到达时间排序，再按优先级排序
{
     if(a.arrive_t==b.arrive_t)
     {
         return a.priority>b.priority;//数越大，优先级越高
     }
     else
     {
         return a.arrive_t<b.arrive_t;
     }
}
bool cmp2(PCB a,PCB b)//按优先级排序
{
    return a.priority>b.priority;
}

void HPF_work()
{
    sort(p,p+n,cmp1);//先按到达时间排序，再按优先级排序
    p[0].finish_t=p[0].arrive_t+p[0].service_t;//第一个进程的完成时间=到达时间+服务时间
    int cnt=1;//判断完成时间内到达的进程个数,设第一个进程已经到达
    for(int i=1;i<n;i++)//看每一个进程
    {
        if(cnt<n)
        {
             for(int j=i;j<n;j++)//看后面来的进程
            {
                if(p[j].arrive_t<=p[i-1].finish_t)//比较到达时间和上一个进程的完成时间
                {
                    cnt++;//如果已经达到就标记
                }
                else
                    break;
            }
            if(cnt>i)//需要排序时
                sort(p+i,p+cnt,cmp2);//按优先级排序
        }
        p[i].finish_t=max(p[i-1].finish_t,p[i].arrive_t)+p[i].service_t;//完成时间

    }
}

bool cmp3(PCB a,PCB b)//按到达时间排序
{
    return a.arrive_t<b.arrive_t;//按到达时间从小到达排序
}
//时间片轮转法,新来的进程应该放在就绪队列的末尾
void RR_work()
{
    int q=2;//设时间片=2
    //先按到达时间排序
    sort(p,p+n,cmp3);//把这些进程编号为0-9
    queue<int> ready_q;//就绪队列
    ready_q.push(0);//先把第一个来的放到就绪队列
    //如果到达了，就放在就绪队列中，弹出队首元素
    int temp;
    int now_time=p[0].arrive_t;//从第一个进程到达时间开始算
    int cnt=1;//第一个进程已经处理了，接下来从p[1]开始看。
    int i;
    printf("进程的执行顺序：\n");
    while(1)
    {
        if(!ready_q.empty())//如果不空，队列中有元素，就占用处理机，进入运行状态
        {
            temp=ready_q.front();//取队头元素
            printf("%c ",p[temp].pname);
            ready_q.pop();//弹出队首元素
            p[temp].run_t=p[temp].run_t+q;//运行时间
            now_time=now_time+q;
             //设有10个进程，下标是从0-9,按顺序排好序的，所以是按顺序到达的
            while(cnt<n&&p[cnt].arrive_t<=now_time)
            {
                ready_q.push(cnt);//放入队尾
                p[cnt].state='m';//进入就绪队列
                cnt++;//等待下一个进程的到达
            }
            if(p[temp].run_t<p[temp].service_t)//如果这个进程还没有运行完成，就放到队列尾部
            {

                p[temp].remaining_t=p[temp].service_t-p[temp].run_t;//剩余时间=需要的服务时间-已经运行的时间

                ready_q.push(temp);//当前的这个再次入队，放在队尾
                p[temp].state='m';//状态为就绪态
            }
            else
            {
                now_time=now_time-(p[temp].run_t-p[temp].service_t);
                p[temp].state='f';//已经执行完了
                p[temp].finish_t=now_time;
            }
        }
        for( i=0;i<n;i++)
        {
            if(p[i].state=='m'||p[i].state=='w')//如果还有进程是等待或者就绪态，就继续进行时间片轮转
                break;
        }
        if(i==n)//如果都执行完了
            break;
    }
    printf("\n");
}
bool cmp4(PCB a,PCB b)
{
    return a.pname<b.pname;//按进程名从小到达排序
}
void Print()
{
    int i;
    if(op=='h'||op=='H')
    {
        printf("进程执行顺序为：\n");
        for(i=0;i<n;i++)
        {
            printf("%c ",p[i].pname);
        }
        printf("\n");
    }
    sort(p,p+n,cmp4);
	printf("--------------------------------------------------------------------------------------------------\n");
	printf("进程名\t\t到达时间\t服务时间\t完成时间\t周转时间\t带权周转时间\n");
	int sum_t1=0;//代表总的周转时间
	double sum_t2=0;//代表总的带权周转时间
	for(i=0;i<n;i++)
	{
	    p[i].turnaround_t=p[i].finish_t-p[i].arrive_t;//周转时间=完成时间-到达时间
        p[i].w_turnaround_t=(double)p[i].turnaround_t/p[i].service_t;//带权周转时间=周转时间/服务时间
		sum_t1=sum_t1 + p[i].turnaround_t;
		sum_t2=sum_t2 + p[i].w_turnaround_t;
		printf("%c\t\t    %d\t\t    %d\t\t   %d\t\t   %d\t\t  %0.2f\n",p[i].pname,p[i].arrive_t,
		       p[i].service_t,p[i].finish_t,p[i].turnaround_t,p[i].w_turnaround_t);

	}
	printf("平均周转时间:%0.2f\n",(double)sum_t1/n);
	printf("平均带权周转时间:%0.2f\n",(double)sum_t2/n);

}

int main()
{
    printf("请输入要使用的调度算法(<h/H:HPF> <r/R:RR>):");
    scanf("%c",&op);
    getchar();
    init();

    if(op=='h'|| op=='H')
    {
        original_HPF_P();
        HPF_work();
        Print();
    }
    if(op=='r'||op=='R')
    {
        original_RR_P();
        RR_work();
        Print();
    }
    return 0;
}

