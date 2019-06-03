#define DATA_LENGTH 34

double H[DATA_LENGTH] = {0,0,5,17,0,17,5,18,0,15,17,12,15,17,7,5,
	    		0,0,16,16,0,13,15,15,0,16,14,15,16,11,15,0,0,5};  // flat high temperature correction
/*
double L[DATA_LENGTH] = {0,0,21,17,0,23,20,27,0,18,22,17,25,22,24,18,
			    0,0,15,19,0,23,21,23,0,15,19,21,23,24,24,23,14,12};  // edge low temperature correction
*/
double Q[DATA_LENGTH] = {0,0,0.0107,0.0100,0,0.0100,0.0027,0.0107,0,0.0080,0.0073,0.0060,0.0073,0.0060,0.0053,0.0073,
			    0,0,0.0040,0.0067,0,0.0080,0.0053,0.0080,0,0.0100,0.0060,0.0027,0.0047,0.0047,0.0067,0,0,0.0273};  // edge low temperature correction
double T0 = 1000.0;

double D[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // edge low temperature delta
double L[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // low temperature coefficient

double K[(DATA_LENGTH-2)/2] = {1,1,148,136,1,144,123,141,1,109,123,138,141,151,148,112};  // flux coefficient
double J[(DATA_LENGTH-2)/2] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // flux offset


