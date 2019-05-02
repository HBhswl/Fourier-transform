#include "FFT2.h"
#include "FFT1.h"
#include <cstddef>
#include <string.h>
#include <math.h>

FFT2::FFT2(void)
{
}

FFT2::FFT2(double* arr, int width, int height) {
	int num_of_all_pixels = width * height;

	cols = width;
	rows = height;

	invec = new Complex[num_of_all_pixels];
	outvec = new Complex[num_of_all_pixels];

	input = arr;
	output = new double[num_of_all_pixels];
	real = new double[num_of_all_pixels];
	imaginary = new double[num_of_all_pixels];

	memset(invec, 0, sizeof(Complex) * num_of_all_pixels);
	memset(outvec, 0, sizeof(Complex) * num_of_all_pixels);
	memset(output, 0, sizeof(double) * num_of_all_pixels);
	memset(real, 0, sizeof(double) * num_of_all_pixels);
	memset(imaginary, 0, sizeof(double) * num_of_all_pixels);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			invec[i * width + j].rl = input[i * width + j];
		}
	}
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

void FFT2::do_fft(){
	fft(invec, cols, rows, outvec);
}

void FFT2::do_ifft(){
	ifft(outvec, cols, rows, invec);
}

void FFT2::do_generate_spectrum(){
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double a = outvec[i * cols + j].rl;
			double b = outvec[i * cols + j].im;
			output[i * cols + j] = sqrt(a * a + b * b);
		}
	}
}

void FFT2::do_log_spectrum(){
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double num = output[i * cols + j];
			output[i * cols + j] = log2(num + 1);
		}
	}
}

void FFT2::do_normalize_spectrum(){
	double min = 999999;
	double max = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double num = output[i * cols + j];
			if (num > max)
				max = num;
			if (num < min)
				min = num;
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double num = output[i * cols + j];
			output[i * cols + j] = 255 * (num - min) / (max - min);
		}
	}
}