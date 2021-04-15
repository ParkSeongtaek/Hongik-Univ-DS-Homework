// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include "post.h"
using namespace std;

void Postfix(Expression);

int main() {
	char linebuf[MAXLEN];
	while (cin.getline(linebuf, MAXLEN)) {
		// getline 은 뒤에 NULL 문자 추가
		Expression e(linebuf, true); // 줄버퍼 이용 Expression 을 만듬
									 // true 는 infix 식을 의미
		try { Postfix(e); }
		catch (char const *msg) {
			cerr << "Exception: " << msg << endl;
		}
	}
}