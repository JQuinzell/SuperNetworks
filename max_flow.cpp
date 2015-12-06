#include <iostream>
#include "print_graph.h"

 Graph maxFlow(Graph &G, int S, int T)
  {
  	vector<vector<Edge>> nodes;
  	AdjacencyList lf;
  	Edge curr_edge;
  	vector<Path> path_set;
  	int curr_node = S;
  	int curr_path_flow;
  	vector<Edge>iterator it;
  	
  	Graph Gf = residualNet(G);
  	
	while(pathExists(Gf,S,T)){
		lf = Gf.list;
  		nodes = list.vertices;
 	 	path_set = paths[S][T];
		curr_path = path_set.pop();
		curr_path_flow = min_element(curr_path.edges.front(), curr_path.edges.back(), minWeight());
		G.max_flow += curr_path_flow;
		for(int i = 0; i < curr_path.edges.size(); i++;){
			curr_edge = curr_path.edges.pop();
			it = find (lf.edges.begin(), lf.edges.end(), curr_edge);
			if (it != lf.edges.end()){
				curr_edge.flow = curr_edge.flow + curr_path_flow;
			}
			else{
				rev_edge = findRevEdge(curr_edge, list.edges);
				curr_edge.flow = rev_edge.flow - curr_path_flow;
			}
		}
		Gf = residualNet(Gf);		  
	}
	Gf.max_flow = G.max_flow
	return Gf;
  }
  
  Graph residualNet(Graph G)
  {
  	AdjacencyList l = G.list;
	Graph Gf(l.size());
	Edge curr_edge;
	Edge residual;
	Edge flow;
	
	while(!l.edges.empty()){
		curr_edge = *l.edges.pop_back();
		residual = Edge(curr_edge.from, curr_edge.to, (curr_edge.weight - curr_edge.flow));
		flow = Edge(curr_edge.to, curr_edge.from, curr_edge.flow);
	}
  	
	return Gf;
  }
  
  bool pathExists(Graph G, int S, int T)
  {
  	AdjacencyList l = G.list;
  	vector<Path> paths = l.paths[S][T]
  	if(paths.empty() == false)
  		return true;
  	else
		return false;
  }
  
  Edge findRevEdge(Edge sEdge, vector<Edge> edges){
  	int source = sEdge.to;
  	int destination = sEdge.from;
	Edge curr_edge, rev_edge;
	
	while(!edges.empty()){
		curr_edge = edges.pop_back();
		if(curr_edge.to == destination && curr_edge.from == source)
			rev_edge = curr_edge;
	}
  	return rev_edge;
  }
  
  minWeight(Edge &e1, Edge &e2){
  	return e1.weight < e2.weight;
  }
