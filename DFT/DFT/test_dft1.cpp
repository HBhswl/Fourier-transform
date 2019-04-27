#include "DFT1.h"

void test_dft1() {
	char msg[256] = "11111";
	double signal[] = { 15, 32, 9, 222, 18, 151, 5, 7, 56, 233, 56, 121, 235, 89, 98, 111 };
	int len = sizeof(signal) / sizeof(double);

	DFT1 dft;
	dft.dft(signal, len);

	printf("傅里叶变换的结果为：\n");
	dft.print();

	LPVOID pVec = NULL;
	int ilen = 0;
	dft.idft(&pVec, &ilen);

	double *vec = (double *)pVec;
	if ((ilen > 0) && (NULL != vec)) {
		printf("傅里叶逆变换的结果为：\n");
		for (int x = 0; x < ilen; x++) {
			printf("idft %d: %lf\n", x + 1, vec[x]);
		}
		delete[] vec;
	}
}