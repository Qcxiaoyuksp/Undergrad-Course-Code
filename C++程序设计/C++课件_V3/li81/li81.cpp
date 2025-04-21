// li81.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double Pd = 0.6;
const int D = 30;
double EliteMean[] = { 
						0.23, 0.34, 0.12, 0.45, 0.81, 0.13, 0.45, 0.86, 0.93, 0.72,
						0.61, 0.26, 0.91, 0.83, 0.34, 0.44, 0.61, 0.25, 0.18, 0.34,
						0.51, 0.66, 0.31, 0.53, 0.84, 0.24, 0.41, 0.95, 0.88, 0.39
};
double Foods[] = { 
						1.51, 3.63, 0.31, 6.53, 3.84, 5.24, 0.41, 2.95, 3.88, 3.39,
						1.23, 2.34, 1.12, 1.45, 5.81, 5.13, 2,45, 5.86, 6.93, 2.72,
						3.61, 3.26, 0.91, 3.83, 3.34, 3.44, 0.61, 5.25, 0.18, 5.34
};

void SelectionDimension( )
{
	int i, j, k, dim;
	int flagd[D], topd[D], SelDim;
	double r, max, temp;

	SelDim = int( D * Pd );
	if( SelDim < 1 )
		SelDim = 1;
	
	for(j = 0; j < D; j++)
		flagd[j] = 1;

	for(i = 0; i < SelDim; i++){

		for(j = 0; j < D; j++)								// Initialize the reference dimension
			if( flagd[j] ){
				max = fabs( EliteMean[j] - Foods[j] );
				dim = j;
				j = D;
			}

		for(j = 0; j < D; j++){
			temp = fabs( EliteMean[j] - Foods[j] );

			if( max < temp && flagd[j] ){
				max = temp;
				dim = j;
			}
		}
		cout << "    Dim = " << dim << "  EliteMean - Foods =  " << max << endl;  
		topd[i] = dim; flagd[dim] = 0;
	}
	cout << endl;

}
int main()
{

	SelectionDimension( );
	
	return 0;
}