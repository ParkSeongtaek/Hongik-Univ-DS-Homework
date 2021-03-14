// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include "rectb.h" // 헤더파일이 변경되었음에 주의
using namespace std;

int main()
{
	Rectangle r(2, 3, 6, 6), s(1, 2, 5, 9);

	cout << "<rectangle r>" << r
	     << "<rectangle s>" << s;
	if (r < s)
		cout << "s is bigger";
	else if (r == s)
		cout << "Same size";
	else cout << "r is bigger";
	cout << endl;
}
