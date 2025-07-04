#define _CRT_SECURE_NO_WARNINGS
#include "cstdio"
#include "string.h"
#include "stdlib.h"
#include "iostream"
#include "cstring"
#define MAXLEN 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

using namespace std;

typedef struct
{
	char op;
	int level;
}opt;

typedef struct          //定义操作符栈
{
	opt st[MAXLEN];
	int top;

}op_stack;


typedef struct          //定义值栈
{
	double D[MAXLEN];
	int top;
}D_stack;

//--------对栈操作的定义-------------
opt peek(op_stack* s)        //定义看栈顶函数
{
	opt error = { '$',-2 };
	if (s->top >= 0)
		return s->st[s->top];
	else
		return error;
}

int IsEmpty(op_stack* s)        //定义判断栈空的函数
{

	if (s->top < 0)
		return 0;
	else
		return s->st[s->top].op;
}

char push(op_stack* s, opt c)      //定义入栈函数
{
	s->top++;
	s->st[s->top] = c;
	return c.op;
}

opt pop(op_stack* s)        //定义出栈函数
{
	opt i;
	opt error = { '$',-2 };
	if (s->top >= 0)
	{
		i = s->st[s->top];
		s->st[s->top].op = '\0';
		s->top--;
		return i;
	}
	else
		return error;
}


void clear(op_stack* s)       //定义初始化栈
{
	s->top = -1;
}

//-----------------------------define the value stack-----------------------
double Dpeek(D_stack* s)        //定义看栈顶函数
{
	if (s->top >= 0)
		return s->D[s->top];
	else
		return 0;
}

int DIsEmpty(D_stack* s)        //定义判断栈空的函数
{

	if (s->top < 0)
		return 0;
	else
		return (int)(s->D[s->top]);
}

double Dpush(D_stack* s, double c)      //定义入栈函数
{
	s->top++;
	s->D[s->top] = c;
	return c;
}

double Dpop(D_stack* s)        //定义出栈函数
{
	double i;
	if (s->top >= 0)
	{
		i = s->D[s->top];
		s->D[s->top] = '\0';
		s->top--;
		return i;
	}
	else return 0;
}


void Dclear(D_stack* s)       //定义初始化栈
{
	s->top = -1;
}

//--------------------定义栈的操作完成---------
//--------------中缀变逆波兰式的函数--------------------
void change(char* str, char* expr, char* kkk)
{
	opt A = { '+',1 };
	opt R = { '-',1 };
	opt M = { '*',2 };
	opt D = { '/',2 };
	opt B = { '(',-1 };
	opt Mo = { '%',2 };

	op_stack os;
	clear(&os);
	while (*str != '#')
	{

		while (*str >= '0' && *str <= '9' || *str == '.')
		{
			*expr = *str;
			expr++;
			str++;
		}

		*expr++ = '&';




		switch (*str)
		{
		case '+':
			while (peek(&os).level >= A.level && IsEmpty(&os))
			{
				*expr++ = pop(&os).op;
			}
			push(&os, A);
			str++;
			break;
		case '-':
			while (peek(&os).level >= R.level && IsEmpty(&os))
			{
				*expr++ = pop(&os).op;

			}
			push(&os, R);
			str++;
			break;
		case '*':
			while (peek(&os).level >= M.level && IsEmpty(&os))
			{
				*expr++ = pop(&os).op;

			}
			push(&os, M);
			str++;
			break;
		case '/':
			while (peek(&os).level >= D.level && IsEmpty(&os))
			{
				*expr++ = pop(&os).op;

			}
			push(&os, D);
			str++;
			break;
		case '(':
			push(&os, B);
			str++;
			break;
		case ')':
			while (peek(&os).level != -1)
			{
				*expr++ = pop(&os).op;
			}
			pop(&os);
			str++;
			break;
		case '#':
			while (IsEmpty(&os))
			{
				*expr++ = pop(&os).op;
				*expr++ = '&';//must add this line
			}
			*expr--;
			*expr = '#';
			break;
		case '%':
			while (peek(&os).level >= Mo.level)
			{
				*expr++ = pop(&os).op;
			}
			push(&os, Mo);
			str++;
			break;
		}
	}
}

//------------------后缀求值函数-------------------------------
double calval(char* le)
{
	int i, leng;
	double result = 0;
	D_stack Data;
	double tmpData, tmp1;
	char tmp[MAXLEN] = { '\0' };
	int a = 0;
	Dclear(&Data);
	while (*le != '\0')
	{
		while (*le >= '0' && *le <= '9' || *le == '.')
		{
			tmp[a++] = *le++;
		}
		le++;
		tmp[a] = '\0';
		tmp1 = atof(tmp);
		if (tmp1 != 0.0) {
			Dpush(&Data, tmp1);
			leng = strlen(tmp);
			for (i = 0; i < leng; i++)   //重新初始化临时数组
				tmp[i] = '\0';
			a = 0;
		}
		switch (*le)
		{
		case '&':
			le++;
			break;
		case '#':
			le++;
			break;
		case '+':
			result = Dpop(&Data) + Dpop(&Data);
			Dpush(&Data, result);
			le++;
			break;
		case '-':
			result = Dpop(&Data) - Dpop(&Data);
			Dpush(&Data, result);
			le++;
			break;
		case '*':
			result = Dpop(&Data) * Dpop(&Data);
			Dpush(&Data, result);
			le++;
			break;
		case '/':
			result = Dpop(&Data) / Dpop(&Data);
			Dpush(&Data, result);
			le++;
			break;
		case '%':
			tmpData = Dpop(&Data);
			result = (double)((int)Dpop(&Data) % (int)tmpData);
			Dpush(&Data, result);
			le++;
			break;
		}
	}

	return result;

}
//----------------------主函数--------------------------

int main()
{
	char string[MAXLEN];
	char exp[MAXLEN] = { '\0' };
	//char exp[MAXLEN] = "1#2#*3#4#*#+";
	//--------数据定义结束----------
	char* kkk;
	kkk = exp;
	puts("输入表达式:");
	gets(string);
	printf("中缀表达式是:%s\n\n", string);
	change(string, exp, kkk);

	printf("逆波兰式是:%s\n", exp);

	printf("\n最后结果:%f\n", calval(exp));

	system("PAUSE");

	return 0;
}
