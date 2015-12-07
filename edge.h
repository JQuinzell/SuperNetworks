#ifndef edge_h
#define edge_h

#include <string>

using namespace std;

struct Edge
{
	int from;
	int to;
	int weight;
	string id;
	int flow;
	bool failed;
	int repair_time;

	Edge(int u, int v, int w) {
		from = u;
		to = v;
		weight = w;
		flow = 0;
		failed = false;
	}
	
	Edge() {
		from = 0;
		to = 0;
		weight = 0;
		flow = 0;
		failed = false;
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
 		return(id == e.id);
	 }
};

#endif
