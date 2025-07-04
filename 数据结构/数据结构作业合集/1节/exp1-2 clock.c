#include  <stdio.h>
#include  <stdlib.h>

  
struct clock
{
	int hour;
	int minute;
	int second;
};
typedef struct clock CLOCK;/*全局变量*/



/*
 Function：update hour, minute, second
 Arguments:   void
 Return：void
*/
void Update(CLOCK *c)                  
{
	c->second++;
	if (c->second == 60) 	   /*如果秒second到60，分钟minute加1*/
	{
		c->second = 0;
		c->minute++;
	}  
	if (c->minute == 60)		/*如果分钟到60，小时hour加1*/
	{
		c->minute = 0;
		c->hour++;
	}
	if (c->hour == 24)			/*如果小时hour到24, 则hour从零开始*/
	{
		c->hour = 0;
	}
}

/*
 Function：显示小时、分、秒display hour, minute, second
 Arguments:  void
 Return：void
*/

void Display(CLOCK *c)			/*'\r' 控制同一个位置*/
{
	printf("%2d:%2d:%2d\r", c->hour, c->minute, c->second); 
}

/*
 Function：延迟 delay one second
 Arguments:  void
 Return：void
*/

void Delay(void)                     
{
	long	t;

	for (t=0; t<50000000; t++)
    {
                						/*空循环延迟用*/
    }
}

main()
{
	long i;
    CLOCK *q;
    q=(CLOCK*)malloc(sizeof(CLOCK));
	q->hour=0;
	q->minute=0;
	q->second=0;		/*初始化hour,minute,second为0*/
	for (i=0; i<100000; i++)		/*表的时间由一个for循环控制*/
	{ 
		Update(q);      				/*update*/
		Display(q);     				/*display*/
		Delay();       				/*delay 1 second*/
	}    
}



