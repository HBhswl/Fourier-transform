#pragma once

#define MAX_VECTOR_SIZE 10000
#define PI 3.1415926

class DCT1 {
public:
	DCT1(void);
	~DCT1(void);

public:
	bool dct(double inVec[], int size, double outVec[]);
	bool idct(double inVec[], int size, double outVec[]);
};