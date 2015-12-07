#ifndef graph_h
#define graph_h

#include <queue>
#include <vector>
#include "adj_list.h"
#include "edge.h"
using namespace std;

class Graph
{
public:
	int max_flow;
	AdjacencyList list;
	int size;
	bool* visited;
	vector<Edge> parent;
	vector<Path> paths;
	int S;
	int T;
	
	Graph(const char* filename):
		list(filename)
	{
		size = list.num_vertices;
		max_flow = 0;
	}

	Graph();
	
	Graph(int n): list(n) {
		max_flow = 0;
		size = n;
	}
	
	Graph(const Graph &G):list(G.size)
	{
		size = G.size;
		max_flow = G.max_flow;
		paths = G.paths;
		list = G.list;
		S = G.S;
		T = G.T;
	}

	void print(bool gf = false) {
		cout << "Printing graph" << endl;
		for(auto node : list.vertices){
			for(Edge edge : node){
				cout << "(" << edge.from.id << ", " << edge.to.id << ")";
				if(gf){
					cout << " -- Weight: " << edge.weight << endl;
				} else {
					cout << " -- flow: " << edge.flow << endl;
				}
			}
		}
		cout << "---" << endl;
		cin.get();
	}
	
	void addEdge(Edge edge){
		list.addEdge(edge);
	}

	void allPaths() {
		DFSTraverse(S);
	}
	
	void augmentEdge(Edge& edge, int val) {
		//find matching edge
		bool found = false;

		for(int i = 0; i < list.vertices.size(); ++i){
			if(!found)
			for(auto curr_edge = list.vertices[i].begin(); curr_edge != list.vertices[i].end(); ++curr_edge){
				if(*curr_edge == edge){
					//augment
					if(edge.residual){
						curr_edge->flow += val;
					} else {
						curr_edge->flow -= val;
					}
					found = true;
					break;
				}
			}
		}
	}

	Graph& operator=(const Graph &G){
		list = G.list;
		size = G.list.num_vertices;
		visited = G.visited;
		paths = G.paths;
		S = G.S;
		T = G.T;
		return *this;
	}

	void BFSTraverse(int source) {
		visited = new bool(size);
		for (int i = 0; i < size; ++i)
			visited[i] = false;

		std::queue<int> q;
		q.push(source);

		visited[source] = true;

		BFSStart();

		while(!q.empty()) {
			int curr = q.front();
			q.pop();

			BFSPreprocessNode(curr);
			for (auto i = list[curr].begin(); i != list[curr].end(); ++i)
			{
				Edge edge = *i;
				if(!visited[edge.to.id]) {
					BFSProcessEdge(edge);
					visited[edge.to.id] = true;
					q.push(edge.to.id);
				}
			}

			BFSPostprocessNode(curr);
		}

		delete [] visited;
		visited = nullptr;
		BFSEnd();
	}

	virtual void BFSStart() {}
	virtual void BFSPreprocessNode(int n) {}
	virtual void BFSProcessEdge(Edge& edge) {}
	virtual void BFSPostprocessNode(int n) {}
	virtual void BFSEnd() {}

	void DFSTraverse(int source) {
		visited = new bool(size);
		parent = vector<Edge>(size);
		for (int i = 0; i < size; ++i){
			visited[i] = false;
		}

		DFSVisit(source);
		DFSEnd();

		delete [] visited;
		visited = nullptr;
	}

	void DFSVisit(int node) {
		visited[node] = true;

		//construct path and add if it is T
		int cur_node = node;
		Edge cur_edge;
		Path p;
		if(node == T){
			// cout << "Solution" << endl;
			while(cur_node != S){
				// cout << cur_node << endl;
				cur_edge = parent[cur_node];
				p.edges.push_front(cur_edge);
				cur_node = cur_edge.from.id;
			}
			paths.push_back(p);
			return;
		}

		for(auto i = list[node].begin(); i != list[node].end(); ++i) {
			Edge edge = *i;
			// edge.print();
			parent[edge.to.id] = edge;
			DFSVisit(edge.to.id);
		}

		// cout << "Done" << endl;
	}

	virtual void DFSEnd() {}	
};

#endif
