#pragma once
#include "ComplexNumber.h"

#define MAX_MATRIX_SIZE 4194304
#define PI 3.1415926
#define LPVOID void*

class DFT2 {
public:
	DFT2(void);
	~DFT2(void);

public:
	bool dft2(double matrix[], int width, int height);
	bool idft2(LPVOID *pMatrix, int *width, int *height);

	void generate_spectrum();	// 对变换结果求模、生成频谱
	void log_spectrum();		// 取对数
	void normalize_spectrum();  // 对频谱进行归一化操作

	bool has_dft2_matrix();		// 是否已经存在变换结果
	bool is_shifted_to_center();// 是否已经频谱原点平移到图像中心

	void clear_dft2_matrix();	// 清楚已有的变换结果
	void print_matrix();		// 打印变换结果
	void print_spectrum();		// 打印频谱
	void shift_spectrum_to_center();	// 将频谱原点平移到图像中心

	void get_two_part();		// 得到实部和虚部谱
public:
	CComplexNumber *m_dft2_matrix;
	double* m_spectrum_data;
	double* real_part;
	double* imaginary_part;

protected:
	bool m_has_dft_matrix;
	bool m_is_normalized;
	bool m_is_spectrum_shifted;
	int m_dft_matrix_height;
	int m_dft_matrix_width;
};