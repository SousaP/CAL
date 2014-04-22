#ifndef PROPONENTE_H_
#define PROPONENTE_H_

#include <string>
#include <iostream>
#include <vector>
#include "Estudante.h"
#include "Pessoa.h"
#include "Projecto.h"

class Proponente : public Pessoa {
	string nome;
	bool Docente;
	Projecto guia;
	vector<Estudante> PrefE;

public:
	Proponente(string n,vector<Estudante> pref,bool Docen,Projecto g);
	void setNome(string nome);
	string getNome() const;
	vector<Estudante> getPreferencias() const;
	void setPref(const vector<Estudante> pref);
	void addPref(Estudante novaPref);
	void setDocente(bool newDocente);
	void removePref(Estudante pref);
	bool operator == (const Proponente &P) const;
	friend ostream & operator << (ostream &os,const Proponente &P);
};



#endif /* PROPONENTE_H_ */
