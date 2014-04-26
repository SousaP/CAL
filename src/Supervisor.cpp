#include "Supervisor.h"

Supervisor::Supervisor(string n, unsigned int nrmax) :
		maxProj(nrmax), Pessoa(iD, n) {
	incID();
}

Supervisor::Supervisor(string n, vector<Proponente*> proj, unsigned int nrmax) :
		Projectos(proj), maxProj(nrmax), Pessoa(iD, n) {
	incID();
}

void Supervisor::setNome(string nome) {
	this->nome = nome;
}

vector<Proponente*> Supervisor::getPreferencias() const {
	return Projectos;
}

void Supervisor::setProj(const vector<Proponente*> p) {
	Projectos = p;
}

void Supervisor::addProj(Proponente* novaPref) {
	Projectos.push_back(novaPref);
}

void Supervisor::setnrMAX(unsigned int nrmax) {
	maxProj = nrmax;
}

void Supervisor::removeProj(Proponente* p) {
	vector<Proponente*>::iterator it = Projectos.begin();

	for (; it != Projectos.end(); it++) {
		if ((*(*it)) == (*p)) {
			Projectos.erase(it);
			return;
		}
	}
}

bool Supervisor::operator ==(const Supervisor &S) const {
	return (this->nome == S.nome && this->maxProj == S.maxProj
			&& this->Projectos == S.Projectos);
}

ostream &operator <<(ostream &os, Supervisor &S) {
	os << "Nome: ";
	os << S.getNome();
	os << " Preferencias: ";
	vector<Proponente*> temp = S.getPreferencias();
	for (unsigned int i = 0; i < temp.size(); i++) {
		os << (*temp[i]).getProj();
		os << ", ";
	}
	return os;
}

void Supervisor::gettingmarried(Pessoa* p) {
	married = true;
	Casamentos.push_back(p);
}

bool Supervisor::fullProj() {
	return (maxProj == Casamentos.size());
}

bool Supervisor::nasPrefs(Pessoa* p) {
	for (unsigned int i = 0; i < Projectos.size(); i++)
		if (Projectos[i]->getNome() == p->getNome())
			return true;

	return false;
}

unsigned int Supervisor::getMax() const{
	return maxProj;
}

string Supervisor::getNomeClass(){
	string e = " (Supervisor) ";
		e += nome;
		return e;
}

string Supervisor::getCasamentos(){
	string s ="";

	for(int i = 0; i < Casamentos.size(); i++)
	{
		s += " ";
		s += Casamentos[i]->getNome();
		s += " ,";
	}

	return s;
}

void Supervisor::setFree(){
	married = false;
	Casamentos.clear();
}


Pessoa* Supervisor::getMarry() {
		return p;
	}

bool Supervisor::nrPref() {
	if (Projectos.size() == 0)
			return false;
		else
			return true;
	}
