// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include "post.h"
using namespace std;

void Eval(Expression);

int main() {
	char line[MAXLEN];
	while (cin.getline(line, MAXLEN)) {
		Expression e(line); // Assume postfix notation
		try { 
			Eval(e); 
		} // 에러 메시지를 받아 출력하고 다음 데이터 받아 처리함
		catch (char const *msg) {
			cerr << "Exception: " << msg << endl;
		}
	}
}