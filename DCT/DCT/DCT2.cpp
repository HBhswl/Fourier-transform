#include "DCT2.h"
#include <cstddef>
#include <math.h>
#include <stdio.h>
#include <string.h>


DCT2::DCT2(double* arr, int width, int height)
{
	int num_of_all_pixels = width * height;

	cols = width;
	rows = height;

	input = arr;
	output = new double[num_of_all_pixels];
	
	memset(output, 0, sizeof(double) * num_of_all_pixels);
}

DCT2::~DCT2(void)
{
}

bool DCT2::dct(double inVec[], int width, int height, double outVec[])
{
	if ((NULL == inVec) || (NULL == outVec))
		return false;
	if (width * height <= 0 || width * height > MAX_MATRIX_SIZE)
		return false;

	for (int i = 0; i < width * height; i++) {
		outVec[i] = 0.0;
	}

	double fix_factor_x = PI / width;
	double fix_factor_y = PI / height;

	double fix_bias_x = PI / (2 * width);
	double fix_bias_y = PI / (2 * height);

	int index = 0;
	for (int u = 0; u < width; u++) {
		for (int v = 0; v < height; v++) {
			double temp = 0.0;
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					double angle1 = u * x * fix_factor_x + u * fix_bias_x;
					double angle2 = v * y * fix_factor_y + v * fix_bias_y;

					temp += inVec[x * height + y] * cos(angle1) * cos(angle2);
				}
			}
			if (u == 0)
				temp = temp * sqrt(1.0 / width);
			else
				temp = temp * sqrt(2.0 / width);
			if (v == 0)
				temp = temp * sqrt(1.0 / height);
			else
				temp = temp * sqrt(2.0 / height);
			outVec[u * height + v] = temp;
			index += 1;
			if (index % 1000 == 0)
				printf("complete %d pixels\n", index);
		}
	}
	return true;
}

bool DCT2::idct(double inVec[], int width, int height, double outVec[])
{
	if ((NULL == inVec) || (NULL == outVec))
		return false;
	if (width * height <= 0 || width * height > MAX_MATRIX_SIZE)
		return false;

	for (int i = 0; i < width * height; i++) {
		outVec[i] = 0.0;
	}

	double fix_factor_x = PI / width;
	double fix_factor_y = PI / height;

	double fix_bias_x = PI / (2 * width);
	double fix_bias_y = PI / (2 * height);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			double temp = 0.0;
			for (int u = 0; u < width; u++) {
				for (int v = 0; v < height; v++) {
					double angle1 = u * x * fix_factor_x + u * fix_bias_x;
					double angle2 = v * y * fix_factor_y + v * fix_bias_y;

					double temp2 = inVec[u * height + v] * cos(angle1) * cos(angle2);
					
					if (u == 0)
						temp2 = temp2 * sqrt(1.0 / width);
					else
						temp2 = temp2 * sqrt(2.0 / width);
					if (v == 0)
						temp2 = temp2 * sqrt(1.0 / height);
					else
						temp2 = temp2 * sqrt(2.0 / height);

					temp += temp2;
				}
			}
			outVec[x * height + y] = temp;
		}
	}
	return true;
}

void DCT2::do_dct() {
	dct(input, cols, rows, output);
}

void DCT2::do_idct() {
	idct(output, cols, rows, input);
}

void DCT2::do_log() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double num = output[i * cols + j];
			output[i * cols + j] = log2(1 + num);
		}
	}
}

void DCT2::do_exp() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double num = output[i * cols + j];
			output[i * cols + j] = pow(2, num);
		}
	}
}

void DCT2::do_normalize() {
	double min = 999999;
	double max = -999999;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double num = output[i * cols + j];
			if (num > max)
				max = num;
			if (num < min)
				min = num;
		}
	}
	printf("the max is %lf \n", max);
	printf("the min is %lf \n", min);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double num = output[i * cols + j];
			output[i * cols + j] = 255 * (num - min) / (max - min);
		}
	}
}