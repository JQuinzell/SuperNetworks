#ifndef adj_list_h
#define adj_list_h

#include <vector>
#include <fstream>
#include "edge.h"

class AdjacencyList
{
private:
  std::vector<std::vector<Edge> > vertices;
  int num_vertices;

public:
  std::vector<Edge*> edges;

  AdjacencyList(const char* filename) {
    load(filename);
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

    infile >> num_edges;
    infile >> num_vertices;

    vertices = std::vector<std::vector<Edge> >(num_vertices);

    for (int i = 0; i < num_edges; ++i)
    {

      infile >> from;
      infile >> to;
      infile >> weight;
      addEdge(Edge(from, to, weight));
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
  
};

#endif
