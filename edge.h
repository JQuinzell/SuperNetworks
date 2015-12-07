#ifndef edge_h
#define edge_h
#include <iostream>
#include <random>
using namespace std;

#include <string>

using namespace std;

struct Edge
{
	int from;
	int to;
	int weight;
	string id;
	int flow;
	int repair_time;
	bool failed;
	bool residual;

	Edge(int u, int v, int w) {
		from = u;
		to = v;
		weight = w;
		flow = 0;
		repair_time = (rand()%100)+1;
		failed = false;
		residual = false;
	}
	
	Edge() {
		from = 0;
		to = 0;
		weight = 0;
		flow = 0;
		repair_time = (rand()%100)+1;
		failed = false;
		residual = false;
	}

	void print() {
		cout << "(" << from << ", " << to << ")" << endl;
	}
	
	Edge& operator=(const Edge e) {
		from = e.from;
		to = e.to;
		id = e.id;
		weight = e.weight;
		flow = e.flow;
		repair_time = e.repair_time;
		return *this;
	}
	
	bool operator!=(const Edge e) {
		return (id != e.id);
 	}
 	
 	bool operator==(const Edge e){
 		return((from == e.from) && (to == e.to));
	 }
};

#endif
