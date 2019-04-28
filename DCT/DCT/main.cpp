#include "DCT1.h"
#include "DCT2.h"
#include <stdio.h>

void test_dct1() {
	double signal[] = { 15, 32, 9, 222, 18, 151, 5, 7, 56, 233, 56, 121, 235, 89, 98, 111 };
	int size = sizeof(signal) / sizeof(double);
	
	double* outVec = new double[size];
	double* invert = new double[size];
	DCT1 dct;
	dct.dct(signal, size, outVec);

	printf("DCT变换结果如下：\n");
	for (int i = 0; i < size; i++) {
		printf("%2d : %lf\n", i, outVec[i]);
	}

	dct.idct(outVec, size, invert);
	
	printf("DCT逆变换结果如下：\n");
	for (int i = 0; i < size; i++) {
		printf("%2d : %lf\n", i, invert[i]);
	}
}

void test_dct2() {
	int width = 4;
	int height = 4;

	double mat[] = { 1, 1, 3, 2, 3, 4, 123, 154, 55, 2, 22, 233, 5, 6, 2, 7 };
	double* outVec = new double[width * height];
	double* invert = new double[width * height];

	DCT2 dct;

	dct.dct(mat, width, height, outVec);

	printf("DCT变换结果如下：\n");
	for (int i = 0; i < width * height; i++) {
		printf("%2d : %lf\n", i, outVec[i]);
	}

	dct.idct(outVec, width, height, invert);

	printf("DCT逆变换结果如下：\n");
	for (int i = 0; i < width * height; i++) {
		printf("%2d : %lf\n", i, invert[i]);
	}
}

int main() {
	// test_dct1();
	test_dct2();
	return 0;
}