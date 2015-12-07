
#ifndef path_h
#define path_h

#include <iostream>
#include <climits>
#include "edge.h"
#include <list>
using namespace std;

class Path
{
	public:
		int flow;
		list<Edge> edges;
		
		Path(){
	 		flow = INT_MAX;
		}

		void addEdge(Edge edge){
			edges.push_front(edge);
			int w = edge.weight;
			if(w < flow) {
				flow = w;
			}
		}
		
		Path& operator=(const Path p){
			flow = p.flow;
			edges = p.edges;
			return *this;
		}

		void print(){
			cout << "Flow: " << flow << endl;
			for (auto i = edges.begin(); i != edges.end(); ++i)
			{
				Edge e = *i;
				cout << e.from.id << " -> " << e.to.id << " | ";
			}
			cout << endl;
		}
};

#endif
