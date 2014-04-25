#include "Pessoa.h"

unsigned int Pessoa::iD = 1;

Pessoa::Pessoa(unsigned int n, string nome) {
	this->nome = nome;
	nrP = n;
}

Pessoa* Pessoa::getPartner() {
	return p;
}

unsigned int Pessoa::getID() {
	return nrP;
}

string Pessoa::getNome() const {
	return nome;
}

void Pessoa::gettingsigle() {
	married = false;
	p = NULL;
}

bool Pessoa::isMarried() {
	return married;
}

void Pessoa::incID() {
	iD++;
}
