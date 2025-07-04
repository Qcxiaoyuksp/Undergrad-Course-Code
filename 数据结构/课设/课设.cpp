#include<iostream>
#include<stack>
#include<string>
#include<sstream>//用来进行流的输入、输出和输入输出操作
#include<vector>//向量（Vector）是一个封装了动态大小数组的顺序容器
#include<algorithm>

using namespace std;


class Caculate {
public:
	//是否输入了表达式, 默认false
	bool is_Input = false;
	//展示菜单
	void show_Menu();
	//获取运算符优先级
	int get_Value(string operation);
	//获取简单表达式计算结果
	//a 代表操作数 1，str 代表 操作运算符，b 代表操作数 2
	// a str b : 例如 a - b, a*b
	int get_result(int a, string str, int b);
	//输入中缀表达式
	void input_Infix();
	//存储中缀表达式
	vector<string> infix_Expression;
	//存储前缀表达式
	vector<string> prefix_Expression;
	//存储后缀表达式
	vector<string> postfix_Expression;
	//由中缀表达式转成前缀表达式
	void to_Prefix();
	//由中缀表达式转成后缀表达式
	void to_Postfix();
	//前缀表达式计算求值
	void caculate_Prefix();
	//中缀表达式计算求值
	void caculate_Infix();
	//后缀表达式计算求值
	void caculate_Postfix();
	//遍历展示vector容器中元素
	void show_Vector(vector<string> expression);
	//展示表达式的各种形式
	void show_Expression();
	//退出系统
	void exit_System();
};


int main() {
	Caculate ca;
	int choice = 0;

	while (true) {
		ca.show_Menu();
		cout << "请输入你的选择：";
		cin >> choice;
		switch (choice)
		{
		case 0:
			ca.exit_System();	//退出系统
			break;
		case 1:
			ca.input_Infix();	//输入中缀表达式
			break;
		case 2:
			ca.caculate_Infix();	//中缀表达式求值
			break;			
		case 3:
			ca.caculate_Prefix();	//前缀表达式求值
			break;			
		case 4:
			ca.caculate_Postfix();	//后缀表达式求值
			break;			
		case 5:
			system("cls");
			ca.show_Expression();	//表达式的各种形式
			break;			
		default:
			cout << "请重新输入你的选择：";
			break;
		}
	}

	system("pause");
	return 0;
}

//退出系统
void Caculate::exit_System() {
	cout << "欢迎下次使用！:)" << endl;
	system("pause");
	exit(0);
}

//展示菜单
void Caculate::show_Menu() {
	cout << endl;
	cout << "*************************************************" << endl;
	cout << "*************** 表达式求值计算器 ****************" << endl;
	cout << "*************************************************" << endl;
	cout << "************* >1. 输入中缀表达式   **************" << endl;
	cout << "************* >2. 中缀表达式求值   **************" << endl;
	cout << "************* >3. 前缀表达式求值   **************" << endl;
	cout << "************* >4. 后缀表达式求值   **************" << endl;
	cout << "************* >5. 表达式的各种形式 **************" << endl;
	cout << "************* >0. 退出系统         **************" << endl;
	cout << "*************************************************" << endl;
	cout << "*************************************************" << endl;
	cout << endl;
}

//获取元素优先级
int Caculate::get_Value(string operation) {
	int value = 0;

	if (operation == "+") {
		value = 1;
	}
	else if (operation == "-") {
		value = 1;
	}
	else if (operation == "*") {
		value = 2;
	}
	else if (operation == "/") {
		value = 2;
	}
	else if (operation == "%") {
		value = 2;
	}
	else {
		value = 0;
	}

	return value;
}

//获取简单表达式计算结果
int Caculate::get_result(int a, string str, int b) {
	int result = 0;
	if (str == "+") {
		result = a + b;
	}
	else if (str == "-") {
		result = a - b;
	}
	else if (str == "*") {
		result = a * b;
	}
	else if (str == "/") {
		result = a / b;
	}
	else if (str == "%") {
		result = a % b;
	}
	else {
		result = 0;
	}

	return result;
}

//输入中缀表达式
void Caculate::input_Infix() {
	this->infix_Expression.clear();		//清空容器，方便接收用户接下来的输入
	system("cls");
	
	cout << "请输入你想要计算的(中缀)表达式：" << endl;
	char cha[50];			//用来接收将要输入的表达式, 最多接收50个字符	
	cin.ignore();			//cin.getline默认以换行符为结束标志,要消耗掉前面的换行符需要多调用一次即使用两次cin.getline()									
	cin.getline(cha, 50);	//或者这之前使用cin.ignore();

	string str = string(cha);				//将字符数组转成字符串
	int len = (int)str.length();		//表达式长度
	int i = 0;

	do {
		if (str[i] == '=' || str[i] == ' ') {			//当为空格或者‘=’ 的时候，就直接跳过
			i++;
		}
		else if ( str[i] < 48 || str[i] > 57) {				//当不再0-9之间，就直接保存
			string temp = "";
			temp += str[i];
			this->infix_Expression.push_back(temp);
			i++;
		}
		else {
			string str_temp = "";
			while (i < len && str[i] >= 48 &&  str[i] <= 57) {	//当在0-9之间就拼接成原来的数字，然后再保存
				str_temp += str[i];
				i++;
			}
			this->infix_Expression.push_back(str_temp);
		}
	} while (i < len);

	this->to_Prefix();			//转换成前缀表达式
	this->to_Postfix();			//转换成后缀表达式

	//更新状态
	this->is_Input = true;

	cout << "===========================" << endl;
	cout << "表达式输入成功！:)" << endl;
	cout << endl;

	system("pause");
	system("cls");
}

//转换成后缀表达式
void Caculate::to_Postfix() {
	//定义符号栈
	stack<string> sta;
	for (vector<string>::iterator it = this->infix_Expression.begin(); it != this->infix_Expression.end(); it++) {
		string str = *it;
		if (str >= "0" && str <= "9") {			//若是遇到数字就直接保存
			this->postfix_Expression.push_back(str);
		}
		else if (str == "(") {			//遇到"(" 就进栈
			sta.push(str);
		}
		else if (str == ")") {			//遇到")" 就去匹配此前的 "(",栈顶元素依次出栈，并保存
			while (sta.top() != "(") {
				this->postfix_Expression.push_back(sta.top());
				sta.pop();
			}
			sta.pop();		//弹出栈顶的 ")"
		}
		else {
			while (sta.size() != 0 && get_Value(sta.top()) >= get_Value(str)) {
				this->postfix_Expression.push_back(sta.top());
				sta.pop();
			}
			sta.push(str);
		}
	}

	//如果栈中最后还有元素，一并输出保存
	while (sta.size() != 0) {
		this->postfix_Expression.push_back(sta.top());
		sta.pop();
	}

}

//转换成前缀表达式
void Caculate::to_Prefix() {
	//定义符号栈
	stack<string> sta;
	vector<string> vec = this->infix_Expression;		//定义一个vec容器来存储中缀表达式，方便接下来的操作
	reverse(vec.begin(), vec.end());
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); it++) {
		string str = *it;
		if (str >= "0" && str <= "9") {			//若是遇到数字就直接保存
			this->prefix_Expression.push_back(str);
		}
		else if (str == ")") {			//遇到"(" 就进栈
			sta.push(str);
		}
		else if (str == "(") {
			while (sta.size() !=0 && sta.top() != ")") {
				this->prefix_Expression.push_back(sta.top());
				sta.pop();
			}  
			sta.pop();		//将 ")"弹出符号栈
		}
		else {
			//如果当前栈顶元素为右括号‘）’，直接将操作符放入符号栈中
			if (!sta.empty() && sta.top() == ")") {
				sta.push(str);
			}
			else {
				//果当前栈顶元素的优先级大于操作数的优先级，则将栈顶元素移除，再次和判断移除后栈的栈顶元素比较优先级大小，
				//直到当前栈顶元素小于或等于操作数优先级，将操作符放入符号栈中
				while (!sta.empty() && get_Value(sta.top()) > get_Value(str)) {
					this->prefix_Expression.push_back(sta.top());
					sta.pop();
				}
				sta.push(str);
			}			
		}
	}

	while (!sta.empty()) {			//最后当栈不为空的时候，将栈中的元素依次移出并保存
		this->prefix_Expression.push_back(sta.top());
		sta.pop();
	}
	reverse(this->prefix_Expression.begin(), this->prefix_Expression.end());
}

//中缀表达式求值
void Caculate::caculate_Infix() {
	//定义两个栈，一个运算符栈，一个操作数栈
	stack<string> operator_Stack;
	stack<int> number_Stack;

	for (vector<string>::iterator it = this->infix_Expression.begin(); it != this->infix_Expression.end(); it++) {
		string str = *it;
		stringstream ss;

		int num = 0;
		if (str[0] >= '0' && str[0] <= '9') {	//如果第一个字符为数字字符，则这个字符串是数字，用istringsteam 转成数字
			istringstream istr(str);			//这样就可以实现多位整数的运算
			istr >> num;
			number_Stack.push(num);
		}

		else if (str == "(") {
				operator_Stack.push(str);
			}
		else if (str == ")") {
			while (operator_Stack.top() != "(") {
					int a = number_Stack.top();
					number_Stack.pop();
					int b = number_Stack.top();
					number_Stack.pop();
					int result = this->get_result(b, operator_Stack.top(), a);
					number_Stack.push(result);
					operator_Stack.pop();
			}
			operator_Stack.pop();		//弹出"("
		}
		else {
			if (operator_Stack.size() == 0 || operator_Stack.top() == "(") {
				operator_Stack.push(str);
			}
			else {
				while (operator_Stack.size() != 0 && get_Value(operator_Stack.top()) >= get_Value(str)) {
					int a = number_Stack.top();
					number_Stack.pop();
					int b = number_Stack.top();
					number_Stack.pop();
					int result = this->get_result(b, operator_Stack.top(), a);
					number_Stack.push(result);
					operator_Stack.pop();
				}
				operator_Stack.push(str);
			}
		}
	}

	while (operator_Stack.size() != 0) {
		int a = number_Stack.top();
		number_Stack.pop();
		int b = number_Stack.top();
		number_Stack.pop();
		int result = this->get_result(b, operator_Stack.top(), a);
		number_Stack.push(result);
		operator_Stack.pop();
	}

	if (this->is_Input) {
		cout << "******************中缀表达式*****************" << endl;
		this->show_Vector(this->infix_Expression);
	}
	else {
		cout << "Oops! 请先输入表达式！" << endl;
	}
	cout << "运算结果为：" << number_Stack.top() << endl;
	number_Stack.pop();

	system("pause");
	system("cls");
}

//前缀表达式求值
void Caculate::caculate_Prefix() {
	stack<int> sta;
	vector<string> vec = this->prefix_Expression;
	reverse(vec.begin(), vec.end());
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); it++) {
		string str = *it;

		int num = 0;
		if (str[0] >= '0' && str[0] <= '9') {	//如果第一个字符为数字字符，则这个字符串是数字，用istringsteam 转成数字
			istringstream istr(str);			//这样就可以实现多位整数的运算
			istr >> num;
			sta.push(num);
		}
	
		else if(sta.size() !=0) {
			//注意与后缀表达式操作数顺序的区别
			int a = sta.top();
			sta.pop();
			int b = sta.top();
			sta.pop();
			int result = this->get_result(a, str, b);
			sta.push(result);
		}
	}
	if (this->is_Input) {
		cout << "******************前缀表达式*****************" << endl;
		this->show_Vector(this->prefix_Expression);
	}
	else {
		cout << "Oops! 请先输入表达式！" << endl;
	}
	cout << "运算结果为：" << sta.top() << endl;
	sta.pop();

	system("pause");
	system("cls");
}

//后缀表达式求值
void Caculate::caculate_Postfix() {
	stack<int> sta;

	for (vector<string>::iterator it = this->postfix_Expression.begin(); it != this->postfix_Expression.end(); it++) {
		string str = *it;
		stringstream ss;

		int num = 0;
		if (str[0] >= '0' && str[0] <= '9') {	//如果第一个字符为数字字符，则这个字符串是数字，用istringsteam 转成数字
			istringstream istr(str);			//这样就可以实现多位整数的运算
			istr >> num;
			sta.push(num);
		}
		else {
			int a = sta.top();
			sta.pop();
			int b = sta.top();
			sta.pop();
			int result = this->get_result(b, str, a);
			sta.push(result);
		}
	}
	if (this->is_Input) {
		cout << "******************后缀表达式*****************" << endl;
		this->show_Vector(this->postfix_Expression);
	}
	else {
		cout << "Oops! 请先输入表达式！" << endl;
	}
	cout << "运算结果为：" << sta.top() << endl;
	sta.pop();

	system("pause");
	system("cls");

}

//遍历展示vector容器中元素
void Caculate::show_Vector(vector<string> expression) {
	for (vector<string>::iterator it = expression.begin(); it != expression.end(); it++) {
		cout << (string)(*it) << " ";
	}
	cout << endl;
}

//展示表达式各种形式
void Caculate::show_Expression() {
	if (this->is_Input) {
		cout << "******************前缀表达式*****************" << endl;
		this->show_Vector(this->prefix_Expression);
		cout << "******************中缀表达式*****************" << endl;
		this->show_Vector(this->infix_Expression);
		cout << "******************后缀表达式*****************" << endl;
		this->show_Vector(this->postfix_Expression);
	}
	else {
		cout << "Oops! 请先输入表达式！" << endl;
	}

	system("pause");
	system("cls");
}
