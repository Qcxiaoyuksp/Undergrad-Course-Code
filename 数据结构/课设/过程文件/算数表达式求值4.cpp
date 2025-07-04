#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 表达式二叉树节点
typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// 创建新节点
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 判断是否为运算符
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// 构造表达式二叉树
Node* constructExpressionTree(char postfix[]) {
    int len = strlen(postfix);
    Node* stack[len];
    int top = -1;

    for (int i = 0; i < len; i++) {
        Node* newNode = createNode(postfix[i]);

        if (!isOperator(postfix[i])) {
            stack[++top] = newNode;
        } else {
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }

    return stack[top];
}

// 非递归前序遍历，输出前缀表达式
void iterativePreorder(Node* root) {
    if (root == NULL)
        return;

    Node* stack[100];
    int top = -1;

    stack[++top] = root;

    while (top >= 0) {
        Node* node = stack[top--];
        printf("%c", node->data);

        if (node->right != NULL)
            stack[++top] = node->right;

        if (node->left != NULL)
            stack[++top] = node->left;
    }

    printf("\n");
}

// 非递归后序遍历，输出后缀表达式
void iterativePostorder(Node* root) {
    if (root == NULL)
        return;

    Node* stack[100];
    int top = -1;
    Node* prev = NULL;

    do {
        while (root != NULL) {
            stack[++top] = root;
            root = root->left;
        }

        while (root == NULL && top >= 0) {
            root = stack[top];

            if (root->right == NULL || root->right == prev) {
                printf("%c", root->data);
                top--;
                prev = root;
                root = NULL;
            } else {
                root = root->right;
            }
        }
    } while (top >= 0);

    printf("\n");
}

int main() {
    char infix[100];
    printf("请输入一个中缀表达式：");
    scanf("%s", infix);

    // 转换为后缀表达式
    int len = strlen(infix);
    char postfix[100];
    char stack[100];
    int top = -1;
    int j = 0;

    for (int i = 0; i < len; i++) {
        char ch = infix[i];

        if (isOperator(ch)) {
            while (top >= 0 && stack[top] != '(' && (ch == '*' || ch == '/') && (stack[top] == '+' || stack[top] == '-')) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = ch;
        } else if (ch == '(') {
            stack[++top] = ch;
        } else if (ch == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--; // 弹出 '('
        } else {
            postfix[j++] = ch;
        }
    }

    while (top >= 0) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';

    printf("后缀表达式：%s\n", postfix);

    // 构造表达式二叉树
    Node* root = constructExpressionTree(postfix);

    printf("前缀表达式：");
    iterativePreorder(root);

    printf("后缀表达式：");
    iterativePostorder(root);

    return 0;
}

