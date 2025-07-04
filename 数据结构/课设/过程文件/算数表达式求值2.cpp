#include<iostream>
#include<string>
#include<stack>
#include<map>
using namespace std;

class infix2postfix
{
public:
    infix2postfix() {}
    infix2postfix(const string& infixExp) : infix(infixExp) {}
    void setInfixExp(const string& infixExp) { infix = infixExp; }
    string postfixExp();
    string prefixExp(); // 新增的方法，用于转换为前缀表达式
private:
    string infix;
    string postfix;
    stack<string> stk;
    map<string, int> oper_prio;
    void set_priority();
};

void infix2postfix::set_priority()
{
    oper_prio["#"] = 1;
    oper_prio[")"] = 2;
    oper_prio["+"] = 3;
    oper_prio["-"] = 3;
    oper_prio["*"] = 4;
    oper_prio["/"] = 4;
    oper_prio["%"] = 4;
    oper_prio["^"] = 5;
    oper_prio["("] = 6;
}

string infix2postfix::postfixExp()
{
    postfix = "";
    set_priority();
    stk.push("#");
    int i = infix.size() - 1; // 从后往前遍历中缀表达式
    string input, topstk;
    for (; i >= 0; )
    {
        topstk = stk.top();
        input = infix.substr(i, 1);
        if (!oper_prio[input])
            postfix = input + postfix; // 将字符放在后面
        else
        {
            if (oper_prio[input] > oper_prio[topstk])
            {
                if (input.compare("(") == 0)
                {
                    while (topstk.compare(")") != 0)
                    {
                        postfix = topstk + postfix;
                        stk.pop();
                        topstk = stk.top();
                    }
                    stk.pop();
                }
                else
                    stk.push(input);
            }
            else
            {
                if (input.compare(")") != 0)
                {
                    postfix = topstk + postfix;
                    stk.pop();
                    continue;
                }
                stk.push(input);
            }
        }
        --i;
    }
    topstk = stk.top();
    while (topstk.compare("#") != 0)
    {
        postfix = topstk + postfix;
        stk.pop();
        topstk = stk.top();
    }
    return postfix;
}

string infix2postfix::prefixExp()
{
    string prefix = "";
    set_priority();
    stk.push("#");
    int i = 0;
    string input, topstk;
    for (; i < infix.size();)
    {
        topstk = stk.top();
        input = infix.substr(i, 1);
        if (!oper_prio[input])
            prefix = input + prefix; // 将字符放在前面
        else
        {
            if (oper_prio[input] > oper_prio[topstk])
            {
                if (input.compare(")") == 0)
                {
                    while (topstk.compare("(") != 0)
                    {
                        prefix = topstk + prefix;
                        stk.pop();
                        topstk = stk.top();
                    }
                    stk.pop();
                }
                else
                    stk.push(input);
            }
            else
            {
                if (input.compare("(") != 0)
                {
                    prefix = topstk + prefix;
                    stk.pop();
                    continue;
                }
                stk.push(input);
            }
        }
        ++i;
    }
    topstk = stk.top();
    while (topstk.compare("#") != 0)
    {
        prefix = topstk + prefix;
        stk.pop();
        topstk = stk.top();
    }
    return prefix;
}

class postfixEval
{
public:
    postfixEval() {}
    void setPostfixExp(const string& postfixExp) { postfix = postfixExp; }
    int evaluate();
private:
    string postfix;
    stack<int> stk;
    void getOperands(int& left, int& right);
    int compute(int left, int right, char op) const;
    bool isOperator(char ch) const;
};

int postfixEval::evaluate()
{
    int i, left, right, expValue;
    char ch;
    for (i = 0; i < postfix.length(); i++)
    {
        ch = postfix[i];
        if (isdigit(ch))
            stk.push(ch - '0');
        else if (isOperator(ch))
        {
            getOperands(left, right);
            stk.push(compute(left, right, ch));
        }
    }
    expValue = stk.top();
    stk.pop();
    return expValue;
}

void postfixEval::getOperands(int& left, int& right)
{
    right = stk.top();
    stk.pop();
    left = stk.top();
    stk.pop();
}

int postfixEval::compute(int left, int right, char op) const
{
    int value;
    switch (op)
    {
    case '+':
        value = left + right;
        break;
    case '-':
        value = left - right;
        break;
    case '*':
        value = left * right;
        break;
    case '/':
        if (right == 0)
            cout << "postfixEval出现除0错误" << endl;
        value = left / right;
        break;
    case '%':
        if (right == 0)
            cout << "postfixEval出现除0错误" << endl;
        value = left % right;
        break;
    case '^':
        if (left == 0 && right == 0)
            cout << "postfixEval出现未定义的0^0现象" << endl;
        value = 1;
        while (right > 0)
        {
            value *= left;
            right--;
        }
        break;
    }
    return value;
}

bool postfixEval::isOperator(char ch) const
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}

int main()
{
    infix2postfix iexp;
    string infix, postfix, prefix;
    postfixEval pexp;
    cout << "**本程序模拟一位数的中缀表达式转化为后缀表达式和前缀表达式及其运算**" << endl;
    cout << "请输入一个一位数的中缀表达式（q to quit!）:" << endl;
    cin >> infix;
    while (infix.compare("q") != 0)
    {
        cout << "你输入的中缀表达式为：" << infix << endl;
        iexp.setInfixExp(infix);
        postfix = iexp.postfixExp();
        prefix = iexp.prefixExp();
        cout << "其相应的后缀表达式为：" << postfix << endl;
        cout << "其相应的前缀表达式为：" << prefix << endl;
        pexp.setPostfixExp(postfix);
        cout << "计算结果为：" << pexp.evaluate() << endl;
        cout << "请输入一个一位数的中缀表达式（q to quit!）:" << endl;
        cin >> infix;
    }
    return 0;
}

