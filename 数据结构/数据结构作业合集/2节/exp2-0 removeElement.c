#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/**
 *  基本方法与双指针法.
 */
int removeElement(int* nums, int numsSize, int val);
int removeElementS(int* nums, int numsSize, int val);

main()
{
	
	char c;
	int i, j;
	int nums[] = { 0, 1, 2, 2, 3, 0, 4, 2 };
	int val, numsSize=8;
	printf("Elements are:");
	for (i = 0; i<numsSize; i++){
		printf("%d ", nums[i]);
	}
	printf("\n");
	while (1){
		printf("remove an element by array\n");
		printf("=====================================================\n");
		printf("1. removeElement by two pointers; 2. removeElement by nested loops; 0. Exit; \n ");
		printf("=====================================================\n");

		scanf(" %c", &c);//fflush(stdin); 

		switch (c){

		case '1':
			printf("Input the removed element:\n");
			scanf(" %d", &val);
			numsSize = removeElement(nums, numsSize, val);
			printf("Elements are:");
			for (i = 0; i<numsSize; i++){
				printf("%d ", nums[i]);
			}
			printf("\n");
			printf("The new numsSize is:%d\n", numsSize);
			break;
		case '2':
			printf("Input the removed element:\n");
			scanf(" %d", &val);
			numsSize = removeElementS(nums, numsSize, val);
			printf("Elements are:");
			for (i = 0; i<numsSize; i++){
				printf("%d ", nums[i]);
			}
			printf("\n");
			printf("The new numsSize is:%d\n", numsSize);
			break;
		case '0':exit(0);
		default:
			printf("Print an incorrect letter;\n");
			break;
		}

	}
	system("PAUSE");

}

int removeElement(int* nums, int numsSize, int val){
	int slowIndex = 0, fastIndex;

	return slowIndex;
}



int removeElementS(int* nums, int numsSize, int val){
	int i, j;
	int Size;


	return Size;
}

