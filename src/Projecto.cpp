#include "Projecto.h"

Projecto :: Projecto(string n, bool superv){
	nome = n;
	supervisor = superv;
}

void Projecto :: setNome(string nome){
	this->nome = nome;
}

string Projecto ::getNome() const{
	return nome;
}

bool Projecto :: getSuperv() const{
	return supervisor;
}

bool Projecto :: operator == (const Projecto &P) const{
   return (this->nome == P.nome && this->supervisor == P.supervisor);
}

ostream & operator << (ostream &os,const Projecto &P){
	os << "Projecto: " << P.getSuperv() << endl;
	return os;
}
