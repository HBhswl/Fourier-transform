#include "DCT2.h"
#include <cstddef>
#include <math.h>
#include <stdio.h>

DCT2::DCT2(void)
{
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

