#include <stdio.h>
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
main(){
	int numsSize,nums[10],target,i,*b,*returnSize;
	printf("请输入数组个数");
	scanf("%d",&numsSize);
	printf("请输入数组");
	for(i=0;i<numsSize;i++){
		scanf("%d",&nums[i]);
	}
	printf("请输入所求的数");
	scanf("%d",&target);
	b=twoSum(nums,numsSize,target,&returnSize);
	printf("%d%d",b,(b+1));
	return 0;}