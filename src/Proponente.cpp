#include <Proponente.h>

Proponente :: Proponente(string n, vector<Estudantes> pref,bool Docen){

	nome = n;
	PrefE = pref;
	Docente = Docen;
}


void Proponente ::setNome(string nome){
 this->nome = nome;
}

string Proponente ::getNome() const{
	return nome;
}

vector<Estudantes> Proponente ::getPreferencias() const{
	return PrefE;
}

void Proponente ::setPref(const vector<Estudantes> pref){
	PrefE = pref;
}

void Proponente ::addPref(Estudantes novaPref){
	PrefE.push_back(novaPref);
}

void Proponente ::setDocente(bool newDocente){
	Docente = newDocente;
}

void Proponente ::removePref(Estudantes pref){
	vector<Estudantes>::iterator it = PrefE.begin();

			for (; it != PrefE.end(); it++) {
				if ((*it) == pref) {
					PrefE.erase(it);
					return;
				}
			}
}

bool &Proponente ::operator == (const Proponente &P) const{
	return this->nome == P.nome && this->Docente = P.Docente && this->PrefE == P.PrefE;
}

ostream &Proponente :: operator << (ostream &os, Proponente &P){
	   os << "Nome: ";
		os << P.nome;
		os << "Preferencias: ";
		vector<string> temp = P.PrefE;
		for (unsigned int i = 0; i < temp.size(); i++){
			os << temp[i];
			os << ", ";
		}
		return os;
}
