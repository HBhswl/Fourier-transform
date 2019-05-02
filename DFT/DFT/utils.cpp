#include <core/core.hpp>
#include <highgui/highgui.hpp>

using namespace cv;

Mat Rgb2Gray(Mat img) {
	Mat Gray(img.rows, img.cols, CV_8U, Scalar(0));
	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++) {
			int r = (int)img.at<Vec3b>(i, j)[0];
			int g = (int)img.at<Vec3b>(i, j)[1];
			int b = (int)img.at<Vec3b>(i, j)[2];
			Gray.at<uchar>(i, j) = (int)(r * 0.299 + g * 0.587 + b * 0.114);
		}
	}
	return Gray;
}

void Mat2Double(Mat img, double* input, int centering) {
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

Mat Double2Mat(double* input, int rows, int cols) {
	Mat Gray(rows, cols, CV_8U, Scalar(0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Gray.at<uchar>(i, j) = (int)input[i * cols + j];
		}
	}
	return Gray;
}