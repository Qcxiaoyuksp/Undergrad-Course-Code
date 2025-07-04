#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>

struct code_val {
	char code;
	char val[20];
};
const char* p[] = { //产生式
"S→E","E→E+T","E→T","T→T*F","T→F","F→(E)","F→i"
};
const char TNT[] = "+*()i#ETF"; //LR分析表列的字符
const int M[][9] = { // LR分析表数字化，列字符 + *()i#ETF用数字012345678标识。
{ 0, 0, 4, 0, 5,0, 1, 2, 3}, //0表示出错，s4用4表示。
{ 6, 0, 0, 0, 0,99}, //Acc用99表示
{-2, 7, 0,-2, 0,-2}, //r2用-2表示
{-4,-4, 0,-4, 0,-4},
{ 0, 0, 4, 0, 5, 0, 8, 2, 3},
{-6,-6, 0,-6, 0,-6},
{ 0, 0, 4, 0, 5, 0, 0, 9, 3},
{ 0, 0, 4, 0, 5, 0, 0, 0,10},
{ 6, 0, 0,11},
{-1, 7, 0,-1, 0,-1},
{-3,-3, 0,-3, 0,-3},
{-5,-5, 0,-5, 0,-5}
};
int col(char); //列定位函数原型
using namespace std;
int main()
{
	int state[50] = { 0 }; //状态栈初值
	char symbol[50] = { '#' }; //符号栈初值
	int top = 0; //栈顶指针初值
	ofstream cout("result.txt"); //语法分析结果输出至文件result.txt
	ifstream cin("test.txt"); // 从test.txt中输入词法分析结果
	struct code_val t; //结构变量，存放单词二元式。
	//t.val = "i+i*i#";
	cin >> t.code >> t.val; //读一单词
	int action;
	int i, j = 0; //输出时使用的计数器，并非必要。
	cout << "step" << '\t' << "状态栈" << '\t' << "符号栈" << '\t' << "输入符号" << endl;//输出标题并非必要。
	do {
		cout << j++ << ')' << '\t'; //输出step，并非必要。
		for (i = 0; i <= top; i++)cout << state[i]; cout << '\t';//输出状态栈内容，并非必要。
		for (i = 0; i <= top; i++)cout << symbol[i]; //输出符号栈内容，并非必要。
		cout << '\t' << t.code << endl; //输出当前输入符号（单词种别），并非必要。
		action = M[state[top]][col(t.code)];
		if (action > 0 && action != 99) { //移进
			state[++top] = action;
			symbol[top] = t.code;
			t.code = t.val[0];
			for (int x = 0; x < 20; x++) {
				t.val[x] = t.val[x + 1];
			}
			//cin >> t.code >> t.val; //读一单词
		}
		else if (action < 0) { //归约
			if (strcmp(p[-action] + 3, "ε")) //ε产生式的右部符号串长度为0，无需退栈。
				top = top - (strlen(p[-action]) - 3); //"→"为汉字,占二字节，故减3。
			state[top + 1] = M[state[top]][col(p[-action][0])]; //产生式左部符号
			symbol[++top] = p[-action][0];
		}
		else if (action == 99) { //接受
			cout << '\t' << "Acc" << endl;
			break;
		}
		else { //出错
			cout << "Err in main()>" << action << endl;
			break;
		}
	} while (1);
}
int col(char c) //将字符+* ()i#ETF分别转换为数字012345678
{
	for (int i = 0; i < (int)strlen(TNT); i++)
		if (c == TNT[i])return i;
	cout << "Err in col char>" << c << endl;
	exit(0); //终止程序运行
}
