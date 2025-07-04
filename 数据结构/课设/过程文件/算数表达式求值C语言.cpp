#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

void push(Stack *stack, char element) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->data[++stack->top] = element;
}

char pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack->data[stack->top--];
}

char top(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is Empty\n");
        return '\0';
    }
    return stack->data[stack->top];
}

int isEmpty(Stack *stack) {
    return (stack->top == -1);
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^');
}

int getPriority(char ch) {
    if (ch == '(' || ch == ')')
        return 1;
    else if (ch == '+' || ch == '-')
        return 2;
    else if (ch == '*' || ch == '/' || ch == '%')
        return 3;
    else if (ch == '^')
        return 4;
    else
        return 0;
}

void infixToPostfix(const char *infixExp, char *postfixExp) {
    Stack stack;
    initialize(&stack);
    int i = 0, j = 0;
    char ch, topOperator;

    while ((ch = infixExp[i++]) != '\0') {
        if (isalnum(ch)) {
            postfixExp[j++] = ch;
        } else if (isOperator(ch)) {
            while (!isEmpty(&stack) && getPriority(top(&stack)) >= getPriority(ch)) {
                topOperator = pop(&stack);
                postfixExp[j++] = topOperator;
            }
            push(&stack, ch);
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && top(&stack) != '(') {
                topOperator = pop(&stack);
                postfixExp[j++] = topOperator;
            }
            if (!isEmpty(&stack) && top(&stack) == '(') {
                pop(&stack);  // Discard the '('
            } else {
                printf("Invalid Expression: Mismatched Parentheses\n");
                return;
            }
        }
    }

    while (!isEmpty(&stack)) {
        topOperator = pop(&stack);
        if (topOperator == '(') {
            printf("Invalid Expression: Mismatched Parentheses\n");
            return;
        }
        postfixExp[j++] = topOperator;
    }

    postfixExp[j] = '\0';
}

int evaluatePostfix(const char *postfixExp) {
    Stack stack;
    initialize(&stack);
    int i = 0;
    char ch;
    int operand1, operand2, result;

    while ((ch = postfixExp[i++]) != '\0') {
        if (isdigit(ch)) {
            push(&stack, ch - '0');
        } else if (isOperator(ch)) {
            operand2 = pop(&stack);
            operand1 = pop(&stack);
            switch (ch) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Error: Division by Zero\n");
                        return 0;
                    }
                    result = operand1 / operand2;
                    break;
                case '%':
                    if (operand2 == 0) {
                        printf("Error: Division by Zero\n");
                        return 0;
                    }
                    result = operand1 % operand2;
                    break;
                case '^':
                    result = 1;
                    while (operand2 > 0) {
                        result *= operand1;
                        operand2--;
                    }
                    break;
            }
            push(&stack, result);
        }
    }

    return pop(&stack);
}

int main() {
    char infixExp[100], postfixExp[100];
    printf("**本程序模拟一位数的中缀表达式转化为后缀表达式及其运算**\n");
    printf("****  学号：2104230414    姓名：张清晨  ****\n");
    printf("请输入一个一位数的中缀表达式（q to quit!）:\n");
    scanf("%s", infixExp);
    while (strcmp(infixExp, "q") != 0) {
        printf("你输入的中缀表达式为：%s\n", infixExp);
        infixToPostfix(infixExp, postfixExp);
        printf("其相应的后缀表达式为：%s\n", postfixExp);
        printf("表达式的运算值：%d\n\n", evaluatePostfix(postfixExp));
        printf("请再输入一个一位数的中缀表达式（q to quit!）:\n");
        scanf("%s", infixExp);
    }

    return 0;
}

