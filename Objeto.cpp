#include "Objeto.h"
#include <algorithm>
using namespace std;

Objeto::Objeto()
{
	//ctor
}

Objeto::Objeto(vector<Vertex> vertices_in, vector<Edge> edges_in, vector<Face> faces_in)
{
	//ctor
	vertices = vertices_in;
	edges = edges_in;
	faces = faces_in;
}

//Funcion para escalar los valores si se pasan o son muy chicos para la ventana de OpenGL
void Objeto::scale()
{ 
	while (biggestOne > 0.3)
	{
		biggestOne = biggestOne / 10;
		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].setX(vertices[i].getX() / 2);
			vertices[i].setY(vertices[i].getY() / 2);
			vertices[i].setZ(vertices[i].getZ() / 2);
		}
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].vertices[0].setX(faces[i].vertices[0].getX() / 2);
			faces[i].vertices[0].setY(faces[i].vertices[0].getY() / 2);
			faces[i].vertices[0].setZ( faces[i].vertices[0].getZ() / 2);

			faces[i].vertices[1].setX( faces[i].vertices[1].getX() / 2);
			faces[i].vertices[1].setY( faces[i].vertices[1].getY() / 2);
			faces[i].vertices[1].setZ( faces[i].vertices[1].getZ() / 2);

			faces[i].vertices[2].setX( faces[i].vertices[2].getX() / 2);
			faces[i].vertices[2].setY( faces[i].vertices[2].getY() / 2);
			faces[i].vertices[2].setZ( faces[i].vertices[2].getZ() / 2);
		}

		for (int i = 0; i < edges.size(); i++)
		{
			edges[i].v1.setX( edges[i].v1.getX()/2);
			edges[i].v1.setY( edges[i].v1.getY()/2);
			edges[i].v1.setZ( edges[i].v1.getZ()/2);

			edges[i].v2.setX( edges[i].v2.getX() / 2);
			edges[i].v2.setY( edges[i].v2.getY() / 2);
			edges[i].v2.setZ( edges[i].v2.getZ() / 2);

		}
	}
	/*
	while (biggestOne < 0.1)
	{
		biggestOne = biggestOne * 10;
		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].x = vertices[i].x * 10;
			vertices[i].y = vertices[i].y * 10;
			vertices[i].z = vertices[i].z * 10;
		}
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].vertices[0].x = faces[i].vertices[0].x * 10;
			faces[i].vertices[0].y = faces[i].vertices[0].y * 10;
			faces[i].vertices[0].z = faces[i].vertices[0].z * 10;

			faces[i].vertices[1].x = faces[i].vertices[1].x * 10;
			faces[i].vertices[1].y = faces[i].vertices[1].y * 10;
			faces[i].vertices[1].z = faces[i].vertices[1].z * 10;

			faces[i].vertices[2].x = faces[i].vertices[2].x * 10;
			faces[i].vertices[2].y = faces[i].vertices[2].y * 10;
			faces[i].vertices[2].z = faces[i].vertices[2].z * 10;
		}

		for (int i = 0; i < edges.size(); i++)
		{
			edges[i].v1.x = edges[i].v1.x * 2;
			edges[i].v1.y = edges[i].v1.y * 2;
			edges[i].v1.z = edges[i].v1.z * 2;

			edges[i].v2.x = edges[i].v2.x * 2;
			edges[i].v2.y = edges[i].v2.y * 2;
			edges[i].v2.z = edges[i].v2.z * 10;

		}
	}
	*/
}

Objeto::~Objeto()
{
	//dtor
}


