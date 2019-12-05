#ifndef POKEMON_H
#define POKEMON_H
#include<vector>
#include <armadillo>
#include "Vertex.h"
#include "Face.h"
#include "Transform.h"
class Pokemon
{
public:

	~Pokemon();

	vector<Face> faces;
	vector<float> color;
	float S;
	int V;
	float angle;
	float t;
	float dt;
	float radio;
	arma::frowvec posicion;
	arma::fmat transf;
	Pokemon(arma::fmat transf_in, vector<Face> faces_in, vector<float> color_in, float S_in, int V_in, arma::frowvec posicion_in, float radio_in);
	void mueve(arma::fmat transform);
	vector<Face> iluminacion(arma::frowvec DOP);
	vector<arma::frowvec> colorea(vector<Face> visibles);
	
};

#endif