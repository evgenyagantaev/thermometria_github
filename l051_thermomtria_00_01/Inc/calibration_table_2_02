#define DATA_LENGTH 34

double H[DATA_LENGTH] = {0,0,17,17,0,17,17,17,0,17,17,17,17,17,17,17,
	    		0,0,17,17,0,17,17,17,0,17,17,17,17,17,17,17,0,0};  // flat high temperature correction

double L[DATA_LENGTH] = {0,0,17+5,17+8,0,17+14,17+8,17+8,0,17,17+14,17+14,17+14,17+13,17+9,17+7,
				0,0,17+14,17+10,0,17+10,17+12,17+8,0,17+13,17+12,17+9,17+12,17+17,17+11,17+7,0,0};  // edge low temperature correction

double T0 = 1000.0;

double D[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // edge low temperature delta
double Q[DATA_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // low temperature coefficient

double K[(DATA_LENGTH-2)/2] = {1,1,158,130,1,159,155,145,1,139,190,155,128,148,158,138};  // flux coefficient
double J[(DATA_LENGTH-2)/2] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // flux offset

//		D[i] = L[i] - H[i];
//		Q[i] = D[i]/(T0+500);		// correction on -5 Celsius

// calibrate
		/*
		for (i = 0; i < (DATA_LENGTH-2); i++)
		{
			if(fill_buffer[i] >= T0)
			{
				fill_buffer[i] = (int32_t)(fill_buffer[i] - H[i]);
			}
			else // t < T0
				fill_buffer[i] = (int32_t)(fill_buffer[i] -(H[i] + (T0-t)*Q[i]));
		}		fill_buffer[DATA_LENGTH - 2] = (int32_t)(t -(H[DATA_LENGTH - 2] + (T0-t)*Q[DATA_LENGTH - 2]));
*/
