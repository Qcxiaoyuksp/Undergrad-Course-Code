#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    int top;
} InfixToPostfix;

typedef struct {
    char postfix[MAX_SIZE];
    int stack[MAX_SIZE];
    int top;
} PostfixEval;

void set_priority();
void set_infix_exp(InfixToPostfix *iexp, const char *infix);
void infix_to_postfix(InfixToPostfix *iexp);
int evaluate_postfix(const char *postfix);
void push(PostfixEval *pexp, int value);
int pop(PostfixEval *pexp);
int is_operator(char ch);

int oper_prio[128];
int oper_prio_out[128];

void set_priority() {
    oper_prio['#'] = 1;
    oper_prio['('] = 2;
    oper_prio['+'] = 3;
    oper_prio['-'] = 3;
    oper_prio['*'] = 4;
    oper_prio['/'] = 4;
    oper_prio['%'] = 4;
    oper_prio['^'] = 5;
    oper_prio[')'] = 6;
}

void set_infix_exp(InfixToPostfix *iexp, const char *infix) {
    strcpy(iexp->infix, infix);
    iexp->top = -1;
}

void infix_to_postfix(InfixToPostfix *iexp) {
    char topstk;
    char input;
    char postfix[MAX_SIZE];
    char *p_postfix = postfix;
    int i = 0;
    set_priority();
    iexp->postfix[0] = '\0';
    int infix_length = strlen(iexp->infix);
    
    for (; i < infix_length;) {
        topstk = iexp->infix[iexp->top];
        input = iexp->infix[i];
        
        if (!oper_prio[input]) {
            *p_postfix++ = input;
            *p_postfix = '\0';
        } else {
            if (oper_prio[input] > oper_prio[topstk]) {
                if (input == ')') {
                    while (topstk != '(') {
                        *p_postfix++ = topstk;
                        *p_postfix = '\0';
                        iexp->top--;
                        topstk = iexp->infix[iexp->top];
                    }
                    iexp->top--;
                } else {
                    iexp->top++;
                    iexp->infix[iexp->top] = input;
                }
            } else {
                if (input != '(') {
                    *p_postfix++ = topstk;
                    *p_postfix = '\0';
                    iexp->top--;
                    continue;
                }
                iexp->top++;
                iexp->infix[iexp->top] = input;
            }
        }
        i++;
    }
    
    while (iexp->top > 0) {
        topstk = iexp->infix[iexp->top];
        *p_postfix++ = topstk;
        *p_postfix = '\0';
        iexp->top--;
    }
    
    strcpy(iexp->postfix, postfix);
}

int evaluate_postfix(const char *postfix) {
    int stack[MAX_SIZE];
    int top = -1;
    int left, right, value;
    int i = 0;
    int postfix_length = strlen(postfix);
    
    for (; i < postfix_length; i++) {
        char ch = postfix[i];
        
        if (isdigit(ch)) {
            stack[++top] = ch - '0';
        } else if (is_operator(ch)) {
            right = stack[top--];
            left = stack[top--];
            value = 0;
            
            switch (ch) {
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
                    if (right == 0) {
                        printf("postfixEval出现除0错误\n");
                        exit(1);
                    }
                    value = left / right;
                    break;
                case '%':
                    if (right == 0) {
                        printf("postfixEval出现除0错误\n");
                        exit(1);
                    }
                    value = left % right;
                    break;
                case '^':
                    if (left == 0 && right == 0) {
                        printf("postfixEval出现未定义的0^0现象\n");
                        exit(1);
                    }
                    value = 1;
                    while (right > 0) {
                        value *= left;
                        right--;
                    }
                    break;
            }
            
            stack[++top] = value;
        }
    }
    
    return stack[top];
}

void push(PostfixEval *pexp, int value) {
    pexp->stack[++pexp->top] = value;
}

int pop(PostfixEval *pexp) {
    return pexp->stack[pexp->top--];
}

int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}

int main() {
    InfixToPostfix iexp;
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    PostfixEval pexp;
    
    printf("**本程序模拟一位数的中缀表达式转化为后缀表达式及其运算**\n");
    printf("****  学号：0876111432    姓名：任敏  ****\n");
    printf("请输入一个一位数的中缀表达式（q to quit!）:\n");
    
    while (scanf("%s", infix) != EOF) {
        if (strcmp(infix, "q") == 0) {
            break;
        }
        
        printf("你输入的中缀表达式为：%s\n", infix);
        set_infix_exp(&iexp, infix);
        infix_to_postfix(&iexp);
        printf("其相应的后缀表达式为：%s\n", iexp.postfix);
        pexp.top = -1;
        printf("表达式的运算值 = %d\n\n", evaluate_postfix(iexp.postfix));
        printf("请再输入一个一位数的中缀表达式（q to quit!）:\n");
    }
    
    return 0;
}

