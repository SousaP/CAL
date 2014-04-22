#ifndef PESSOA_H_
#define PESSOA_H_



class Pessoa {

public:
	static unsigned int iD;
	unsigned int ID;
	Pessoa(){}
	bool nrPref(){
		// retorna se tem preferencias ou nao
	}
	static void incID(){
		iD++;
	}
	unsigned int getID(){return ID;}

};

unsigned int Pessoa :: iD = 1;


#endif /* PESSOA_H_ */
