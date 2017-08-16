#define DATA_LENGTH 34

double H[DATA_LENGTH] = {0,0,30,30,0,30,30,30,0,30,30,30,30,30,30,30,
	    		0,0,30,30,0,30,30,30,0,30,30,30,30,30,30,30,0,0};  // flat high temperature correction
/*
double L[DATA_LENGTH] = {0,0,21,17,0,23,20,27,0,18,22,17,25,22,24,18,
			    0,0,15,19,0,23,21,23,0,15,19,21,23,24,24,23,14,12};  // edge low temperature correction
*/
double L[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // edge low temperature correction
double T0 = 1000.0;

double D[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // edge low temperature delta
double Q[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // low temperature coefficient

double K[(DATA_LENGTH-2)/2] = {1,1,148,136,1,144,123,141,1,109,123,138,141,151,148,112};  // flux coefficient
double J[(DATA_LENGTH-2)/2] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // flux offset


