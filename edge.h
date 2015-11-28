#ifndef edge_h
#define edge_h

struct Edge
{
  int from;
  int to;
  int weight;
  int id;

  Edge(int u, int v, int w) {
    from = u;
    to = v;
    weight = w;
  }
};

#endif