
#ifndef path_h
#define path_h

#include <iostream>
#include <climits>
#include "edge.h"
using namespace std;

class Path
{
	public:
		int flow;
		std::vector<Edge> edges;
		
		Path(){
	 		flow = INT_MAX;
		}

		void addEdge(Edge edge){
			edges.push_back(edge);
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
			for (std::vector<Edge>::reverse_iterator i = edges.rbegin(); i != edges.rend(); ++i)
			{
				Edge e = *i;
				cout << e.from.id << " -> " << e.to.id << " | ";
			}
			cout << endl;
		}
};

#endif
