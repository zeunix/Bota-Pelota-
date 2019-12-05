
#include "Vertex.h"

Vertex::Vertex()
{
	//ctor
}

Vertex::Vertex(float x_in, float y_in, float z_in)
{
	//ctor
	x = x_in;
	y = y_in;
	z = z_in;
}


Vertex::~Vertex()
{
	//dtor
}

vector<float> Vertex::getVertex() {
	vector<float> v;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	return v;
}

void Vertex::setVertex(arma::frowvec vertex) {
	x = vertex[0];
	y = vertex[1];
	z = vertex[2];
}

arma::fcolvec Vertex::homg() {
	arma::fcolvec p = { {x},{y},{z},{1.0} };
	return p;
}

float Vertex::getX() {
	return x;
}
void Vertex::setX(float val) {
	x = val;
}
float Vertex::getY() {
	return y;
}
void Vertex::setY(float val) {
	y = val;
}
float Vertex::getZ() {
	return z;
}
void Vertex::setZ(float val) {
	z = val;
}

