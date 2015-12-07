#ifndef adj_list_h
#define adj_list_h

#include <vector>
#include <fstream>
#include <random>
#include "edge.h"
#include "path.h"
using namespace std;

class AdjacencyList
{
private:
	bool* visited;
	int* parent;
	bool finish_dfs;

public:
	std::vector<Edge> edges;
	std::vector<std::vector<Edge> > vertices;
	int num_vertices;

	AdjacencyList(const char* filename) {
		load(filename);
	}
	
	AdjacencyList(int n): vertices(n){
		num_vertices = n;
	}
	
	AdjacencyList& operator=(const AdjacencyList l){
		edges = l.edges;
		num_vertices = l.num_vertices;
		for(int i = 0; i < num_vertices; i++){
			vertices[i] = l.vertices[i];
		}
		return *this;
	}

	/*
		Load in a graph from file
		assumes vertices are numbered from 0
	*/
	void load(const char* file) {
		std::ifstream infile;
		infile.open(file);

		int from;
		int to;
		int weight;
		int num_edges;
		int id = 0;

		infile >> num_edges;
		infile >> num_vertices;

		vertices = std::vector<std::vector<Edge> >(num_vertices);

		for (int i = 0; i < num_edges; ++i)
		{
		weight = (rand()%10)+1;
			infile >> from;
			infile >> to;
			Edge edge = Edge(from, to, weight);
			edge.id = id++;
			addEdge(edge);
		}

		infile.close();
	}
	
	Path calculatePath(int S, int T){
		Path path;

		//DFS

		int size = vertices.size();
		visited = new bool(size);
		parent = new int(size);
		finish_dfs = false;

		for (int i = 0; i < size; ++i) {
			visited[i] = false;
			parent[i] = -1;
		}

		DFSVisit(S, T, path);

		delete [] visited;
		delete [] parent;

		//END DFS

		return path;
	}

	void DFSVisit(int node, int T, Path& p) {
		visited[node] = true;

		for(auto i = vertices[node].begin(); i != vertices[node].end(); ++i) {
			Edge edge = *i;
			parent[i.from] = node;

			if(i.from == T)
				finish_dfs = true;

			if(!finish_dfs && !visited[i.from])
				DFSVisit(edge.to, T, p);

			else{
				p.addEdge(edge);
				break;
			}
		}
	}

	void addEdge(Edge edge) {
		vertices[edge.from].push_back(edge);
		edges.push_back(edge);
	}

 // int size() { return num_vertices; }

	/*
		Access edges from a specific vertex
	*/
	std::vector<Edge>& operator[](const int i) {
		return vertices[i];
	}
	
	bool isPath(int source, int destination)
	{
		Edge edge = vertices[source].back();
		if(edge.to != destination && !vertices[edge.to].empty())
			return isPath(edge.to, destination);
		else{
			return true;
		}
		return false;
	}
};

#endif
