#ifndef PROJECTOS_H_
#define PROJECTOS_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Projectos {
	string nome;
	bool supervisor;

public:
	Projectos(string n, bool superv);
	void setNome(string nome);
	string getNome() const;
	bool getSuperv() const;
	bool &operator == (const Projectos &P) const;
	ostream & operator << (ostream &os, const Projectos &P);
};


#endif /* PROJECTOS_H_ */
