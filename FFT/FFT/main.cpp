#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <string.h>
#include "FFT2.h"
#include <ctime>

using namespace cv;

void test_fft2();
void test_fft1();
Mat Rgb2Gray(Mat img);
void Mat2Double(Mat img, double* input, int centering);
Mat Double2Mat(double* input, int rows, int cols);

int main() {
	// test_fft2();
	// test_fft1();

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

	Mat2Double(dst, input, 1);
	FFT2 fft2(input, cols, rows);

	clock_t startTime, endTime;
	startTime = clock();
	fft2.do_fft();
	endTime = clock();
	printf("Time used = %lf s", (double)(endTime - startTime) / CLOCKS_PER_SEC);

	fft2.do_generate_spectrum();
	fft2.do_log_spectrum();
	fft2.do_normalize_spectrum();

	double* output = fft2.output;
	
	dst = Double2Mat(output, rows, cols);
	imshow("spec", dst);
	waitKey(0);

	return 0;
}

