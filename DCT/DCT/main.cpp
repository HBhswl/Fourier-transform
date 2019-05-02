#include "DCT1.h"
#include "DCT2.h"
#include <stdio.h>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <ctime>

using namespace cv;

void test_dct1();
void test_dct2();
Mat Rgb2Gray(Mat img);
void Mat2Double(Mat img, double* input, int centering);
Mat Double2Mat(double* input, int rows, int cols);
void processing(double* input, int rows, int cols, double ave);


int main() {
	// test_dct1();
	// test_dct2();

	// show the original picture
	
	Mat img = imread("D:/My_code/C++/Fourier-transform/images/lufei.png");
	imshow("img", img);
	waitKey(0);

	// transform it to gray
	Mat Gray = Rgb2Gray(img);
	imshow("Gray", Gray);
	waitKey(0);

	// resize the picture to sutable size.
	Mat dst;
	resize(Gray, dst, Size(256, 256));
	imshow("DST", dst);
	waitKey(0);

	int rows = dst.rows;
	int cols = dst.cols;
	double* input = new double[rows * cols];

	Mat2Double(dst, input, 0);
	DCT2 dct2(input, cols, rows);

	clock_t startTime, endTime;
	startTime = clock();
	dct2.do_dct();
	endTime = clock();
	printf("Time used = %lf s\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	
	// dct2.do_translation();
	// dct2.do_log();
	// dct2.do_normalize(1);
	// dct2.do_exp();
	dct2.do_normalize(255);

	double* output = dct2.output;

	double total = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// printf("%.1f ", output[i * cols + j]);
			total += output[i * cols + j];
		}
		printf("\n");
	}
	// printf("ave = %lf \n", total / cols / rows);
	processing(output, rows, cols, total / cols / rows);
	

	dst = Double2Mat(output, rows, cols);
	imshow("spec", dst);
	waitKey(0);

	return 0;
}