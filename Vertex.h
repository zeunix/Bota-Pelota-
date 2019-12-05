#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include<vector>
#include <armadillo>

using namespace std;

class Vertex
{
public:
	
	Vertex();
	Vertex(float x_in, float y_in, float z_in);
	virtual ~Vertex();
	void inline print() { cout << x << "," << y << "," << z << endl; }
	arma::fcolvec homg();
	vector<float> getVertex();
	void setVertex(arma::frowvec);

	float getX();
	void setX(float val);
	float getY();
	void setY(float val);
	float getZ();
	void setZ(float val);

protected:

private:
	float x;
	float y;
	float z;

};

#endif // VERTEX_H
