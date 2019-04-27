#pragma once

#define MAX_MATRIX_SIZE 4194304
#define PI 3.141592653
#define MAX_VECTOR_SIZE 10000

typedef struct Complex {
	double rl;
	double im;
}Complex;

class FFT1 {
public:
	FFT1(void);
	~FFT1(void);

public:
	bool fft(Complex inVec[], int len, Complex outVec[]);
	bool ifft(Complex inVec[], int len, Complex outVec[]);

	bool is_power_of_two(int num);
	int get_computation_layers(int num);
};