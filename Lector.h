#ifndef LECTOR_H
#define LECTOR_H
#include "Objeto.h"

using namespace std;

class Lector
{
public:
	Lector(string name);
	virtual ~Lector();

	vector<string> split(string str, string sep);
	void read();

	string filename;
	vector<Objeto> objetos;


protected:

private:
};

#endif // LECTOR_H
