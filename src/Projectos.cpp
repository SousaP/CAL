#include "Projectos.h"

Projectos :: Projectos(string n, bool superv){
	nome = n;
	supervisor = superv;
}

void Projectos :: setNome(string nome){
	this->nome = nome;
}

string Projectos ::getNome() const{
	return nome;
}

bool Projectos :: getSuperv() const{
	return supervisor;
}

bool Projectos :: operator == (const Projectos &P) const{
	if(this->nome == P.nome && this->supervisor == P.supervisor)
		return true;
	else return false;
}

ostream & operator << (ostream &os,const Projectos &P){
	os << "Projecto: " << P.getSuperv() << endl;
	return os;
}
