#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Max 50

//设置运算符优先级别
struct pri{
  char ch;
  int pri; 
}lope[7]={{'+',3},{'-',3},{'*',5},{'/',5},{'(',1},{')',6},{'=',0}},
rope[7]={{'+',2},{'-',2},{'*',4},{'/',4},{'(',6},{')',1},{'=',0}};

//存放表达式的栈
typedef struct strstack{
char ch[Max];
int top;
}STRSTACK;
//二叉树结点
typedef struct Node{
    int tag;
    union{
        char ch;
        int num;
    }var;
    struct Node * lchild,*rchild;
}NODE;
//指向二叉树的栈
struct Nodestk{
    NODE * stk[Max];
    int top;
}s;

void insert(char *str,int i)
{
    int j;
    j=strlen(str)-1;
    while(j>=i)
    {
        str[j+1]=str[j];
        j--;
    }
    str[i]='0';
}
//检查表达式合法性
int check(char str[])
{
    int i=0;
    int stack=0;
    if(str[0]=='-')
        insert(str,0);
    while(str[i]!='\0')
    {
        if(str[i]>=48&&str[i]<=57)
        {
            while(str[i]>=48&&str[i]<=57)
                i++;
			i--;
			if(str[i+1]=='=')
				break;
         /*   if(str[i+1]==')')

            {
                stack--;
                if(stack<0)
                {
                    printf("出错了，括号匹配错误！\n");
                    return 0;
                }
            }*/
            if(str[i+1]!=42&&str[i+1]!=43&&str[i+1]!=45&&str[i+1]!=47&&str[i+1]!=')')
            {
                printf("出错了，数字后必须为后括号或符号\n");
                return 0;
            }
        }
        else if(str[i]=='(')
        {
            stack++;
            if(str[i+1]=='-')
                insert(str,i+1);
            if(str[i+1]>57||str[i+1]<48)
            {
                printf("出错了！前括号后必须为数字或负号！\n");
                return 0;
            }
        }

        else  if(str[i]==42||str[i]==43||str[i]==45||str[i]==47)
        {
            if(str[i+1]=='(')
                stack++;
            if((str[i+1]<48||str[i+1]>57)&&str[i+1]!='(')
            {
                printf("出错了，符号后必须为数字或前括号\n");
                return 0;
            }
        }
        else  if(str[i]==')')
        {
                stack--;
                if(stack<0)
                {
                    printf("出错了，括号匹配错误！\n");
                    return 0;
                }
            	if(str[i+1]=='=')
				break;
            if(str[i+1]=='(')
            {
                printf("出错了，后括号后不能为前括号！\n");
                return 0;
            }
        }
        else
        {
            printf("出错了，出现非法字符！\n");
            return 0;
        }
        i++;
    }
    printf("祝贺你，表达式正确！\n");
    return 1;
}
//比较两字符优先级别
int compare(char leftch, char rightch){
int i,nl,nr;
for(i=0;i<7;i++){
if(leftch==lope[i].ch)
    nl=lope[i].pri;
if(rightch==rope[i].ch)
    nr=rope[i].pri;
}
return (nr-nl);
}
//创建字符结点
NODE * CreatchNode(char ch){
    NODE * p=(NODE *)malloc(sizeof(NODE));
    p->tag=1;
    p->var.ch=ch;
    p->lchild=p->rchild=NULL;
    return p;
}
//创建数字结点
NODE * CreatnumNode(int num){
    NODE * p=(NODE *)malloc(sizeof(NODE));
    p->tag=0;
    p->var.num=num;
    p->lchild=p->rchild=NULL;
    return p;
}
//ch入栈到stack
int push(STRSTACK &str, char ch){
    if(str.top>=Max-1) return 0;
    else{
        str.ch[++(str.top)]=ch;
        return 1;
    }
}
//出栈
int pop(STRSTACK &str,char &ch){
    if(str.top<0) return 0;
    else{
        ch=str.ch[str.top--];
        return 1;
    }
}
//指向二叉树的结点指针入栈
int pushNode(struct Nodestk &s,NODE * p){
    if(s.top>=Max-1) return 0;
    else{s.stk[++s.top]=p;
    return 1;
    }
}
//指向二叉树的结点指针出栈
int popNode(struct Nodestk &s,NODE * &p){
    if(s.top<0) return 0;
    else {
        p=s.stk[s.top--];
        return 1;
    }
}
//输出结点
void PrintNode(NODE * p){
    if(p->tag==0) printf("%d ",p->var.num);
    else printf("%c ",p->var.ch);
}
//中缀表达式转换成二叉树
NODE *  expchange(char * strp){
   STRSTACK opstr;
   opstr.top=0;opstr.ch[opstr.top]='=';
    char tempch;
    int comp,n;
    NODE * p=NULL,*a=NULL,*b=NULL;
   s.top=-1;

       while(*strp!='='){
        if(*strp<='9'&&*strp>='0'){
            n=0;
            while(*strp<='9'&&*strp>='0'){
                n=n*10+(*strp-'0');
                *strp++;
            }
            p=CreatnumNode(n);
            pushNode(s,p);//PrintNode(p);printf("入栈\ts.top1=%d\n",s.top);
        }
        else{
            comp=compare(opstr.ch[opstr.top], *strp);
            if(comp>0) push(opstr,*strp++);
            else if(comp<0){
                pop(opstr,tempch);
                p=CreatchNode(tempch);
                popNode(s,a);//PrintNode(a);printf("出栈\ts.top1=%d\n",s.top+1);
                popNode(s,b);//PrintNode(b);printf("出栈\ts.top1=%d\n",s.top+1);
                pushNode(s,p);//PrintNode(p);printf("入栈\ts.top1=%d\n",s.top);
                p->lchild=b;p->rchild=a;

            }
            else {pop(opstr,tempch);
                strp++;}
        }
    }
    while(opstr.ch[opstr.top]!='='){
                pop(opstr,tempch);
                p=CreatchNode(tempch);
                popNode(s,a);//PrintNode(a);printf("出栈\ts.top1=%d\n",s.top+1);
                popNode(s,b);//PrintNode(b);printf("出栈\ts.top1=%d\n",s.top+1);
                pushNode(s,p);//PrintNode(p);printf("入栈\ts.top1=%d\n",s.top);
                p->lchild=b;p->rchild=a;

    }
    //printf("\n根结点为：");PrintNode(s.stk[s.top]);
    return s.stk[s.top];
}
//后序遍历二叉树
void PostOrder(NODE * b){
        if(b){
        PostOrder(b->lchild);
        PostOrder(b->rchild);
        PrintNode(b);
    }
}
//中序遍历二叉树
void InOrder(NODE *b){
    if(b){
        InOrder(b->lchild);
        PrintNode(b);
        InOrder(b->rchild);
    }
}
//前序遍历二叉树
void PerOrder(NODE *b){
    if(b){
        PrintNode(b);
        PerOrder(b->lchild);
        PerOrder(b->rchild);
    }
}
//二叉树表达式求值
double TreeValue(NODE * b){
    if(b->tag==0) return (double)b->var.num;
    else {
        switch(b->var.ch){
            case '+': return (TreeValue(b->lchild)+TreeValue(b->rchild));break;
            case '-': return (TreeValue(b->lchild)-TreeValue(b->rchild));break;
            case '*': return (TreeValue(b->lchild)*TreeValue(b->rchild));break;
            case '/': return (TreeValue(b->lchild)/TreeValue(b->rchild));break;
        }
    }
}
//main函数
int main(){
    char str[Max],*strp=str;
    NODE * thead;
    printf("\n请输入所要求值的表达式，以‘=’结束：（如“3+2*4+(2-1)=”）\n");
    gets(str);
    if(check(str)){
    thead=expchange(strp);
    printf("\n后缀表达式：");
    PostOrder(thead);
    printf("\n中缀表达式：");
    InOrder(thead);
    printf("\n前缀表达式：");
    PerOrder(thead);
    printf("\n运算结果为：%lf",TreeValue(thead));
    }
    return 0;
}
