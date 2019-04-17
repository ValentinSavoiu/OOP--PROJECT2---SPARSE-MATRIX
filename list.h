

template <class T>
class list {
	template <class U> friend class SquareMatrix;
public:
	int dim;
	int cap;
	node <T> *l;
	int size() {
		return dim;
	}
	list(int DIM = 0, int CAP = 10) :dim(DIM), cap(CAP) {
		l = new node<T>[cap];
		//cout << "Constructor\n";
	}
	list(const list &A) {
		dim = A.dim;
		cap = A.cap;
		l = new node<T>[cap];
		for (int i = 0; i < dim; ++i)
			l[i] = A.l[i];
	}
	~list() {
		delete[] l;
		//cout << "Destructor\n";
	}
	list &operator= (const list &A) {
		delete[] l;
		dim = A.dim;
		cap = A.cap;
		l = new node<T>[cap];
		for (int i = 0; i < dim; ++i)
			l[i] = A.l[i];
		return *this;
	}
	void insert(node<T> u) {
		if (u.x == 0) return;
		if (dim == cap) {
			node <T>* aux = new node<T>[2 * cap];
			if (aux == nullptr) throw "N-am destula memorie. RIP";
			cap = 2 * cap;
			for (int i = 0; i < dim; ++i)
				aux[i] = l[i];
			delete l;
			l = aux;
		}
		int i = dim - 1;
		while (i >= 0 && u < l[i]) --i;
		if (i == -1) {
			for (int j = dim; j > 0; --j)
				l[j] = l[j - 1];
			l[0] = u;
			++dim;
			return;
		}
		if (u == l[i]) {
			l[i].x = l[i].x + u.x;
			if (l[i].x != 0) return;
			for (int j = i; j < dim - 1; ++j)
				l[j] = l[j + 1];
			--dim;
			return;
		}
		for (int j = dim; j > i + 1; ++j)
			l[j] = l[j - 1];
		l[i + 1] = u;
		++dim;
	}
	void erase(int poz) {
		if (poz < 0 || poz >= dim) throw "Pozitie invalida la stergere";
		for (int i = poz; i < dim - 1; ++i)
			l[i] = l[i + 1];
		--dim;
	}

	int find(int line, int colu) {
		for (int i = 0; i < dim; ++i)
			if (l[i].lin == line && l[i].col == colu)
				return i;
		return -1;
	}

	friend ostream& operator << (ostream &out, const list<T> &L) {
		for (int i = 0; i < L.dim; ++i)
			out << L.l[i] << ' ' << ' ';
		return out;
	}

};