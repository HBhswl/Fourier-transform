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
	bool dft(double vec[], int len);	// 1维傅里叶变换
	bool idft(LPVOID *pVec, int *ilen);	// 1维傅里叶逆变换

	bool has_dft_vector();		// 是否已存有变换结果

	void clear_dft_vector();	// 清除已有的变换结果
	void print();				// 打印变换结果

public:
	CComplexNumber *m_dft_vector;	// 保存变换结果

private:
	bool m_has_dft_vector;
	int m_dft_vector_size;			// 变换结果的长度
};