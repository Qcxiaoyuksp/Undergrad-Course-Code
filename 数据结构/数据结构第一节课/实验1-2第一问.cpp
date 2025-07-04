#include  <stdio.h>
#include  <stdlib.h>

struct clock
{
	int hour;
	int minute;
	int second;
};
typedef struct clock CLOCK;

void Update(struct clock *t)
{   
	static long m = 1;   

	t->hour = m / 3600;   
	t->minute = (m - 3600 * t->hour) / 60;   
	t->second = m % 60;   //Modulus operation
	m++;   
	if (t->hour == 24)   
	{      
		m = 1;  
		t->hour = 0; 
	}
}

void Display(struct clock *t)			/*'\r' 控制同一个位置*/
{
	printf("%2d:%2d:%2d\r", t->hour, t->minute, t->second); 
}

void Delay(void)                     
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
	struct clock *t = (CLOCK *)malloc(sizeof(struct clock));
	t->hour = t->minute = t->second = 0;		/*初始化hour,minute,second为0*/
	for (i=0; i<100000; i++)		/*表的时间由一个for循环控制*/
	{ 
		Update(t);      				/*update*/
		Display(t);     				/*display*/
		Delay();       				/*delay 1 second*/
	}    
	return 0;
}


