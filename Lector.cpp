#define _CRT_SECURE_NO_WARNINGS
#include "Lector.h"
#include <vector>
#include "Objeto.h"
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"
#include <string>
#include <string.h>
#include <fstream>



using namespace std;

Lector::Lector(string name)
{
	//ctor
	filename = name;


}

Lector::~Lector()
{
	//dtor
}

vector<string> Lector::split(string str, string sep) {
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	vector<string> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

void Lector::read()
{

	ifstream file(filename);
	char linea[128];
	bool start = true;
	Objeto* o = new Objeto();
	while (!file.eof())
	{


		file.getline(linea, sizeof(linea));
		string l(linea);


		cout << linea << endl;

		
		if (l.length() > 1)
		{
			vector<string> arr = split(l, " ");
			//Hace un nuevo objeto declarado con la linea o o g
			if (arr[0] == "o" || arr[0] == "g")
			{
				if (!start)
				{
					objetos.push_back(*o);
					delete(o);
					o = new Objeto();
				}
				if (arr.size() == 1)
					return;
				else
				{
					o->name = arr[1];
				}
				start = false;

			}

			//Hace un nuevo objeto con nombre igual al nombre del documento
			if (start && (arr[0] == "v" || arr[0] == "f"))
			{
				vector<string> aux = split(filename, ".");
				o->name = aux[0];
			}

			//Hace los vertices
			if (arr[0] == "v")
			{
				Vertex v;
				v.setX(stof(arr[1]));
				v.setY(stof(arr[2]));
				v.setZ(stof(arr[3]));
				o->vertices.push_back(v);

				//Calculo del biggestOne para escalar
				if (o->vertices.size() == 1)
				{
					if (v.getX() >= v.getY() && v.getX() >= v.getZ() && v.getX() != 0)
						o->biggestOne = v.getX();
					if (v.getY() >= v.getX() && v.getY() >= v.getZ() && v.getZ() != 0)
						o->biggestOne = v.getY();
					if (v.getZ() >= v.getX() && v.getZ() >= v.getY() && v.getZ() != 0)
						o->biggestOne = v.getZ();
				}
				else {
					if (v.getX() > o->biggestOne && v.getX() != 0)
						o->biggestOne = v.getX();
					if (v.getY() > o->biggestOne && v.getY() != 0)
						o->biggestOne = v.getY();
					if (v.getZ() > o->biggestOne && v.getZ() != 0)
						o->biggestOne = v.getZ();
				}

			}
			
			//Hace las caras
			if (arr[0] == "f")
			{
				Face f;
				
				for (int i = 1; i < arr.size(); i++)
				{
					vector<string> arr2 = split(arr[i], "/");
					f.vertices.push_back(o->vertices[stoi(arr2[0]) - 1]);

					if (i > 1)
					{
						Edge e;
						e.v1 = f.vertices[i - 2];
						e.v2 = f.vertices[i-1];
						f.edges.push_back(e);
						o->edges.push_back(e);
						

						
					}
					if (i == arr2.size() - 1)
					{
						Edge e;
						e.v1 = f.vertices[0];
						e.v2 = f.vertices[i-1];

						f.edges.push_back(e);
						o->edges.push_back(e);
					}
					cout << i << endl;

				}
				

				o->faces.push_back(f);

			}

		}



	}
	cout << "Biggest One: " << o->biggestOne << endl;
	o->scale();
	objetos.push_back(*o);
	file.close();

}

