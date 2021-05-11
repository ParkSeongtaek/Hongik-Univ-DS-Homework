// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include <queue>
using namespace std;

int main()
{
	priority_queue<int> maxPQ;
	maxPQ.push(15); maxPQ.push(14);
	maxPQ.push(21); maxPQ.push(2);
	maxPQ.push(10); maxPQ.push(20);

	while (!maxPQ.empty()) {
		cout << maxPQ.top() << " "; maxPQ.pop();
	}
	cout << endl;
}