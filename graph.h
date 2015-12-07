#ifndef graph_h
#define graph_h

#include <queue>
#include "adj_list.h"
#include "edge.h"

class Graph
{
public:
	int max_flow;
	AdjacencyList list;
	int size;
	bool* visited;
	vector<Path> paths;
	
	Graph(const char* filename):
		list(filename)
	{
		size = list.num_vertices;
		max_flow = 0;
	}
	
	Graph(int n): list(n) {
		max_flow = 0;
		size = n;
	}
	
	Graph(const Graph &G): list(G.size){
		size = G.size;
		max_flow = G.max_flow;
	}
	
	void addEdge(Edge edge){
		list.addEdge(edge);
	}
	
	Graph& operator=(const Graph G){
		list = G.list;
		size = G.list.num_vertices;
		visited = G.visited;
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
				if(!visited[edge.to]) {
					BFSProcessEdge(edge);
					visited[edge.to] = true;
					q.push(edge.to);
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
		for (int i = 0; i < size; ++i)
			visited[i] = false;

		DFSStart();
		DFSVisit(source);
		DFSEnd();

		delete [] visited;
		visited = nullptr;
	}

	void DFSVisit(int node) {
		DFSPreprocessNode(node);
		visited[node] = true;

		for(auto i = list[node].begin(); i != list[node].end(); ++i) {
			Edge edge = *i;
			DFSProcessEdge(edge);
			DFSVisit(edge.to);
		}

		DFSPostprocessNode(node);
	}

	virtual void DFSStart() {}
	virtual void DFSPreprocessNode(int n) {}
	virtual void DFSProcessEdge(Edge& edge) {}
	virtual void DFSPostprocessNode(int n) {}
	virtual void DFSEnd() {}	
};

#endif
