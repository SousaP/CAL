#include "Supervisor.h"

Supervisor :: Supervisor(string n, unsigned int nrmax)
:nome(n), maxProj(nrmax){}


Supervisor :: Supervisor(string n, vector<Projecto>  proj,unsigned int nrmax)
: nome(n), Projectos(proj), maxProj(nrmax){}

void Supervisor :: setNome(string nome){
	this->nome = nome;
}

string Supervisor :: getNome() const{
	return nome;
}

vector<Projecto> Supervisor ::getPreferencias() const{
	return Projectos;
}

void Supervisor :: setProj(const vector<Projecto> p){
	Projectos = p;
}

void Supervisor :: addProj(Projecto novaPref){
	Projectos.push_back(novaPref);
}

void Supervisor :: setnrMAX(unsigned int nrmax){
	maxProj = nrmax;
}

void Supervisor :: removeProj(Projecto p){
	vector<Projecto>::iterator it = Projectos.begin();

			for (; it != Projectos.end(); it++) {
				if ((*it) == p) {
					Projectos.erase(it);
					return;
				}
			}
}

bool Supervisor :: operator == (const Supervisor &S) const{
	return (this->nome == S.nome && this->maxProj == S.maxProj && this->Projectos == S.Projectos);
}

ostream &operator << (ostream &os, Supervisor &S){
	os << "Nome: ";
		os << S.getNome();
		os << "Supervisando: ";
		vector<Projecto> temp = S.getPreferencias();
		for (unsigned int i = 0; i < temp.size(); i++){
			os << temp[i];
			os << ", ";
		}
		return os;
}
