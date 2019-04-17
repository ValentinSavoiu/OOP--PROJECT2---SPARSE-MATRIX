#pragma once
template <class T>
class SquareMatrix {
	template <class U> friend class RectMatrix;
protected:
	int nr, N;
	list<T> *lines;
public:
	int getN() {
		return N;
	}
	SquareMatrix(int n = 5) {
		N = n;  nr = 0;
		lines = new list<T>[N + 1];
	}
	SquareMatrix(const SquareMatrix<T> &Mat) {
		N = Mat.N;
		nr = Mat.nr;
		lines = new list<T>[N + 1];
		for (int i = 1; i <= N; ++i)
			lines[i] = Mat.lines[i];
	}

	virtual char type() const {
		return 'S';
	};
	virtual void citire(istream& in) {
		in >> this->N >> this->nr;
		delete[] this->lines;
		int line, col;
		T val;
		this->lines = new list<T>[this->N + 1];
		for (int i = 1; i <= this->nr; ++i) {
			in >> line >> col >> val;
			if (line > N || line < 1 || col > N || col < 1) throw "Pozitie invalida";
			this->lines[line].insert(node<T>(val, line, col));
		}
	}
	virtual void afisare(ostream& out) const {
		out << this->N << ' ' << this->N << ' ' << this->nr << '\n';
		out << "Det = " << this->det() << '\n';
		for (int i = 1; i <= this->N; ++i) {
			if (this->lines[i].dim)
				out << this->lines[i] << '\n';
		}
	}
	friend istream& operator >> (istream& in, SquareMatrix<T> &Mat) {
		Mat.citire(in);
		return in;
	}
	friend ostream& operator << (ostream &out, const SquareMatrix<T> &Mat) {
		Mat.afisare(out);
		return out;
	}
	SquareMatrix& operator= (const SquareMatrix &Mat) {
		delete[]lines;
		N = Mat.N;
		nr = Mat.nr;
		lines = new list<T>[N + 1];
		for (int i = 1; i <= N; ++i)
			lines[i] = Mat.lines[i];
		return *this;
	}
	bool isDiagonal() {
		for (int i = 1; i <= N; ++i) {
			if (lines[i].dim > 1) return false;
			if (lines[i].dim == 0) continue;
			if (lines[i].l[0].col != i) return false;
		}
		return true;
	}
	 bool checkMultiply(const SquareMatrix<T> & Mat) const{
		if (Mat.type() == 'R') return true;
		cout << Mat.type() << '\n';
		if (N == Mat.N) return true;
		return false;
	}
	SquareMatrix<T> operator* (const SquareMatrix<T> &Mat) const {
		if (!checkMultiply(Mat)) throw "Inmultire imposibila de matrice";
		SquareMatrix <T> Res(N);
		for (int i = 1; i <= N; ++i) {
			for (int j = 0; j < lines[i].dim; ++j) {
				int colo = lines[i].l[j].col;
				for (int k = 0; k < Mat.lines[colo].dim; ++k) 
					Res.lines[i].insert(lines[i].l[j] * Mat.lines[colo].l[k]);
			}
		}
		for (int i = 1; i <= N; ++i)
			Res.nr = Res.nr + Res.lines[i].dim;
		return Res;
	}

	bool operator== (const SquareMatrix<T> &Mat) const {
		//if (N != Mat.N || M != Mat.M || nr != Mat.nr) return false;
		if (N != Mat.N || nr != Mat.nr) return false;
		for (int i = 1; i <= N; ++i)
			for (int j = 0; j <= lines[i].size(); ++j)
				if (!lines[i].l[j].equal(Mat.lines[i].l[j]))
					return false;
		return true;
	}
	virtual bool operator < (const SquareMatrix<T> &Mat) const {
		if (N != Mat.N) return N < Mat.N;
		//if (M != Mat.M) return M < Mat.M;
		if (nr != Mat.nr) return nr < Mat.nr;
		for (int i = 1; i <= N; ++i)
			for (int j = 0; j <= lines[i].size(); ++j)
				if (!lines[i].l[j].equal(Mat.lines[i].l[j])) {
					return lines[i].l[j].mai_mic(Mat.lines[i].l[j]);
				}
		return false;
	}
	virtual T det() const {
		if (N == 1) return lines[1].l[0].x;
		T res = 0;
		for (int j = 0; j < lines[1].size(); ++j) {
			T t = lines[1].l[j].x;;
			int col = lines[1].l[j].col;
			if (t != 0) {
				res = res + t * complement(1, col);
			}
		}
		return res;
	}
	virtual SquareMatrix<T> inv() const{
		T dete = this->det();
		if (dete == 0) throw "Matricea nu are inversa";
		SquareMatrix<T> Aux(N);
		for (int i = 1; i <= N; ++i) {
			for (int j = 0; j < lines[i].size(); ++j) {
				int col = lines[i].l[j].col;
				T t = lines[i].l[j].x;
				if (t == 0) continue;
				node<T> nod(complement(i, col) / dete, col, i);
				Aux.lines[col].insert(nod);
			}
		}
		for (int i = 1; i <= N; ++i)
			Aux.nr += Aux.lines[i].dim;
		return Aux;
	}

	virtual T complement(int L, int C) const {
		if (N == 1) return lines[1].l[0].x;
		SquareMatrix <T> Aux(N - 1);
		int difL = 0, difC = 0;
		for (int i = 1; i <= N; ++i) {
			if (i == L) continue;
			if (i < L) difL = 0;
			else difL = 1;
			for (int j = 0; j < lines[i].size(); ++j) {
				int c = lines[i].l[j].col;
				if (c == C) continue;
				if (c < C)
					difC = 0;
				else difC = 1;
				Aux.lines[i - difL].insert(node<T>(lines[i].l[j].x, i - difL, c - difC));

			}
		}
		return Aux.det() * (1 - 2 * ((L + C) % 2));
	}
	virtual SquareMatrix<T> operator+ (const SquareMatrix<T> &Mat) const {
		if (Mat.type() != this->type())
			throw "Adunare imposibila de matrice";
		SquareMatrix <T> SqMat = Mat;
		if (this->N != SqMat.N)
			throw "Adunare imposibila de matrice";
		SquareMatrix<T> Res(this->N);
		for (int i = 1; i <= this->N; ++i) {
			for (int j = 0; j < this->lines[i].dim; ++j)
				Res.lines[i].insert(this->lines[i].l[j]);
			for (int j = 0; j < SqMat.lines[i].dim; ++j)
				Res.lines[i].insert(SqMat.lines[i].l[j]);
			Res.nr = Res.nr + Res.lines[i].dim;
		}
		return Res;
	}

	SquareMatrix<T> operator- () const {
		SquareMatrix<T> Res(*this);
		for (int i = 1; i <= this->N; ++i)
			for (int j = 0; j < this->lines[i].dim; ++j)
				Res.lines[i].l[j].x = this->lines[i].l[j].x * (-1);
		return Res;
	}

	SquareMatrix<T> operator- (const SquareMatrix<T> &Mat) const {
		return (*this) + (-Mat);
	}

	virtual ~SquareMatrix<T>() {
		delete[] lines;
	}
};




