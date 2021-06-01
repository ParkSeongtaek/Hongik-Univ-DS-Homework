// 금속조형디자인과 3학년
// B743014 양혜진

#include <fstream>
#include <queue>
#include <algorithm>
#include "mstree.h"
int NNODES; // #nodes in the graph is global

priority_queue<Edge, vector<Edge>, Compare> *PQ;

void sollin() {
	Sets sets(NNODES);
	int nedges = 0; // #edges found up to now
}

void ReadEdges4sollin(istream& is) {
	PQ = new priority_queue<Edge, vector<Edge>, Compare> [NNODES];
	Edge e;

	while (GetEdge(is, NNODES, e)){
		PQ[e.v1].push(e);
		PQ[e.v2].push(e);
	}
}

int main(int argc, char *argv[]) {
	ifstream is;
	if (argc==1) is.open("mstree.dat"); else is.open(argv[1]);
	if (!is) { cerr << "No such input file\n"; return 1; }
	is >> NNODES;
	if (NNODES < 2) { cerr << "#nodes must be 2.." << endl; return 1; }

	try { ReadEdges4sollin(is); sollin(); }
	catch (char const *str)
		{ cerr << "Exception: " << str << endl; return 1; }
}