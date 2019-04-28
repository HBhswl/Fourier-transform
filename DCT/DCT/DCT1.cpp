#include "DCT1.h"
#include <cstddef>
#include <math.h>
#include <stdio.h>

DCT1::DCT1(void){

}

DCT1::~DCT1(void) {

}

bool DCT1::dct(double inVec[], int size, double outVec[]) {
	if ((NULL == inVec) || (NULL == outVec))
		return false;
	if (size <= 0)
		return false;

	for (int i = 0; i < size; i++) {
		outVec[i] = 0.0;
	}

	double fix_factor = PI / size;
	double fix_bias = PI / (2 * size);

	for (int u = 0; u < size; u++) {
		for (int x = 0; x < size; x++) {
			double angle = u * x * fix_factor + u * fix_bias;
			double temp = inVec[x] * cos(angle);
			if (u == 0)
				outVec[u] = outVec[u] + temp * sqrt(1.0 / size);
			else
				outVec[u] = outVec[u] + temp * sqrt(2.0 / size);
		}
	}

	return true;
}


bool DCT1::idct(double inVec[], int size, double outVec[]) {
	if ((NULL == inVec) || (NULL == outVec))
		return false;
	if (size <= 0)
		return false;

	for (int i = 0; i < size; i++) {
		outVec[i] = 0.0;
	}

	double fix_factor = PI / size;
	double fix_bias = PI / (2 * size);

	for (int x = 0; x < size; x++) {
		for (int u = 0; u < size; u++) {
			double angle = u * x * fix_factor + u * fix_bias;
			double temp = inVec[u] * cos(angle);
			if (u == 0)
				outVec[x] += temp * sqrt(1.0 / size);
			else
				outVec[x] += temp * sqrt(2.0 / size);
		}
	}

	return true;
}
