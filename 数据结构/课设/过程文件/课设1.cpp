#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_SIZE 50

#define ADD 1
#define SUB 1
#define MUL 2
#define DIV 2
#define Demo 2
#define Index 3

typedef struct {
    char** data;
    int top;
} Stack;

void initStack(Stack* stack);
int isEmpty(Stack* stack);
int isFull(Stack* stack);
void push(Stack* stack, char* data);
void pop(Stack* stack);
char* top(Stack* stack);

void exit_System();
void show_Menu();
int get_Value(char *operation);
int get_result(int a, char *str, int b);
int input_Infix();
void to_Prefix(char infix[][50], int infix_Size);
void to_Postfix(char infix[][50], int infix_Size);
void caculate_Prefix();
void caculate_Infix();
void caculate_Postfix();
void show_Vector(char **expression, int size);
void show_Expression();

char **infix_Expression;
char **prefix_Expression;
char **postfix_Expression;
int infix_Size = 0;
int prefix_Size = 0;
int postfix_Size = 0;

int main()
{
    int choice = 0;

    while (1)
    {
        show_Menu();
        printf("请输入你的选择：");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            exit_System();
            break;
        case 1:
            input_Infix();
            break;
        case 2:
            caculate_Infix();
            break;
        case 3:
            caculate_Prefix();
            break;
        case 4:
            caculate_Postfix();
            break;
        case 5:
            system("cls");
            show_Expression();
            break;
        default:
            break;
        }
    }

    return 0;
}


void show_Menu() {
    printf("\n");
    printf("*************************************************\n");
    printf("*************** 表达式求值计算器 ****************\n");
    printf("*************************************************\n");
    printf("************* >1. 输入中缀表达式   **************\n");
    printf("************* >2. 中缀表达式求值   **************\n");
    printf("************* >3. 前缀表达式求值   **************\n");
    printf("************* >4. 后缀表达式求值   **************\n");
    printf("************* >5. 表达式的各种形式 **************\n");
    printf("************* >0. 退出系统         **************\n");
    printf("*************************************************\n");
    printf("*************************************************\n");
    printf("\n");
}


int get_Value(char* operation) {
    int value = 0;

    if (strcmp(operation, "+") == 0) {
        value = ADD;
    }
    else if (strcmp(operation, "-") == 0) {
        value = SUB;
    }
    else if (strcmp(operation, "*") == 0) {
        value = MUL;
    }
    else if (strcmp(operation, "/") == 0) {
        value = DIV;
    }
    else if (strcmp(operation, "%") == 0) {
        value = Demo;
    }
    else if (strcmp(operation, "^") == 0) {
        value = Index;
    }
    else {
        value = 0;
    }

    return value;
}


int get_result(int a, char* str, int b) {
    int result = 0;

    if (strcmp(str, "+") == 0) {
        result = a + b;
    }
    else if (strcmp(str, "-") == 0) {
        result = a - b;
    }
    else if (strcmp(str, "*") == 0) {
        result = a * b;
    }
    else if (strcmp(str, "/") == 0) {
        result = a / b;
    }
    else if (strcmp(str, "%") == 0) {
        result = a % b;
    }
    else if (strcmp(str, "^") == 0) {
        result = pow(a, b);
    }
    else {
        result = 0;
    }

    return result;
}


int input_Infix() {
    char infixExpression[50];     // 用于接收将要输入的表达式，最多接收50个字符
    printf("请输入你想要计算的(中缀)表达式：\n");
    fflush(stdin);
    fgets(infixExpression, sizeof(infixExpression), stdin);
    infixExpression[strcspn(infixExpression, "\n")] = '\0';  // 去除换行符

    char infix[50][50];           // 存储中缀表达式的单个元素
    int infix_Size = 0;            // 中缀表达式的长度
    int i = 0;
    int is_Input = 0;

    // 解析输入的中缀表达式
    do {
        if (infixExpression[i] == '=' || infixExpression[i] == ' ') {
            i++;
        }
        else if (infixExpression[i] < '0' || infixExpression[i] > '9') {
            char temp[2] = {infixExpression[i], '\0'};
            strcpy(infix[infix_Size], temp);
            infix_Size++;
            i++;
        }
        else {
            char strTemp[50] = "";
            while (i < strlen(infixExpression) && infixExpression[i] >= '0' && infixExpression[i] <= '9') {
                strncat(strTemp, &infixExpression[i], 1);
                i++;
            }
            strcpy(infix[infix_Size], strTemp);
            infix_Size++;
        }
    } while (i < strlen(infixExpression));

    // 转换为前缀表达式
    to_Prefix(infix, infix_Size);

    // 转换为后缀表达式
    to_Postfix(infix, infix_Size);

    // 更新状态
    is_Input = 1;

    printf("===========================\n");
    printf("表达式输入成功！:)\n\n");
    system("pause");
    system("cls");
    return is_Input;
}

void to_Prefix(char infix[][50], int infix_Size)
{
    // TODO: 实现将中缀表达式转换为前缀表达式的逻辑
    char prefix[MAX_SIZE][MAX_SIZE];
    int prefix_Size = 0;
    Stack sta;
    initStack(&sta);

    //int infix_Size = sizeof(infix_Expression) / sizeof(infix_Expression[0]);  // Assuming infix is a global variable
    for (int i = infix_Size - 1; i >= 0; i--) {
        char* str = infix[i];
        if (strcmp(str, ")") == 0) {
            push(&sta, str);
        }
        else if (strcmp(str, "(") == 0) {
            while (!isEmpty(&sta) && strcmp(top(&sta), ")") != 0) {
                strcpy(prefix[prefix_Size], top(&sta));
                prefix_Size++;
                pop(&sta);
            }
            pop(&sta);
        }
        else {
            if (!isEmpty(&sta) && strcmp(top(&sta), ")") == 0) {
                push(&sta, str);
            }
            else {
                while (!isEmpty(&sta) && get_Value(top(&sta)) > get_Value(str)) {
                    strcpy(prefix[prefix_Size], top(&sta));
                    prefix_Size++;
                    pop(&sta);
                }
                push(&sta, str);
            }
        }
    }

    while (!isEmpty(&sta)) {
        strcpy(prefix[prefix_Size], top(&sta));
        prefix_Size++;
        pop(&sta);
    }

    // Reverse the prefix expression
    int i = 0, j = prefix_Size - 1;
    while (i < j) {
        char temp[MAX_SIZE];
        strcpy(temp, prefix[i]);
        strcpy(prefix[i], prefix[j]);
        strcpy(prefix[j], temp);
        i++;
        j--;
    }
}

void to_Postfix(char infix[][50], int infix_Size)
{
    // TODO: 实现将中缀表达式转换为后缀表达式的逻辑
    char postfix[MAX_SIZE][MAX_SIZE];
    int postfix_Size = 0;
    Stack sta;
    initStack(&sta);

    for (int i = 0; i < infix_Size; i++) {
        char* str = infix[i];
        if (strcmp(str, "(") == 0) {
            push(&sta, str);
        }
        else if (strcmp(str, ")") == 0) {
            while (strcmp(top(&sta), "(") != 0) {
                strcpy(postfix[postfix_Size], top(&sta));
                postfix_Size++;
                pop(&sta);
            }
            pop(&sta);
        }
        else {
            while (!isEmpty(&sta) && get_Value(top(&sta)) >= get_Value(str)) {
                strcpy(postfix[postfix_Size], top(&sta));
                postfix_Size++;
                pop(&sta);
            }
            push(&sta, str);
        }
    }

    while (!isEmpty(&sta)) {
        strcpy(postfix[postfix_Size], top(&sta));
        postfix_Size++;
        pop(&sta);
    }
}

void caculate_Prefix()
{
    // TODO: 实现前缀表达式求值的逻辑
    Stack sta;
    initStack(&sta);

    int prefix_Size = sizeof(prefix_Expression) / sizeof(prefix_Expression[0]);  // Assuming prefix_Expression is a global variable
    for (int i = 0; i < prefix_Size; i++) {
        char* str = prefix_Expression[i];
        if (isdigit(str[0])) {
            push(&sta, str);
        }
        else if (!isEmpty(&sta)) {
            int a = atoi(top(&sta));
            pop(&sta);
            int b = atoi(top(&sta));
            pop(&sta);
            int result = get_result(a, str, b);
            char result_str[MAX_SIZE];
            sprintf(result_str, "%d", result);
            push(&sta, result_str);
        }
    }

    printf("结果为：%s\n", top(&sta));
    pop(&sta);
}

// TODO: 实现中缀表达式求值的逻辑
void caculate_Infix()
{
    Stack operator_Stack;
    Stack number_Stack;
    initStack(&operator_Stack);
    initStack(&number_Stack);

    int infix_Size = sizeof(infix_Expression) / sizeof(infix_Expression[0]);  // Assuming infix_Expression is a global variable
    for (int i = 0; i < infix_Size; i++) {
        char* str = infix_Expression[i];
        if (isdigit(str[0])) {
            int num = atoi(str);
            char num_str[MAX_SIZE];
            sprintf(num_str, "%d", num);
            push(&number_Stack, num_str);
        }
        else if (strcmp(str, "(") == 0) {
            push(&operator_Stack, str);
        }
        else if (strcmp(str, ")") == 0) {
            while (strcmp(top(&operator_Stack), "(") != 0) {
                char* op = top(&operator_Stack);
                pop(&operator_Stack);
                int a = atoi(top(&number_Stack));
                pop(&number_Stack);
                int b = atoi(top(&number_Stack));
                pop(&number_Stack);
                int result = get_result(b, op, a);
                char result_str[MAX_SIZE];
                sprintf(result_str, "%d", result);
                push(&number_Stack, result_str);
            }
            pop(&operator_Stack);  // Pop "("
        }
        else {
            if (isEmpty(&operator_Stack) || strcmp(top(&operator_Stack), "(") == 0) {
                push(&operator_Stack, str);
            }
            else {
                while (!isEmpty(&operator_Stack) && get_Value(top(&operator_Stack)) >= get_Value(str)) {
                    char* op = top(&operator_Stack);
                    pop(&operator_Stack);
                    int a = atoi(top(&number_Stack));
                    pop(&number_Stack);
                    int b = atoi(top(&number_Stack));
                    pop(&number_Stack);
                    int result = get_result(b, op, a);
                    char result_str[MAX_SIZE];
                    sprintf(result_str, "%d", result);
                    push(&number_Stack, result_str);
                }
                push(&operator_Stack, str);
            }
        }
    }

    while (!isEmpty(&operator_Stack)) {
        char* op = top(&operator_Stack);
        pop(&operator_Stack);
        int a = atoi(top(&number_Stack));
        pop(&number_Stack);
        int b = atoi(top(&number_Stack));
        pop(&number_Stack);
        int result = get_result(b, op, a);
        char result_str[MAX_SIZE];
        sprintf(result_str, "%d", result);
        push(&number_Stack, result_str);
    }

    printf("运算结果为：%s\n", top(&number_Stack));
    pop(&number_Stack);
}

// TODO: 实现后缀表达式求值的逻辑

void caculate_Postfix()
{
    Stack sta;
    initStack(&sta);

    int postfix_Size = sizeof(postfix_Expression) / sizeof(postfix_Expression[0]);  // Assuming postfix_Expression is a global variable
    for (int i = 0; i < postfix_Size; i++) {
        char* str = postfix_Expression[i];
        if (isdigit(str[0])) {
            int num = atoi(str);
            char num_str[MAX_SIZE];
            sprintf(num_str, "%d", num);
            push(&sta, num_str);
        }
        else {
            char* op = str;
            int a = atoi(top(&sta));
            pop(&sta);
            int b = atoi(top(&sta));
            pop(&sta);
            int result = get_result(b, op, a);
            char result_str[MAX_SIZE];
            sprintf(result_str, "%d", result);
            push(&sta, result_str);
        }
    }

    printf("结果为：%s\n", top(&sta));
    pop(&sta);
}


void show_Vector(char **expression, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s ", expression[i]);
    }
    printf("\n");
}

void show_Expression()
{
    if (input_Infix()) {
        printf("******************前缀表达式*****************\n");
        show_Vector(prefix_Expression, prefix_Size); 
        printf("******************中缀表达式*****************\n");
        show_Vector(infix_Expression, infix_Size);
        printf("******************后缀表达式*****************\n");
        show_Vector(postfix_Expression, postfix_Size);  
    }
    else {
        printf("Oops! 请先输入表达式！\n");
    }

    system("pause");
    system("cls");
}

void exit_System()
{
    for (int i = 0; i < infix_Size; i++)
    {
        free(infix_Expression[i]);
    }
    free(infix_Expression);

    for (int i = 0; i < prefix_Size; i++)
    {
        free(prefix_Expression[i]);
    }
    free(prefix_Expression);

    for (int i = 0; i < postfix_Size; i++)
    {
        free(postfix_Expression[i]);
    }
    free(postfix_Expression);
    
	printf("欢迎下次使用！\n");
	system("pause");
    exit(0);
}


//栈的操作


void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, char* data)
{
    if (stack->top == MAX_SIZE - 1)
    {
        printf("Stack Overflow\n");
        return;
    }

    stack->top++;
    stack->data[stack->top] = (char* )malloc(strlen(data) + 1);
    strcpy(stack->data[stack->top], data);
}

void pop(Stack* stack) {
    if (!isEmpty(stack)) {
        stack->top--;
    }
}

char* top(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return NULL;
}
