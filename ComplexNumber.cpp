#include "pch.h"
#include "ComplexNumber.h"
#include <iostream>

ComplexNumber::ComplexNumber() {
	re = 0;
	im = 0;
}

ComplexNumber::ComplexNumber(double x) {
	re = x;
	im = 0;
}

ComplexNumber::ComplexNumber(double x, double y) {
	re = x;
	im = y;
}

ComplexNumber::ComplexNumber(const ComplexNumber& c) {
	re = c.re;
	im = c.im;
}

std::istream& operator >> (std::istream& is, ComplexNumber &c) {
	double x, y;
	is >> x >> y;
	c.setIm(y);
	c.setReal(x);
	return is;
}

std::ostream& operator << (std::ostream& os, ComplexNumber c) {
	if (abs(c.re) < 1e-12) c.re = 0;
	if (abs(c.im) < 1e-12) c.im = 0;
	if (c.im != 0 && c.re != 0)
		os << c.re << " + " << c.im << 'i';
	else if (c.im == 0) {
		os << c.re;
	}
	else os << c.im << 'i';
	return os;
}

ComplexNumber ComplexNumber:: operator- () const {
	ComplexNumber c(-re, -im);
	return c;
}

ComplexNumber ComplexNumber:: operator~ () const {
	ComplexNumber c(re, -im);
	return c;
}


double abs(ComplexNumber c) {
	return sqrt(c.re*c.re + c.im*c.im);
}


ComplexNumber ComplexNumber::inverse() const {
	double abso = abs(*this);
	return ~(*this) / abso / abso;
}

ComplexNumber ComplexNumber::operator+ (const ComplexNumber &a) const {
	ComplexNumber c(re + a.re, im + a.im);
	return c;
}

ComplexNumber& ComplexNumber:: operator= (double b) {
	re = b;
	im = 0;
	return *this;
}

bool ComplexNumber::operator== (double b) const {
	return ((im == 0) && (re == b));
}

bool ComplexNumber::operator!= (double b) const {
	return !((*this) == b);
}


ComplexNumber ComplexNumber:: operator- (const ComplexNumber &a) const {
	ComplexNumber c;
	c = a + -(*this);
	return c;
}

ComplexNumber ComplexNumber:: operator* (const ComplexNumber &a) const {
	ComplexNumber c;
	c.re = (a.re * re - a.im * im);
	c.im = (a.im * re + a.re * im);
	return c;
}

ComplexNumber ComplexNumber:: operator/ (const ComplexNumber &a) const {
	return (*this) * a.inverse();
}

ComplexNumber ComplexNumber:: operator* (double b) const {
	ComplexNumber c(re * b, im * b);
	return c;
}

ComplexNumber ComplexNumber:: operator/ (double b) const {
	if (b == 0) throw("Impartire la zero!");
	ComplexNumber c(re / b, im / b);
	return c;
}

bool ComplexNumber :: operator < (ComplexNumber a) const {
	if (a.re != re) return re < a.re;
	return im < a.im;
}

bool ComplexNumber :: operator == (ComplexNumber a) const {
	return (*this - a == 0);
}

bool ComplexNumber :: operator != (ComplexNumber a) const {
	return !(a == (*this));
}


double ComplexNumber::getIm() {
	return im;
}
double ComplexNumber::getReal() {
	return re;
}
void ComplexNumber::setReal(double x) {
	re = x;
}
void ComplexNumber::setIm(double x) {
	im = x;
}
ComplexNumber::~ComplexNumber() {}
