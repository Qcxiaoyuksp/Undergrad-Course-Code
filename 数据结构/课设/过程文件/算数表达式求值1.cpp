#include<iostream>
#include<string>
#include<stack>
#include<map>
using namespace std;
//#include<math.h>
class infix2postfix
{
public:
	//默认构造函数
	infix2postfix(){}
	//构造函数，初始化中缀表达式
	infix2postfix(const string& infixExp):infix(infixExp){}
	//设置中缀表达式infix
	void setInfixExp(const string& infixExp){infix=infixExp;}
	//求取并返回后缀表达式
	string postfixExp();
private:
	string infix;//用于转换的中缀表达式
	string postfix;//后缀表达式
	stack<string> stk;//用于存储运算符的堆栈
	map<string,int> oper_prio,oper_prio_out;//用于存储运算符的优先级
	void set_priority();//设置运算符（'+'、'-'、'*'、'/'、'%'、'^'）的优先级
};
//设置运算符（'+'、'-'、'*'、'/'、'%'、'^'）的优先级
void infix2postfix::set_priority()
{
	oper_prio["#"]=1; 
	oper_prio["("]=2;
	oper_prio["+"]=3;
	oper_prio["-"]=3;
	oper_prio["*"]=4;
	oper_prio["/"]=4;
	oper_prio["%"]=4;
	oper_prio["^"]=5;
	oper_prio[")"]=6;
}
//求取并返回后缀表达式
string infix2postfix::postfixExp()
{
	postfix="";
	set_priority();
	stk.push("#");
	int i=0;
	string input,topstk;
	for(;i<infix.size();)
	{//取运算符栈的栈顶
		topstk=stk.top();
		//取出当前带输入的符号
		input=infix.substr(i,1);
		//若待输入的符号不是运算符，直接放入postfix
		if(!oper_prio[input])
			postfix+=input;
		//待输入的符号是个运算符
		//进一步判断它的优先级和运算符栈顶运算符的优先级
		else
		{
			//若待输入运算符的优先级比运算符栈顶运算符的优先级高
			//区分对待待输入运算符为“）”和其他情况
			if(oper_prio[input]>oper_prio[topstk])
			{//若待输入的运算符为“）”，pop出栈直至“（”，否则直接入栈
				if(input.compare(")")==0)
				{
					while(topstk.compare("(")!=0)
					{
						postfix +=topstk;
						stk.pop();
						topstk=stk.top();
					}//end while
					stk.pop();
				}
				else
					stk.push(input);
			}
			//待输入运算符的优先级比运算符栈顶运算符的优先级低
			//区分对待待输入运算符为“（”和其他情况
			else
			{
				//若待输入的运算符为“(”，pop出栈直遇到栈顶运算符的优先级高的情况
				//否则，直接入栈
				if(input.compare("(")!=0)
				{
					postfix+=topstk;
					stk.pop();
					//出栈后，继续与下一个栈顶运算符比较优先级
					continue;
				};//end if
				stk.push(input);
			}//end if
		}//end else
		//取infix的下一个元素输入
		++i;
	}//end for
	//将运算符栈中剩余的符号pop出栈，直至遇到保护标志“#”
	topstk=stk.top();
	while(topstk.compare("#")!=0)
	{
		postfix+=topstk;
		stk.pop();
		topstk=stk.top();
	}//end while
	return postfix;
}
/*postfixEval类的声明*/
class postfixEval
{
public:
       //默认构造函数
	postfixEval(){};
	//设置后缀表达式
	void setPostfixExp(const string& postfixExp){postfix=postfixExp;};
	//计算后缀表达式并返回其值
	int evaluate();
private:
	string postfix;//待求值的后缀表达式
	stack<int> stk;//存放操作数的堆栈
	void getOperands(int& left,int& right);
	//从堆栈中取得左右操作数
	int compute(int left,int right,char op) const;
	//计算表达式“left op right”的值
	bool isOperator(char ch) const;
	//判断是否为运算符
};
/*实现计算过程*/
int postfixEval::evaluate()
{
	int i,left,right,expValue;
	char ch;
	//扫描后缀表达式直至表达式结束
	for(i=0;i<postfix.length();i++)
	{
		//取得当前字符
		ch=postfix[i];
		//若为操作数，压入操作数堆栈
		if(isdigit(ch))
			stk.push(ch-'0');
		//若为运算符则取出其前两个操作数执行运算，并将结果压入操作数栈
		else if(isOperator(ch))
		{
			getOperands(left,right);
			stk.push(compute(left,right,ch));
		}//end if
	}//end for
	//操作数的栈顶即为最后的运算结果
	expValue=stk.top();stk.pop();
	return expValue;
}
//从堆栈中取得左右操作数
void postfixEval::getOperands(int& left,int& right)
{
	//取得右操作数
	right=stk.top();
	stk.pop();
	//取得左操作数
	left=stk.top();
	stk.pop();
}
//计算表达式“left op right”的值
int postfixEval::compute(int left,int right,char op) const
{
	int value;
	switch(op)
	{
	case'+': value=left+right;
		break;
	case'-': value=left-right;
		break;
	case'*': value=left*right;
		break;
	case'/':if(right==0)
				cout<<"postfixEval出现除0错误"<<endl;
		value=left/right;
		break;
	case'%': if(right==0)
				 cout<<"postfixEval出现除0错误"<<endl;
		value=left%right;
		break;
	case'^':if(left==0 && right==0)
				cout<<"postfixEval出现未定义的0^0现象"<<endl;
		value=1;
		while(right>0)
		{
			value*=left;
			right--;
		}
		break;
	}//end switch
	return value;
}
//判断是否为运算符
bool postfixEval::isOperator(char ch) const
{
	return ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='^';
}
int main()
{
	infix2postfix iexp;
	string infix,postfix;
	postfixEval pexp;
	cout<<"**本程序模拟一位数的中缀表达式转化为后缀表达式及其运算**"<<endl;
   cout<<"****  学号：2104230414    姓名：张清晨  ****"<<endl;
	cout<<"请输入一个一位数的中缀表达式（q to quit!）:"<<endl;
	cin>>infix;
	while(infix.compare("q")!=0)
	{
		cout<<"你输入的中缀表达式为："<<infix<<endl;
		iexp.setInfixExp(infix);
		//求出相应的后缀表达式并输出
		postfix=iexp.postfixExp();
		cout<<"其相应的后缀表达式为"<<postfix<<endl;
		//计算后缀表达式的值并输出
		pexp.setPostfixExp(postfix);
		cout<<"表达式的运算值="<<pexp.evaluate()<<endl<<endl;
		cout<<"请再输入一个一位数的中缀表达式（q to quit!）:"<<endl;
		cin>>infix;
	}
	
	return 0;
}

