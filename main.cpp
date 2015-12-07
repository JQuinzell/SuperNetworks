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

=======
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

// Recovery algorithm that prioritizes high value paths
queue<string> priorityRecovery(Graph G, int S, int T);

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
	int flow_change;

	cout << "Start Maxflow - Gf" << endl;
	Graph Gf = residualNet(G);
	// Gf.print(true);
	curr_path = Gf.list.calculatePath(S,T);
	
	cout << "Start loop" << endl;
	while(!curr_path.edges.empty()){
		// curr_path.print();

		//update G
		for(Edge curr_edge : curr_path.edges){
			G.augmentEdge(curr_edge, curr_path.flow);
		}
		G.max_flow += curr_path.flow;
		
		// G.print();
		Gf = residualNet(G);
		// Gf.print(true);
		curr_path = Gf.list.calculatePath(S,T);			
	}
	cout << "end" << endl;
	Gf.max_flow = G.max_flow;
	return G;
}
	
Graph residualNet(Graph &G)
{
	Graph Gf(G.list.vertices.size());
	
	for(auto node : G.list.vertices){
		for(Edge curr_edge : node){
			Edge residual(curr_edge.from, curr_edge.to, (curr_edge.weight - curr_edge.flow));
			residual.residual = true;
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
	string id;
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
			kdl >> word; // ignore id
			kdl >> id;
			out << source << " " << target << endl;
		}
	}
	return;
}

queue<string> priorityRecovery(Graph G, int S, int T)
{
	int curr_flow = 0, time = 0, max_val = 0, work_time = 0;
	Path selected;
	queue<string> rec_q;
	Graph M = maxFlow(G, S, T);
	Graph curr, N, H;

	// will iterate until C matches M
	while (curr_flow < M.max_flow)
	{
		Graph G = H;
		// test all paths in max flow graph
		while (!G.paths.empty())
		{
			// add path to test-graph
			Path P = G.paths.back();
			G.paths.pop_back();
			// Find work time required for path
			for (Edge E : P.edges)
			{
				if (E.failed)
				{
					N.list.addEdge(E);
					work_time += E.repair_time;
				}
			}
			// TODO: repair time of nodes?

			// Compare value of flow over repair time
			int value = maxFlowVal(N, S, T) - maxFlowVal(curr, S, T) / work_time;
			if (max_val < value)
			{
				max_val = value;
				selected = P;
			}
		}

		// recover selected path
		for (Edge E : selected.edges)
		{
			if (E.failed)
			{
				curr.list.addEdge(E);
				time += E.repair_time;
				rec_q.push(E.id);
			}
		}

		// TODO: recover nodes in selected path 
		// for all nodes IN PATH
		// if failing
		// increment time
		// set to working
		// push to rec_q
		curr_flow = maxFlowVal(curr, S, T);
	}
	/*
	// TODO: recover nodes
	for ( all nodes )
	{
	// if failing, recover
	}
	*/
	// for all edges
	for (int i = 0; i < H.list.vertices.size(); i++)
	{
		for (auto edge = H.list.vertices[i].begin(); edge != H.list.vertices[i].end(); edge++)
		{
			curr.list.addEdge(*edge);
			time += edge->repair_time;
			rec_q.push(edge->id);
		}
	}
	return rec_q;
}

