#ifndef Estudante_H_
#define Estudante_H_


#include <string>
#include <iostream>
#include <vector>
#include "Projecto.h"
#include "Pessoa.h"

using namespace std;

class Estudante: public Pessoa {
	string nome;
	vector<Projecto> preferencias;
	bool projecto;

public:
	Estudante(string n, vector<Projecto> pref);
	void setNome(string nome);
	string getNome() const;
	vector<Projecto> getPreferencias() const;
	void setPref(const vector<Projecto> pref);
	void addPref(Projecto novaPref);
	void setProj();
	void removePref(Projecto pref);
	bool operator == (const Estudante &E) const;
	friend ostream &operator << (ostream &os,const Estudante &E);
};


#endif /* Estudante_H_ */
