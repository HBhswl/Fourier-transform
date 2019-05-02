#pragma once
#include "FFT1.h"

class FFT2 {
public:
	FFT2(void);
	FFT2(double* arr, int width, int height);
	~FFT2(void);

public:
	bool fft(Complex inVec[], int width, int height, Complex outVec[]);
	bool ifft(Complex inVec[], int width, int height, Complex outVec[]);

	void do_fft();
	void do_ifft();
	void do_generate_spectrum();
	void do_log_spectrum();
	void do_normalize_spectrum();

	void transpose(Complex inVec[], int width, int height);
	bool is_power_of_two(int num);

public:
	Complex* invec;
	Complex* outvec;

	double* input;
	double* output;
	double* real;
	double* imaginary;

	int rows;
	int cols;
};