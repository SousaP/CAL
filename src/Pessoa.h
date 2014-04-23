#ifndef PESSOA_H_
#define PESSOA_H_



class Pessoa {

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
