#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i,j,*a;
    a = (int *)malloc(2*sizeof(int));
    for (i=0;i<numsSize-1;i++) {
       for(j=i+1;j<numsSize;j++){
           if (*(nums+i)+*(nums+j)==target){
               a[0]=i;
              a[1]=j;
              printf("%d%d",i,j);
              *returnSize=2;
               return a;
           }
      
       }
    } 
     *returnSize=0;  
    return a;
}
int main(void){
	int nums[4]={2,5,6,8}; 
	int *returnSize;
	twoSum(nums,4,7,returnSize);
	
	return 0;
	}
