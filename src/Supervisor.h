#ifndef SUPERVISORES_H_
#define SUPERVISORES_H_

#include <string>
#include <iostream>
#include <vector>
#include "Projecto.h"

class Supervisor : public Pessoa{
	unsigned int maxProj;
	vector<Projecto> Projectos;

public:
	Supervisor(string n, unsigned int nrmax);
	Supervisor(string n, vector<Projecto>  proj,unsigned int nrmax);
	void setNome(string nome);
	string getNome() const;
	vector<Projecto> getPreferencias() const;
	void setProj(const vector<Projecto> p);
	void addProj(Projecto novaPref);
	void setnrMAX(unsigned int nrmax);
	void removeProj(Projecto p);
	bool operator == (const Supervisor &S) const;
	friend ostream & operator << (ostream &os, Supervisor &S);
};






#endif /* SUPERVISORES_H_ */
