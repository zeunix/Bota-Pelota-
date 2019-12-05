#ifndef OBJETO_H
#define OBJETO_H
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"
#include <vector>

using namespace std;


class Objeto
{
public:
	Objeto();
	Objeto(vector<Vertex> vertices_in, vector<Edge> edges_in, vector<Face> faces_in);
	void scale();
	virtual ~Objeto();
	vector<Vertex> vertices;
	vector<Edge> edges;
	vector<Face> faces;
	string name;
	float biggestOne;

protected:

private:

};

#endif // OBJETO_H
