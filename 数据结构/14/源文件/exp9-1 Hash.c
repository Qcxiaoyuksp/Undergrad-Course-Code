/*exp9-1 Hash*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

#define OK          1
#define SUCCESS     1
#define UNSUCCESS   0
#define ERROR       0
#define TRUE        1
#define FALSE       0
#define OVERFLOW    -1
#define HASH_LENGTH 11 //表长
#define HASH_M 11 //哈希函数%11

typedef int Status;

typedef struct{
	int *elem;//定义关键字为整型
	int count;//当前哈希表中的关键字个数
	int length;//当前哈希表的容量
}HashTable;

Status InitHash(HashTable *H);
int Hash(int key); //哈希函数
int Collision(int p, int c);
Status SearchHash(HashTable H, int key, int *p, int *c);
Status InsertHash(HashTable *H, int key, int *p, int *c);

int main()
{
	
	char ch;
	int i,key;
	int p = 0, c = 0;
	HashTable H;
	int arr[] = { 1, 13, 12, 34, 38, 33, 27, 22 };

	while(1){
		printf("Hash Table's Implementation\n");
		printf("===========================================\n");
		printf("1. Initialize a Hash Table;  2. Insert some values;\n");
		printf("3. Search a Value;    0. Exit;\n");
		printf("===========================================\n");
		
		scanf(" %c",&ch);
		
		switch(ch){
		case '1':
			InitHash(&H);
			printf("\n");
			break;
		case '2':
			for (i = 0; i < 8; i++) {
				InsertHash(&H, arr[i], &p, &c);//
			}
			printf("\n");
			break;
		case '3':
	    	printf("Input a value for search：\n");
			scanf(" %d", &key);
			if (SearchHash(H, key, &p, &c))
				printf("哈希地址为%d:冲突次数为%d.\n", p,c);
			else
				printf("The value %d is not found.\n", key);
			printf("\n");
			break;
				
		case '0':exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;	
		}
	}
	system("PAUSE");
	return 0;
}

Status InitHash(HashTable *H){
	H->elem = (int *)malloc(HASH_LENGTH*sizeof(int));
	if (!H) exit(OVERFLOW);
	memset(H->elem, 0, sizeof(int)*HASH_LENGTH);
	//H->elem[HASH_LENGTH] = { 0,0,0,0 };
	H->count = 0;
	H->length = HASH_LENGTH;
	return OK;
}


int Hash(int key)//哈希函数
{
	return key % HASH_M;
}

int Collision(int p, int c)
{//冲突处理函数,以线性探测再散列作为冲突处理方式
	return (p + c) % HASH_M;//重新找到的哈希地址
}
/*查找关键字key在哈希表中的位置，如果查找成功返回SUCCESS，否则返回UNSUCCESS。
 用p返回关键字在哈希表中的位置, c为处理冲突的次数。
 用p也可返回关键字要插入的位置, c为处理冲突的次数*/
Status SearchHash(HashTable H, int key, int *p, int *c)
{
	int q;
    *c=0;
    *p=Hash(key);
    
    while(H.elem[*p]!=0 && H.elem[*p]!=key)
    {
        *p=Collision(*p,*c++);
    }
    if(H.elem[*p]==key)
        return SUCCESS;
    else
        return UNSUCCESS;

}

/*若哈希表H中无关键字key则插入*/
Status InsertHash(HashTable *H, int key, int *p, int *c)
{ 
	if(SearchHash(*H,key,p,c))
        return ERROR;
        
    if(*c<H->length)
    {
        H->elem[*p]=key;
        H->count++;
        *c=0;
        printf("%d insert successful!\n",key);
        return OK;
    }
    else
    {
        *c=0;
        return ERROR;
    }

}
