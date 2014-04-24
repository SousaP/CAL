#include "MIEIC.h"

#include <sstream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string>

using namespace std;

MIEIC::MIEIC(unsigned int ano) {
	priFaseOk = false;
	this->ano = ano;
	loadProjectos();
	loadEstudantes();
	loadProponentes();
	loadSupervisores();
	StartPriFase();
	StartSecFase();
}

MIEIC::~MIEIC() {
	saveProjectos();
	saveProponentes();
	saveEstudantes();
	saveSupervisores();
}

void MIEIC::ListProjs() {

	cout << "\n||||| sem LISTAGEM PROJETOS  |||||\n";
	vector<Projecto*>::const_iterator it = Projectos.begin();

	for (unsigned int i = 1; it != Projectos.end(); it++, i++)
		cout << i << ".  " << (*(*it)) << endl;

	cout << "----------------------------------";

}

void MIEIC::ListPropos() {

	cout << "\n||||| LISTAGEM PROPONENTES  |||||\n";
	vector<Proponente*>::const_iterator it = Proponentes.begin();

	for (unsigned int i = 1; it != Proponentes.end(); it++, i++)
		cout << i << ".  " << (*(*it)) << endl;

	cout << "----------------------------------";
}

void MIEIC::ListEstuds() {

	cout << "\n||||| LISTAGEM ESTUDANTES |||||\n";
	vector<Estudante*>::const_iterator it = Estudantes.begin();

	for (unsigned int i = 1; it != Estudantes.end(); it++, i++)
		cout << i << ".  " << (*(*it)) << endl;

	cout << "----------------------------------";

}

void MIEIC::ListSupervs() {

	cout << "\n||||| LISTAGEM SUPERVISORES |||||\n";
	vector<Supervisor*>::const_iterator it = Supervisores.begin();

	for (unsigned int i = 1; it != Supervisores.end(); it++, i++)
		cout << i << ".  " << (*(*it)) << endl;

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
		if ((*it)->getInfo()->getID() == (unsigned int) iDFont)
			font = (*it)->getInfo();

		else if ((*it)->getInfo()->getID() == (unsigned int) iDDist)
			dest = (*it)->getInfo();
	}

	PriFase.addEdge(font, dest, peso);
}

bool MIEIC::verificaPref(int idFont, int idDist) {

	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();

	vector<Vertex<Pessoa*> *>::iterator it = temp.begin();

	for (; it != temp.end(); it++)
		if ((*(*it)->getInfo()).getID() == (unsigned int) idFont)
			break;

	vector<Edge<Pessoa*> > edges = (*it)->getEdges();

	for (unsigned int i = 0; i < edges.size(); i++) {
		if (edges[i].getDest()->getID() == (unsigned int) idDist)
			return true;
	}

	return false;
}

void MIEIC::EstudantesPref() {

	vector<Estudante> temp;

	for (unsigned int i = 0; i < Estudantes.size(); i++)
		if (!(*Estudantes[i]).nrPref()) {
			temp.push_back((*Estudantes[i]));
		}

	for (unsigned int a = 0; a < temp.size(); a++) {
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
			for (unsigned int c = 0; c < Proponentes.size(); c++)
				cout << c << ". " << Proponentes[c]->getProj() << endl;

			int peso = 1;
			do {

				getline(cin, novaPref);
				int novaPrefn = atoi(novaPref.c_str());
				novaPrefn--;
				if ((unsigned int) novaPrefn >= 0
						&& (unsigned int) novaPrefn < Proponentes.size()) {
					if (!verificaPref(Estudantes[IDpref]->getID(),
							Proponentes[novaPrefn]->getID())) {

						addEdge(Estudantes[IDpref]->getID(),
								Proponentes[novaPrefn]->getID(), peso);

						if (Estudantes[IDpref]->nasPrefs(
								Proponentes[novaPrefn])) {
							Estudantes[IDpref]->addPref(
									Proponentes[novaPrefn]->getProjP());
							peso++;
						}
					}

				}

			} while (novaPref != "parar");

		}

	}

}

void MIEIC::ProponentesPref() {
	vector<Proponente*> temp;

	for (unsigned int i = 0; i < Proponentes.size(); i++)
		if (!Proponentes[i]->nrPref())
			temp.push_back(Proponentes[i]);

	for (unsigned int a = 0; a < temp.size(); a++) {
		cout << a << ". " << (*temp[a]) << endl;
	}

	string escolha;
	while (temp.size() > 0 && escolha != "sair") {
		cout << "Proponente [nr] a escolher preferencias? ";
		getline(cin, escolha);
		unsigned int IDpref = atoi(escolha.c_str());
		IDpref--;

		if (IDpref >= 0 && IDpref < temp.size()) {
			cout
					<< "Estudantes [nr] para pref por ordem? \"parar\" para terminar ";
			string novaPref;
			for (unsigned int c = 0; c < Estudantes.size(); c++)
				cout << c << ". " << (*Estudantes[c]) << endl;

			int peso = 1;
			do {

				getline(cin, novaPref);
				int novaPrefn = atoi(novaPref.c_str());
				novaPrefn--;
				if ((unsigned int) novaPrefn >= 0
						&& (unsigned int) novaPrefn < Proponentes.size()) {
					if (!verificaPref(Proponentes[IDpref]->getID(),
							Proponentes[novaPrefn]->getID())) {

						addEdge(Proponentes[IDpref]->getID(),
								Estudantes[novaPrefn]->getID(), peso);

						Estudante E = (*Estudantes[novaPrefn]);
						if (Proponentes[IDpref]->nasPrefs(&E)) {
							Proponentes[IDpref]->addPref(&E);
							peso++;
						}
					}

				}

			} while (novaPref != "parar");

		}

	}

}

void MIEIC::SupervisoresPref() {

	vector<Supervisor> temp;

	for (unsigned int i = 0; i < Supervisores.size(); i++)
		if (!(*Supervisores[i]).nrPref()) {
			temp.push_back((*Supervisores[i]));
		}

	for (unsigned int a = 0; a < temp.size(); a++) {
		cout << a << ". " << temp[a] << endl;
	}

	string escolha;
	while (temp.size() > 0 && escolha != "sair") {
		cout << "Supervisor [nr] a escolher preferencias? ";
		getline(cin, escolha);
		unsigned int IDpref = atoi(escolha.c_str());
		IDpref--;

		if (IDpref >= 0 && IDpref < temp.size()) {
			cout
					<< "Projecto [nr] para pref por ordem? \"parar\" para terminar ";
			string novaPref;
			for (unsigned int c = 0; c < Proponentes.size(); c++)
				cout << c << ". " << Proponentes[c]->getProj() << endl;

			int peso = 1;
			do {

				getline(cin, novaPref);
				int novaPrefn = atoi(novaPref.c_str());
				novaPrefn--;
				if ((unsigned int) novaPrefn >= 0
						&& (unsigned int) novaPrefn < Proponentes.size()) {
					if (!verificaPref(Supervisores[IDpref]->getID(),
							Proponentes[novaPrefn]->getID())) {

						addEdge(Supervisores[IDpref]->getID(),
								Proponentes[novaPrefn]->getID(), peso);

						Proponente P = (*Proponentes[novaPrefn]);
						if (Supervisores[IDpref]->nasPrefs(&P)) {
							Supervisores[IDpref]->addProj(&P);
							peso++;
						}
					}

				}

			} while (novaPref != "parar");

		}

	}

}

void MIEIC::StartPriFase() {

	Pessoa* P;
	for (unsigned int i = 0; i < Estudantes.size(); i++) {
		(*P) = (*Estudantes[i]);
		PriFase.addVertex(P);
	}
}

void MIEIC::StartSecFase() {

	Pessoa* P;
	for (unsigned int i = 0; i < Supervisores.size(); i++) {
		(*P) = (*Supervisores[i]);
		SecFase.addVertex(P);
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
				|| escolha == "projectos") {

		}

	}
}

void MIEIC::SegundaFase() {
	if (!priFaseOk) {
		cout << "\n Primeira fase nao completa";
		return;
	}
	string escolha = "";

	while (escolha != "Sair" && escolha != "sair" && escolha != "4") {
		cout << "1. Escolhas dos Supervisores\n";
		cout << "2. Atribuir Projectos\n";
		cout << "3. Sair";
		getline(cin, escolha);

		if (escolha == "1" || escolha == "Supervisores"
				|| escolha == "supervisores")
			SupervisoresPref();
		else if (escolha == "2" || escolha == "Atribuir"
				|| escolha == "atribuir") {

		}

	}
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
		cout << "\n1. Estudante\n2. Proponente \n3. Supervisor\n5. Sair \n";
		cin >> escolha;

		if (escolha == "1" || escolha == "Estudante"
				|| escolha == "estudante") {
			string nomeE;
			cout << "\nNome: ";

			getline(cin, nomeE);

			Estudante* Ep = new Estudante(nomeE);
			Estudantes.push_back(Ep);
			Pessoa *p = &(*Ep);
			PriFase.addVertex(p);

		} else if (escolha == "2" || escolha == "Proponente"
				|| escolha == "proponente") {
			string nomeP;
			cout << "\nNome: ";

			cin.ignore();
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

			string ProjN;
			cout << "Nome do projecto: ";
			getline(cin, ProjN);

			Projecto* pj  = new Projecto(ProjN,sup);
			Projectos.push_back(pj);
			Proponente* Pp = new Proponente(nomeP, sup,pj);
			Proponentes.push_back(Pp);
			Pessoa *p = &(*Pp);
			PriFase.addVertex(p);
		} else if (escolha == "3" || escolha == "Supervisor"
				|| escolha == "supervisor") {
			string nomeS;
			cout << "\nNome: ";
			cin.ignore();
			getline(cin, nomeS);

			string nrmax;
			do {
				cout << "Numero Maximo de Projectos: ";
				getline(cin, nrmax);
			} while (atoi(nrmax.c_str()) < 0);

			Supervisor* Sp = new Supervisor(nomeS, atoi(nrmax.c_str()));
			Pessoa *p = &(*Sp);
			PriFase.addVertex(p);
			Supervisores.push_back(Sp);
		}

	} while (escolha != "Sair" && escolha != "sair" && escolha != "5");
}

void MIEIC::Menu() {

	string escolha = "";

	while (escolha != "Sair" && escolha != "sair" && escolha != "5") {

		cout
				<< "\n1. Criar elementos\n2. Listagem\n3. Primeira fase.\n4. Segunda Fase.\n5. Sair\n";
		cin.ignore();
		getline(cin, escolha);

		if (escolha == "Criar" || escolha == "criar" || escolha == "1")
			Criar();

		else if (escolha == "Listagem" || escolha == "listagem"
				|| escolha == "2") {
			string list;
			do {

				cout
						<< "\nListagem de: Projectos? Estudantes? Proponentes? Supervisors? Sair \n";
				cin.ignore();
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

	vector<Estudante*> prefTemp = p.getPreferencias();
	vector<Estudante*>::const_iterator itP = prefTemp.begin();

	for (; itP != prefTemp.end(); itP++) {
		if ((*itP)->getMarry()->getID() == e.getID())
			return true;
		if ((*itP)->getID() == (*itP)->getMarry()->getID()) {
			return false;
		}
	}
	return false;
}

bool MIEIC::checkIfAllMarried() {

	vector<Estudante*>::const_iterator itE = Estudantes.begin();
	for (; itE != Estudantes.end(); itE++) {
		if (!(*itE)->isMarried()) {
			return false;
		}
	}
	return true;
}

void MIEIC::solteirar(int id) {

	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();
	for (unsigned int i = 0; i < temp.size(); i++)
		if ((*temp[i]).getInfo()->getID() == (unsigned int) id)
			(*temp[i]).getInfo()->gettingsigle();

}

void MIEIC::Marry() {

	vector<Estudante*>::const_iterator itE = Estudantes.begin();

	while (!checkIfAllMarried()) {
		vector<Proponente*>::const_iterator itP = Proponentes.begin();
		if (!(*itE)->isMarried()) {
			for (; itP != Proponentes.end(); itP++) {
				if (!(*itP)->isMarried()
						&& verificaPref((*itE)->getID(), (*itP)->getID())) {
					(*itP)->gettingmarried((*itE));
					(*itE)->gettingmarried((*itP));

				} else {
					if (comparePropPref(*(*itE), *(*itP))) {
						solteirar((*itP)->getMarry()->getID());
						(*itP)->gettingmarried((*itE));
						(*itE)->gettingmarried((*itP));
					}
				}
			}
		}
	}
}

void MIEIC::setpropofree() {
	for (unsigned int i = 0; i < Supervisores.size(); i++) {
		Supervisores[i]->gettingsigle();
	}
}

bool MIEIC::checkIfAllMarried2() {
	/*
	 * Este check faz check se os proponentes tem todos rela�ao e se os Supervisores ja estao todos com as vagas preenchidas
	 * */

	bool prop = true;
	vector<Proponente*>::const_iterator itP = Proponentes.begin();
	for (; itP != Proponentes.end(); itP++) {
		if ((*itP)->getDocente() && !(*itP)->isMarried()) {
			prop = false;
			break;
		}
	}

	bool Super = true;
	vector<Supervisor*>::const_iterator itS = Supervisores.begin();
	for (; itS != Supervisores.end(); itS++) {
		if (!(*itS)->isMarried() || !(*itS)->fullProj()) {
			Super = false;
			break;
		}
	}

	return (prop && Super);
}

void MIEIC::tryMarrySuperv(Supervisor* s) {

	vector<Vertex<Pessoa*> *> temp = SecFase.getVertexSet();

	vector<Edge<Pessoa*> > Sedges;

	for (unsigned int i = 0; i < temp.size(); i++) {
		if (temp[i]->getInfo()->getID() == s->getID())
			Sedges = temp[i]->getEdges();
	}

	Pessoa* tryM;
	for (unsigned int c = 0; c < Sedges.size(); c++) {
		if (!Sedges[c].getDest()->isMarried()) {
			tryM = Sedges[c].getDest();

			s->gettingmarried(tryM);
			tryM->gettingmarried(s);

		}
	}

}

void MIEIC::MarrySuperv() {

	vector<Supervisor*>::const_iterator itS = Supervisores.begin();

	//por os proponentes solteiros porque vieram da primeira fase
	setpropofree();

	while (!checkIfAllMarried2()) {
		tryMarrySuperv((*itS));

		itS++;

		if (itS == Supervisores.end())
			itS = Supervisores.begin();

	}

}
/*
 Ha um problema.
 ou se calhar nao, mas temos de coordenar o codigo conforme isso
 entao tipo, nos temos o grafo, com a pessoa
 e a pessoa imagine-mos � estudante (so por exemplo)
 se e no grafo o as preferencias estao representadas,
 � preciso ter um membro na fun�ao estudante a dizer quais as preferencias?
 talvez nao... ou talvez sim?

 este projeto tem erros no supervisor, nao percebo porque, mas agora estou cansado,
 amanha de manha tento-os resolver,

 depois agora vi um problema, tinhamos um vector de projetos no estudante
 mas depois nos queremos � ligar um proponente ao estudante, e nao um projeto

 mas o problema tambem � que nao da para ter um vector de proponentes no estudante
 e no proponentes um vetor de estudante, porque depois da montes de erros de inception

 estou agora a tentar rever o codigo e por tudo conforme o que agora esta, a adicionar as preferencias
 no estudante a partir do projeto mas a associar um proponente



 Pedro o Sousa

 */

void MIEIC::loadProjectos() {
	string filename = "Projectos";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ifstream myfile(filename.c_str());

	string nome, boolean, recebido;
	bool sup;

	while (myfile.good()) {

		myfile >> recebido;
		if (recebido != "") {
			nome = recebido;
		}

		myfile >> recebido;
		if (recebido != "") {
			boolean = recebido;
			if (boolean == "true")
				sup = true;
			else
				sup = false;
		}

		Projecto temp = Projecto(nome, sup);
		Projectos.push_back(&temp);
	}
	myfile.close();
}

void MIEIC::loadEstudantes() {
	string filename = "Estudantes";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ifstream myfile(filename.c_str());

	string nome, preferencia, recebido;
	vector<Projecto*> preferencias;

	while (myfile.good()) {

		myfile >> recebido;
		if (recebido != "") {
			nome = recebido;
		}

		while (myfile.good()) {
			myfile >> recebido;
			if (recebido != "") {
				if (recebido == "END") {
					break;
				} else {
					preferencia = recebido;
					for (int i = 0; i < Projectos.size(); i++) {
						if (Projectos[i]->getNome() == preferencia) {
							preferencias.push_back(Projectos[i]);
							break;
						}
					}
				}
			}

		}
		Estudante temp = Estudante(nome, preferencias);
		Estudantes.push_back(&temp);
	}
	myfile.close();

}

void MIEIC::loadProponentes() {
	string filename = "Proponentes";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ifstream myfile(filename.c_str());

	string nomeprop, tipo, nomeproj, preferencia, recebido, boolean;
	bool doc, sup;
	Projecto temp;
	vector<Estudante*> preferencias;

	while (myfile.good()) {

		myfile >> recebido;
		if (recebido != "") {
			nomeprop = recebido;
		}

		myfile >> recebido;
		if (recebido != "") {
			tipo = recebido;
			if (tipo == "true")
				doc = true;
			else
				doc = false;
		}

		myfile >> recebido;
		if (recebido != "") {
			nomeproj = recebido;
		}

		myfile >> recebido;
		if (recebido != "") {
			boolean = recebido;
			if (boolean == "true")
				sup = true;
			else
				sup = false;
		}

		Projecto proj = Projecto(nomeproj, sup);

		while (myfile.good()) {
			myfile >> recebido;
			if (recebido != "") {
				if (recebido == "END") {
					break;
				} else {
					preferencia = recebido;
					for (unsigned int i = 0; i < Estudantes.size(); i++) {
						if (Estudantes[i]->getNome() == preferencia) {
							preferencias.push_back(Estudantes[i]);
							break;
						}
					}

				}

			}
		}
		Proponente temp = Proponente(nomeprop, preferencias, doc, &proj);
		Proponentes.push_back(&temp);
	}
	myfile.close();
}

void MIEIC::loadSupervisores() {
	string filename = "Supervisores";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ifstream myfile(filename.c_str());

	string nome, nrmax, preferencia, recebido;
	unsigned int max;
	vector<Proponente*> preferencias;

	while (myfile.good()) {

		myfile >> recebido;
		if (recebido != "") {
			nome = recebido;
		}

		myfile >> recebido;
		if (recebido != "") {
			nrmax = recebido;
			max = atoi(nrmax.c_str());
		}

		while (myfile.good()) {
			myfile >> recebido;
			if (recebido != "") {
				if (recebido == "END") {
					break;
				} else {
					preferencia = recebido;
					for (unsigned int i = 0; i < Projectos.size(); i++) {
						if (Proponentes[i]->getNome() == preferencia) {
							preferencias.push_back(Proponentes[i]);
							break;
						}
					}
				}
			}

		}
		Supervisor temp = Supervisor(nome, preferencias, max);
		Supervisores.push_back(&temp);
	}
	myfile.close();
}

void MIEIC::saveProjectos() {
	string filename = "Projectos";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ofstream myfile(filename.c_str());

	for (unsigned int i = 0; i < Projectos.size(); i++) {
		myfile << Projectos[i]->getNome() << endl;
		if (Projectos[i]->getSuperv() == true)
			myfile << "true" << endl;
		else
			myfile << "false" << endl;
	}
	myfile.close();
}

void MIEIC::saveEstudantes() {
	string filename = "Estudantes";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ofstream myfile(filename.c_str());

	for (unsigned int i = 0; i < Estudantes.size(); i++) {
		myfile << Estudantes[i]->getNome() << endl;
		for (unsigned int j = 0; j < Estudantes[i]->getPreferencias().size();
				j++) {
			myfile << Estudantes[i]->getPreferencias()[j]->getNome() << endl;
		}
		myfile << "END" << endl;
	}
	myfile.close();
}

void MIEIC::saveProponentes() {
	string filename = "Proponentes";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ofstream myfile(filename.c_str());

	for (unsigned int i = 0; i < Proponentes.size(); i++) {
		myfile << Proponentes[i]->getNome() << endl;
		if (Proponentes[i]->getDocente() == true)
			myfile << "true" << endl;
		else
			myfile << "false" << endl;
		myfile << Proponentes[i]->getProj() << endl;
		if (Proponentes[i]->getProjP()->getSuperv() == true)
			myfile << "true" << endl;
		else
			myfile << "false" << endl;
		for (unsigned int j = 0; j < Proponentes[i]->getPreferencias().size();
				j++) {
			myfile << Proponentes[i]->getPreferencias()[j]->getNome() << endl;
		}
		myfile << "END" << endl;
	}
	myfile.close();
}

void MIEIC::saveSupervisores() {
	string filename = "Supervisores";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ofstream myfile(filename.c_str());

	for (unsigned int i = 0; i < Supervisores.size(); i++) {
		myfile << Supervisores[i]->getNome() << endl
				<< Supervisores[i]->getMax() << endl;
		for (unsigned int j = 0; j < Supervisores[i]->getPreferencias().size();
				j++) {
			myfile << Supervisores[i]->getPreferencias()[j]->getNome() << endl;
		}
		myfile << "END" << endl;
	}
	myfile.close();
}
