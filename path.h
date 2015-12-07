#ifndef path_h
#define path_h

#include <iostream>
#include "edge.h"

class Path
{
	public:
		int flow;
		std::vector<Edge> edges;
		
		Path(){
	 		flow = 0;
		 }
		
		Path(int source, int destination, Edge sEdge, std::vector<std::vector<Edge>> nodes){
			int curr_node = sEdge.to;
			Edge curr_edge = sEdge;
		
			flow = sEdge.weight;
			edges.push_back(sEdge);
			sEdge.inPath = true;
			
			while(curr_node != destination){
				curr_edge = findEdge(nodes, curr_node, source, destination);
				edges.push_back(&curr_edge);
				curr_edge.inPath = true;
				if(curr_edge.weight < flow)
					flow = curr_edge.weight;
				curr_node = curr_edge.to;
			}
	 	}
	 	
	 	Edge findEdge(std::vector<std::vector<Edge>> n, int cn, int S, int T){
		 	Edge edge = n[cn].back();
		 	n[cn].pop_back();
		 	if(edge.to == T && edge.inPath){
		 		if(!n[cn].empty()){
		 			edge = findEdge(n, cn, S, T);
				 }
				 else{
				 	edge = findEdge(n, edge.from, S, T);
				 }
			 }
			 return edge;
		 }
		
		/*std::vector<Edge>& operator=(const std::vector<Edge> e){
			for(Edge curr_edge : e){
				edges.push_back(&curr_edge);
			}
			return *this;
		}
		
		Path& operator=(const Path p){
			from = p.from;
			to = p.to;
			flow = p.flow;
			edges = p.edges;
			return *this;
		}
		
		bool operator==(const Path p){						
			return (edges == p.edges);
		}*/
};

#endif
