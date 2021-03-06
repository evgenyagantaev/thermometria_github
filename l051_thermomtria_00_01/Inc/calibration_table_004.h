#define DATA_LENGTH 34

double H[DATA_LENGTH] = {0,0,17,15,0,17,17,17,0,15,21,13,19,21,21,17,
	    		0,0,17,14,0,13,17,17,0,18,15,15,19,19,21,21,-2,0};  // flat high temperature correction
/*
double L[DATA_LENGTH] = {0,0,21,17,0,23,20,27,0,18,22,17,25,22,24,18,
			    0,0,15,19,0,23,21,23,0,15,19,21,23,24,24,23,14,12};  // edge low temperature correction
*/
double L[DATA_LENGTH] = {0,0,27,19,0,21,22,28,0,25,23,17,30,25,30,21,
			    0,0,16,23,0,23,25,25,0,15,23,21,25,27,33,25,23,21};  // edge low temperature correction
double T0 = 1000.0;

double D[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // edge low temperature delta
double Q[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // low temperature coefficient

double K[(DATA_LENGTH-2)/2] = {1,1,158,130,1,159,155,145,1,139,190,155,128,148,158,138};  // flux coefficient
double J[(DATA_LENGTH-2)/2] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // flux offset

