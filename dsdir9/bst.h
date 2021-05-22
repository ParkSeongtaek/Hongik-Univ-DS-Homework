// 금속조형디자인과 3학년
// B743014 양혜진

#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>
using namespace std;

template <class K, class E>
struct Node {
	Node(K ky, E el, int lsize=1, Node<K, E> *left=0, Node<K, E> *right=0)
		: key(ky), element(el), leftSize(lsize), leftChild(left), rightChild(right) { }
	
	K key;
	E element;
	int leftSize;
	Node<K, E> *leftChild;
	Node<K, E> *rightChild;
};

template <class K, class E>
class BST {
	public:
		BST() { root = 0; } // empty tree
		void Insert(K &newkey, E el) { Insert(root, newkey, el); }
		void Delete(K &oldkey) { Delete(root, oldkey); }
		void Inorder() { Inorder(root); }
		void Postorder() { Postorder(root); }
		bool Get(const K&, E&);
		bool RankGet(int r, K& k, E& e);
		bool Print();

	private: // helper 함수들
		void Visit(Node<K, E> *); 
		void Insert(Node<K, E>* &, K, E);
		void Delete(Node<K, E>* &, K);
		void Inorder(Node<K, E> *); 
		void Postorder(Node<K, E> *);

		Node<K, E> *root;
};

template <class K, class E>
void BST<K, E>::Visit(Node<K, E> *ptr)
	{ cout << ptr->key << ":" << ptr->element << " "; }

template <class K, class E>
void BST<K, E>::Insert(Node<K, E>* &ptr, K newkey, E el) { // Insert의 helper 함수	
	if (ptr==0) ptr = new Node<K, E>(newkey, el);
	else if (newkey < ptr->key) {
		ptr->leftSize++;
		Insert(ptr->leftChild, newkey, el);
	}
	else if (newkey > ptr->key) Insert(ptr->rightChild, newkey, el);
	else ptr->element = el; // Update element
}

template <class K, class E>
void BST<K, E>::Inorder(Node<K, E> *currentNode) { // Inorder helper 함수
	if (currentNode) {
		Inorder(currentNode->leftChild);
		Visit(currentNode);
		Inorder(currentNode->rightChild);
	}
}

template <class K, class E>
void BST<K, E>::Postorder(Node<K, E> *currentNode) { // Postorder의 helper 함수
	if (currentNode) {
		Postorder(currentNode->leftChild);
		Postorder(currentNode->rightChild);
		Visit(currentNode);
	}
}

template <class K, class E>
bool BST<K, E>::Get(const K& k, E& e) {
	Node<K, E> *ptr = root;
	while (ptr) {
		if (k < ptr->key) ptr = ptr->leftChild;
		else if (k > ptr->key) ptr = ptr->rightChild;
		else { e = ptr->element; return true; }
	}
	return false;
}

template <class K, class E>
bool BST<K, E>::Print() {
	cout << endl << "Inorder traversal :	"; Inorder();
	cout << endl << "Postorder traversal :	"; Postorder();
	cout << endl;
}

template <class K, class E>
bool BST<K, E>::RankGet(int r, K& k, E& e) {
	Node<K, E> *ptr = root;
	while (ptr) {
		if (r < ptr->leftSize) ptr = ptr->leftChild;
		else if (r > ptr->leftSize) {
			r -= ptr->leftSize;
			ptr = ptr->rightChild;
		}
		else { k = ptr->key; e = ptr->element; return true; }
	}
	return false;
}

template <class K, class E>
void BST<K, E>::Delete(Node<K, E>* &ptr, K oldkey) {
	Node<K, E> *tmpptr; Node<K, E> *tmpdaddyptr;
	if (ptr == 0) return; // 그런 노드가 없으므로, 그냥 return
	if (oldkey < ptr->key) Delete(ptr->leftChild, oldkey);
	else if (oldkey > ptr->key) Delete(ptr->rightChild, oldkey);
	else { // ptr 노드가 바로 지울 노드인 경우
		if (!ptr->leftSize && !ptr->rightChild) { delete ptr; ptr = 0; return; }
		else if (!ptr->rightChild)
		{ tmpptr = ptr; ptr = ptr->leftChild; delete tmpptr; return; }
		else if (!ptr->leftChild)
		{ tmpptr = ptr; ptr = ptr->rightChild; delete tmpptr; return; }
		else {
			Node<K, E> *rc = ptr->rightChild;
			if (!rc->leftChild) { 
				ptr->key = rc->key; ptr->element = rc->element;
				ptr->rightChild = rc->rightChild;
				delete rc; return;
			}
			else {
				Node<K, E> *lc = rc->leftChild;
				while (!lc->leftChild) { 
					tmpdaddyptr = lc;
					lc = lc->leftChild; 
				}
				ptr->key = lc->key; ptr->element = lc->element;
				tmpdaddyptr->leftChild = lc->rightChild;
				delete lc; return;
			}
		}
	}
}

#endif