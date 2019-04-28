#pragma once
#include "FFT1.h"

class FFT2 {
public:
	FFT2(void);
	~FFT2(void);

public:
	bool fft(Complex inVec[], int width, int height, Complex outVec[]);
	bool ifft(Complex inVec[], int width, int height, Complex outVec[]);

	void transpose(Complex inVec[], int width, int height);
	bool is_power_of_two(int num);
	
};