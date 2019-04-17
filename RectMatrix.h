#pragma once
#include "SquareMatrix.h"
template <class T>
class RectMatrix : public SquareMatrix<T> {
	int M;
public:
	RectMatrix(int n = 0, int m = 0) : SquareMatrix<T>(n), M(m){}
	RectMatrix(const SquareMatrix<T> &Mat): SquareMatrix<T>(Mat) {
		M = Mat.N;
	}
	virtual char type() const{
		return 'R';
	}
	virtual T det() {
		throw "Nu e patratica";
	}
	virtual SquareMatrix <T> inv() {
		throw "Nu e patratica";
	}
	RectMatrix& operator= (const RectMatrix<T> &Mat) {
		this->SquareMatrix<T>::operator= (Mat);
		if (Mat.type() == 'R')
			M = Mat.M;
		return *this;
	}
	virtual void citire(istream& in) {
		in >> this->N >> this->M >> this->nr;
		delete[] this->lines;
		int line, col;
		T val;
		this->lines = new list<T>[this->N + 1];
		for (int i = 1; i <= this->nr; ++i) {
			in >> line >> col >> val;
			if (line > this-> N || line < 1 || col > M || col < 1) throw "Pozitie invalida";
			this->lines[line].insert(node<T>(val, line, col));
		}
	}
	virtual void afisare(ostream& out) const {
		out << this->N << ' ' << this->M << ' ' << this->nr << '\n';
		for (int i = 1; i <= this->N; ++i) {
			if (this->lines[i].dim)
				out << this->lines[i] << '\n';
		}
	}
	virtual T complement() {
		throw "Nu e patratica";
	}
	virtual bool operator < (const RectMatrix<T> &Mat) const {
		if (this -> N != Mat.N) return this -> N < Mat.N;
		if (M != Mat.M) return M < Mat.M;
		return this->SquareMatrix<T>::operator<(Mat);
	}
	virtual RectMatrix<T> operator+ (const RectMatrix<T> &Mat) const {
		if (Mat.N != this -> N || Mat.M != M) throw "Adunare imposibila de matrice";
		RectMatrix <T> Res(this->SquareMatrix<T>::operator+(Mat));
		Res.M = M;
		return Res;
	} 
	virtual bool checkMultiply(const RectMatrix<T> & Mat) const{
		if (M == Mat.N) return true;
		return false;
	}
	virtual RectMatrix<T> operator* (const RectMatrix<T> &Mat) const {
		if (this->M != Mat.N) throw "Inmultire imposibila de matrice";
		if (this->N == Mat.M) {
			SquareMatrix<T> Res(this->SquareMatrix<T>::operator*(Mat));
			return Res;
		}
		RectMatrix<T> Res(this->SquareMatrix<T>::operator*(Mat));
		Res.N = this -> N;
		Res.M = Mat.M;
		return Res;
	}
	virtual ~RectMatrix()  {  };
};

