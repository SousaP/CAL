#ifndef PESSOA_H_
#define PESSOA_H_

#include "string"
using namespace std;

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
	static void incID() {
		iD++;
	}
	unsigned int getID() {
		return nrP;
	}
	bool isMarried() {
		return married;
	}
	virtual void gettingmarried(Pessoa* p) = 0;
	void gettingsigle() {
		married = false;
		p = NULL;
	}
	virtual bool nasPrefs(Pessoa* p) = 0;
	virtual string getNome() const {
		return nome;
	}

};

#endif /* PESSOA_H_ */
