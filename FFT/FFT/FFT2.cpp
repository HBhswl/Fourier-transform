#include "FFT2.h"
#include "FFT1.h"
#include <cstddef>
#include <string.h>
#include <math.h>

FFT2::FFT2(void)
{
}

FFT2::~FFT2(void)
{
}

bool FFT2::is_power_of_two(int num) {
	int temp = num;
	int mod = 0;
	int result = 0;

	if (num < 2)
		return false;
	if (num == 2)
		return true;

	while (temp > 1) {
		result = temp / 2;
		mod = temp % 2;
		if (mod)
			return false;
		if (2 == result)
			return true;
		temp = result;
	}
	return false;
}

void FFT2::transpose(Complex inVec[], int width, int height) {
	Complex* copy = new Complex[width * height];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			copy[i * width + j] = inVec[j * height + i];
		}
	}
	
	memcpy(inVec, copy, width * height * sizeof(Complex));
}

bool FFT2::fft(Complex inVec[], int width, int height, Complex outVec[]) {
	if ((NULL == inVec) || (NULL == outVec))
		return false;
	if ((width * height <= 0) || (width * height > MAX_MATRIX_SIZE))
		return false;
	if (!is_power_of_two(width) || !is_power_of_two(height))
		return false;
	FFT1 t;
	Complex * copy = new Complex[width * height];
	Complex * temp = new Complex[width * height];
	memcpy(copy, inVec, width * height * sizeof(Complex));

	Complex * line = new Complex[width];
	Complex * outLine = new Complex[width];
	for (int i = 0; i < height; i++) {
		memcpy(line, copy + i * width, width * sizeof(Complex));
		t.fft(line, width, outLine);
		memcpy(copy + i * width, outLine, width * sizeof(Complex));
	}

	transpose(copy, width, height);

	Complex* row = new Complex[height];
	Complex* outRow = new Complex[height];
	for (int i = 0; i < width; i++) {
		memcpy(row, copy + i * height, height * sizeof(Complex));
		t.fft(row, height, outRow);
		memcpy(copy + i * height, outRow, height * sizeof(Complex));
	}

	transpose(copy, height, width);
	memcpy(outVec, copy, width * height * sizeof(Complex));

	delete[] copy;
	delete[] line;
	delete[] outLine;
	delete[] row;
	delete[] outRow;

	return true;
}

bool FFT2::ifft(Complex inVec[], int width, int height, Complex outVec[])
{
	if ((NULL == inVec) || (NULL == outVec))
		return false;
	if ((width * height <= 0) || (width * height > MAX_MATRIX_SIZE))
		return false;
	if (!is_power_of_two(width) || !is_power_of_two(height))
		return false;
	FFT1 t;
	Complex * copy = new Complex[width * height];
	Complex * temp = new Complex[width * height];
	memcpy(copy, inVec, width * height * sizeof(Complex));

	Complex * line = new Complex[width];
	Complex * outLine = new Complex[width];
	for (int i = 0; i < height; i++) {
		memcpy(line, copy + i * width, width * sizeof(Complex));
		t.ifft(line, width, outLine);
		memcpy(copy + i * width, outLine, width * sizeof(Complex));
	}

	transpose(copy, width, height);

	Complex* row = new Complex[height];
	Complex* outRow = new Complex[height];
	for (int i = 0; i < width; i++) {
		memcpy(row, copy + i * height, height * sizeof(Complex));
		t.ifft(row, height, outRow);
		memcpy(copy + i * height, outRow, height * sizeof(Complex));
	}

	transpose(copy, height, width);
	memcpy(outVec, copy, width * height * sizeof(Complex));

	delete[] copy;
	delete[] line;
	delete[] outLine;
	delete[] row;
	delete[] outRow;

	return true;
}

