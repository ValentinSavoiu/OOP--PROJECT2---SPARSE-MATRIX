using namespace std;
template <class T>
class node {
	template <class U> friend class list;
	template <class U> friend class SquareMatrix;
	template <class U> friend class RectMatrix;
	T x;
	int lin;
	int col;
public:
	node(T X = 0, int lini = 0, int colo = 0) : lin(lini), col(colo), x(X) {}
	node(const node& no) {
		x = no.x;
		lin = no.lin;
		col = no.col;
	}
	node& operator= (const node &no) {
		x = no.x;
		lin = no.lin;
		col = no.col;
		return *this;
	}
	node operator* (node<T> no) {
		node <T> res;
		res.lin = lin;
		res.col = no.col;
		res.x = x * no.x;
		return res;
	}
	~node() {}
	bool operator < (node <T> no) {
		if (lin != no.lin) return lin < no.lin;
		return col < no.col;
	}
	bool mai_mic(node <T> no) {
		if (lin != no.lin) return lin < no.lin;
		if (col != no.col) return col < no.col;
		return x < no.x;
	}
	bool equal(node <T> no) {
		return lin == no.lin && col == no.col && x == no.x;
	}
	bool operator == (node <T> no) {
		return (lin == no.lin && col == no.col);
	}
	friend ostream & operator << (ostream & out, node <T> &no) {
		out << no.lin << ' ' << no.col << ' ' << no.x;
		return out;
	}
};