#include <stdio.h>
#include <math.h>
A(int a)
{
	int sum=0,b;
	while(true){
		b==a%10;
		if(b>0){
			sum++;
			a==a/10;
		}
		else{
			break;
		}
	}
	printf("是%d位",sum);

}
/*void B(int b){
	int a[100];
	int sum=0;
	while(true){
		if((b%10)>0){
			sum++;
		}
		break;
	}
	for(int i=0;i<sum;i++){
		a[i]=b%10;
		printf("%d\n",&a[i]);
	}
	

}
void C(int c[]){
	int sum=0;
	int len1 = sizeof(c) / sizeof(c[0]);
	for(int i=0;i<len1;i++){
		sum=sum+pow(c[i],i);
	}
	printf("相加得出%d\n",sum);

}*/
int main(void){
	int a,b,c[100],d;
	printf("输入想判断位数的数字"); 
	scanf("%d",&a);
	/*&printf("输入想输出每一位的数字");
	scanf("%d",&b);
	printf("输入想输出几位数的整数");
	scanf("%d",&d);
	printf("输入想合成一个整数数的数字");
		for(int i=0;i<d;i++){
			scanf("%d",&c[i]);
		}*/
		A(a);
		/*B(b);
		C(c);*/
		return 0;
}















