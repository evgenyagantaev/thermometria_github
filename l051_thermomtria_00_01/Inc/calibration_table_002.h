#define DATA_LENGTH 34

double H[DATA_LENGTH] = {0,0,535,535,0,535,535,535,0,535,535,535,535,535,535,535,
	    		0,0,535,535,0,535,535,535,0,535,535,535,535,535,535,535,3,3};  // flat high temperature correction

double L[DATA_LENGTH] = {0,0,535,535,0,535,535,535,0,535,535,535,535,535,535,535,
			    0,0,535,535,0,535,535,535,0,535,535,535,535,535,535,535,25,25};  // edge low temperature correction
double T0 = 1000.0;

double D[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // edge low temperature delta
double Q[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // low temperature coefficient

double K[(DATA_LENGTH-2)/2] = {128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128};  // flux coefficient
double J[(DATA_LENGTH-2)/2] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // flux offset
