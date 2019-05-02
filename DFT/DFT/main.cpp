#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <string.h>
#include "DFT2.h"
#include <ctime>
void test_dft1();
void test_dft2();
using namespace cv;

Mat Rgb2Gray(Mat img);
void Mat2Double(Mat img, double* input, int centering);
Mat Double2Mat(double* input, int rows, int cols);

int main() {
	// test_dft1();
	// test_dft2();

	// show the original picture.
	Mat img = imread("D:/My_code/C++/Fourier-transform/images/lufei.png");
	imshow("img", img);
	waitKey(0);

	// transform it to gray.
	Mat Gray = Rgb2Gray(img);
	imshow("Gray", Gray);
	waitKey(0);

	// resize the picture to suitable size.
	Mat dst;
	resize(Gray, dst, Size(128, 128));
	imshow("DST", dst);
	waitKey(0);

	int rows = dst.rows;
	int cols = dst.cols;
	double* input = new double[rows * cols];

	Mat2Double(dst, input, 0);
	DFT2 dft2;
	
	// calculate the time used
	clock_t startTime, endTime;
	startTime = clock();
	dft2.dft2(input, cols, rows);
	endTime = clock();
	printf("Time used = %lf s", (double)(endTime - startTime) / CLOCKS_PER_SEC);

	
	dft2.generate_spectrum();
	dft2.log_spectrum();
	dft2.normalize_spectrum();
	
	double* output = dft2.m_spectrum_data;
	
	dft2.get_two_part();
	double* real = dft2.real_part;
	double* imag = dft2.imaginary_part;

	dst = Double2Mat(real, rows, cols);
	imshow("real", dst);
	waitKey(0);
	
	dst = Double2Mat(imag, rows, cols);
	imshow("imag", dst);
	waitKey(0);

	dst = Double2Mat(output, rows, cols);
	imshow("spec", dst);
	waitKey(0);

	return 0;
}

