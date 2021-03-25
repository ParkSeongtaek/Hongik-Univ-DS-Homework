// 금속조형디자인과 3학년
// B743014 양혜진

#include<iostream>
#include<stack>
using namespace std;

const int MAXSIZE = 100; //up to 100 by 100 maze aㅣlowed
bool maze[MAXSIZE + 2][MAXSIZE + 2] = { 0 };
bool mark[MAXSIZE + 1][MAXSIZE + 1] = { 0 };

enum directions{ N, NE, E, SE, S, SW, W, NW };
struct offsets {
	int a, b;
} move[8] = { -1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1 };
struct Items {
	Items(int xx = 0, int yy = 0, int dd = 0) : x(xx), y(yy), dir(dd)
		{}
	int x, y, dir;
};

template <class T>
ostream& operator<<(ostream& os, stack<T>& s) {
	// 스택의 내용을 역순으로 출력
	// 구현방법1: 하나씩 꺼내 다른 임시 스택에
	// 저장한 후, 최종적으로 그 임시 스택에서 출력
	// top(), pop(), push(..)의 사용법만 알면 됨
	return os;
}

ostream& operator<<(ostream& os, Items& item) {
	static int count = 0; // 5 Items 출력시 마다 줄바꾸기 위해
	os << "(" << item.x << ", " << item.y << ")";
	count++; if ((count % 5) == 0) cout << end;
	return os;
}

void Path(const int m, const int p) {
	mark[1][1] = 1;
	stack<Items> stack; // C++ STD stack 을 이용하라
	Items temp(1, 1, E);
	stack.push(temp);
	// ...
	/* 구현은 책과 동일하나, 최종 경로의 출력은 다음과 같다.
		cout << stack;
		temp.x = i; temp.y = j; cout << " -> " << temp;
		temp.x = m; temp.y = p; cout << " -> " << temp << endl;
	*/
	// ...
}

void getdata(istream& is, int& m, int& p) {
	// 자료파일을 읽어들여 maze 에 저장한다.
	is >> m >> p;
	for (int i = 0; i < m + 2; i++) // 왼쪽 벽과 오른쪽 벽 작성
		{ maze[i][0] = 1; maze[i][p + 1] = 1; }
	for (int j = 1; j <= p; j++) // 윗벽과 아랫벽 작성
		{ maze[0][j] = 1; maze[m + 1][j] = 1; }
	for (int i = 1; i <= m; i++) // 자료를 읽어들인다
		for (int j = 1; j <= p; j++)
			is >> maze[i][j];
}