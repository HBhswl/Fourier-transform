#pragma once
#include "ComplexNumber.h"

#define MAX_VECTOR_SIZE 2048
#define PI	3.1415926
#define LPVOID void*

class DFT1 {
public:
	DFT1(void);
	~DFT1(void);

public:
	bool dft(double vec[], int len);	// 1ά����Ҷ�任
	bool idft(LPVOID *pVec, int *ilen);	// 1ά����Ҷ��任

	bool has_dft_vector();		// �Ƿ��Ѵ��б任���

	void clear_dft_vector();	// ������еı任���
	void print();				// ��ӡ�任���

public:
	CComplexNumber *m_dft_vector;	// ����任���

private:
	bool m_has_dft_vector;
	int m_dft_vector_size;			// �任����ĳ���
};