#ifndef path_h
#define path_h

#include <iostream>
#include "edge.h"

class Path
{
	private:
		int from;
		int to;
	public:
		int flow;
		vector<Edge*> edges;
		
		Path(int source, int destination, Edge sEdge, std::vector<std::vector<Edge>> nodes){
			int curr_node;
			Edge curr_edge;
			
			from = source;
			to = destination;
			flow = sEdge.weight;
			edge.push_back(sEdge);
		
			curr_node = sEdge.to;
			while(curr_edge != sEdge){
				curr_edge = nodes[source].pop();
			}
			while(curr_node != destination){
				curr_node = curr_edge.to;
				curr_edge = nodes[curr_node].pop();
				edges.push_back(curr_edge);
				if(curr_edge.weight < flow)
					flow = curr_edge.weight;
			}
		}
}
