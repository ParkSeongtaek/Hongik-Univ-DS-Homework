#include <iostream>
#include "polya.h"
using namespace std;

istream& operator>>(istream& is, Polynomial& p) {
// terms and (coefficoent, exponent)의 pair들을 읽어들인다.
// 높은 차수의 항부터 저장되었다고 가정한다.
	int noofterms; float coef; int exp;
	is >> noofterms;
	for (int i = 0; i < noofterms; i++) {
		is >> coef >> exp; // 계수와 지수 pair를 읽어들인다.
	p.NewTerm(coef, exp);
	}
	return is;
}

ostream& operator<<(ostream& os, Polynomial& p) {
	...
	return os;
}

Polynomial::Polynomial():capacity(4), terms(0)
{
	termsArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	// 다항식 뒤에 새로운 항을 추가하는 함수
	if (terms == capacity) {
		capacity *= 2;
		Term *temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}

Polynomial Polynomial::operator+(Polynomial& b)
{
	// 교재의 Add와 동일한 함수로 이름만 바꾸면 됨
}
