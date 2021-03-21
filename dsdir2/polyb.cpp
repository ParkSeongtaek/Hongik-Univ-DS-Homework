// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
using namespace std;
#include "polyb.h"

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
	for (int i = 0; i < p.terms; i++) {
		if (i != 0)
		{
			os << " ";
			if (p.termArray[i].coef > 0) os << "+";
		}
		if (p.termArray[i].coef == -1) os << "-";
		else if (p.termArray[i].coef != 1) os << p.termArray[i].coef;
		if (p.termArray[i].exp != 0) os << "x^" << p.termArray[i].exp;
	}
	os << endl;
	return os;
}

Polynomial::Polynomial():capacity(4), terms(0)
{
	termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	// 다항식 뒤에 새로운 항을 추가하는 함수
	if (terms == capacity) { // 새로운 항들을 저장할 공간이 충분하지 않은 경우
		capacity *= 2; // termArray 배열의 크기인 capacity 를 두배로 확장한다.
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
	Polynomial c;
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms))
	{
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	// *this 의 나머지 항들을 추가한다
	for (; aPos < terms; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	// b(x) 의 나머지 항들을 추가한다
	for (; bPos < terms; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

Polynomial Polynomial::operator*(Polynomial& b)
{
	Polynomial c;
	
	for (int i = 0; i < terms; i++)
	{
		Polynomial temp;
		for (int j = 0; j < b.terms; j++) // 계수끼리는 곱해주고, 지수끼리는 더해준다.
			temp.NewTerm(termArray[i].coef * b.termArray[j].coef, termArray[i].exp + b.termArray[j].exp);
		c = c + (temp);
	}
	return c;
}