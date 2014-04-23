#ifndef PESSOA_H_
#define PESSOA_H_

#include "string"
using namespace std;


class Pessoa {

protected:

	string nome;

public:

	Pessoa(unsigned int n, string nome){
		this->nome = nome;
		nrP = n;}
	static unsigned int iD;
	unsigned int nrP;
	bool nrPref(){
		// retorna se tem preferencias ou nao
	}
	static void incID(){
		iD++;
	}
	unsigned int getID(){return nrP;}

};




#endif /* PESSOA_H_ */
