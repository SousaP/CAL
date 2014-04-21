#include "Estudantes.h"


Estudantes :: Estudantes(string n, vector<Projectos> pref)
{
nome = n;
preferencias = pref;
projecto = false;
}


void Estudantes :: setNome(string nome){
	this->nome = nome;
}

string Estudantes :: getNome() const{
return nome;
}

vector<Projectos> Estudantes :: getPreferencias() const{
	return preferencias;
}

void  Estudantes :: setPref(const vector<Projectos> pref){
	preferencias = pref;
}

void Estudantes :: addPref(Projectos novaPref){
	preferencias.push_back(novaPref);
}

void  Estudantes :: setProj(){
	projecto = true;
}

void Estudantes :: removePref(Projectos pref){

	vector<Projectos>::iterator it = preferencias.begin();

		for (; it != preferencias.end(); it++) {
			if ((*it) == pref) {
				preferencias.erase(it);
				return;
			}
		}

}

bool Estudantes :: operator == (const Estudantes &E) const{

	if(this->nome == E.nome && this->preferencias == E.preferencias && this->projecto == E.projecto)
		return true;
	else
		return false;
}


ostream & operator << (ostream &os,const Estudantes &E){
	os << "Nome: ";
	os << E.getNome();
	os << "Preferencias: ";
	vector<Projectos> temp = E.getPreferencias();
	for (unsigned int i = 0; i < temp.size(); i++){
		os << temp[i];
		os << ", ";
	}
	return os;
}
