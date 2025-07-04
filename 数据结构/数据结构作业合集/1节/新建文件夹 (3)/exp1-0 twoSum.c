#include <stdio.h>
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
 
