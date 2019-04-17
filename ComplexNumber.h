#pragma once
#include <iostream>
class ComplexNumber {
	template <class T> friend class SquareMatrix;
	template <class T> friend class RectMatrix;


private:
	double re, im;
public:
	double getReal();
	void setReal(double x);
	double getIm();
	void setIm(double x);
	ComplexNumber inverse() const;
	friend double abs(ComplexNumber c);
	ComplexNumber& operator= (double b);
	bool operator == (double b) const;
	bool operator != (double b) const;
	bool operator == (ComplexNumber a) const;
	bool operator != (ComplexNumber a) const;
	bool operator < (ComplexNumber a) const;
	ComplexNumber operator+ (const ComplexNumber &b) const;
	ComplexNumber operator- (const ComplexNumber &b) const;
	ComplexNumber operator- () const;
	ComplexNumber operator~ () const;
	ComplexNumber operator* (const ComplexNumber &b) const;
	ComplexNumber operator* (double r) const;
	ComplexNumber operator/ (double r) const;
	ComplexNumber operator/ (const ComplexNumber &b) const;
	friend std::istream& operator >> (std::istream& is, ComplexNumber &c);
	friend std::ostream& operator << (std::ostream& os, ComplexNumber c);
	ComplexNumber();
	ComplexNumber(double x, double y);
	ComplexNumber(double x);
	ComplexNumber(const ComplexNumber& c);
	~ComplexNumber();
};

