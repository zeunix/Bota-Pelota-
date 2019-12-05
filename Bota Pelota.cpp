// Bota Pelota.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <gl/GLU.h>
#include  <GLFW/glfw3.h>
#include <armadillo>
#include "Lector.h"
#include "Objeto.h"
#include "Transform.h"
#include "Pokebola.h"
#include "Pokemon.h"


arma::frowvec posicionpikachu() {
	srand(time(NULL));
	float x = ((rand() % 40) / 10.0) - 2.0;
	float y = 0.0;
	float z = ((rand() % 50) / 10.0)*-1.0;
	arma::frowvec pos = { x,y,z };
	return pos;
}

int main(void)
{
	//valores del usuario
	int velocidad = 0;
	while (velocidad < 1 || velocidad>5) {
		cout << "Escoge velocidad (1-5):" << endl;
		cin >> velocidad;
	}
	int dx=-10;
	int dy=-10;
	int dz = 0;
	while (dx < 0) {
		cout << "Direcci�n en X :" << endl;
		cin >> dx;
	}
	while (dy < 0) {
		cout << "Direcci�n en Y :" << endl;
		cin >> dy;
	}
	cout << "Direcci�n en z :" << endl;
	cin >> dz;
	
	

	//camara y ojo
	arma::frowvec eye = { -10.0, 0.5, 0.0 };
	arma::frowvec camera = { 0.0, 0.0, 0.0 };
	arma::frowvec DOP = arma::normalise(camera - eye);
	float angley = 0.0;

	GLFWwindow* window;

	Lector lectorPokebola = Lector("pokeball3.obj");
	Lector lectorPokemon = Lector("pikachu.obj");

	lectorPokebola.read();
	lectorPokemon.read();

	Objeto pokebola_o = lectorPokebola.objetos[0];
	Objeto pokemon_o = lectorPokemon.objetos[0];

	//POKEBOLA
	std::vector< Face > pokebola_faces = pokebola_o.faces;
	Transform Tr = Transform();
	arma::fmat transf = Tr.S(0.1,0.1,0.1)*Tr.T(-3.0,0.0, 0.0);
	float radio = pokebola_o.biggestOne;
	//Transformacion, caras, colores, T, R, S, velocidad
	Pokebola pokebola = Pokebola(transf, pokebola_faces, { 1.0, 0.0, 0.0 }, velocidad, dx, dy, dz, radio);
	

	//POKEMON
	arma::frowvec posicion_pokemon = posicionpikachu();
	//posicion_pokemon = { -1,0,-1 };
	std::vector<Face> pokemon_faces = pokemon_o.faces;
	arma::fmat transf_pokemon = Tr.S(0.3,0.3,0.3)*Tr.R(0, 1, 0, -90.0)*Tr.T(posicion_pokemon[0], posicion_pokemon[1], posicion_pokemon[2]);
	//Transformacion, caras, colores, S, V
	radio = pokemon_o.biggestOne;
	Pokemon pokemon = Pokemon(transf_pokemon, pokemon_faces, { 1.0, 1.0, 0.0 }, 0.7, 0, posicion_pokemon, radio);
	pokemon.mueve(transf_pokemon);

	if (!glfwInit())
	{
		fprintf(stderr, "Fallo al inicializar GLFW\n");
		getchar();
		return -1;
	}

	window = glfwCreateWindow(1024, 768, "Pokemon Go VECG", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Fallo al abrir la ventana de GLFW.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

	//  Proyecciones
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	float ar = width / height;

	//  Proyecci�n en paralelo
	glViewport(0, 0, width, height);
	glOrtho(-ar, ar, -1.0, 1.0, -40.0, 40.0);
	

	//  Proyecci�n en perspectiva
	//glFrustum(-ar, ar, -ar, ar, 0.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	do {
		//Mueve camara
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			arma::fcolvec transeye = { {eye[0]}, {eye[1]}, {eye[2]} ,{1.0} };
			arma::fmat rotarcamara = Tr.R(0.0, 1.0, 0.0, -5.0);
			arma::fcolvec res = rotarcamara*transeye;
			eye = { res[0], res[1], res[2] };
			DOP = arma::normalise(camera - eye);
			
			
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			arma::fcolvec transeye = { {eye[0]}, {eye[1]}, {eye[2]} ,{1.0} };
			arma::fmat rotarcamara = Tr.R(0.0, 1.0, 0.0, 5.0);
			arma::fcolvec res = rotarcamara * transeye;
			eye = { res[0], res[1], res[2] };
			DOP = arma::normalise(camera - eye);


		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			arma::fcolvec transeye = { {eye[0]}, {eye[1]}, {eye[2]} ,{1.0} };
			float angle = 2.0;
			if (angley >= 76.0) {
				angle = 0.0;
			}
			angley += angle;
			arma::fmat rotarcamara = Tr.R(0.0, 0.0, 1.0, angle);
			arma::fcolvec res = rotarcamara * transeye;
			eye = { res[0], res[1], res[2] };
			DOP = arma::normalise(camera - eye);


		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			arma::fcolvec transeye = { {eye[0]}, {eye[1]}, {eye[2]} ,{1.0} };
			float angle = -2.0;
			if (angley <= -50.0) {

				angle = 0.0;
			}
			angley += angle;
			arma::fmat rotarcamara = Tr.R(0.0, 0.0, 1.0, angle);
			arma::fcolvec res = rotarcamara * transeye;
			eye = { res[0], res[1], res[2] };
			DOP = arma::normalise(camera - eye);


		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eye[0], eye[1], eye[2],
			camera[0], camera[1], camera[2],
			0.0, 1.0, 0.0);

		//ground
		vector<Vertex> ground_vertices;
		Vertex vg = Vertex(-9, 0, -5);
		ground_vertices.push_back(vg);
		vg = Vertex(9, 0, -5);
		ground_vertices.push_back(vg);
		vg = Vertex(9, -0.1, 5);
		ground_vertices.push_back(vg);
		vg = Vertex(-9, -0.1, 5);
		ground_vertices.push_back(vg);

		glBegin(GL_QUADS);
		glColor3f(0, 0.2, 0);
		for (int i = 0; i < 4; i++)
		{
			arma::frowvec vert = ground_vertices[i].getVertex();
			glVertex3f(vert[0], vert[1], vert[2]);


		}
		glEnd();

		// Dibujar el pokemon


		vector<Face> visibles_pokemon = pokemon.iluminacion(DOP);
		vector<arma::frowvec> colores = pokemon.colorea(visibles_pokemon);
		glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < visibles_pokemon.size(); i++) {
			glColor3f(colores[i][0], colores[i][1], colores[i][2]);
			for (int j = 0; j < 3; j++) {
				arma::frowvec vert = visibles_pokemon[i].vertices[j].getVertex();
				glVertex3f(vert[0], vert[1], vert[2]);
			}

		}
		glEnd();
		// Fin dibujado del pokemon

		// Dibujar la pokebola[0].vertices[0].getVertex();
		posicion_pokemon = pokemon.faces[200].vertices[0].getVertex();
		std::vector< Vertex > pokebola_vertices = pokebola.lanza(transf, pokemon.radio, posicion_pokemon);

		glColor3f(pokebola.color[0], pokebola.color[1], pokebola.color[2]);
		glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < pokebola_vertices.size(); i++) {
			arma::frowvec vert = pokebola_vertices[i].getVertex();
			glVertex3f(vert[0], vert[1], vert[2]);
		}
		glEnd();
		// Fin dibujado de la pokebola

		
			


			//Checa si lo atrapo
			if (pokebola.atrapa)
			{
				std::cout << "ATRAPADO" << endl;

				/*glfwTerminate();
				fflush(stdin);
				getchar();

				return 0;*/
			}


		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);



	glfwTerminate();

	return 0;
}