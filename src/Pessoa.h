#ifndef PESSOA_H_
#define PESSOA_H_

#include "string"
using namespace std;


class Pessoa {
	string nome;
public:

	Pessoa(unsigned int n){nrP = n;}
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
