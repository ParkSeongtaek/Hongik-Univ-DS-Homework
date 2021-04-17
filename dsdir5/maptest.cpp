// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include <map>
#include <cstring>	// strcmp 를 위해 필요함
using namespace std;

struct cmp {
	bool operator() (char const *a, char const *b)
		{ return strcmp(a, b) < 0; }
};

map<char *, float, cmp> ST;	// Symbol Table

void StoreIntoST(char *name, float val) {
	// Symbol Table 에서 name 을 키로 val 을 값으로 하는 pair 를 저장하라
	ST[name] = val;
	// 원래는 ST.insert(pair<char *, float>(name, val));
}

void PrintValue(char *name) {
	map<char *, float, cmp>::iterator iter;
	iter = ST.find(name);
	if (iter == ST.end())
		cout << name << " does not exit" << endl;
	else
		cout << name << " " << ST[name] << endl;
		// 원래는 cout << iter->first << " " << iter->second << endl;
}

int main() {
	StoreIntoST((char *)"abro", 23);
	StoreIntoST((char *)"bb", 34.5);
	StoreIntoST((char *)"haha", 99);
	ST.erase("bb");	// 심볼 테이블에서 지우기

	StoreIntoST((char *)"bb", 1234.5);

	PrintValue((char *)"bb");
	PrintValue((char *)"haha");
	PrintValue((char *)"hoho");
}