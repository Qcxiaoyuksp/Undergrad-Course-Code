#include<stdio.h>
int main(){
	
	int i,n,max;
	printf("请输入数字个数：");
	scanf("%d",&n);
	int a[n];
	printf ("请输入需要判断的数字：");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	max=a[0];
	for(i=1;i<n;i++){
		if(max<a[i]){
			max=a[i];
		}
	}
	printf("最大数是%d",max);
	return 0;
} 
