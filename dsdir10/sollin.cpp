// 금속조형디자인과 3학년
// B743014 양혜진

#include <fstream>
#include <queue>
#include <algorithm>
#include "mstree.h"
int NNODES; // #nodes in the graph is global

priority_queue<Edge, vector<Edge>, Compare> *PQ;

void MergePQ(int v, int root) {
	while (!PQ[v].empty()) {
		Edge e = PQ[v].top(); PQ[v].pop();
		PQ[root].push(e);
	}
}

void sollin() {
	Sets sets(NNODES);
	int nedges = 0; // #edges found up to now

	for (int v = 0; v < NNODES - 1; v++) {
		if (PQ[v].empty()) throw "No Spanning Tree Exists.";
		Edge e = PQ[v].top(); PQ[v].pop();
		int v1root = sets.Find(e.v1); int v2root = sets.Find(e.v2);
		if  (v1root != v2root) {
			sets.Union(e.v1, e.v2);
			cout << e; nedges++;
			int vroot = sets.Find(e.v1);
			if (!PQ[v2root].empty()) MergePQ(v1root, v2root);
			else MergePQ(v2root, vroot);
		}
	}
	int v = 0;
	while (nedges < NNODES - 1) {
		if (PQ[v].empty()) {
			v++; continue;
		}
		Edge e = PQ[v].top(); PQ[v].pop();
		int v1root = sets.Find(e.v1); int v2root = sets.Find(e.v2);
		if (v1root != v2root) { // different sets
			sets.Union(v1root, v2root); nedges++;
			cout << e;
		}
		v++;
	}
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