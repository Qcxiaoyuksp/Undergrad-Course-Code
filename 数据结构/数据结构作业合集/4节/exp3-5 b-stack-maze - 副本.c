//顺序栈的应用：迷宫  

#include <stdio.h>  
#include <stdlib.h>  
  
#define OK      1  
#define ERROR   0  
#define TRUE    1  
#define FALSE   0  
#define STACK_INIT_SIZE 100  
#define STACKINCREMENT 10  
  
#define COLUMN 10   //迷宫行数  
#define ROW 10      //迷宫列数  
  
typedef int Status; //函数返回状态  
  
typedef struct{//迷宫类型  
    char **maze;//迷宫数据  
    int **footprint;//足迹数据  
    int row;//行数  
    int column;//列数  
}MazeType;  
  
typedef struct{//迷宫位置坐标  
    int x;  
    int y;  
}PosType;  
  
typedef struct{  
    int order;//通道块在路径上的"序号"  
    PosType location;//通道块在迷宫中的"坐标位置"  
    int direction;//从此通信块走向下一通道块的"方向"  
}SElemType;  //栈元素类型  
  
typedef struct{//顺序栈结构定义  
    SElemType *base;  
    SElemType *top;  
    int stacksize;  
}SqStack;  
  
Status InitStack(SqStack *S);  
    //构造一个空栈S  
Status InitMaze(MazeType *M);  
    //初始化迷宫数据  
Status DestroyStack(SqStack *S);  
    //销毁栈S，S不再存在  
Status ClearStack(SqStack *S);  
    //把栈S置为空栈  
Status StackEmpty(SqStack S);  
    //若栈S为空栈，则返回TRUE，否则返回FALSE  
int StackLength(SqStack S);  
    //返回S元素的个数，即栈的长度  
Status GetTop(SqStack S,SElemType *e);  
    //若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE  
Status Push(SqStack *S,SElemType e);  
    //插入元素e为新的栈顶元素  
Status Pop(SqStack *S,SElemType *e);  
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR  
Status StackTraverse(const SqStack *S);  
    //从栈底到栈顶依次对每个元素进行访问  


Status PrintMaze(MazeType *M);  
    //输出迷宫  
Status MazePath(SqStack *S,MazeType maze,PosType start,PosType end);  
    //若迷宫maze中存在从入口start到出口end的通道，则求得一条存放在栈中（从栈底  
    //到栈顶），并返回TRUE；否则返回FALSE  
Status FootPrint(MazeType *M,PosType pos);  
    //将迷宫的当前位置pos设置为"走过"，即footprint该位置为1  
Status Pass(MazeType *M,PosType pos);  
    //判断当前位置是否走过  
SElemType NewSElem(int step,PosType pos,int d);  
    //创建新结点，用step，pos，d初始化该结点  
PosType NextPos(PosType pos,int d);  
    //将位置pos的方向设为d  

Status PrintFoot(MazeType *M,SqStack *S);  
    //输出迷宫的路径  
int main()  
{  
    MazeType maze;//迷宫结构  
    SqStack stack;//顺序栈，存储迷宫路径  
    PosType start,end;//迷宫的起点和终点；  
    start.x=0;start.y=1;//迷宫的起点  
    end.x=8;end.y=9;//迷宫的终点  
    InitMaze(&maze);//迷宫初始化  
    printf("迷宫形状：\n");  
    PrintMaze(&maze);//打印迷宫形状  
    if(TRUE==MazePath(&stack,maze,start,end))  
        printf("迷宫可解.\n");  
    else  
        printf("迷宫不可解.\n"); 

	system("PAUSE");
    return 0;  
}  
  
Status InitStack(SqStack *S){  
    //构造一个空栈S  
    S->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));  
    if(!S->base)//分配失败  
    {  
        printf("分配内存失败.\n");  
        exit(0);  
    }  
    S->top=S->base;  
    S->stacksize=STACK_INIT_SIZE;  
    return OK;  
}  
  
Status InitMaze(MazeType *M){  
    //初始化迷宫数据  
    int i,j;  
    char mz[ROW][COLUMN]={  
    '#',' ','#','#','#','#','#','#','#','#',  
    '#',' ',' ','#',' ',' ',' ','#',' ','#',  
    '#',' ',' ','#',' ',' ',' ','#',' ','#',  
    '#',' ',' ',' ',' ','#','#',' ',' ','#',  
    '#',' ','#','#','#',' ',' ',' ',' ','#',  
    '#',' ',' ',' ','#',' ','#',' ','#','#',  
    '#',' ','#',' ',' ',' ','#',' ',' ','#',  
    '#',' ','#','#','#',' ','#','#',' ','#',  
    '#','#',' ',' ',' ',' ',' ',' ',' ',' ',  
    '#','#','#','#','#','#','#','#','#','#'  
    };  
  
    M->maze=(char **)malloc(sizeof(char *)*ROW);  
    M->footprint=(int **)malloc(sizeof(int *)*ROW);  
    if(!M->maze||!M->footprint){  
        printf("申请空间失败，迷宫无法初始化.\n");  
        return ERROR;  
        exit(0);  
    }  
    for(i=0;i<ROW;i++){  
        M->maze[i]=(char *)malloc(sizeof(char)*COLUMN);  
        M->footprint[i]=(int *)malloc(sizeof(int)*COLUMN);  
        if(!M->maze[i]||!M->footprint[i]){  
            printf("申请空间失败，迷宫初始化失败.\n");  
            return ERROR;  
            exit(0);  
        }  
    }  
    for(i=0;i<ROW;i++){  
        for(j=0;j<COLUMN;j++){  
            M->maze[i][j]=mz[i][j];  
            M->footprint[i][j]=0;  
        }  
    }  
    M->row=ROW;//行  
    M->column=COLUMN;//列  
    return OK;  
}  
  
Status DestroyStack(SqStack *S){  
    //销毁栈S，S不再存在  
    if(!S)//S为空  
    {  
        printf("指针为空，释放失败.\n");  
        exit(0);  
    }  
    free(S);  
    return OK;  
}  
  
Status ClearStack(SqStack *S){  
    //把栈S置为空栈  
    if(!S)//S不存在  
        return FALSE;  
    S->top=S->base;//直接将栈顶指针指向栈底  
    return OK;  
}  
  
Status StackEmpty(SqStack S){  
    //若栈S为空栈，则返回TRUE，否则返回FALSE  
    if(S.top==S.base)  
        return TRUE;  
    else  
        return FALSE;  
}  
  
int StackLength(SqStack S){  
    //返回S元素的个数，即栈的长度  
    return S.stacksize;  
}  
  
Status GetTop(SqStack S,SElemType *e){  
    //若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE  
    if(S.top==S.base){  
        printf("栈为空.\n");  
        return FALSE;  
    }else{  
        *e=*(S.top-1);  
        printf("栈顶元素：%c\n",*e);  
        return OK;  
    }  
}  
  
Status Push(SqStack *S,SElemType e){  
    //插入元素e为新的栈顶元素  
    if(S->top-S->base>=S->stacksize){//栈已满，追加存储空间  
        S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));  
        if(!S->base)  
        {  
            printf("重新申请空间失败.\n");  
            exit(0);  
        }  
        S->top=S->base+S->stacksize;//更改栈顶指针  
        S->stacksize+=STACKINCREMENT;  
    }  
    *S->top++=e;  
    return OK;  
}  
  
Status Pop(SqStack *S,SElemType *e){  
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR  
    if(S->top==S->base){//栈为空  
        printf("栈为空.\n");  
        return ERROR;  
    }  
    *e=*(--S->top);  
    return OK;  
}  
  
Status StackTraverse(const SqStack *S){  
    //从栈底到栈顶依次对每个元素进行访问  
    SElemType *p=S->base;  
    if(S->base==S->top)  
    {  
        printf("栈为空.\n");  
        return FALSE;  
    }  
    printf("栈中元素：");  
    while(p!=S->top)  
    {  
		printf("x=%d,y=%d\n", p->location.x, p->location.y);
        *p++;  
    }  
    printf("\n");  
    return OK;  
}  
  
Status PrintMaze(MazeType *M){  
    //输出迷宫  
    int i,j;  
    for(i=0;i<M->row;i++){  
        for(j=0;j<M->column;j++){  
            printf("%c",M->maze[i][j]);  
        }  
        printf("\n");  
    }  
    printf("\n");  
    return OK;  
}  
  
Status PrintFoot(MazeType *M,SqStack *S){  
    //输出迷宫的路径  
    int i,j;  
    SElemType *p;  
    for(i=0;i<M->row;i++){  
        for(j=0;j<M->column;j++){  
            M->footprint[i][j]=0;  
        }  
    }  
    p=S->base;  
    if(S->base==S->top)  
    {  
        printf("栈为空.\n");  
        return FALSE;  
    }  
    while(p!=S->top)  
    {  
		M->footprint[p->location.x][p->location.y] = 1;
        *p++;  
    }  
    for(i=0;i<M->row;i++){  
        for(j=0;j<M->column;j++){  
            printf("%d",M->footprint[i][j]);  
        }  
        printf("\n");  
    }  
  
    return OK;  
}  
  
Status MazePath(SqStack *S,MazeType maze,PosType start,PosType end){  
    //若迷宫maze中存在从入口start到出口end的通道，则求得一条存放在栈中（从栈底  
    //到栈顶），并返回TRUE；否则返回FALSE  
   




 
}  
  
Status FootPrint(MazeType *M,PosType pos){  
    //将迷宫的当前位置pos设置为"走过"，即footprint该位置为1  
    if((pos.x>M->row)||(pos.y>M->column))  
        return FALSE;  
    M->footprint[pos.x][pos.y]=1;  
        return TRUE;  
}  
  
Status Pass(MazeType *M,PosType pos){  
    //判断当前位置是否可通，即为走过的通道块  
    if((M->row<pos.x)||(M->column<pos.y)){  
        printf("位置越位.\n");  
        exit(0);  
    }  
    if((0==M->footprint[pos.x][pos.y])&&(M->maze[pos.x][pos.y]==' '))  //可以通过，且没走过
        return TRUE;  
    else  
        return FALSE;  
}  
  
SElemType NewSElem(int step,PosType pos,int d){  
    //创建新结点，用step，pos，d初始化该结点  
    SElemType e;  
    e.order=step;  
	e.location = pos;
	e.direction = d;
    return e;  
}  
  
PosType NextPos(PosType pos,int d){  
    //获取pos位置d方向的位置  
    switch(d){  
    case 1://东  
        pos.x++;  
        break;  
    case 2://南  
        pos.y++;  
        break;  
    case 3://西  
        pos.x--;  
        break;  
    case 4://北  
        pos.y--;  
        break;  
    default:  
        printf("位置编号出错.\n");  
    }  
    return pos;  
}  
  
