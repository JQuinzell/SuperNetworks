//Brandon DeVille, Jared Rainwater, John Maruska
//Algorithms 2500
//Project 2

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "graph.h"
#include "adj_list.h"
#include "edge.h"
#include "path.h"
using namespace std;

Graph maxFlow(Graph& G, int S, int T);
Graph residualNet(Graph &G);
bool pathExists(Graph &G, int S, int T);
Edge findRevEdge(Edge sEdge, vector<Edge> edges);
int minWeight(std::vector<Edge> e);
bool findEdge(std::vector<Edge> e, Edge sEdge);

/* Parses the passed file and creates a new output file. 
 * This file ("adj_list.txt") holds # edges, # nodes, 
 * and IDs of nodes on each connection
 */
void parser(const char* infile);


int main()
{
	Graph G(4);
	Graph Gf(4);
	
	G.addEdge(Edge(0, 1, 5));
	G.addEdge(Edge(0, 2, 7));
	G.addEdge(Edge(1, 2, 6));
	G.addEdge(Edge(1, 3, 8));
	G.addEdge(Edge(2, 3, 9));

	Gf = maxFlow(G, 0, 3);
	cout << "Max Flow: " << G.max_flow << endl;
	
	return 0;
}

Graph maxFlow(Graph& G, int S, int T)
{
	vector<vector<Edge>> nodes;
	AdjacencyList lf(G.list.num_vertices);
	Edge rev_edge;
	Path curr_path;
	int curr_node = S;

	Graph Gf = residualNet(G);
	curr_path = Gf.list.calculatePath(S,T);
	
	while(!curr_path.edges.empty()){
		cout << "go" << endl;
		lf = Gf.list;
		nodes = lf.vertices;
		G.paths.push_back(curr_path);
		G.max_flow += curr_path.flow;
		cout << G.max_flow << endl;
		for(Edge curr_edge : curr_path.edges){
			if (findEdge(lf.edges, curr_edge)){
				curr_edge.flow = curr_edge.flow + curr_path.flow;
			}
			else{
				rev_edge = findRevEdge(curr_edge, Gf.list.edges);
				curr_edge.flow = rev_edge.flow - curr_path.flow;
			}
		}
		Gf = residualNet(Gf);
		curr_path = Gf.list.calculatePath(S,T);			
	}
	cout << "end" << endl;
	Gf.max_flow = G.max_flow;
	return G;
}
	
Graph residualNet(Graph &G)
{
	Graph Gf(G.list.num_vertices);
	
	for(auto node : G.list.vertices){
		for(Edge curr_edge : node){
			Edge residual(curr_edge.from, curr_edge.to, (curr_edge.weight - curr_edge.flow));
			if(residual.weight != 0){
				residual.flow = curr_edge.flow;
				Gf.addEdge(residual);	
			}
			Edge flow(curr_edge.to, curr_edge.from, curr_edge.flow);
			if(flow.weight != 0){
				flow.flow = curr_edge.weight;
				Gf.addEdge(flow);	
			}
		}
	}
	return Gf;
}
	
bool pathExists(Graph &G, int S, int T)
{
	return(G.list.isPath(S,T));
}
	
Edge findRevEdge(Edge sEdge, vector<Edge> edges){
	int source = sEdge.to;
	int destination = sEdge.from;
	Edge curr_edge, rev_edge;
	
	cout << "not here2" << endl;
	while(!edges.empty()){
		curr_edge = edges.back();
		edges.pop_back();
		if(curr_edge.to == destination && curr_edge.from == source)
			rev_edge = curr_edge;
	}
	cout << "not here3" << endl;
	return rev_edge;
}

int minWeight(std::vector<Edge> e){
	Edge min_edge = e.back();
	
	for(Edge curr_edge : e){
		if (curr_edge.weight < min_edge.weight)
			min_edge = curr_edge;
	}
	return min_edge.weight;
}

bool findEdge(std::vector<Edge> e, Edge sEdge){
	for(Edge curr_edge : e){
		if(sEdge == curr_edge)
			return true;
	}
	return false;
}

void parser(const char* infile)
{
	ifstream kdl;
	ofstream out;
	string word;
	int source, target, tot_edges = 0, tot_nodes = 0;

	kdl.open(infile);

	// Find total edges and nodes
	while (kdl >> word)
	{
		if (word == "edge")
			tot_edges++;
		if (word == "node")
			tot_nodes++;
	}
	kdl.close();

	out.open("adj_list.txt");
	kdl.open(infile);
	out << tot_edges << " " << tot_nodes << endl;

	// Search file for edges
	while (kdl >> word);
	{
		if (word == "edge")
		{
			kdl >> word; kdl >> word; // ignore "[ source"
			kdl >> source;
			kdl >> word; // ignore "target"
			kdl >> target;

			out << source << " " << target << endl;
		}
	}
	return;
}