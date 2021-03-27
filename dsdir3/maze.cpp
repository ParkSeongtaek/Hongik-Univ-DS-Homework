// 금속조형디자인과 3학년
// B743014 양혜진

#include<iostream>
#include<stack>

const int MAXSIZE = 100; //up to 100 by 100 maze aㅣlowed
bool maze[MAXSIZE + 2][MAXSIZE + 2] = { 0 };
bool mark[MAXSIZE + 1][MAXSIZE + 1] = { 0 };
int markCount = 0;

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
std::ostream& operator<<(std::ostream& os, std::stack<T>& s) {
	std::stack<T> s2;
	// 스택의 내용을 역순으로 출력
	// 구현방법1: 하나씩 꺼내 다른 임시 스택에
	// 저장한 후, 최종적으로 그 임시 스택에서 출력
	// top(), pop(), push(..)의 사용법만 알면 됨
	while (!s.empty())
	{
		s2.push(s.top());
		s.pop();
	}
	while (!s2.empty())
	{
		os << " -> " << s2.top();
		s2.pop();
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, Items& item) {
	static int count = 0; // 5 Items 출력시 마다 줄바꾸기 위해
	os << "(" << item.x << ", " << item.y << ")";
	count++; if ((count % 5) == 0) std::cout << std::endl;
	return os;
}

void Path(const int m, const int p) {
	// (1, 1)에서 시작
	mark[1][1] = 1;
	markCount++;
	std::stack<Items> stack; // C++ STD stack 을 이용하라
	Items temp(1, 1, E); // temp.x temp.y temp.dir를 설정한다
	stack.push(temp);

	while (!stack.empty()) // 스택이 공백이 아닐때
	{
		temp = stack.top();
		stack.pop(); // 스택에서 삭제
		int i = temp.x; int j = temp.y; int d = temp.dir;
		while (d < 8) // 앞으로 이동
		{ // [i][j] 에서 [g][h]로 이동한다.
			int g = i + move[d].a; int h = j + move[d].b;
			if ((g == m) && (h == p)) { // 출구 도착
				std::cout << stack;
				temp.x = i; temp.y = j; std::cout << " -> " << temp;
				temp.x = m; temp.y = p; std::cout << " -> " << temp << std::endl;
				std::cout << "#nodes visited = " << markCount << " out of " << (m * p) << std::endl;
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h])) { // 새로운 위치
				mark[g][h] = 1;
				markCount++;
				temp.x = i; temp.y = j; temp.dir = d + 1;
				stack.push(temp);
				i = g; j = h; d = N;
			}
			else d++; // 새로운 방향 시도
		}
	}
	std::cout << "No path in maze." << std::endl;
}

void getdata(std::istream& is, int& m, int& p) {
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