#ifndef EDGE_H
#define EDGE_H
#include "Vertex.h"


class Edge
{
public:
	Edge();
	Edge(Vertex v1_in, Vertex v2_in);
	virtual ~Edge();
	Vertex v1;
	Vertex v2;

protected:

private:

};

#endif // EDGE_H
