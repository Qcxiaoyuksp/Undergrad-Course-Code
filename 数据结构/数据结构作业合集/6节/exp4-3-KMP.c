#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
#define MAX_CHAR 256 //0-255 ，一个字符可表示的值2^8个，标准可见字符数128个。
#define SIZE 256

void print(int *array, int n, char *arrayName);
void getNext(char * p, int * next, int n);
int KMP(char * t, char * p);

void main()
{
    char text[256], pattern[256];

	while (1)
    {
        puts("Please input the text and the pattern:(input Q to quit.)");
        gets(text);
        if (!strcmp(text, "Q") || ! strcmp(text, "q")) break;
        gets(pattern);

		printf("Found it, the position is %d\n", KMP(text, pattern)); 
        printf("\n");
    }
	system("PAUSE");
}

/*输出一个整型数组next */
void print(int *array, int n, char *arrayName)
{
    int i;
 
    printf("%s:", arrayName);
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}


/* 计算next数组 */
void getNext(char * p, int * next,int n)
{
    next[0] = -1;
    int k = -1;
    int j = 0;
    while(j < n - 1)
    {
        if(k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }

	print(next, n-1, "next[]");
}

/* KMP匹配 */
int KMP(char * t, char * p)
{
	int *next;
	int i = 0, j = 0;
	int lent, lenp;
	
	lent = strlen(t);
	lenp = strlen(p);
	next = (int *)malloc(sizeof(int)*lenp);
	getNext(t,next,lent);
	while(i < lent)
    {
        if(j == -1 || p[j] == t[i])
        {
            ++j;
            ++i;
          if(j==lenp)
          	return (i-j+1);
		  
        }
        else
        {
            j = next[j];
        }
    }
return (-1);

}



