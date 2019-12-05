#ifndef POKEBOLA_H
#define POKEBOLA_H
#include<vector>
#include <armadillo>
#include "Vertex.h"
#include "Face.h"
#include "Transform.h"
class Pokebola
{
public:

	~Pokebola();

	vector<Face> faces;
	vector<float> color;
	float T;
	float R;
	float S;
	int V;
	float angle;
	float t;
	arma::fmat MB;
	arma::fcolvec GHx;
	arma::fcolvec GHy;
	arma::fcolvec GHz;
	float dt;
	int dx;
	int dy;
	int dz;
	arma::fmat transf;
	float radio;
	bool atrapa = false;
	arma::fcolvec centro;
	Pokebola(arma::fmat transf_in, vector<Face> faces_in, vector<float> color_in, int V_in, int dx_in, int dy_in, int dz_in, float radio_in);
	vector<Vertex> lanza(arma::fmat transform, float pikaradio, arma::frowvec pikaposicion);
	vector<Face> iluminacion(arma::frowvec DOP);
	vector<arma::frowvec> colorea(vector<Face> visibles);
	
};

#endif