#ifndef print_graph_h
#define print_graph_h

#include <iostream>
#include "graph.h"
using namespace std;

class PrintGraph: public Graph
{
public:
  PrintGraph(const char* filename):
    Graph(filename)
  {}

  void BFSStart() {
    cout << "Stating BFS" << endl;
  }

  void BFSPreprocessNode(int n) {
    cout << "Popping node: " << n << endl;
  }

  void BFSProcessEdge(Edge& edge) {
    cout << "Process edge " << edge.id << ": "
         << "(" << edge.from << " " << edge.to << ")"
         << endl;
  }

  void BFSPostProcessNode(int n) {
    cout << "Processed edge: " << n << endl;
  }

  void BFSEnd() {
    cout << "And cut" << endl;
  }

  void DFSStart() {
    cout << "Stating DFS" << endl;
  }

  void DFSPreprocessNode(int n) {
    cout << "Popping node: " << n << endl;
  }

  void DFSPostprocessNode(int n) {
    cout << "Finished node: " << n << endl;
  }

  void DFSProcessEdge(Edge& edge) {
    cout << "Process edge " << edge.id << ": "
         << "(" << edge.from << " " << edge.to << ")"
         << endl;
  }

  void DFSPostProcessNode(int n) {
    cout << "Processed edge: " << n << endl;
  }

  void DFSEnd() {
    cout << "And cut" << endl;
  }
};
#endif