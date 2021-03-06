#include "Proponente.h"

Proponente::Proponente(string n, bool Docen, Projecto* g) :
		Docente(Docen), Pessoa(iD, n), guia(g) {
	incID();
}

Proponente::Proponente(string n, vector<Estudante*> pref, bool Docen,
		Projecto* g) :
		guia(g), PrefE(pref), Docente(Docen), Pessoa(iD, n) {
	incID();
}

void Proponente::setNome(string nome) {
	this->nome = nome;
}

vector<Estudante*> Proponente::getPreferencias() const {
	return PrefE;
}

void Proponente::setPref(const vector<Estudante*> pref) {
	PrefE = pref;
}

void Proponente::addPref(Estudante* novaPref) {
	PrefE.push_back(novaPref);
}

void Proponente::setDocente(bool newDocente) {
	Docente = newDocente;
}

void Proponente::removePref(Estudante* pref) {
	vector<Estudante*>::iterator it = PrefE.begin();

	for (; it != PrefE.end(); it++) {
		if ((*(*it)) == (*pref)) {
			PrefE.erase(it);
			return;
		}
	}
}

bool Proponente::operator ==(const Proponente &P) const {
	return (this->nome == P.nome && this->Docente == P.Docente
			&& this->PrefE == P.PrefE);
}

ostream &operator <<(ostream &os, const Proponente &P) {
	os << "Nome: ";
	os << P.getNome();
	os << "  Preferencias: ";
	vector<Estudante*> temp = P.getPreferencias();
	for (unsigned int i = 0; i < temp.size(); i++) {
		os << (*temp[i]).getNome();
		os << ", ";
	}
	return os;
}

bool Proponente::nrPref() {

	if (PrefE.size() == 0)
		return false;
	else
		return true;
}

string Proponente::getProj() {
	string retorno = "Projecto: ";
	retorno += guia->getNome();
	return retorno;
}
void Proponente::gettingmarried(Pessoa* p) {
	this->p = p;
	married = true;
}

bool Proponente::getDocente() {
	return Docente;
}

Projecto* Proponente::getProjP() {
	return guia;
}

bool Proponente::nasPrefs(Pessoa* p) {
	for (unsigned int i = 0; i < PrefE.size(); i++)
		if (PrefE[i]->getNome() == p->getNome())
			return true;

	return false;
}

string Proponente::getNomeClass(){
	string e = " (Proponente) ";
		e += nome;
		return e;
}
