// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
void PrintArray(T *a, const int n)
{
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
}

struct cmp {
	bool operator() (int i, int j) { return i > j; }
} myobj;

int main() {
	int a[] = { 0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19 };
	int n = sizeof(a) / sizeof(int) - 1; // 0번째 성분 제외

	cout << "Before Sorting : "; PrintArray(a, n);
	sort(a+1, a+n+1, myobj); // a[0, n-1]정렬 경우는 sort(a, a+n, myobj)
	cout << "After Sorting : "; PrintArray(a, n);
}
