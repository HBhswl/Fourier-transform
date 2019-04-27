#include "DFT2.h"

void test_dft2() {
	int width = 4;
	int height = 3;

	double mat[] = { 1, 1, 3, 2, 3, 4, 123, 154, 55, 2, 22, 233 };

	DFT2 dft2;
	dft2.dft2(mat, width, height);
	dft2.print_matrix();

	dft2.generate_spectrum();
	dft2.normalize_spectrum();
	dft2.print_spectrum();

	LPVOID pMat = NULL;
	int iwidth = 0;
	int iheight = 0;

	dft2.idft2(&pMat, &iwidth, &iheight);

	double* iMat = (double*)pMat;
	if ((iwidth * iheight > 0) && (NULL != iMat)) {
		for (int x = 0; x < iheight; x++) {
			for (int y = 0; y < iwidth; y++) {
				printf("inverse fourier result %d, %d: %lf, %lf\n", x + 1, y + 1, iMat[y + x * iwidth]);
			}
		}
		delete[] iMat;
	}
}