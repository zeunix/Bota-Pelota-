#include "Pokebola.h"



Pokebola::Pokebola(arma::fmat transf_in, vector<Face> faces_in, vector<float> color_in, int V_in, int dx_in, int dy_in, int dz_in, float radio_in)
{
	transf = transf_in;
	faces = faces_in;
	color = color_in;

	V = V_in;
	angle = 0.0;
	t = 0.0;
	dx = dx_in;
	dy = dy_in;
	dz = dz_in;
	radio = radio_in;
	centro = { {-3.0}, {0.0}, {0.0} , {1.0} };

	MB = { {-1.0, 3.0, -3.0, 1.0},
					{3.0, -6.0, 3.0, 0.0},
					{-3.0, 3.0, 0.0, 0.0},
					{1.0, 0.0, 0.0, 0.0} };

	GHx = { {0.0}, {float(2.0)+float(dx)}, {float(4.0)+float(dx)}, {float(6.0)+float(dx)} };
	GHy = { {0.0}, {float(3.0)+float(dy)}, {float(3.0)+float(dy)}, {0.0} };
	GHz = { {0.0}, {float(dz)*float(0.33)}, {float(dz)*float(0.66)}, {float(dz)} };
	
	dt = .05*(V);
}


vector<Vertex> Pokebola::lanza(arma::fmat transform, float pikaradio, arma::frowvec pikaposicion)
{
	pikaposicion[1] = pikaposicion[1] + 0.2;
	Transform Tr = Transform();
	//Aumeta angulo
	angle = (angle < 360.0f) ? angle + V : 0.0f;
	//rota sobre eje
	transf = transf * Tr.R(0.0f, 0.0f, 1.0f, angle);
	centro =  Tr.R(0.0f, 0.0f, 1.0f, angle) *centro;
	float QX;
	float QY;
	float QZ;
	//Calcula Qx y Qy
	if (t <= 1.1) {
		arma::frowvec Tvec = { pow(t,3), pow(t,2), t, 1.0 };
		arma::fmat Qtx = Tvec * MB * GHx;
		arma::fmat Qty = Tvec * MB * GHy;
		arma::fmat Qtz = Tvec * MB * GHz;
		QX = Qtx(0);
		QY = Qty(0);
		QZ = Qtz(0);
		t += dt;
		Qtx.print();
		Qty.print();
		Qtz.print();

		transf = transform * Tr.T(QX, QY, QZ);

	}




	vector<Vertex> vertices;
	for (unsigned int i = 0; i < faces.size(); i++) {
		arma::fcolvec v = faces[i].vertices[0].homg();
		arma::fcolvec vp = transf * v;
		Vertex rv = Vertex();
		rv.setVertex(arma::trans(vp));
		vertices.push_back(rv);

		v = faces[i].vertices[1].homg();
		vp = transf * v;
		rv = Vertex();
		rv.setVertex(arma::trans(vp));
		vertices.push_back(rv);

		v = faces[i].vertices[2].homg();
		vp = transf * v;
		rv = Vertex();
		rv.setVertex(arma::trans(vp));
		vertices.push_back(rv);
	}
	float dist = sqrt(powf((vertices[0].getX() - pikaposicion[0]), 2) + powf((vertices[0].getY() - 0.2), 2) + powf((vertices[0].getZ() - pikaposicion[2]), 2));
	if ( dist<= 0.25)
		atrapa = true;
	return vertices;
}

vector<Face> Pokebola::iluminacion(arma::frowvec DOP)
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

vector<arma::frowvec> Pokebola::colorea(vector<Face> visibles) {
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

Pokebola::~Pokebola()
{
}
