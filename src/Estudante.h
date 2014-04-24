#ifndef Estudante_H_
#define Estudante_H_


#include <string>
#include <iostream>
#include <vector>
#include "Projecto.h"

using namespace std;

class Estudante: public Pessoa {
	vector<Projecto*> preferencias;
	bool projecto;

public:
	Estudante(string n, vector<Projecto*> pref);
	Estudante(string n);
	void setNome(string nome);
	string getNome() const;
	vector<Projecto*> getPreferencias() const;
	void setPref(const vector<Projecto*> pref);
	void addPref(Projecto* novaPref);
	void setProj();
	void removePref(Projecto* pref);
	bool operator == (const Estudante &E) const;
	friend ostream &operator << (ostream &os,const Estudante &E);
	bool nrPref();
	Pessoa* getMarry(){return p;}
	void gettingmarried(Pessoa* p);
	bool nasPrefs(Pessoa* p);
};


#endif /* Estudante_H_ */
