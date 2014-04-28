#ifndef PESSOA_H_
#define PESSOA_H_

#include "string"
using namespace std;

/*
 * Classe mãe das classes Estudante, Supervisor e Proponente
 */
class Pessoa {

protected:
	Pessoa* p = NULL;
	string nome;
	bool married;

public:

	Pessoa(unsigned int n, string nome);
	static unsigned int iD;
	unsigned int nrP;
	virtual bool nrPref() = 0;
	static void incID();
	unsigned int getID();
	bool isMarried();
	virtual void gettingmarried(Pessoa* p) = 0;
	void gettingsigle();
	virtual bool nasPrefs(Pessoa* p) = 0;
	string getNome() const;
	Pessoa* getPartner();
	virtual string getNomeClass() = 0;

};

#endif /* PESSOA_H_ */
