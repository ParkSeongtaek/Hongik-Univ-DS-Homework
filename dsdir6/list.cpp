// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include "list.h"

ostream& operator<<(ostream& os, IntList& il)
{
	Node *ptr = il.first;
	while (ptr != 0)
	{
		os << ptr->data << " ";
		ptr = ptr->link;
	}
	os << endl;
	return os;
}

void IntList::Push_Back(int e)
{
	if (!first)
		first = last = new Node(e);
	else {
		last->link = new Node(e);
		last = last->link;
	}
}

int IntList::Front()		// 맨 앞 성분 return
{
	if (!first) return 0;
	else return first->data;
}

void IntList::Pop_Front()	// 맨 앞 노드 제거
{
	Node *tmp;

	if (!first) return ;
	tmp = first;
	first = first->link;
	delete tmp;
}

void IntList::Push_Front(int e)	// 맨 앞에 노드 추가
{
	Node *tmp;

	if (!first)
		first = last = new Node(e);
	else {
		tmp = first;
		first = new Node(e);
		first->link = tmp;
	}
}

void IntList::Insert(int e) 	// 정렬된 리스트에 새 노드 추가
{
	if (!first) Push_Front(e);
	else if (first->data > e) Push_Front(e);
	else if (first->data == e) { }
	else {
		Node *q = first; Node *p = first->link;
		while (p && p->data < e)
		{
			q = p;
			p = p->link;
		}
		if (!p) Push_Back(e);
		else if ( p-> data == e ) { }
		else {
			q->link = new Node(e);
			q->link->link = p;
		}
	}
}