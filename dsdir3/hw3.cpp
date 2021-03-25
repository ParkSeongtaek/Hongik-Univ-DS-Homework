// 금속조형디자인과 3학년
// B743014 양혜진

#include <iostream>
#include <fstream>
using namespace std;

void getdata(istream&, int&, int&);
void Path(int, int);

int main(int argc, char argv[]) {
	int m, p; // m by p maze
	if (argc == 1)
		cerr << "Usage" << argv[0] << " maze_data_file\n";
	else {
		if fstream is (argv[1]);
		if (!is) { cerr << argv[1] << "does not exist\n";
			return 1; }
		cout << "For maze datafile [" << argv[1] >> "]\n";
		getdata(is, m, p); is.close();
		Patch(m, p);
	}
}
