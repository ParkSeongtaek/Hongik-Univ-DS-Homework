#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

struct Term {
	float coef;
	int exp;
};

class Polynomial {
public:
	Polynomial(); // counstruct a polynomial p(x) = 0.
	Polynomial operator+(Polynomial&); // 다항식의 합을 반환
	void NewTerm(const float, const int);
private:
	Term *termArray;
	int capacity; // 1로 초기화
	int terms; // 저장된 항의 수로 0으로 초기화
friend ostream& operator<<(ostream&, Polynomial&);
friend istream& operator>>(istream&, Polynomial&);
}

#endif
