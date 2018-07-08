#ifndef COMPLEX_H_INCLUDED_
#define COMPLEX_H_INCLUDED_

#include "general.h"

class Complex {
public:
	real r, i; 
	Complex(void) { }
	Complex(real a, real b) { r=a; i=b; }
	inline const Complex operator+(const Complex &c) const {
		return Complex( r + c.r, i + c.i);
	}
	inline const Complex operator-(const Complex &c) const {
		return Complex( r - c.r, i - c.i);
	}	
	inline const Complex operator*(const Complex &c) const {
		return Complex( r*c.r - i*c.i, r*c.i + i*c.r);
	}
	inline const Complex operator/(const real &divisor) const {
		return Complex( r/divisor, i/divisor);
	}

};

inline const Complex conj(const Complex &c) {
	return Complex( c.r, -c.i);
}

#endif
