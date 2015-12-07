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
int maxFlowVal(Graph& G, int S, int T);
Graph residualNet(Graph &G);

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
	
	G.addEdge(Edge(0, 1, 5));
	G.addEdge(Edge(0, 2, 7));
	G.addEdge(Edge(1, 2, 6));
	G.addEdge(Edge(1, 3, 8));
	G.addEdge(Edge(2, 3, 9));

	G.S = 0;
	G.T = 3;
	G.allPaths();

	G = maxFlow(G, 0, 3);
	cout << "Max Flow: " << G.max_flow << endl;
	
	return 0;
}

Graph maxFlow(Graph& G, int S, int T){
	Path curr_path;

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

int maxFlowVal(Graph& G, int S, int T){
	Path curr_path;

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
	return G.max_flow;
}
	
Graph residualNet(Graph &G)
{
	Graph Gf(G.list.vertices.size());
	
	for(auto node : G.list.vertices){
		for(Edge curr_edge : node){
			Edge residual(curr_edge.from.id, curr_edge.to.id, (curr_edge.weight - curr_edge.flow));
			residual.residual = true;
			if(residual.weight != 0){
				residual.flow = curr_edge.flow;
				Gf.addEdge(residual);	
			}
			Edge flow(curr_edge.to.id, curr_edge.from.id, curr_edge.flow);
			if(flow.weight != 0){
				flow.flow = curr_edge.weight;
				Gf.addEdge(flow);	
			}
		}
	}
	return Gf;
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
	while (kdl >> word)
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

queue<string> priorityRecovery(Graph& H, int S, int T)
{
	int curr_flow = 0, time = 0, max_val = 0, work_time = 0;
	Path selected;
	queue<string> rec_q;
	Graph M = maxFlow(H, S, T);
	Graph curr(H.list.vertices.size());
	Graph N(H.list.vertices.size()); 
	Graph G(H.list.vertices.size()); // Current graph, next graph, 

	// will iterate until C matches M
	while (curr_flow < M.max_flow)
	{
		Graph G = H; // H represents network. G modifiable version
		// test all paths in max flow graph
		while (!G.paths.empty())
		{
			N = curr;
			Path P = G.paths.back(); // add path
			G.paths.pop_back(); // remove from G
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
			int value = (maxFlowVal(N, S, T) - maxFlowVal(curr, S, T)) / work_time;
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
				E.failed = false;
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
			edge->failed = false;
			rec_q.push(edge->id);
		}
	}
	return rec_q;
}

