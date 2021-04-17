// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include <stack>
#include <map>	// 추가하여야 함
#include "post.h"
using namespace std;

ostream& operator<<(ostream&, Token);
Token NextToken(Expression&);

struct cmp_str {
	bool operator() (char const *a, char const *b)
		{ return strcmp(a, b) < 0; }
};

map<char *, float, cmp_str> ST; // 심볼 테이블 ST 선언
map<char *, float, cmp_str>::iterator iter; // iterator 선언
// 참고: iter 선언은 GetVal 안으로 이동해도 됨

float GetVal(Token& opnd) {
	if (opnd.type == NUM) return opnd.val;
	if (opnd.type == ID)
	{
		// ID 인 경우 ST 에서 그 값을 찾아 return 하고,
		// ST 에 존재하지 않으면 0을 return 하자
		iter = ST.find((char *)opnd.str);
		if (iter == ST.end()) 
			return (0);
		else 
			return ST[(char *)opnd.str];
	}
}

Token UnaryOp(int op, Token& x)
{	// UMINUS 와 '!'의 2 경우를 처리함
	if (!x.IsOperand()) throw "Operand Only for Unary Operator";
	Token tmp; tmp.type = NUM;
	if (op == UMINUS) tmp.val = - GetVal(x);
	else if (op == '!') tmp.val = ! GetVal(x);
	else throw "Invalid unary operator";
	return tmp;
}

// 배정문 처리를 추가한 BinaryOp 을 구현
Token BinaryOp(int op, Token& left, Token& right)
{	// 실수 값의 경우 %는 허용 안됨
	if (!left.IsOperand() || !right.IsOperand())
		throw "Two Operands required for Binary Operation";
	Token tmp; tmp.type = NUM;
	float val1 = GetVal(left), val2 = GetVal(right);
	if (op == '+') tmp.val = val1 + val2;
	else if (op == '-') tmp.val = val1 - val2;
	else if (op == '*') tmp.val = val1 * val2;
	else if (op == '/') tmp.val = val1 / val2;

	else if (op == '<') tmp.val = val1 < val2;
	else if (op == '>') tmp.val = val1 > val2;
	else if (op == GE) tmp.val = val1 >= val2;
	else if (op == LE) tmp.val = val1 <= val2;
	else if (op == EQ) tmp.val = val1 == val2;
	else if (op == NE) tmp.val = val1 != val2;
	else if (op == AND) tmp.val = val1 && val2;
	else if (op == OR) tmp.val = val1 || val2;

	else if (op == '=' && left.type == ID) { // 배정문 처리 필요
		// left.str 을 키, val2(right의 값)를 값으로 하는 pair 를 ST 에 저장
		ST[(char*)left.str] = val2;
		return left;
	}
	
	else throw "No such binary operator";
	return tmp;
}

void Eval(Expression e)
{	// postfix 표현식을 입력으로 받아 그 값을 계산한다.
	stack<Token> stack;
	Token opnd1, opnd2;
	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
	{
		if (x.IsOperand()) stack.push(x);
		else { // x 는 연산자 토큰이다.
			int op = x.type; // 해당 연산자를 꺼내 저장
			if (op == UMINUS || op == '!') { // unary operator
				opnd1 = stack.top(); stack.pop();
				stack.push(UnaryOp(op, opnd1));
			} else { // binary opertor
				opnd2 = stack.top(); stack.pop();
				opnd1 = stack.top(); stack.pop();
				stack.push(BinaryOp(op, opnd1, opnd2));
			}
		}
	}
	cout << stack.top() << endl; stack.pop(); // 최종 계산 결과 출력
}