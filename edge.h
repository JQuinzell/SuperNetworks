#ifndef edge_h
#define edge_h

struct Edge
{
	int from;
	int to;
	int weight;
	int id;
	int flow;
	bool inPath;

	Edge(int u, int v, int w) {
		from = u;
		to = v;
		weight = w;
		flow = 0;
		inPath = false;
	}
	
	Edge() {
		from = 0;
		to = 0;
		weight = 0;
		flow = 0;
		inPath = false;
	}
	
	Edge& operator=(const Edge e) {
		from = e.from;
		to = e.to;
		id = e.id;
		weight = e.weight;
		flow = e.flow;
		return *this;
	}
	
	bool operator!=(const Edge e) {
		return (id != e.id);
 	}
 	
 	bool operator==(const Edge e){
 		return(id == e.id);
	 }
};

#endif
