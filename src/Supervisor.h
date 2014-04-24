#ifndef SUPERVISORES_H_
#define SUPERVISORES_H_

#include <string>
#include <iostream>
#include <vector>
#include "Proponente.h"

class Supervisor: public Pessoa {
	unsigned int maxProj;
	vector<Proponente*> Projectos;

public:
	Supervisor(string n, unsigned int nrmax);
	Supervisor(string n, vector<Proponente*> proj, unsigned int nrmax);
	void setNome(string nome);
	unsigned int getMax() const;
	vector<Proponente*> getPreferencias() const;
	void setProj(const vector<Proponente*> p);
	void addProj(Proponente* novaPref);
	void setnrMAX(unsigned int nrmax);
	void removeProj(Proponente* p);
	bool operator ==(const Supervisor &S) const;
	friend ostream & operator <<(ostream &os, Supervisor &S);
	Pessoa* getMarry() {
		return p;
	}
	bool nrPref() {
		return false;
	}
	void gettingmarried(Pessoa* p);
	bool fullProj();
	bool nasPrefs(Pessoa* p);

};

#endif /* SUPERVISORES_H_ */
