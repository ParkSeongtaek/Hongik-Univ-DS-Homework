// 금속조형디자인과 3학년
// B743014 양혜진

#include "maxheap.h"
int main()
{
	MaxHeap<int> H;
	H.Push(15); H.Push(14); H.Push(21); H.Push(2);
	H.Push(10); H.Push(20);

	cout << H;

	while (!H.IsEmpty())
	{
		cout << H.Top() << " "; H.Pop();
	}
	cout << endl;
}