#ifndef POST_H
#define POST_H

// 1자 토큰 이외의 토큰에 대한 토큰 타입의 정의가 필요함
#define ID		257 // 변수 이름이 갖는 타입
#define NUM		258 // 25나 35.7 같은 숫자가 갖는 타입
#define EQ		259 // == 이 갖는 타입
#define NE		260 // != 이 갖는 타입
#define GE		261 // >= 이 갖는 타입
#define LE		262 // <= 이 갖는 타입
#define AND		263 // && 가 갖는 타입
#define OR		264 // || 이 갖는 타입
#define UMINUS	265 // -u(즉 unray -)가 갖는 타입
// 참고: 1자 (연산자) 토큰의 토큰타입 = 그 문자의 Ascii 코드
#define MAXLEN	80

#include <cstring>	// for strlen

struct Expression {
	Expression(char* linebuf, bool inf=false)
		: buf(linebuf), pos(0), len(strlen(buf)), infix(inf) {}
	char* buf;
	int pos;	// Expression 내의 현재의 위치 ( [0..len-1] 사이의 수 )
	int len;	// Expression 의 buf 가 가리키는 문자열의 길이
	bool infix;	// true for inifx expression ( - 처리 위해 필요 )
};

struct Token {
	bool operator==(char);
	bool operator!=(char);
	Token();
	Token(char); // 1자 토큰: (연산자) 토큰 자체를 타입으로 취급
	Token(char, char, int); // 2자 토큰(예 <=)과 그 타입(예 LE)
	Token(char*, int); // ID 토큰의 이름 및 그 길이
	Token(float); // NUM 토큰의 값 저장
	bool IsOperand(); // 토큰 타입이 ID 혹은 NUM 이면 true
	int type; // 1자 토큰은 그 자체값; 그 외는 미리 정의된 값
	union {
		struct { char *str; int len; }; // NUM 이외 토큰값 및 그 길이
		float val; // 타입이 NUM 인 경우 그 값을 저장
	};
};
#endif