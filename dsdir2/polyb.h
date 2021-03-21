// 금속조형디자인과 3학년
// B743014 양혜진

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

struct Term {
	float coef; // 계수(coefficient)
	int exp; // 지수 (exponent)
};

class Polynomial {
public:
	Polynomial(); // counstruct a polynomial p(x) = 0.
	Polynomial operator+(Polynomial&); // 다항식의 합을 반환
	Polynomial operator*(Polynomial&); // 다항식의 곱을 반환
	void NewTerm(const float, const int);
private:
	Term *termArray; // 0이 아닌 항의 배열
	int capacity; // termArray의 크기: 1로 초기화
	int terms; // 0이 아닌 항의 수: 저장된 항의 수로 0으로 초기화
friend ostream& operator<<(ostream&, Polynomial&);
friend istream& operator>>(istream&, Polynomial&);
};

#endif
