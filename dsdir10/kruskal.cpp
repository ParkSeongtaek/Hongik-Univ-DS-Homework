// 금속조형디자인과 3학년
// B743014 양혜진

#include <fstream>
#include <queue>
#include "mstree.h"
int NNODES; // #nodes in the graph is global

priority_queue<Edge, vector<Edge>, Compare> PQ;
void kruskal() {
	Sets sets(NNODES);
	int nedges = 0; // #edges found up to now
	while(nedges < NNODES - 1) {
		if (PQ.empty()) throw "No Spanning Tree Exists.";
		Edge e = PQ.top(); PQ.pop();

		int v1root = sets.Find(e.v1); int v2root = sets.Find(e.v2);
		if (v1root != v2root) { // different sets
			sets.Union(v1root, v2root); nedges++;
			cout << e;
		}
	}
}