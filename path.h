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
	 		flow = MAX_INT;
		}

		void addEdge(Edge edge){
			edges.push_back(edge);
			int w = edge.weight;
			if(w < flow) {
				flow = w;
			}
		}
};

#endif