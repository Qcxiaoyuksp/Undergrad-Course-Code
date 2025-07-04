#include  <stdio.h>
#include  <stdlib.h>

//int hour, minute, second;         /*全局变量*/

/*
struct clock              //结构体 
{
	int hour;
	int minute;
	int second;
};
typedef struct clock CLOCK;
*/

typedef struct clock              //结构体指针 
{
	int hour;
	int minute;
	int second;
}clock,*CLOCK;


/*
 Function：update hour, minute, second
 Arguments:   void
 Return：void
*/


/*void Update(void)                  
{
	second++;
	if (second == 60) 	   /*如果秒second到60，分钟minute加1*/
/*	{
		second = 0;
		minute++;
	}  
	if (minute == 60)		/*如果分钟到60，小时hour加1*/
/*	{
		minute = 0;
		hour++;
	}
	if (hour == 24)			/*如果小时hour到24, 则hour从零开始*/
/*	{
		hour = 0;
	}
}*/

void Update(struct clock *t)
{
	static long m=1;
	
	t->hour=m/3600;
	t->minute=(m-3600*t->hour)/60;
	t->second=m%60;
	m++;
	if(t->hour==24)
		m=1;
}

/*
 Function：显示小时、分、秒display hour, minute, second
 Arguments:  void
 Return：void
*/

void Display(struct clock *t)			/*'\r' 控制同一个位置*/
{
	printf("%2d:%2d:%2d\r", t->hour, t->minute, t->second); 
}

/*
 Function：延迟 delay one second
 Arguments:  void
 Return：void
*/

void Delay()                     
{
	long	t;

	for (t=0; t<50000000; t++)
    {
                						/*空循环延迟用*/
    }
}

int main()
{
	long i;
	clock t;

	t.hour = t.minute = t.second = 0;		/*初始化hour,minute,second为0*/
	for (i=0; i<100000; i++)		/*表的时间由一个for循环控制*/
	{ 
		Update(&t);      				/*update*/
		Display(&t);     				/*display*/
		Delay();       				/*delay 1 second*/
	}    
	return 0;
}



