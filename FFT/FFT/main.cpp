#include "FFT1.h"
#include <string.h>
#include <stdio.h>


int main() {
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

	return 0;
}

