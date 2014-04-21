#ifndef ESTUDANTES_H_
#define ESTUDANTES_H_


#include <string>
#include <iostream>
#include <vector>
#include "Projectos.h"

using namespace std;

class Estudantes {
	string nome;
	vector<Projectos> preferencias;
	bool projecto;

public:
	Estudantes(string n, vector<Projectos> pref);
	void setNome(string nome);
	string getNome() const;
	vector<Projectos> getPreferencias() const;
	void setPref(const vector<Projectos> pref);
	void addPref(Projectos novaPref);
	void setProj();
	void removePref(Projectos pref);
	bool operator == (const Estudantes &E) const;
	friend ostream &operator << (ostream &os,const Estudantes &E);
};


#endif /* ESTUDANTES_H_ */
