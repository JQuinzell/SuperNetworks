#ifndef edge_h
#define edge_h
#include <iostream>
#include <random>
#include <string>
using namespace std;

struct Node
{
	int id;
	int repair_time;
	bool failed;
	
	Node(int i){
		id = i;
		repair_time = (rand()%100)+1;
		failed = false;
	}
	
	Node(){
		id = (-INT_MAX);
		repair_time = (rand()%100)+1;
		failed = false;
	}
	
	Node& operator=(const Node n) {
		id = n.id;
		repair_time = n.repair_time;
		failed = n.failed;
		return *this;
	}
	
	bool operator==(const Node n){
 		return(id == n.id);
	 }
};

struct Edge
{
	Node from;
	Node to;
	int weight;
	string id;
	int flow;
	int repair_time;
	bool failed;
	bool residual;

	Edge(Node u, Node v, int w) {
		from = u;
		to = v;
		weight = w;
		flow = 0;
		repair_time = (rand()%100)+1;
		failed = false;
		residual = false;
	}
	
	Edge() {
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
