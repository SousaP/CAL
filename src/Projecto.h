#ifndef Projecto_H_
#define Projecto_H_

#include <string>
#include <iostream>
#include <vector>
#include "Pessoa.h"

using namespace std;

class Projecto {
	string nome;
	bool supervisor;

public:
	Projecto() {};
	Projecto(string n, bool superv);
	void setNome(string nome);
	string getNome() const;
	bool getSuperv() const;
	bool operator ==(const Projecto &P) const;
	friend ostream & operator <<(ostream &os, const Projecto &P);
};

#endif /* Projecto_H_ */
