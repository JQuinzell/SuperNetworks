#ifndef edge_h
#define edge_h

struct Edge
{
  int from;
  int to;
  int weight;
  int id;
  int flow;

  Edge(int u, int v, int w=0) {
    from = u;
    to = v;
    weight = w;
    flow = 0;
  }
};

#endif
