#pragma once

#define MAX_MATRIX_SIZE 2048 * 2048
#define PI 3.1415926

class DCT2 {
public:
	DCT2(double* arr, int width, int height);
	~DCT2(void);

public:
	bool dct(double inVec[], int width, int height, double outVec[]);
	bool idct(double inVec[], int width, int height, double outVec[]);

	void do_dct();
	void do_idct();
	void do_log();
	void do_exp();
	void do_normalize(double maxNumber);
	void do_translation();

public:
	double* input;
	double* output;

	int rows;
	int cols;

};