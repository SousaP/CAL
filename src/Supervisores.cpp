#include <Supervisores.h>

Supervisores :: Supervisores(string n, vector<Projectos>  proj,unsigned int nrmax){
	nome = n;
	projectos = proj;
	maxProj = nrmax;
}

void Supervisores :: setNome(string nome){
	this->nome = nome;
}

string Supervisores :: getNome() const{
	return nome;
}

vector<Projectos> Supervisores ::getPreferencias() const{
	return projectos;
}

void Supervisores :: setProj(const vector<Projectos> p){
	projectos = p;
}

void Supervisores :: addProj(Projectos novaPref){
	projectos.push_back(novaPref);
}

void Supervisores :: setnrMAX(unsigned int nrmax){
	maxProj = nrmax;
}

void Supervisores :: removeProj(Projectos p){
	vector<Projectos>::iterator it = projectos.begin();

			for (; it != projectos.end(); it++) {
				if ((*it) == p) {
					projectos.erase(it);
					return;
				}
			}
}

bool &Supervisores :: operator == (const Supervisores &S) const{
	return this->nome == S.nome && this->maxProj == S.maxProj && this->projectos == S.projectos;
}

ostream &Supervisores :: operator << (ostream &os, Supervisores &S){
	os << "Nome: ";
		os << S.nome;
		os << "Supervisando: ";
		vector<string> temp = S.projectos;
		for (unsigned int i = 0; i < temp.size(); i++){
			os << temp[i];
			os << ", ";
		}
		return os;
}
