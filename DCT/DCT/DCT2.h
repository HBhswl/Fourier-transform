#pragma once

#define MAX_MATRIX_SIZE 2048 * 2048
#define PI 3.1415926

class DCT2 {
public:
	DCT2(void);
	~DCT2(void);

public:
	bool dct(double inVec[], int width, int height, double outVec[]);
	bool idct(double inVec[], int width, int height, double outVec[]);
};