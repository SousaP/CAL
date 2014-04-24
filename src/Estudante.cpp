#include "Estudante.h"

Estudante::Estudante(string n, vector<Projecto*> pref) :
		preferencias(pref), projecto(false), Pessoa(iD, n) {
	incID();
}

Estudante::Estudante(string n) :
		Pessoa(iD, n) {
	incID();
	projecto = false;
}

void Estudante::setNome(string nome) {
	this->nome = nome;
}

string Estudante::getNome() const {
	return nome;
}

vector<Projecto*> Estudante::getPreferencias() const {
	return preferencias;
}

void Estudante::setPref(const vector<Projecto*> pref) {
	preferencias = pref;
}

void Estudante::addPref(Projecto* novaPref) {
	preferencias.push_back(novaPref);
}

void Estudante::setProj() {
	projecto = true;
}

void Estudante::removePref(Projecto* pref) {

	vector<Projecto*>::iterator it = preferencias.begin();

	for (; it != preferencias.end(); it++) {
		if ((*(*it)) == (*pref)) {
			preferencias.erase(it);
			return;
		}
	}

}

bool Estudante::operator ==(const Estudante &E) const {

	return (this->nome == E.nome && this->preferencias == E.preferencias
			&& this->projecto == E.projecto);

}

ostream & operator <<(ostream &os, const Estudante &E) {
	os << "Nome: ";
	os << E.getNome();
	os << "Preferencias: ";
	vector<Projecto*> temp = E.getPreferencias();
	for (unsigned int i = 0; i < temp.size(); i++) {
		os << (*temp[i]);
		os << ", ";
	}
	return os;
}

bool Estudante::nrPref() {

	if (preferencias.size() == 0)
		return false;
	else
		return true;
}

void Estudante::gettingmarried(Pessoa* p) {
	(*this->p) = (*p);
	married = true;
}

bool Estudante::nasPrefs(Pessoa* p) {

	for (int i = 0; i < preferencias.size(); i++)
		if (preferencias[i]->getNome() == p->getNome())
			return true;

	return false;
}
