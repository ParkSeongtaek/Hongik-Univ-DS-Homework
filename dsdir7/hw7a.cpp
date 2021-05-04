// 금속조형디자인과 3학년
// B743014 양혜진

#include "tree0.h"

int main() {
	Tree<double> tree;
	double dval;

	cout << "Enter values:\n";
	while (cin >> dval)
		tree.insert(dval);
	cout << endl << "Preorder traversal:	"; tree.Preorder();
	cout << endl << "Inorder traversal:	"; tree.Inorder();
	cout << endl << "Postorder traversal:	"; tree.Postorder();
	cout << endl << "Levelorder traversal:	"; tree.Levelorder();
}