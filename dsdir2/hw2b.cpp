// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
using namespace std;
#include "polyb.h"

int main() {
	Polynomial p1, p2, p3;

	cin >> p1 >> p2; // 2개의 다항식을 읽어들인다.
	p3 = p1 * p2; // 2개의 다항식의 곱을 저장한다.
	cout << p1 << p2 << p3;
}
