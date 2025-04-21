// li82.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double Foods[] = { 
						1.23, 2.34, 1.12, 1.45, 5.81, 5.13, 2.45, 5.86, 6.93, 2.72,
						0.61, 0.26, 0.91, 0.83, 0.34, 0.44, 0.61, 0.25, 0.19, 0.34,
						1.51, 3.63, 0.31, 6.53, 3.84, 5.24, 0.41, 2.95, 3.88, 3.39,
						0.51, 0.66, 0.31, 0.53, 0.84, 0.24, 0.41, 0.95, 0.88, 0.39,
						3.61, 3.26, 0.91, 3.83, 3.34, 3.44, 0.61, 5.25, 0.18, 5.34
};

const int  ptop =  10;
int	bestp[50];

void pbestsort()
{
	int i, j, temp;

    for(i = 0; i < 50; i++){
		bestp[i] = i;
	}

	for( i = 0; i < ptop; i++ )
	    for(j = i + 1; j < 50; j++){
		
			if (Foods[bestp[j]] < Foods[bestp[i]]){
				temp = bestp[i];
				bestp[i] = bestp[j];
				bestp[j] = temp;
			}
		}
}

void SwapElite(int x, int y)
{
	int j;
	double temp;

	temp = Foods[x];	Foods[x] = Foods[y];	Foods[y] = temp;
}

void MigrationElite()
{
	int i, j, k;
	int	flagM[10], flagTop[10];

	for(i = 0; i < ptop; i++){
		flagM[i] = 0;
		flagTop[i] = 0;
	}

	for(i = 0; i < ptop; i++){
		if(bestp[i] > 19 && bestp[i] < 30){
			flagTop[i] = 1;
			flagM[bestp[i] - 20] = 1;
		}
	}

	j = k = 0;
	while(j < 10 && k < 10){
		while( flagM[j] && j < 10 )
			j++;
		while( flagTop[k] && k < 10 )
			 k++;
		if (j < 10 && k < 10)
		{
			SwapElite(j + 20, bestp[k]);
			flagTop[k++] = 1;
			flagM[j++] = 1;
		}
	}
}
 
int main(int argc, char* argv[])
{
	int i;

	for( i = 0; i < 50; i++ )
	{
		cout << Foods[i] << "    " ;
		if( i % 10 == 9 )
			cout << endl;
	}
	cout << endl;
	pbestsort();
	MigrationElite();

	for( i = 0; i < 50; i++ )
	{
		cout << Foods[i] << "    " ;
		if( i % 10 == 9 )
			cout << endl;
	}

	return 0;
}

