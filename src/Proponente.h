#ifndef PROPONENTE_H_
#define PROPONENTE_H_

#include <string>
#include <iostream>
#include <vector>
#include <Estudantes.h>


class Proponente {
	string nome;
	bool Docente;
	vector<Estudantes> PrefE;

public:
	Proponente(string n, vector<Estudantes> pref,bool Docen);
	void setNome(string nome);
	string getNome() const;
	vector<Estudantes> getPreferencias() const;
	void setPref(const vector<Estudantes> pref);
	void addPref(Estudantes novaPref);
	void setDocente(bool newDocente);
	void removePref(Estudantes pref);
	bool &operator == (const Proponente &P) const;
	ostream & operator << (ostream &os, Proponente &P);
};



#endif /* PROPONENTE_H_ */
