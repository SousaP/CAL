#include "MIEIC.h"

#include <sstream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

typedef unsigned int unint;
using namespace std;

MIEIC::MIEIC(unsigned int ano) {
	priFaseOk = false;
	this->ano = ano;
	//loadProjectos();
	loadEstudantes();
	loadProponentes();
	loadSupervisores();
	StartPriFase();
}

void MIEIC::loadEstudantes() {
	string temp = "Estudantes";
	temp += ano;
	temp += ".txt";
	ifstream file(temp.c_str());
	if (!file.is_open())
		return;

	string linha;
	string linha2;
	string linha3;
	while (!file.eof()) {
		getline(file, linha);
		getline(file, linha2);

		if (linha != "" && linha2 != "") {

			string indice;
			vector<Projecto> temp;
			do {
				istringstream ss(linha2);
				getline(ss, indice, ',');

				//temp.push_back(Projectos[atoi(indice.c_str())]);

			} while (indice != "");

			//Estudantes.push_back(Estudantes(linha,temp));

		}
	}
	file.close();

}

void MIEIC::loadProponentes() {
	string temp = "Proponentes";
	temp += ano;
	temp += ".txt";
	ifstream file(temp.c_str());
	if (!file.is_open())
		return;

	string linha;
	string linha2;
	string linha3;
	while (!file.eof()) {
		getline(file, linha);
		getline(file, linha2);
		getline(file, linha3);

		if (linha != "" && linha2 != "" && linha3 != "") {

			string indice;
			vector<Estudante> temp;
			do {
				istringstream ss(linha3);
				getline(ss, indice, ',');

				//temp.push_back(Estudantes[atoi(indice.c_str())]);

			} while (indice != "");

			//proponentes.push_back(Proponente(linha,temp,atoi(linha2.c_str())));

		}
	}
	file.close();

}

void MIEIC::loadSupervisores() {
	string temp = "Supervisores";
	temp += ano;
	temp += ".txt";
	ifstream file(temp.c_str());
	if (!file.is_open())
		return;

	string linha;
	string linha2;
	string linha3;
	while (!file.eof()) {
		getline(file, linha);
		getline(file, linha2);
		getline(file, linha3);

		if (linha != "" && linha2 != "" && linha3 != "") {

			string indice;
			vector<Projecto> temp;
			do {
				istringstream ss(linha3);
				getline(ss, indice, ',');

				//temp.push_back(projectos[atoi(indice.c_str())]);

			} while (indice != "");

//			supervisores.push_back(Supervisores(linha,temp,atoi(linha2.c_str())));

		}
	}
	file.close();

}

void MIEIC::ListProjs() {

	cout << "\n||||| sem LISTAGEM PROJETOS  |||||\n";

}

void MIEIC::ListPropos() {

	cout << "\n||||| LISTAGEM PROPONENTES  |||||\n";
	vector<Proponente>::iterator it = Proponentes.begin();

	for (int i = 1; it != Proponentes.end(); it++, i++)
		cout << i << ".  " << (*it) << endl;

	cout << "----------------------------------";
}

void MIEIC::ListEstuds() {

	cout << "\n||||| LISTAGEM ESTUDANTES |||||\n";
	vector<Estudante>::iterator it = Estudantes.begin();

	for (int i = 1; it != Estudantes.end(); it++, i++)
		cout << i << ".  " << (*it) << endl;

	cout << "----------------------------------";

}

void MIEIC::ListSupervs() {

	cout << "\n||||| LISTAGEM SUPERVISORES |||||\n";
	vector<Supervisor>::iterator it = Supervisores.begin();

	for (int i = 1; it != Supervisores.end(); it++, i++)
		cout << i << ".  " << (*it) << endl;

	cout << "----------------------------------";

}

bool MIEIC::Listagem(string pessoa) {

	if (pessoa == "Projectos" || pessoa == "projectos")
		ListProjs();
	else if (pessoa == "Proponentes" || pessoa == "proponentes")
		ListPropos();
	else if (pessoa == "Estudantes" || pessoa == "estudantes")
		ListEstuds();
	else if (pessoa == "Supervisores" || pessoa == "supervisores")
		ListSupervs();
	else
		return false;

	return true;

}

void MIEIC::addEdge(int iDFont, int iDDist, int peso) {

	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();
	vector<Vertex<Pessoa*> *>::iterator it = temp.begin();

	Pessoa* font;
	Pessoa* dest;

	for (; it != temp.end(); it++) {
		if ((*it)->getInfo()->getID() == iDFont)
			font = (*it)->getInfo();

		else if ((*it)->getInfo()->getID() == iDDist)
			dest = (*it)->getInfo();
	}

	PriFase.addEdge(font, dest, peso);
}

bool MIEIC::verificaPref(int idFont, int idDist) {

	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();

	vector<Vertex<Pessoa*> *>::iterator it = temp.begin();

	for (; it != temp.end(); it++)
		if ((*(*it)->getInfo()).getID() == idFont)
			break;

	vector<Edge<Pessoa*> > edges = (*it)->getEdges();

	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].getDest()->getID() == idDist)
			return true;
	}

	return false;
}

void MIEIC::EstudantesPref() {

	vector<Estudante> temp;

	for (int i = 0; i < Estudantes.size(); i++)
		if (!Estudantes[i].nrPref())
			temp.push_back(Estudantes[i]);

	for (int a = 0; a < temp.size(); a++) {
		cout << a << ". " << temp[a] << endl;
	}

	string escolha;
	while (temp.size() > 0 && escolha != "sair") {
		cout << "Estudante [nr] a escolher preferencias? ";
		getline(cin, escolha);
		unsigned int IDpref = atoi(escolha.c_str());
		IDpref--;

		if (IDpref >= 0 && IDpref < temp.size()) {
			cout
					<< "Projecto [nr] para pref por ordem? \"parar\" para terminar ";
			string novaPref;
			for (int c = 0; c < Proponentes.size(); c++)
				cout << c << ". " << Proponentes[c].getProj() << endl;

			int peso = 1;
			do {

				getline(cin, novaPref);
				int novaPrefn = atoi(novaPref.c_str());
				novaPrefn--;
				if (novaPrefn >= 0 && novaPrefn < Proponentes.size()) {
					if (!verificaPref(Estudantes[IDpref].getID(),
							Proponentes[novaPrefn].getID())) {

						addEdge(Estudantes[IDpref].getID(),
								Proponentes[novaPrefn].getID(), peso);

						peso++;
					}

				}

			} while (novaPref != "parar");

		}

	}

}

void MIEIC::ProponentesPref() {

}

void MIEIC::SupervisoresPref() {

}

void MIEIC::StartPriFase() {

	Pessoa* P;
	for (int i = 0; i < Estudantes.size(); i++) {
		P = &Estudantes[i];
		PriFase.addVertex(P);
	}
}

void MIEIC::PrimeiraFase() {
	string escolha = "";

	while (escolha != "Sair" && escolha != "sair" && escolha != "4") {
		cout << "1. Escolhas dos Estudantes\n";
		cout << "2. Escolhas dos Proponentes\n";
		cout << "3. Atribuir Projectos\n";
		cout << "4. Sair";
		getline(cin, escolha);

		if (escolha == "1" || escolha == "Estudantes"
				|| escolha == "estudantes")
			EstudantesPref();
		else if (escolha == "2" || escolha == "Proponentes"
				|| escolha == "proponentes")
			ProponentesPref();
		else if (escolha == "3" || escolha == "Projectos"
				|| escolha == "projectos")
			SupervisoresPref();

	}
}

void MIEIC::SegundaFase() {

}

bool MIEIC::FirstFaseComplete() {

	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();

	vector<Vertex<Pessoa*> *>::iterator it = temp.begin();

	for (; it != temp.end(); it++)
		if ((*(*it)->getInfo()).nrPref())
			return false;

	return true;
}

void MIEIC::Criar() {

	string escolha;

	do {
		cout
				<< "\n1. Projecto\n2. Estudante\n3. Proponente 4. Supervisor\n5. Sair \n";
		cin >> escolha;

		if (escolha == "2" || escolha == "Estudante"
				|| escolha == "estudante") {
			string nomeE;
			cout << "\nNome: ";
			getline(cin, nomeE);

			Estudantes.push_back(Estudante(nomeE));
			Pessoa* P = &Estudantes[Estudantes.size() - 1];
			PriFase.addVertex(P);

		} else if (escolha == "3" || escolha == "Proponente"
				|| escolha == "proponente") {
			string nomeP;
			cout << "\nNome: ";
			getline(cin, nomeP);

			string superv;
			bool sup;
			do {
				cout << "Precisa de um Docente para supervisionar?(S/N) ";

				getline(cin, superv);
			} while (superv != "S" && superv != "s" && superv != "n"
					&& superv != "N");

			if (superv != "S" || superv != "s")
				sup = true;
			else
				sup = false;

			Proponentes.push_back(Proponente(nomeP, sup));
		} else if (escolha == "4" || escolha == "Supervisor"
				|| escolha == "supervisor") {
			string nomeS;
			cout << "\nNome: ";
			getline(cin, nomeS);

			string nrmax;
			do {
				cout << "Numero Maximo de Projectos: ";
				getline(cin, nrmax);
			} while (atoi(nrmax.c_str()) > 0);

			Supervisores.push_back(Supervisor(nomeS, atoi(nrmax.c_str())));
		}

	} while (escolha != "Sair" && escolha != "sair" && escolha != "5");
}

void MIEIC::Menu() {

	string escolha = "";

	while (escolha != "Sair" && escolha != "sair" && escolha != "4") {

		cout
				<< "\n1. Criar elementos\n2. Listagem\n3. Primeira fase.\n4. Segunda Fase.\n5. Sair\n";
		cin >> escolha;

		if (escolha == "Criar" || escolha == "criar" || escolha == "1")
			Criar();

		else if (escolha == "Listagem" || escolha == "listagem"
				|| escolha == "2") {
			string list;
			do {

				cout
						<< "\nListagem de: Projecto? Estudante? Proponente? Supervisor? Sair \n";
				getline(cin, list);

			} while (!Listagem(list) && (list != "Sair" || list != "sair"));

		}

		else if (escolha == "Primeira" || escolha == "primeira"
				|| escolha == "3")
			PrimeiraFase();

		else if (escolha == "Segunda" || escolha == "segunda" || escolha == "4")
			SegundaFase();

	}
}

bool MIEIC::comparePropPref(Estudante e, Proponente p) {

	vector<Estudante> prefTemp = p.getPreferencias();
	vector<Estudante>::iterator itP = prefTemp.begin();

	for (; itP != prefTemp.end(); itP++) {
		if (itP->getMarry()->getID() == e.getID())
			return true;
		if (itP->getID() == itP->getMarry()->getID()) {
			return false;
		}
	}
	return false;
}

bool MIEIC::checkIfAllMarried() {

}

void MIEIC::Marry() {

	vector<Estudante>::iterator itE = Estudantes.begin();

	while (!checkIfAllMarried()) {
		vector<Proponente>::iterator itP = Proponentes.begin();
		if (!itE->isMarried()) {
			for (; itP != Proponentes.end(); itP++) {
				if (!itE->isMarried()) {
					//marry
				} else {
					if (comparePropPref((*itE), (*itP))) {
						//marry E and P
						//make itP->getMarry single
						//actualize itP->getMarry to E
					}
				}
			}
		}
	}
}
