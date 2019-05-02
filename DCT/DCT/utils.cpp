#include "DCT1.h"
#include "DCT2.h"
#include <stdio.h>
#include <core/core.hpp>
#include <highgui/highgui.hpp>

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

	DCT2 dct(mat, width, height);

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

cv::Mat Rgb2Gray(cv::Mat img) {
	cv::Mat Gray(img.rows, img.cols, CV_8U, cv::Scalar(0));
	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++) {
			int r = (int)img.at<cv::Vec3b>(i, j)[0];
			int g = (int)img.at<cv::Vec3b>(i, j)[1];
			int b = (int)img.at<cv::Vec3b>(i, j)[2];
			Gray.at<uchar>(i, j) = (int)(r * 0.299 + g * 0.587 + b * 0.114);
		}
	}
	return Gray;
}

void Mat2Double(cv::Mat img, double* input, int centering) {
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (centering) {
				if ((i + j) % 2 == 0)
					input[i * img.cols + j] = (double)img.at<uchar>(i, j);
				else
					input[i * img.cols + j] = -(double)img.at<uchar>(i, j);
			}
			else {
				input[i * img.cols + j] = (double)img.at<uchar>(i, j);
			}
		}
	}
}

cv::Mat Double2Mat(double* input, int rows, int cols) {
	cv::Mat Gray(rows, cols, CV_8U, cv::Scalar(0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Gray.at<uchar>(i, j) = (int)input[i * cols + j];
		}
	}
	return Gray;
}