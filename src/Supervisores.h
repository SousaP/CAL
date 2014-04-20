#ifndef SUPERVISORES_H_
#define SUPERVISORES_H_

#include <string>
#include <iostream>
#include <vector>
#include <Projectos.h>

class Supervisores {
	string nome;
	unsigned int maxProj;
	vector<Projectos> projectos;

public:
	Supervisores(string n, vector<Projectos>  proj,unsigned int nrmax);
	void setNome(string nome);
	string getNome() const;
	vector<Projectos> getPreferencias() const;
	void setProj(const vector<Projectos> p);
	void addProj(Projectos novaPref);
	void setnrMAX(unsigned int nrmax);
	void removeProj(Projectos p);
	bool &operator == (const Supervisores &S) const;
	ostream & operator << (ostream &os, Supervisores &S);
};






#endif /* SUPERVISORES_H_ */
