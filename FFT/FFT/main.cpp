#include "FFT1.h"
#include "FFT2.h"
#include <string.h>
#include <stdio.h>

void test_fft1() {
	double vec[] = { 15, 32, 9, 222, 118, 151, 5, 7, 56, 233, 56, 121, 235, 89, 98, 111 };
	int len = sizeof(vec) / sizeof(double);

	Complex* inVec = new Complex[len];
	Complex* outVec = new Complex[len];
	Complex* invert = new Complex[len];

	memset(inVec, 0, len * sizeof(Complex));
	for (int i = 0; i < len; i++)
		inVec[i].rl = vec[i];

	// Fourier transformation
	FFT1 t;
	t.fft(inVec, len, outVec);

	// print result
	printf("���ٸ���Ҷ�任���Ϊ��\n");
	for (int i = 0; i < len; i++) {
		if (outVec[i].im < 0)
			printf("result[%d]: %lf - %lfi\n", i + 1, outVec[i].rl, -outVec[i].im);
		else
			printf("result[%d]: %lf + %lfi\n", i + 1, outVec[i].rl, outVec[i].im);
	}

	printf("11111 ��任���Ϊ��");
	t.ifft(outVec, len, invert);
	for (int i = 0; i < len; i++) {
		printf("ifft[%d]: %lf\n", i + 1, invert[i].rl);
	}

	delete[] inVec;
	delete[] outVec;
	delete[] invert;
}

void test_fft2() {
	int width = 4;
	int height = 4;

	double mat[] = {1, 1, 3, 2, 3, 4, 123, 154, 55, 2, 22, 233, 5, 6, 2, 7};

	Complex* inVec = new Complex[width * height];
	Complex* outVec = new Complex[width * height];
	Complex* invert = new Complex[width * height];

	memset(inVec, 0, width * height * sizeof(Complex));
	for (int i = 0; i < width * height; i++)
		inVec[i].rl = mat[i];

	// Fourier transformation
	FFT2 t;
	t.fft(inVec, width, height, outVec);

	// print result
	printf("���ٸ���Ҷ�任���Ϊ��\n");
	for (int i = 0; i < width * height; i++) {
		if (outVec[i].im < 0)
			printf("result[%d]: %lf - %lfi\n", i + 1, outVec[i].rl, -outVec[i].im);
		else
			printf("result[%d]: %lf + %lfi\n", i + 1, outVec[i].rl, outVec[i].im);
	}
}

int main() {
	test_fft2();
	// test_fft1();
	return 0;
}

