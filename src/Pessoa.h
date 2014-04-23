#ifndef PESSOA_H_
#define PESSOA_H_

#include "string"
using namespace std;


class Pessoa {

protected:

	string nome;
	bool married;

public:

	Pessoa(unsigned int n, string nome){
		this->nome = nome;
		nrP = n;}
	static unsigned int iD;
	unsigned int nrP;
	virtual bool nrPref(){
		// retorna se tem preferencias ou nao
	}
	static void incID(){
		iD++;
	}
	unsigned int getID(){return nrP;}
	bool isMarried() {return married;}

};




#endif /* PESSOA_H_ */
