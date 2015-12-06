#ifndef adj_list_h
#define adj_list_h

#include <vector>
#include <fstream>
#include <random>
#include "edge.h"

class AdjacencyList
{
private:
  std::vector<std::vector<Edge> > vertices;
  std::vector<std::vector<std::vector<Path>>> pathways;
  int num_vertices;

public:
  std::vector<Edge*> edges;
  std::vector<Path*> paths;

  AdjacencyList(const char* filename) {
    load(filename);
  }
  
  AdjacencyList(int n): vertices(n){
  	num_vertices = n;
  }

  /*
    Load in a graph from file
    assumes vertices are numbered from 0
  */
  void load(const char* file) {
    std::ifstream infile;
    infile.open(file);
    std::vector<Edge> curr_edges;
	Edge curr_edge;

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
    for(int i = 0; i < num_vertices; i++){
		for(int j = 0, j < num_vertices; j++){
			curr_edges = vertices[i];
			curr_edge = curr_edges.pop();
			while(curr_edges.empty() != true){
				if(isPath(j, curr_edge, vertices) == true){
					Path p(i, j, curr_edge, vertices);
					pathways[i][j].push_back(p);	
					paths.push_back(p);
				}
				else
					curr_edge = curr_edges.pop();
			}
		}	
	}

    infile.close();
  }

  void addEdge(Edge edge) {
    vertices[edge.from].push_back(edge);
    edges.push_back(&edge);
  }

  int size() { return num_vertices; }

  /*
    Access edges from a specific vertex
  */
  std::vector<Edge>& operator[](const int i) {
    return vertices[i];
  }
  
/*  int maxFlow(int S, int T)
	 {
		std::vector<std::vector<Edge>> nodes = vertices;
		Edge curr_edge;
		int curr_node;
		int flow = 0;
		int max_flow = 0;
		int num_links = nodes[S].size();
		
		curr_node = S;
		while(isPath(T, curr_edge) == true)
		{
			curr_edge = nodes[curr_node].pop();
			max_flow+=findpathFlow(curr_node, T, flow, curr_edge, nodes);
		}
		return max_flow;
	}

  int findPathFlow(int S, int T, int flow, Edge sEdge, vector<Edge> nodes)
	{
		if (flow == 0)
			flow = curr_edge.weight;
		if (curr_edge.weight < flow)
			flow = curr_edge.weight;
		if ((S != T) && (isPath(T, sEdge) == true))
		{
			curr_node = sEdge.to;
			curr_edge = nodes[curr_node].pop();
			flow = findPathFlow(curr_node, T, flow, curr_edge);
		}
		return flow;
	}*/
	
  bool isPath(int destination, Edge sEdge, std::vector<std::vector<Edge>> nodes)
	{
		while(!nodes[sEdge.to].empty())
	  	{
	  		Edge next_edge = nodes[sEdge.to].pop();
			if(sEdge.to != destination)
			{
	  			return isPath(destination, nextEdge, nodes)	
			}
			else
			{
				return true;
			}
		}
		return false;
	}
};

#endif
