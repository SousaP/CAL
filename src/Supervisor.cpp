#include "Supervisor.h"


Supervisor :: Supervisor(string n, unsigned int nrmax)
:maxProj(nrmax), Pessoa(iD, n){
	incID();
}


Supervisor :: Supervisor(string n, vector<Proponente*>  proj,unsigned int nrmax)
:Projectos(proj), maxProj(nrmax), Pessoa(iD, n){
	incID();
}

void Supervisor :: setNome(string nome){
	this->nome = nome;
}

string Supervisor :: getNome() const{
	return nome;
}

vector<Proponente*> Supervisor ::getPreferencias() const{
	return Projectos;
}

void Supervisor :: setProj(const vector<Proponente*> p){
	Projectos = p;
}

void Supervisor :: addProj(Proponente* novaPref){
	Projectos.push_back(novaPref);
}

void Supervisor :: setnrMAX(unsigned int nrmax){
	maxProj = nrmax;
}

void Supervisor :: removeProj(Proponente* p){
	vector<Proponente*>::const_iterator it = Projectos.begin();

			for (; it != Projectos.end(); it++) {
				if ((*(*it)) == (*p)) {
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

void Supervisor :: gettingmarried(Pessoa* p){
	(*this->p) = (*p);
	married = true;
}

bool Supervisor :: fullProj(){
	return (maxProj == Projectos.size());
}
