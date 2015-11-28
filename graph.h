#ifndef graph_h
#define graph_h

#include <queue>
#include "adj_list.h"
#include "edge.h"

class Graph
{
private:
  AdjacencyList list;
  int size;

public:
  Graph(const char* filename):
    list(filename)
  {
    size = list.size();
  }

  void BFSTraverse(int source) {
    bool *visited = new bool(size);
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

      BFSPostProcessNode(curr);
    }

    delete [] visited;
    BFSEnd();
  }

  virtual void BFSStart() {}
  virtual void BFSPreprocessNode(int n) {}
  virtual void BFSProcessEdge(Edge& edge) {}
  virtual void BFSPostProcessNode(int n) {}
  virtual void BFSEnd() {}
};

#endif