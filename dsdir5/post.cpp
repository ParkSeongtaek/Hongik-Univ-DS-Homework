// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include <stack>
#include "post.h"
using namespace std;

Token::Token() {}
Token::Token(char c) : len(1), type(c)
	{ str = new char[1]; str[0] = c; } // 디폴트 타입 = c itself
Token::Token(char c, char c2, int ty) : len(2), type(ty)
	{ str = new char[2]; str[0] = c; str[1] = c2; }
Token::Token(char *arr, int l) : type(ID), len(l) {
	str = new char[len + 1];
	for (int i = 0; i < len; i++) str[i] = arr[i];
	str[len] = '\0';
}
Token::Token(float v) : val(v), type(NUM) {}

bool Token::operator==(char b) { return len==1 && str[0]==b; }
bool Token::operator!=(char b) { return len!=1 || str[0]!=b; }
bool Token::IsOperand() { return type == ID || type == NUM; }

ostream& operator<<(ostream& os, Token t) {
	if (t.type == NUM) os << t.val;
	else for (int i = 0; i < t.len; i++) os << t.str[i];
	os << " "; return os;
}

bool IsAlpha(char c) { return c>='a' && c<='z' || c>='A' && c<='Z'; }
bool IsDigit(char c) { return c >= '0' && c <= '9'; }

bool GetID(Expression& e, Token& tok) {
	char c = e.buf[e.pos];
	if (!IsAlpha(c)) return false;
	int pos_start = e.pos; e.pos++;
	while (IsAlpha(c = e.buf[e.pos]) || IsDigit(c)) e.pos++;
	int idlen = e.pos - pos_start;
	tok = Token(e.buf + pos_start, idlen); // ID Token
	return true;
}

bool GetNUM(Expression& e, Token& tok) {
	char c; // "357"같은 숫자가 나오면 실수 357.0으로 바꾸자
	if (!IsDigit(c = e.buf[e.pos])) return false; // 숫자만 됨
	float val = c - '0'; e.pos++;
	while (IsDigit(c = e.buf[e.pos])) 
		{ val = val * 10 + c - '0'; e.pos++; }
	// (option) 현재 읽은 c 가 '.'이면 소수점 이하 추가 처리 필요
	if (e.buf[e.pos] == '.') {
		e.pos++;
		int point = 10;
		while (IsDigit(c = e.buf[e.pos])) 
		{ val = val + ((float)(c - '0') / point); point *= 10; e.pos++; }
	}
	// (option) 과학적 표기면 추가처리 필요
	if (e.buf[e.pos] == 'e' || e.buf[e.pos] == 'E') {
		e.pos++;
		int exponent = 0;
		while (IsDigit(c = e.buf[e.pos])) 
		{ exponent = exponent * 10 + c - '0'; e.pos++; }
		while (exponent)
		{ val  = val * 10; exponent--; }
	}
	tok = Token(val); // NUM Token
	return true;
}

void SkipBlanks(Expression& e) {
	char c;
	while (e.pos < e.len && ((c=e.buf[e.pos] == ' ' || c == '\t')))
		e.pos++;
}

bool TwoCharOp(Expression& e, Token& tok) {
	// 7가지 2자 토큰들 <= >= == != && || -u 을 처리
	if (e.pos >= e.len-1) return false; // 2자 이상 남아있어야 함
	char c = e.buf[e.pos]; char c2 = e.buf[e.pos+1];
	int op; // LE GE EQ NE AND OR UMINUS
	if (c == '<' && c2 == '=') op = LE;
	else if (c == '>' && c2 == '=') op = GE;
	else if (c == '=' && c2 == '=') op = EQ;
	else if (c == '!' && c2 == '=') op = NE;
	else if (c == '&' && c2 == '&') op = AND;
	else if (c == '|' && c2 == '|') op = OR;
	else if (c == '>' && c2 == '=') op = GE;
	else return false; // 2자 토큰이 아니면 false 를 return 한다.
	tok = Token(c, c2, op); e.pos += 2;
	return true;
}

bool OneCharOp(Expression& e, Token& tok) {
	char c = e.buf[e.pos];
	if (c=='-' || c=='!' || c=='*' || c=='/' || c=='%' ||
		c=='+' || c=='<' || c=='>' || c=='(' || c==')' || c=='=')
		{ tok = Token(c); e.pos++; return true; }
	return false;
}

Token NextToken(Expression& e) {
	static bool opndFound = false; // operand 미발견(for infix 식)
	Token tok;
	SkipBlanks(e);
	if (e.pos == e.len) tok = Token('#'); // 토큰 없음을 알리는 토큰
	else if (GetID(e, tok) || GetNUM(e, tok)) { } // do nothing
	else if (TwoCharOp(e, tok)) { } // do nothing
	else if (OneCharOp(e, tok)) { // 1자 토큰 여부 점검
		if (e.infix && tok.type=='-' && !opndFound) // operand 후 아님
			tok = Token('-', 'u', UMINUS); // -u (즉 unary -)로 바꾼다
	 }
	else throw "Illegal Character Found";
	if (e.infix) opndFound = tok.IsOperand();
	return tok;
}

int icp(Token& t) { // in-coming priority
	// type 이 '('면 0, UMINUS 나 '!'면 1, '*'나 '/'나 '%'면 2,
	if (t.type == '(') return 0;
	if (t.type == UMINUS || t.type == '!') return 1;
	if (t.type == '*' || t.type == '/' || t.type == '%') return 2;
	// '+'나 '-'면 3, '<'나 '>'나 LE나 GE면 4, EQ나 NE면 5,
	if (t.type == '+' || t.type == '-') return 3;
	if (t.type == '<' || t.type == '>') return 4;
	if (t.type == LE || t.type == GE) return 4;
	if (t.type == EQ || t.type == NE) return 5;
	// AND면 6, OR이면 7, '='이면 8, '#'면 10을 return 한다.
	if (t.type == AND) return 6;
	if (t.type == OR) return 7;
	if (t.type == '=') return 8;
	if (t.type == '#') return 10;
}

int isp(Token& t) { // '(' 경우 9를 기타는 icp(t)를 반환
	if (t.type == '(') return 9;
	else return icp(t);
}

void Postfix(Expression e) {
	// STL 이용하고, 교재의 마지막 for 문을 다음 두 줄로 바꾼다.
	// while (stack.top()!='#') { cout << stack.top(); stack.pop(); }
	// stack.pop();
	std::stack<Token> stack;
	stack.push(Token('#'));
	
	for (Token x = NextToken(e); x != '#'; x = NextToken(e)) {
		if (x.IsOperand()) cout << x;
		else if (x == ')') {
			// unstack until '('
			for (; stack.top() != '('; stack.pop())
				cout << stack.top();
			stack.pop(); // unstack '('
		}
		else { // x is an operator
			for (; isp(stack.top()) <= icp(x); stack.pop()){
				if (x == '=' && stack.top() == '=') break;
				cout << stack.top();
			}
			stack.push(x);
		}
	}
	// end of expression; empty the stack
	//cout << "now print the stack" << endl;
	while (stack.top()!='#') { cout << stack.top(); stack.pop(); }
	stack.pop();
	cout << endl;
}