#include <stdio.h>
#include<stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i,j,*a;
    a = (int *)malloc(2*sizeof(int));
    for (i=0;i<numsSize-1;i++) {
       for(j=i+1;j<numsSize;j++){
           if (*(nums+i)+*(nums+j)==target){
               a[0]=i;
              a[1]=j;
              *returnSize=2;
               return a;
           }
       }
    } 
     *returnSize=0;  
    return a;
}
int main() 
{
	int i,numsSize,target;
	int* nums;
	printf("请输入整数数组的个数：\n");
	scanf("%d",&numsSize);
	printf("输入%d个整数：\n",numsSize);
	for(i=0;i<numsSize-1;i++){
		scanf("%d",nums);
	} 
	printf("请输入一个整数目标值：");
	scanf("%d",&target);
	int* twoSum(int* nums, int numsSize, int target, int* returnSize);
	
	return 0;
}

