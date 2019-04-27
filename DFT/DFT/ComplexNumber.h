#pragma once
# include <stdio.h>

class CComplexNumber
{
public:
	CComplexNumber(double rl, double im);
	CComplexNumber(void);
	~CComplexNumber(void);

public:
	double m_rl;	// real part
	double m_im;	// imagery part

public:
	// 重载四则运算符号
	inline CComplexNumber operator +(const CComplexNumber &c) {
		return CComplexNumber(m_rl + c.m_rl, m_im + c.m_im);
	}

	inline CComplexNumber operator -(const CComplexNumber &c) {
		return CComplexNumber(m_rl - c.m_rl, m_im - c.m_im);
	}

	inline CComplexNumber operator *(const CComplexNumber &c) {
		return CComplexNumber(m_rl * c.m_rl - m_im * c.m_im, m_rl * c.m_im + m_im * c.m_rl);
	}

	inline CComplexNumber operator /(const CComplexNumber &c) {
		if ((0 == c.m_im) && (0 == c.m_rl)) {
			printf("divide 0 error!");
			return CComplexNumber(m_rl, m_im);
		}
		return CComplexNumber((m_rl * c.m_rl + m_im * c.m_im) / (c.m_im * c.m_im + c.m_rl * c.m_rl),
			(m_im * c.m_rl - m_rl * c.m_im) / (c.m_im * c.m_im + c.m_rl * c.m_rl)
		);
	}

	void setValue(double rl, double im);
};