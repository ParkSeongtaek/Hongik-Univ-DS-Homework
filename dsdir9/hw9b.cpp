// 금속조형디자인과 3학년
// B743014 양혜진

#include <fstream>
#include "bst.h" // include file 명이 바뀌었음

void File2Tree(istream& fin, BST<string, int>& tree) {
    string command, key; int elt; int r;

    while(fin >> command) {
        if(command == "print") tree.Print();
        else if(command == "insert")
            { fin >> key >> elt; tree.Insert(key,elt); }
        else if(command == "get") {
            fin >> key;
            if (tree.Get(key, elt))
                cout << "The value of " << key << " is "
                    << elt << endl;
            else cout << "No such key: " << key << endl;
        }
        else if (command == "rankget") {
            fin >> r;
            if (tree.RankGet(r, key, elt))
                cout << "The " << r << "-th element is "
                    << key << ":" << elt << endl;
            else cout << "No such ranking:" << r << endl;
        }
        else if (command == "delete")
            { fin >> key; tree.Delete(key); }
        else
            cout << "Invalid command : " << command << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2)
        { cerr << "Usage: " << argv[0] << " infile\n"; return 1; }
    ifstream fin(argv[1]);
    if (!fin) { cerr << argv[1] << " open failed\n"; return 1; }
    
	BST<string, int> small;
    File2Tree(fin, small);
    fin.close();

	if (argc == 2) return 0; //argv[2]가 없으면 종료
	ifstream fin2(argv[2]);
	if (!fin2) { cerr << argv[2] << " open failed\n"; return 1; }

	BST<string, int> big;

	cout << "\n2nd tree follows\n";
    File2Tree(fin2, big);
    fin2.close();

	BST<string, int> finaltree;
	finaltree.TwoWayJoin(small, big);
	cout << "\n<two way joined tree final print>";
	finaltree.Print();
}