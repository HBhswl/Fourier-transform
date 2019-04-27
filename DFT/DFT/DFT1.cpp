#include "DFT1.h"
#include "math.h"

DFT1::DFT1(void)
{
	m_dft_vector = NULL;
	m_has_dft_vector = false;
	m_dft_vector_size = 0;
}

DFT1::~DFT1(void) {
	if (m_has_dft_vector && (NULL != m_dft_vector) && (m_dft_vector_size > 0))
		delete[] m_dft_vector;
}

bool DFT1::has_dft_vector() {
	return m_has_dft_vector;
}

void DFT1::clear_dft_vector() {
	if (m_has_dft_vector && (NULL != m_dft_vector) && (m_dft_vector_size > 0)) {
		delete[] m_dft_vector;
		m_has_dft_vector = false;
		m_dft_vector_size = 0;
	}
}

void DFT1::print() {
	char msg[256] = "1111";

	if ((!m_has_dft_vector) || (NULL == m_has_dft_vector) || (m_dft_vector_size <= 0))
		return;

	for (int i = 0; i < m_dft_vector_size; i++) {
		printf("%d: %lf + %lfi\n", i + 1, m_dft_vector[i].m_rl, m_dft_vector[i].m_im);
	}
}

bool DFT1::dft(double vec[], int len) {
	if ((len <= 0) || (NULL == vec)) {
		return false;
	}

	clear_dft_vector();

	m_dft_vector = new CComplexNumber[len];
	for (int u = 0; u < len; u++) {
		m_dft_vector[u].setValue(0, 0);
	}

	CComplexNumber cplTemp(0, 0);
	double fixed_factor = (-2 * PI) / len;

	for (int u = 0; u < len; u++) {
		for (int x = 0; x < len; x++) {
			double power = u * x * fixed_factor;
			cplTemp.m_rl = vec[x] * cos(power);
			cplTemp.m_im = vec[x] * sin(power);
			m_dft_vector[u] = m_dft_vector[u] + cplTemp;
		}
	}
	m_has_dft_vector = true;
	m_dft_vector_size = len;

	printf("the m_dft_size = %d\n", len);
	return true;
}

bool DFT1::idft(LPVOID *pVec, int *ilen) {
	if ((!m_has_dft_vector) || (NULL == m_dft_vector) || (m_dft_vector_size <= 0))
		return false;

	*pVec = (LPVOID)new double[m_dft_vector_size];

	CComplexNumber cplTemp(0, 0);
	CComplexNumber cplResult(0, 0);

	double fixed_factor = (2 * PI) / m_dft_vector_size;

	for (int x = 0; x < m_dft_vector_size; x++) {
		for (int u = 0; u < m_dft_vector_size; u++) {
			double power = u * x * fixed_factor;
			cplTemp.setValue(cos(power), sin(power));
			cplResult = cplResult + m_dft_vector[u] * cplTemp;
		}
		((double *)*pVec)[x] = cplResult.m_rl / m_dft_vector_size;
		cplResult.setValue(0, 0);
	}

	*ilen = m_dft_vector_size;
	printf("the m_dft_size = %d\n", m_dft_vector_size);
	return true;
}