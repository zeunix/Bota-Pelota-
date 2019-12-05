#include "Pokemon.h"



Pokemon::Pokemon(arma::fmat transf_in, vector<Face> faces_in, vector<float> color_in, float S_in, int V_in, arma::frowvec posicion_in, float radio_in)
{
	transf = transf_in;
	faces = faces_in;
	color = color_in;
	S = S_in;
	V = V_in;

	posicion = posicion_in;
	radio = radio_in;
	dt = 0.05*(V + 1);
}

void Pokemon::mueve(arma::fmat transform)
{
	Transform Tr = Transform();



	//transforma
	transf = transf;


	vector<Vertex> vertices;
	for (unsigned int i = 0; i < faces.size(); i++) {
		arma::fcolvec v = faces[i].vertices[0].homg();
		arma::fcolvec vp = transf * v;
		Vertex rv = Vertex();
		rv.setVertex(arma::trans(vp));
		faces[i].vertices[0]=rv;

		v = faces[i].vertices[1].homg();
		vp = transf * v;
		rv = Vertex();
		rv.setVertex(arma::trans(vp));
		faces[i].vertices[1]= rv;

		v = faces[i].vertices[2].homg();
		vp = transf * v;
		rv = Vertex();
		rv.setVertex(arma::trans(vp));
		faces[i].vertices[2]=rv;
	}
}

vector<Face> Pokemon::iluminacion(arma::frowvec DOP)
{
	vector<Face> visible_faces;
	for (int i = 0; i < faces.size(); i++)
	{
		Face f = faces[i];
		//Sacar normales
		arma::fcolvec v0 = { {f.vertices[0].getX()}, {f.vertices[0].getY()}, f.vertices[0].getZ() };
		arma::fcolvec v1 = { {f.vertices[1].getX()}, {f.vertices[1].getY()}, f.vertices[1].getZ() };
		arma::fcolvec v2 = { {f.vertices[2].getX()}, {f.vertices[2].getY()}, f.vertices[2].getZ() };
		arma::fcolvec N = arma::cross((v1 - v0), (v2 - v0));
		N = arma::normalise(N);
		float seve = arma::dot(DOP, N);
		if (seve > 0) {
			visible_faces.push_back(f);
		}

	}
	return visible_faces;
}

vector<arma::frowvec> Pokemon::colorea(vector<Face> visibles) {
	vector<arma::frowvec> colores;

	float Ia = 0.95;
	float Ka = 0.85;
	float Ip = 0.8;
	float Kd = 0.75;

	arma::fcolvec F = { -8.0, 8.0, -8.0 };
	for (int i = 0; i < visibles.size(); i++)
	{
		//Normales normalizadas
		Face f = visibles[i];
		//Sacar normales
		arma::frowvec v0 = { f.vertices[0].getX(), f.vertices[0].getY(), f.vertices[0].getZ() };
		arma::frowvec v1 = { f.vertices[1].getX(), f.vertices[1].getY(), f.vertices[1].getZ() };
		arma::frowvec v2 = { f.vertices[2].getX(), f.vertices[2].getY(), f.vertices[2].getZ() };
		arma::frowvec N = arma::cross((v1 - v0), (v2 - v0));
		N = arma::normalise(N);

		//Obtener L normalizada
		arma::fcolvec v0t = { {f.vertices[0].getX()}, {f.vertices[0].getY()}, {f.vertices[0].getZ() } };
		arma::fcolvec L = arma::normalise(F - v0t);
			   
		float I = Ia * Ka + Ip * Kd*arma::dot(N, L);
		arma::frowvec c = { I*color[0], I*color[1], I*color[2] };
		colores.push_back(c);
	}


	return colores;
}

Pokemon::~Pokemon()
{
}
