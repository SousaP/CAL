#ifndef PROPONENTE_H_
#define PROPONENTE_H_

#include <string>
#include <iostream>
#include <vector>
#include "Estudante.h"
#include "Projecto.h"

class Proponente: public Pessoa {
	bool Docente;
	Projecto* guia;
	vector<Estudante*> PrefE;

public:
	Proponente(string n, vector<Estudante*> pref, bool Docen, Projecto* g);
	Proponente(string n, bool Docen,Projecto* g);
	void setNome(string nome);
	vector<Estudante*> getPreferencias() const;
	void setPref(const vector<Estudante*> pref);
	void addPref(Estudante* novaPref);
	void setDocente(bool newDocente);
	void removePref(Estudante* pref);
	bool operator ==(const Proponente &P) const;
	friend ostream & operator <<(ostream &os, const Proponente &P);
	bool nrPref();
	string getProj();
	Pessoa* getMarry() {
		return p;
	}
	void gettingmarried(Pessoa* p);
	bool getDocente();
	Projecto* getProjP();
	bool nasPrefs(Pessoa* p);
	string getNomeClass();
};

#endif /* PROPONENTE_H_ */
