// 금속조형디자인과 3학년
// B743014 양혜진

#include <fstream>
#include "bst.h" // include file 명이 바뀌었음

voidFile2Tre(istream& fin, BST<string, int>& tree) {
    string command, key; int elt; int r;

    while(fin >> command) {
        if(command == "print") tree.Print();
        else if(comand == "insert")
            { fin >> key >> elt; tree.Insert(key,elt); }
        else if(comand == "get") {
            fin >> key;
            if (tree.Get(key, elt))
                cout << "The value of " << key << "is"
                    << elt << endl;
            else cout << "No such key: " << key << endl;
        }
        else
            cout << "Invalid command : " << command << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2)
        { cerr << "Usage: " << argv[0] << " infile\n"; return 1; }
    ifstream fin(argv[1]);
    if (!fin) { cerr << argv[1] << " open failed\n"; return 1; }
    BST<string, int> tree;
    File2Tree(fin, tree);
    fin.close();
}