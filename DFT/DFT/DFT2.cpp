#include "DFT2.h"
#include "math.h"
#include "string.h"

DFT2::DFT2(void)
{
	m_dft2_matrix = NULL;
	m_spectrum_data = NULL;
	m_has_dft_matrix = false;
	m_is_normalized = false;
	m_is_spectrum_shifted = false;
	m_dft_matrix_height = 0;
	m_dft_matrix_width = 0;
}

DFT2::~DFT2(void) {
	if (m_has_dft_matrix && (NULL != m_dft2_matrix) && (m_dft_matrix_height * m_dft_matrix_width > 0)) {
		delete[] m_dft2_matrix;
	}
	if (NULL != m_spectrum_data)
		delete[] m_spectrum_data;
}

bool DFT2::has_dft2_matrix()
{
	return m_has_dft_matrix;
}
bool DFT2::is_shifted_to_center()
{
	return m_is_spectrum_shifted;
}

void DFT2::clear_dft2_matrix() {
	if (m_has_dft_matrix && (NULL != m_dft2_matrix) && (m_dft_matrix_height * m_dft_matrix_width > 0)) {
		delete[] m_dft2_matrix;
		m_has_dft_matrix = false;
		m_dft_matrix_height = 0;
		m_dft_matrix_width = 0;
	}
}


void DFT2::print_matrix()
{
	if ((!m_has_dft_matrix) || (NULL == m_dft2_matrix) || (m_dft_matrix_height <= 0) || (m_dft_matrix_width <= 0))
		return;

	for (int u = 0; u < m_dft_matrix_height; u++) {
		for (int v = 0; v < m_dft_matrix_width; v++) {
			printf("[%d,%d]: %lf + %lfi\n", u + 1, v + 1, m_dft2_matrix[v + u * m_dft_matrix_width].m_rl, m_dft2_matrix[v + u * m_dft_matrix_width].m_im);
		}
	}
}

void DFT2::print_spectrum()
{
	char msg[256] = "11111 ";

	if ((!m_has_dft_matrix) || (NULL == m_dft2_matrix) || (m_dft_matrix_height <= 0) || (m_dft_matrix_width <= 0) || (NULL == m_spectrum_data))
		return;

	for (int u = 0; u < m_dft_matrix_height; u++) {
		for (int v = 0; v < m_dft_matrix_width; v++) {
			printf("[%d,%d]: %lf\n", u + 1, v + 1, m_spectrum_data[v + u * m_dft_matrix_width]);
		}
	}
}

bool DFT2::dft2(double matrix[], int width, int height) {
	if ((width * height <= 0) || ((width * height > MAX_MATRIX_SIZE)))
		return false;

	clear_dft2_matrix();

	m_dft2_matrix = new CComplexNumber[width * height];
	CComplexNumber cplTemp(0, 0);
	double fixed_factor_for_axisX = (-2 * PI) / height;
	double fixed_factor_for_axisY = (-2 * PI) / width;

	int index = 0;
	for (int u = 0; u < height; u++) {
		for (int v = 0; v < width; v++) {
			for (int x = 0; x < height; x++) {
				for (int y = 0; y < width; y++) {
					double powerX = u * x * fixed_factor_for_axisX;
					double powerY = v * y * fixed_factor_for_axisY;
					cplTemp.m_rl = matrix[y + x * width] * cos(powerX + powerY);
					cplTemp.m_im = matrix[y + x * width] * sin(powerX + powerY);
					m_dft2_matrix[v + u * width] = m_dft2_matrix[v + u * width] + cplTemp;
				}
			}
			index += 1;
			printf("Complete %d pixels\n", index);
		}
	}

	m_has_dft_matrix = true;
	m_dft_matrix_height = height;
	m_dft_matrix_width = width;
	return true;
}

bool DFT2::idft2(LPVOID* pMatrix, int* width, int* height)
{
	if ((!m_has_dft_matrix) || (NULL == m_dft2_matrix) || ((m_dft_matrix_height * m_dft_matrix_width) <= 0) || (!width) || (!height))
		return false;

	if (*pMatrix)
		delete[] * pMatrix;
	*pMatrix = (LPVOID)new double[m_dft_matrix_height * m_dft_matrix_width];

	CComplexNumber   cplTemp(0, 0);
	CComplexNumber   cplResult(0, 0);
	double fixed_factor_for_axisX = (2 * PI) / m_dft_matrix_height;                  // evaluate i2¦Ð/N of i2¦Ðux/N, and store the value for computing efficiency
	double fixed_factor_for_axisY = (2 * PI) / m_dft_matrix_width;                   // evaluate i2¦Ð/N of i2¦Ðux/N, and store the value for computing efficiency
	for (int x = 0; x < m_dft_matrix_height; x++) {
		for (int y = 0; y < m_dft_matrix_width; y++) {
			for (int u = 0; u < m_dft_matrix_height; u++) {
				for (int v = 0; v < m_dft_matrix_width; v++) {
					double powerU = u * x * fixed_factor_for_axisX;         // evaluate i2¦Ðux/N
					double powerV = v * y * fixed_factor_for_axisY;         // evaluate i2¦Ðux/N
					cplTemp.setValue(cos(powerU + powerV), sin(powerU + powerV));
					cplResult = cplResult + m_dft2_matrix[v + u * m_dft_matrix_width] * cplTemp;
				}
			}
			((double*)* pMatrix)[y + x * m_dft_matrix_width] = cplResult.m_rl / (m_dft_matrix_height * m_dft_matrix_width);
			cplResult.setValue(0, 0);
		}
	}

	// now we have the inverse transformed matrix, keep the info
	printf("inverse fourier result: %lX", pMatrix);
	*width = m_dft_matrix_width;
	*height = m_dft_matrix_height;
	return true;
}

void DFT2::generate_spectrum() {
	if (m_has_dft_matrix && (NULL != m_dft2_matrix) && (m_dft_matrix_height * m_dft_matrix_width > 0)) {
		if (NULL != m_spectrum_data) {
			delete[] m_spectrum_data;
			m_is_spectrum_shifted = false;
		}
		m_spectrum_data = new double[m_dft_matrix_height * m_dft_matrix_width];
		for (int u = 0; u < m_dft_matrix_height; u++) {
			for (int v = 0; v < m_dft_matrix_width; v++) {
				double a = m_dft2_matrix[v + u * m_dft_matrix_width].m_rl * m_dft2_matrix[v + u * m_dft_matrix_width].m_rl;
				double b = m_dft2_matrix[v + u * m_dft_matrix_width].m_im * m_dft2_matrix[v + u * m_dft_matrix_width].m_im;
				m_spectrum_data[v + u * m_dft_matrix_width] = sqrt(a + b);
			}
		}
	}
}

void DFT2::log_spectrum() {
	for (int u = 0; u < m_dft_matrix_height; u++) {
		for (int v = 0; v < m_dft_matrix_width; v++) {
			m_spectrum_data[v + u * m_dft_matrix_width] = log2(m_spectrum_data[v + u * m_dft_matrix_width] + 1);
		}
	}
}

void DFT2::normalize_spectrum() {
	if (m_has_dft_matrix && (NULL != m_dft2_matrix) && ((m_dft_matrix_height * m_dft_matrix_width) > 0) && ((NULL != m_spectrum_data))) {
		// get max value
		double max = 0;
		double min = 0;
		for (int u = 0; u < m_dft_matrix_height; u++) {
			for (int v = 0; v < m_dft_matrix_width; v++) {
				if (m_spectrum_data[v + u * m_dft_matrix_width] > max) {
					max = m_spectrum_data[v + u * m_dft_matrix_width];
				}
				if (m_spectrum_data[v + u * m_dft_matrix_width] < min) {
					min = m_spectrum_data[v + u * m_dft_matrix_width];
				}
			}
		}

		
	
		for (int u = 0; u < m_dft_matrix_height; u++) {
			for (int v = 0; v < m_dft_matrix_width; v++) {
				m_spectrum_data[v + u * m_dft_matrix_width] = 255 * (m_spectrum_data[v + u * m_dft_matrix_width] - min) / (max - min);
			}
		}

		m_is_normalized = true;
	}
	else
		m_is_normalized = false;
}


void DFT2::shift_spectrum_to_center()
{
	if (m_is_spectrum_shifted)
		return;
	if (m_has_dft_matrix && (NULL != m_dft2_matrix) && ((m_dft_matrix_height * m_dft_matrix_width) > 0) && ((NULL != m_spectrum_data))) {
		double* tempData = new double[m_dft_matrix_height * m_dft_matrix_width];
		memcpy(tempData, m_spectrum_data, m_dft_matrix_height * m_dft_matrix_width * sizeof(double));
		//ÒÆµ½ÖÐÐÄ  

		for (int u = 0; u < m_dft_matrix_height; u++) {
			for (int v = 0; v < m_dft_matrix_width; v++) {
				if ((u < (m_dft_matrix_height / 2)) && (v < (m_dft_matrix_width / 2))) {
					m_spectrum_data[v + u * m_dft_matrix_width] =
						tempData[m_dft_matrix_width / 2 + v + (m_dft_matrix_height / 2 + u) * m_dft_matrix_width];
				}
				else if ((u < (m_dft_matrix_height / 2)) && (v >= (m_dft_matrix_width / 2))) {
					m_spectrum_data[v + u * m_dft_matrix_width] =
						tempData[(v - m_dft_matrix_width / 2) + (m_dft_matrix_height / 2 + u) * m_dft_matrix_width];
				}
				else if ((u >= (m_dft_matrix_height / 2)) && (v < (m_dft_matrix_width / 2))) {
					m_spectrum_data[v + u * m_dft_matrix_width] =
						tempData[(m_dft_matrix_width / 2 + v) + (u - m_dft_matrix_height / 2) * m_dft_matrix_width];
				}
				else if ((u >= (m_dft_matrix_height / 2)) && (v >= (m_dft_matrix_width / 2))) {
					m_spectrum_data[v + u * m_dft_matrix_width] =
						tempData[(v - m_dft_matrix_width / 2) + (u - m_dft_matrix_height / 2) * m_dft_matrix_width];
				}
			}
		}
		m_is_spectrum_shifted = true;

		if (tempData)
			delete[] tempData;
	}
}

void DFT2::get_two_part() {
	real_part = new double[m_dft_matrix_height * m_dft_matrix_width];
	imaginary_part = new double[m_dft_matrix_height * m_dft_matrix_width];
	for (int i = 0; i < m_dft_matrix_height; i++) {
		for (int j = 0; j < m_dft_matrix_width; j++) {
			real_part[i * m_dft_matrix_width + j] = m_dft2_matrix[i * m_dft_matrix_width + j].m_rl;
			imaginary_part[i * m_dft_matrix_width + j] = m_dft2_matrix[i * m_dft_matrix_width + j].m_im;
		}
	}
}