#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

//判断当前字符串是否为关键字
bool isKey(string s)
{
    //关键字数组
    string keyArray[] = {"int", "char", "string", "bool", "float", "double", "true", "false", "return",
                        "if", "else", "while", "for", "default", "do", "public", "static", "switch"};
    //与当前字符串一一对比
    for (int i = 0; i < sizeof(keyArray); i++)
	{
        if (keyArray[i] == s)
            return true;
        else
            return false;
    }
}

//判断当前字符是否是运算符
bool isOperator(char ch)
{
    if ('+' == ch || '-' == ch || '*' == ch || '/' == ch || '%' == ch || '^'==ch || '='==ch || '<'==ch || '>'==ch || '!'==ch)
        return true;
    else
        return false;
}

//判断当前字符是否是界限符分隔符
bool isSeparator(char ch)
{
    if(',' == ch || ';' == ch || '{' == ch || '}' == ch || '(' == ch || ')' == ch)
        return true;
    else
        return false;
}


int main( )
{
    //定义字符变量，保存从源程序中读取的单个字符
    char ch;
    //定义字符串，保存从源程序中连续读取的字符串
    string result;
    //存放每个获取的单词的值
    string resultArray[999];
    //记录获取单词的个数
    int resultNum = 0;

    //代码存放的文件名
    string file = "example1_1.txt";
    //string file = "example2_1.txt";

    ifstream infile;
    //将文件流对象与文件连接起来
    infile.open(file.data());
    //若失败,则输出错误消息,并终止程序运行
    assert(infile.is_open());

    //txt文本中读取空格符与换行符
    //infile >> noskipws;
    //读取文本中的一个字符
    infile >> ch;

    while (!infile.eof())
    {
        //ch是英文字母或者下划线
        if(isalpha(ch) || '_'==ch)
		{
            result.append(1,ch);
            infile >> ch;
            //判断是否为关键字
            if(isKey(result))
			{
                resultArray[resultNum++] = "(2," + result + ")";
                result = "";
            }
            //读入首字符为字母，继续读入字母、数字、下划线，组成标识符或者关键字
            while(isalpha(ch) || isdigit(ch) || '_' == ch)
			{
                result.append(1,ch);
                infile >> ch;
                if(isKey(result))
				{
                    resultArray[resultNum++] = "(2," + result + ")";
                    result = "";
                }
            }
            //读入操作符或者运算符，正确保存标识符或者关键字
            if(isSeparator(ch) || isOperator(ch))
			{
                if(isKey(result))
				{
                    resultArray[resultNum++] = "(2," + result + ")";
                    result = "";
                    continue;
                }
                else
				{
                    if(isdigit(result.at(0)))
                        resultArray[resultNum++] = "(Error," + result + ")";
					else
                        resultArray[resultNum++] = "(1," + result + ")";
                    result = "";
                    continue;
                }

            }
            //读入不是字母、数字、运算符、标识符，继续读入直到遇到运算符或者分隔符
            else
			{
                result.append(1,ch);
                infile >> ch;
                while(!isSeparator(ch) && !isOperator(ch))
				{
                    result.append(1,ch);
                    infile >> ch;
                }
                resultArray[resultNum++] = "(Error," + result + ")";
                result = "";
                continue;
            }
        }
        //读入数字
        else if(isdigit(ch))
		{
            result.append(1,ch);
            infile >> ch;
            //继续读入数字，组成常数
            while(isdigit(ch))
			{
                result.append(1,ch);
                infile >> ch;
            }
            //遇到操作符或者运算符，正常终止
            if(isOperator(ch) || isSeparator(ch))
			{
                resultArray[resultNum++] = "(3," + result + ")";
                result="";
                continue;
            }
            //读入其他错误字符
            else
			{
                result.append(1,ch);
                infile >> ch;
                while(!isSeparator(ch) && !isOperator(ch))
				{
                    result.append(1,ch);
                    infile >> ch;
                }
                resultArray[resultNum++]="(Error,"+result+")";
                result = "";
                continue;
            }
        }
        //遇到运算符
        else if(isOperator(ch))
		{
            result.append(1,ch);
            infile >> ch;
            //判断是否存在<=、>=、!=
            if("<" == result || ">" == result || "!" == result)
			{
                if('='==ch)
				{
                    result.append(1,ch);
                    infile >> ch;
                }
            }
            //判断是否存在++
            if("+" == result)
			{
                if('+'==ch)
				{
                    result.append(1,ch);
                    infile >> ch;
                }
            }
            //判断是否存在--
            if("-" == result)
			{
                if('-'==ch)
				{
                    result.append(1,ch);
                    infile >> ch;
                }
            }
            //下一个读入符为字母、数字、分隔符，即正确
            if(isalpha(ch) || isdigit(ch) || isSeparator(ch))
			{
                resultArray[resultNum++] = "(4," + result + ")";
                result = "";
                continue;
            }
            else
			{
                //将错误输入符一起读入，直到正确
                while(!isSeparator(ch) && !isalpha(ch) && !isdigit(ch))
				{
                    result.append(1,ch);
                    infile >> ch;
                }
                resultArray[resultNum++] = "(Error,"+result+")";
                result = "";
                continue;
            }
        }
        //读取到分隔符
        else if(isSeparator(ch))
		{
            result.append(1,ch);
            resultArray[resultNum++] = "(5," + result + ")";
            result = "";
            infile >> ch;
        }
        //读取到未定义输入
        else{
            //出错处理
            result.append(1,ch);
            resultArray[resultNum++] = "(Error," + result + ")";
            result = "";
            infile >> ch;

        }
    }
    //关闭文件输入流
    infile.close();

    //以 （单词类编码，值） 输出结果
    for(int i=0;i<resultNum;i++){
        cout << resultArray[i] << endl;
    }

   return 0;
}

