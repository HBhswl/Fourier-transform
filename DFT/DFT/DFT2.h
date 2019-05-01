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

	void generate_spectrum();	// �Ա任�����ģ������Ƶ��
	void log_spectrum();		// ȡ����
	void normalize_spectrum();  // ��Ƶ�׽��й�һ������

	bool has_dft2_matrix();		// �Ƿ��Ѿ����ڱ任���
	bool is_shifted_to_center();// �Ƿ��Ѿ�Ƶ��ԭ��ƽ�Ƶ�ͼ������

	void clear_dft2_matrix();	// ������еı任���
	void print_matrix();		// ��ӡ�任���
	void print_spectrum();		// ��ӡƵ��
	void shift_spectrum_to_center();	// ��Ƶ��ԭ��ƽ�Ƶ�ͼ������

	void get_two_part();		// �õ�ʵ�����鲿��
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