//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define F_PATH "d:\\myfile\\input.txt"

int bruteForceMatch(char *str, char *pattern);

int main(){
	FILE *fp;
	int i=0,j,location;
	char *str;
	char *pattern;
	
    char filename[30];
	
	printf("Enter a file name:");
	scanf("%s",filename);
//  if((fp=fopen(F_PATH, "r"))==NULL)
	if((fp=fopen(filename, "r"))==NULL)//d:\\myfile\\input.txt  打开
	{
		printf("can't open the file!\n");
		exit(0);	
	} 
		
	str = (char *)malloc(sizeof(char)*1024);
    pattern = (char *)malloc(sizeof(char)*1024);
	//str存储地址，100读100个字符，fp打开的文件
    if(fgets(str,100,fp)== NULL||fgets(pattern,100,fp)== NULL){ //读取
    	printf("can't match!\n");
		exit(0);
	}
	fclose(fp);//关闭
	location = bruteForceMatch(str, pattern);
	if (location == -1){
       printf("Don't find the pattern!\n");	
	} 
	else{
		printf("The location of %s is: %d\n", pattern, location);
	}

	system("pause");

	return 0;
}

int bruteForceMatch(char *str, char *pattern)
{	
	int i, k, j;
   int lenStr, lenPattern; 
   
   lenStr=strlen(str);
   j=0; 
   lenPattern=strlen(pattern);
   for(i=0;i<lenStr;i++){
   	k=i;
   	while(str[k]==pattern[j])
   	{
   		k++;
   		j++;
	   }
	   if(j==lenPattern)
	   break;
	   j=0;
   } 
   return i;
}  
