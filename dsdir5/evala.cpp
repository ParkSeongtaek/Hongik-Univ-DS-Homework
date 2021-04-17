// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include <stack>
#include "post.h"
using namespace std;

ostream& operator<<(ostream&, Token);
Token NextToken(Expression&);

float GetVal(Token& opnd) {
	if (opnd.type == NUM) return opnd.val;
	return 0; // ID인 경우는 일단 0을 return 하자(추후 수정 예정)
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

	else if (op == '=') throw "Assignment Not Yet Implemented";
	
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