/* a[0] to a[n-1] is the array to sort */

#include <stdio.h>

#define ARR_SIZE 30
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2



typedef int Status;
typedef int ElemType;

int Partition (ElemType *R, int low, int high);
void QuickSort(ElemType *R, int low, int high);

int main()
{
	int k, n;

	ElemType a[ARR_SIZE]={0};
	printf("Input the number of elements:\n");
	scanf(" %d", &n);
	
	printf("Input %d score:", n);
	
	for (k=0; k<n; k++)
	{
		scanf(" %d", &a[k]);
	}
	
	printf("The original order is:\n");
	for (k=0; k<n; k++)
	{
		printf(" %d\n", a[k]);
	}
	
	
	QuickSort(a, 0, k-1);
	
	printf("The new order is:\n");
	for (k=0; k<n; k++)
	{
		printf(" %d\n", a[k]);
	}
	
	
//    system("PAUSE");
}


int Partition (ElemType *R, int low, int high) //从大区间到小区间进行处理。 让pivot作为指标，左边小，右边大 
{
    ElemType pivot;
    pivot = R[low];
            
    while (low < high) { 
              while (low < high && R[high] >= pivot)   --high;
               R[low] = R[high];     //assign the value once     
               while (low<high && R[low]<=pivot)  ++low;
               R[high] = R[low];       
    }
    R[low] = pivot;
    return low;          //return the position of the pivot
}

void QuickSort (ElemType *R, int low, int high)
{   
	int q;         
	if (low < high) {
         q = Partition(R, low, high);
         QuickSort (R, low, q); //sort the left
         QuickSort (R, q + 1, high); //sort the right
    }
}
