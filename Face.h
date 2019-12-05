#ifndef FACE_H
#define FACE_H
#include "Edge.h"
#include <vector>

using namespace std;
class Face
{
public:
	Face();
	Face(vector<Edge> edges_in);
	vector<Vertex> vertices;
	vector<Edge> edges;

	virtual ~Face();

protected:

private:

};

#endif // FACE_H
