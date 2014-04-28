#include "MIEIC.h"

#include <sstream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string>

using namespace std;

/*
 * Construtor da classe MIEIC, trata do carregamento dos dados guardados em ficheiros de texto
 */
MIEIC::MIEIC(unsigned int ano) {
	priFaseOk = false;
	secFaseOk = false;
	this->ano = ano;
	loadProjectos();
	loadEstudantes();
	loadProponentes();
	loadSupervisores();
	StartPriFase();
	StartSecFase();
}

/*
 * Destrutor da classe, guarda todos as alterações feitas aos elementos da estrutura em ficheiros de texto
 */
MIEIC::~MIEIC() {
	saveProjectos();
	saveProponentes();
	saveEstudantes();
	saveSupervisores();
}

/*
 * Função que apresenta a lista de todos os Projetos
 */
void MIEIC::ListProjs() {

	cout << "\n||||| LISTAGEM PROJETOS  |||||\n";
	vector<Projecto*>::const_iterator it = Projectos.begin();

	for (unsigned int i = 1; it != Projectos.end(); it++, i++)
		cout << i << ".  " << (*(*it)) << endl;

	cout << "----------------------------------";

}

/*
 * Função que apresenta a lista de todos os Proponentes
 */
void MIEIC::ListPropos() {

	cout << "\n||||| LISTAGEM PROPONENTES  |||||\n";
	vector<Proponente*>::const_iterator it = Proponentes.begin();

	for (unsigned int i = 1; it != Proponentes.end(); it++, i++)
		cout << i << ". " << (*(*it)) << endl;

	cout << "----------------------------------";
}

/*
 * Função que apresenta a lista de todos os Estudantes
 */
void MIEIC::ListEstuds() {

	cout << "\n||||| LISTAGEM ESTUDANTES |||||\n";
	vector<Estudante*>::const_iterator it = Estudantes.begin();

	for (unsigned int i = 1; it != Estudantes.end(); it++, i++)
		cout << i << ". " << (*(*it)) << endl;

	cout << "----------------------------------";

}

/*
 * Função que apresenta a lista de todos os Supervisores
 */
void MIEIC::ListSupervs() {

	cout << "\n||||| LISTAGEM SUPERVISORES |||||\n";
	vector<Supervisor*>::const_iterator it = Supervisores.begin();

	for (unsigned int i = 1; it != Supervisores.end(); it++, i++)
		cout << i << ".  " << (*(*it)) << endl;

	cout << "----------------------------------";

}

/*
 * Função que apresenta a no Standard Output os grafos existentes na classe MIEIC
 */
void MIEIC::ListGrafo() {

	cout << "\n||||| GRAFO 1 |||||\n";
	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();
	vector<Vertex<Pessoa*> *>::const_iterator it = temp.begin();

	for (unsigned int i = 1; it != temp.end(); it++, i++)
		cout << i << ".  " << (*it)->getInfo()->getNomeClass() << "\n";

	cout << "----------------------------------";

	cout << "\n||||| GRAFO 2 |||||\n";
	temp = SecFase.getVertexSet();
	it = temp.begin();

	for (unsigned int i = 1; it != temp.end(); it++, i++)
		cout << i << ".  " << (*it)->getInfo()->getNomeClass() << "\n";

	cout << "----------------------------------";

	//showgraph();
}

/*
 * Gere a apresentação das listagens
 */
bool MIEIC::Listagem(string pessoa) {

	if (pessoa == "Grafo" || pessoa == "grafo" || pessoa == "1")
		ListGrafo();
	else if (pessoa == "Projectos" || pessoa == "projectos" || pessoa == "2")
		ListProjs();
	else if (pessoa == "Estudantes" || pessoa == "estudantes" || pessoa == "3")
		ListEstuds();
	else if (pessoa == "Proponentes" || pessoa == "proponentes"
			|| pessoa == "4")
		ListPropos();
	else if (pessoa == "Supervisores" || pessoa == "supervisores"
			|| pessoa == "5")
		ListSupervs();
	else
		return false;

	return true;

}

/*
 * Adiciona uma Edge ao grafo cujo número é passado pelo parâmetro "grafo", com o peso dado pelo parâmetro "peso" e com
 * o destino e fonte que também são passados como parâmtros
 */
bool MIEIC::addEdge(int iDFont, int iDDist, int peso, int grafo) {

	vector<Vertex<Pessoa*> *> temp;

	if (grafo == 1)
		temp = PriFase.getVertexSet();
	else if (grafo == 2)
		temp = SecFase.getVertexSet();
	else
		return false;

	vector<Vertex<Pessoa*> *>::iterator it = temp.begin();

	Pessoa* font;
	Pessoa* dest;

	for (; it != temp.end(); it++) {
		if ((*it)->getInfo()->getID() == (unsigned int) iDFont)
			font = (*it)->getInfo();

		else if ((*it)->getInfo()->getID() == (unsigned int) iDDist)
			dest = (*it)->getInfo();
	}

	if (grafo == 1)
		return PriFase.addEdge(font, dest, peso);
	else
		return SecFase.addEdge(font, dest, peso);
}

/*
 * Verifica se o vertex com id=idDist, presente no grafo com o número do parâmetro "grafo"
 * está presente nas preferências do vertex com id=idFonte
 */
bool MIEIC::verificaPref(int idFont, int idDist, int grafo) {

	vector<Vertex<Pessoa*> *> temp;

	if (grafo == 1)
		temp = PriFase.getVertexSet();
	else if (grafo == 2)
		temp = SecFase.getVertexSet();
	else
		return false;

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

/*
 * Adiciona preferencias dos Estudantes em relação aos projetos segundo comandos do utilizador
 */
void MIEIC::EstudantesPref() {

	cout << "\n PREFERENCIAS DOS ESTUDANTES \n";

	vector<Estudante*> temp;

	for (unsigned int i = 0; i < Estudantes.size(); i++)
		if (!(*Estudantes[i]).nrPref()) {
			temp.push_back(Estudantes[i]);
		}

	for (unsigned int a = 0; a < temp.size(); a++) {
		cout << a + 1 << ". " << (*temp[a]) << endl;
	}

	string escolha;
	string novaPref;
	while (temp.size() > 0 && escolha != "sair") {
		cout << "Estudante [nr] a escolher preferencias? ";
		getline(cin, escolha);
		unsigned int IDpref = atoi(escolha.c_str());
		IDpref--;

		if (IDpref >= 0 && IDpref < temp.size()) {

			for (unsigned int c = 0; c < Proponentes.size(); c++)
				cout << c + 1 << ". " << Proponentes[c]->getProj() << endl;

			cout
					<< "Projecto [nr] para pref por ordem? \"parar\" para terminar\n";
			int peso = 1;
			do {

				getline(cin, novaPref);
				int novaPrefn = atoi(novaPref.c_str());
				novaPrefn--;
				if ((unsigned int) novaPrefn >= 0
						&& (unsigned int) novaPrefn < Proponentes.size()) {
					if (!verificaPref(temp[IDpref]->getID(),
							Proponentes[novaPrefn]->getID(), 1)) {

						if (!addEdge(temp[IDpref]->getID(),
								Proponentes[novaPrefn]->getID(), peso, 1))
							cout << "\n\n ERRO AO ADICIONAR PREFERENCIAS \n\n";

						if (!temp[IDpref]->nasPrefs(Proponentes[novaPrefn])) {
							temp[IDpref]->addPref(
									Proponentes[novaPrefn]->getProjP());
							peso++;
						}
					}

				}

			} while (novaPref != "parar");
			return;
		}

	}

}

/*
 * Adiciona preferencias dos Proponentes em relação aos Estudantes segundo comandos do utilizador
 */
void MIEIC::ProponentesPref() {

	cout << "\n PREFERENCIAS DOS PROPONENTES \n";
	vector<Proponente*> temp;

	for (unsigned int i = 0; i < Proponentes.size(); i++)
		if (!Proponentes[i]->nrPref())
			temp.push_back(Proponentes[i]);

	for (unsigned int a = 0; a < temp.size(); a++) {
		cout << a + 1 << ". " << (*temp[a]) << endl;
	}

	string escolha;
	while (temp.size() > 0 && escolha != "sair") {
		cout << "\nProponente [nr] a escolher preferencias? ";
		getline(cin, escolha);
		unsigned int IDpref = atoi(escolha.c_str());
		IDpref--;

		if (IDpref >= 0 && IDpref < temp.size()) {

			string novaPref;
			for (unsigned int c = 0; c < Estudantes.size(); c++)
				cout << c + 1 << (*Estudantes[c]) << endl;
			cout
					<< "Estudantes [nr] para pref por ordem? \"parar\" para terminar\n";
			int peso = 1;
			do {

				getline(cin, novaPref);
				int novaPrefn = atoi(novaPref.c_str());
				novaPrefn--;
				if ((unsigned int) novaPrefn >= 0
						&& (unsigned int) novaPrefn < Estudantes.size()) {
					if (!verificaPref(temp[IDpref]->getID(),
							Estudantes[novaPrefn]->getID(), 1)) {

						if (!addEdge(temp[IDpref]->getID(),
								Estudantes[novaPrefn]->getID(), peso, 1))
							cout << "\n\n ERRO AO ADICIONAR PREFERENCIAS \n\n";

						if (!temp[IDpref]->nasPrefs(Estudantes[novaPrefn])) {
							temp[IDpref]->addPref(Estudantes[novaPrefn]);
							peso++;
						}
					}

				}

			} while (novaPref != "parar");
			return;

		}

	}

}

/*
 * Adiciona preferencias dos Supervisores em relação aos projetos segundo comandos do utilizador
 */
void MIEIC::SupervisoresPref() {

	vector<Supervisor*> tempS;

	for (unsigned int i = 0; i < Supervisores.size(); i++)
		if (!Supervisores[i]->nrPref()) {
			tempS.push_back(Supervisores[i]);
		}

	for (unsigned int a = 0; a < tempS.size(); a++) {
		cout << a + 1 << ". " << (*tempS[a]) << endl;
	}

	string escolha;
	while (tempS.size() > 0 && escolha != "sair") {
		cout << "Supervisor [nr] a escolher preferencias? ";
		getline(cin, escolha);
		unsigned int IDpref = atoi(escolha.c_str());
		IDpref--;

		if (IDpref >= 0 && IDpref < tempS.size()) {

			string novaPref;
			vector<Proponente*> tempP;

			for (unsigned int c = 0; c < Proponentes.size(); c++)
				if (Proponentes[c]->getDocente())
					tempP.push_back(Proponentes[c]);

			for (unsigned int c = 0; c < tempP.size(); c++)
				cout << c + 1 << ". " << tempP[c]->getProj() << endl;

			cout
					<< "Projecto [nr] para pref por ordem? \"parar\" para terminar ";
			int peso = 1;
			do {

				getline(cin, novaPref);
				int novaPrefn = atoi(novaPref.c_str());
				novaPrefn--;

				if ((unsigned int) novaPrefn >= 0
						&& (unsigned int) novaPrefn < tempP.size()) {

					if (!verificaPref(tempS[IDpref]->getID(),
							tempP[novaPrefn]->getID(), 2)) {
						if (!addEdge(tempS[IDpref]->getID(),
								tempP[novaPrefn]->getID(), peso, 2))
							cout << "\n\n ERRO AO ADICIONAR PREFERENCIAS \n\n";

						if (!tempS[IDpref]->nasPrefs(tempP[novaPrefn])) {
							tempS[IDpref]->addProj(tempP[novaPrefn]);
							peso++;
						}
					}

				}

			} while (novaPref != "parar");
			return;
		}

	}

}

/*
 * Função principal e gestora da primeira fase a qual consiste em atribuir projetos aos Estudantes
 */
void MIEIC::StartPriFase() {

	Pessoa* P;

	for (unsigned int i = 0; i < Estudantes.size(); i++) {
		P = Estudantes[i];
		PriFase.addVertex(P);
	}

	for (unsigned int i = 0; i < Proponentes.size(); i++) {
		P = Proponentes[i];
		PriFase.addVertex(P);
	}

	vector<Projecto*> temp;
	vector<Estudante*> tempE;
	for (unsigned int i = 0; i < Estudantes.size(); i++) {
		temp = Estudantes[i]->getPreferencias();
		for (unsigned int c = 0; c < Proponentes.size(); c++) {

			for (unsigned int d = 0; d < temp.size(); d++) {

				if (Proponentes[c]->getProjP()->getNome() == temp[d]->getNome())
					if (!addEdge(Estudantes[i]->getID(),
							Proponentes[c]->getID(), (d + 1), 1))
						cout << "\n\n ERRO AO ADICIONAR PREFERENCIAS \n\n";

			}

			tempE = Proponentes[c]->getPreferencias();

			for (unsigned int d = 0; d < tempE.size(); d++) {

				if (tempE[d]->getNome() == Estudantes[i]->getNome())
					if (!addEdge(Proponentes[c]->getID(),
							Estudantes[i]->getID(), (d + 1), 1))
						cout << "\n\n ERRO AO ADICIONAR PREFERENCIAS \n\n";

			}

		}
	}

}

/*
 * Função principal e gestora da segunda fase a qual consiste em atribuir projetos aos Supervisores
 */
void MIEIC::StartSecFase() {

	Pessoa* P;

	for (unsigned int i = 0; i < Proponentes.size(); i++) {
		P = Proponentes[i];
		SecFase.addVertex(P);
	}

	for (unsigned int i = 0; i < Supervisores.size(); i++) {
		P = Supervisores[i];
		SecFase.addVertex(P);

	}

	vector<Proponente*> temp;
	for (unsigned int i = 0; i < Supervisores.size(); i++) {

		temp = Supervisores[i]->getPreferencias();
		for (unsigned int c = 0; c < Proponentes.size(); c++) {

			for (unsigned int d = 0; d < temp.size(); d++) {

				if (Proponentes[c]->getID() == temp[d]->getID())
					if (!addEdge(Supervisores[i]->getID(),
							Proponentes[c]->getID(), (d + 1), 2))
						cout << "\n\n ERRO AO ADICIONAR PREFERENCIAS \n\n";

			}
		}

	}

}

/*
 * Função que retorna o peso da Edge(preferência) com o número id passado como parâmetro
 */
unsigned int MIEIC::nrPref(Vertex<Pessoa*> *p, unsigned int id) {
	vector<Edge<Pessoa*> > temp = p->getEdges();

	for (unsigned int pos = 0; pos < temp.size(); pos++)
		if (temp[pos].getDest()->getID() == id)
			return temp[pos].getweight();

	return 0;
}

/*
 * Apresenta no standard output todos os casamentos realizados entre projects/proponentes e estudantes
 */
void MIEIC::showWedd() {
//	if (!priFaseOk)
	//	return;

	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();

	vector<Vertex<Pessoa*> *>::const_iterator it = temp.begin();

	cout << "\n CASAMENTOS \n";
	for (; it != temp.end(); it++) {
		if ((*it)->getInfo()->isMarried()) {
			cout << "\n " << (*it)->getInfo()->getNomeClass()
					<< " esta casado com "
					<< (*it)->getInfo()->getPartner()->getNomeClass();
			cout << " sendo esta a sua "
					<< nrPref((*it), (*it)->getInfo()->getPartner()->getID())
					<< "a opcao\n";
		} else
			cout << "\n " << (*it)->getInfo()->getNomeClass()
					<< " esta solteiro \n";
	}

	cout << "\n----------------\n";
}

/*
 * Menu da primeira fase
 */
void MIEIC::PrimeiraFase() {
	string escolha = "";

	while (escolha != "Sair" && escolha != "sair" && escolha != "5") {
		cout << "1. Escolhas dos Estudantes\n";
		cout << "2. Escolhas dos Proponentes\n";
		cout << "3. Atribuir Projectos\n";
		cout << "4. Ver Casamentos\n";
		cout << "5. Sair";
		cin >> escolha;

		if (escolha == "1" || escolha == "Estudantes"
				|| escolha == "estudantes")
			EstudantesPref();
		else if (escolha == "2" || escolha == "Proponentes"
				|| escolha == "proponentes")
			ProponentesPref();
		else if (escolha == "3" || escolha == "Projectos"
				|| escolha == "projectos") {
			if (!FirstFaseComplete())
				cout << "\n\n-----Sem preferencias necessarias---\n\n";
			else
				Marry();
		} else if (escolha == "4" || escolha == "casamentos"
				|| escolha == "Casamentos")
			showWedd();

	}
}

/*
 * Apresenta no standard output todos os casamentos realizados entre projects/proponentes e supervisores
 */
void MIEIC::showSupervProjs() {
	if (!secFaseOk)
		return;
	vector<Supervisor *>::const_iterator it = Supervisores.begin();

	cout << "\n CASAMENTOS \n";
	for (; it != Supervisores.end(); it++) {
		if ((*it)->isMarried()) {
			cout << "\n " << (*it)->getNomeClass() << " esta a supervisionar: "
					<< (*it)->getCasamentos()

					<< endl;
		} else
			cout << "\n " << (*it)->getNomeClass() << " esta solteiro\n";
	}
	cout << "\n----------------\n";

}

/*
 * Menu da segunda fase
 */
void MIEIC::SegundaFase() {
	if (!priFaseOk) {
		cout << "\n Primeira fase nao completa";
		return;
	}
	string escolha = "";

	while (escolha != "Sair" && escolha != "sair" && escolha != "4") {
		cout << "1. Escolhas dos Supervisores\n";
		cout << "2. Atribuir Projectos\n";
		cout << "3. Ver Projectos dos Supervisores\n";
		cout << "4. Sair";
		getline(cin, escolha);

		if (escolha == "1" || escolha == "Supervisores"
				|| escolha == "supervisores")
			SupervisoresPref();
		else if (escolha == "2" || escolha == "Atribuir"
				|| escolha == "atribuir")
			MarrySuperv();
		else if (escolha == "3" || escolha == "Casamento"
				|| escolha == "casamentos")
			showSupervProjs();

	}
}

/*
 * Verifica se a primeira fase está completa
 */
bool MIEIC::FirstFaseComplete() {

	if (Proponentes.size() < Estudantes.size())
		return false;

	for (unsigned int i = 0; i < Proponentes.size(); i++)
		if (!Proponentes[i]->nrPref())
			return false;

	for (unsigned int i = 0; i < Estudantes.size(); i++)
		if (!Estudantes[i]->nrPref())
			return false;

	return true;
}

/*
 * Menu de criação de elementos (Proponentes, estudantes, supervisores e projectos)
 */
void MIEIC::Criar() {

	string escolha;

	do {
		cout << "\n1. Estudante\n2. Proponente \n3. Supervisor\n4. Sair \n";
		cin >> escolha;

		if (escolha == "1" || escolha == "Estudante"
				|| escolha == "estudante") {
			string nomeE;
			cout << "\nNome: ";

			cin.ignore();
			getline(cin, nomeE);

			Estudante* Ep = new Estudante(nomeE);
			Estudantes.push_back(Ep);
			Pessoa *p = Ep;
			if (!PriFase.addVertex(p))
				cout << "\n ERRO AO ADICIONAR AO GRAFO \n";

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

			if (superv == "S" || superv == "s")
				sup = true;
			else
				sup = false;

			string ProjN;
			cout << "Nome do projecto: ";
			getline(cin, ProjN);

			Projecto* pj = new Projecto(ProjN, sup);
			Projectos.push_back(pj);
			Proponente* Pp = new Proponente(nomeP, sup, pj);
			Proponentes.push_back(Pp);
			Pessoa *p = &(*Pp);
			if (!PriFase.addVertex(p))
				cout << "\n ERRO AO ADICIONAR AO GRAFO 1\n";

			if (!SecFase.addVertex(p))
				cout << "\n ERRO AO ADICIONAR AO GRAFO 2\n";
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
			if (!SecFase.addVertex(p))
				cout << "\n ERRO AO ADICIONAR AO GRAFO \n";
			Supervisores.push_back(Sp);
		}

	} while (escolha != "Sair" && escolha != "sair" && escolha != "4");
}

/*
 * Menu principal
 */
void MIEIC::Menu() {

	string escolha = "";
	cin.ignore();
	while (escolha != "Sair" && escolha != "sair" && escolha != "5") {

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
						<< "\nListagem de: Grafo? Projectos? Estudantes? Proponentes? Supervisors? Sair \n";
				getline(cin, list);

			} while (!Listagem(list) && list != "Sair" && list != "sair");

		}

		else if (escolha == "Primeira" || escolha == "primeira"
				|| escolha == "3")
			PrimeiraFase();

		else if (escolha == "Segunda" || escolha == "segunda" || escolha == "4")
			SegundaFase();

	}
}


/*
 * Ve se o proponente prefere o casamento atual ou o possivel casamento com o estudante "e"
 */
bool MIEIC::comparePropPref(Estudante *e, Proponente *p) {

	vector<Estudante*> prefTemp = p->getPreferencias();
	vector<Estudante*>::const_iterator itP = prefTemp.begin();
	for (; itP != prefTemp.end(); itP++) {
		if ((*itP)->getID() == e->getID())
			return true;
		else if ((*itP)->getID() == p->getMarry()->getID())
			return false;
	}

	return false;
}

/*
 * retorna as preferencias do estudante com o id recebido
 */
vector<Proponente*> MIEIC::getProp(unsigned int id) {

	vector<Proponente*> temp;
	vector<Projecto*> pref;
	vector<Estudante*>::const_iterator itE = Estudantes.begin();
	for (; itE != Estudantes.end(); itE++) {

		if ((*itE)->getID() == id) {
			pref = (*itE)->getPreferencias();

			for (unsigned int c = 0; c < pref.size(); c++)
				for (unsigned int i = 0; i < Proponentes.size(); i++)
					if (Proponentes[i]->getProjP()->getNome()
							== pref[c]->getNome())
						temp.push_back(Proponentes[i]);

		}

	}
	return temp;

}

/*
 * Verifica se todos os estudantes têm um projecto atribuido
 */
bool MIEIC::checkStudents() {

	vector<Proponente*> temp;
	vector<Projecto*> pref;
	vector<Estudante*>::const_iterator itE = Estudantes.begin();
	for (; itE != Estudantes.end(); itE++) {
		if (!(*itE)->isMarried()) {
			pref = (*itE)->getPreferencias();

			for (unsigned int i = 0; i < Proponentes.size(); i++)
				for (unsigned int c = 0; c < pref.size(); c++)
					if (Proponentes[i]->getProjP()->getNome()
							== pref[c]->getNome())
						temp.push_back(Proponentes[i]);

			for (unsigned int d = 0; d < temp.size(); d++)
				if (!temp[d]->isMarried())
					return false;
		}
	}

	return true;
}

/*
 * Elimina a ligação de um elemento do grafo a outro elemento
 */
void MIEIC::solteirar(int id) {

	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();
	for (unsigned int i = 0; i < temp.size(); i++)
		if ((*temp[i]).getInfo()->getID() == (unsigned int) id)
			(*temp[i]).getInfo()->gettingsigle();

}

/*
 * Verifica se um proponente com um projeto de nome nomeProj já está ligado a um estudante
 */
bool MIEIC::preferencesOccupied(string nomeProj) {
	vector<Proponente*>::const_iterator itP = Proponentes.begin();
	for (; itP != Proponentes.end(); itP++) {
		if ((*itP)->getProjP()->getNome() == nomeProj && (*itP)->isMarried())
			return true;
	}
	return false;
}

/*
 * Verifica se todos os projetos preferidos pelos estudantes que ainda não têm projecto atribuido ja estão ocupadas
 */
bool MIEIC::checkPreferences() {

	vector<Estudante*> temp;

	vector<Estudante*>::const_iterator itE = Estudantes.begin();
	for (; itE != Estudantes.end(); itE++) {
		if (!(*itE)->isMarried()) {
			temp.push_back(*itE);
		}
	}

	vector<Estudante*>::const_iterator itT = temp.begin();
	for (; itE != temp.end(); itT++) {
		for (unsigned int i = 0; i < (*itT)->getPreferencias().size(); i++) {
			if (!preferencesOccupied((*itT)->getPreferencias()[i]->getNome()))
				return false;
		}
	}

	return true;
}

/*
 * Funçao base para gerar os casamentos da primeira fase
 */
void MIEIC::Marry() {

	vector<Estudante*>::iterator itE = Estudantes.begin();
	vector<Proponente*>::iterator itP = Proponentes.begin();

	vector<Proponente*> pref;
	while (!checkStudents()) {

		if (!(*itE)->isMarried()) {

			pref = getProp((*itE)->getID());

			for (unsigned int i = 0; i < pref.size(); i++) {

				if (!pref[i]->isMarried()) {
					pref[i]->gettingmarried((*itE));
					(*itE)->gettingmarried(pref[i]);
					break;
				} else if (comparePropPref((*itE), pref[i])) {
					solteirar(pref[i]->getMarry()->getID());
					(pref[i])->gettingmarried((*itE));
					(*itE)->gettingmarried(pref[i]);
					break;
				}

			}
		}

		itE++;
		if (itE == Estudantes.end())
			itE = Estudantes.begin();
	}

	priFaseOk = true;
}

/*
 * poe os proponentes solteiros depois da primeira fase
 */
void MIEIC::setpropofree() {
	for (unsigned int i = 0; i < Proponentes.size(); i++) {
		Proponentes[i]->gettingsigle();
	}
}

bool MIEIC::checkIfAllMarried2() {
	/*
	 * Este check faz check se os proponentes tem todos relaçao e se os Supervisores ja estao todos com as vagas preenchidas
	 * */

	vector<Proponente*> pref;
	vector<Supervisor*>::const_iterator itS = Supervisores.begin();
	for (; itS != Supervisores.end(); itS++) {
		pref = (*itS)->getPreferencias();

		if (!(*itS)->fullProj()) {

			for (unsigned int i = 0; i < pref.size(); i++) {
				if (!pref[i]->isMarried())
					return false;
			}

		}
	}

	return true;
}

/*
 * tenta arranjar projetos para o Supervisor s
 */
void MIEIC::tryMarrySuperv(Supervisor* s) {

	vector<Vertex<Pessoa*> *> temp = SecFase.getVertexSet();

	vector<Edge<Pessoa*> > Sedges;

	for (unsigned int i = 0; i < temp.size(); i++) {
		if (temp[i]->getInfo()->getID() == s->getID())
			Sedges = temp[i]->getEdges();
	}

	Pessoa* tryM;
	vector <Proponente*> pref = s->getPreferencias();
	for(unsigned int d = 0; d < pref.size(); d++)
	for (unsigned int c = 0; c < Sedges.size(); c++) {
		if (!Sedges[c].getDest()->isMarried() && pref[d]->getID() == Sedges[c].getDest()->getID()) {
			tryM = Sedges[c].getDest();

			s->gettingmarried(tryM);
			tryM->gettingmarried(s);

			return;
		}
	}

}

/*
 * Funçao base para a distribuiçao de projetos para os supervisores
 */
void MIEIC::MarrySuperv() {

	vector<Supervisor*>::iterator itS = Supervisores.begin();

//por os proponentes solteiros porque vieram da primeira fase
	setpropofree();

	//para o caso de ja ter feito um marry antes
	for (unsigned int i = 0; i < Supervisores.size(); i++)
		Supervisores[i]->setFree();

	while (!checkIfAllMarried2()) {
		tryMarrySuperv((*itS));

		itS++;

		if (itS == Supervisores.end())
			itS = Supervisores.begin();

	}

	secFaseOk = true;
}

/*
 * Funções de load e save dos dados
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

	if (myfile.good())
		while (!myfile.eof()) {
			while (myfile) {

				getline(myfile, recebido);
				if (recebido != "") {
					nome = recebido;
				}

				getline(myfile, recebido);
				if (recebido != "") {
					boolean = recebido;
					if (boolean == "true")
						sup = true;
					else
						sup = false;
				}
				if (nome != "") {
					Projecto* temp = new Projecto(nome, sup);
					Projectos.push_back(temp);
				}
				nome = "";
			}
		}
	myfile.close();
	cout << "Projetos done" << endl;
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

	if (myfile.good())
		while (!myfile.eof()) {

			getline(myfile, recebido);
			if (recebido != "") {
				nome = recebido;
			}

			while (myfile) {
				getline(myfile, recebido);
				if (recebido != "") {
					if (recebido == "END") {
						break;
					} else {
						preferencia = recebido;
						for (unsigned int i = 0; i < Projectos.size(); i++) {
							if (Projectos[i]->getNome() == preferencia) {
								preferencias.push_back(Projectos[i]);
								break;
							}
						}
					}
				}

			}
			if (nome != "") {
				Estudante* temp = new Estudante(nome, preferencias);
				Estudantes.push_back(temp);
			}
			nome = "";
			preferencias.clear();
		}
	myfile.close();

	cout << "Estudantes done" << endl;
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

	if (myfile.good())
		while (!myfile.eof()) {

			getline(myfile, recebido);
			if (recebido != "") {
				nomeprop = recebido;
			}

			getline(myfile, recebido);
			if (recebido != "") {
				tipo = recebido;
				if (tipo == "true")
					doc = true;
				else
					doc = false;
			}

			getline(myfile, recebido);
			if (recebido != "") {
				nomeproj = recebido;
			}

			getline(myfile, recebido);
			if (recebido != "") {
				boolean = recebido;
				if (boolean == "true")
					sup = true;
				else
					sup = false;
			}

			Projecto* proj = new Projecto(nomeproj, sup);

			while (myfile) {
				getline(myfile, recebido);
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
			if (nomeprop != "") {
				Proponente* temp = new Proponente(nomeprop, preferencias, doc,
						proj);
				Proponentes.push_back(temp);
			}
			nomeprop = "";
			preferencias.clear();
		}

	myfile.close();

	cout << "Proponentes done" << endl;
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

	if (myfile.good())
		while (!myfile.eof()) {

			getline(myfile, recebido);
			if (recebido != "") {
				nome = recebido;
			}

			getline(myfile, recebido);
			if (recebido != "") {
				nrmax = recebido;
				max = atoi(nrmax.c_str());
			}

			while (myfile) {
				getline(myfile, recebido);
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
			if (nome != "") {
				Supervisor* temp = new Supervisor(nome, preferencias, max);
				Supervisores.push_back(temp);
			}
			nome = "";
			preferencias.clear();
		}

	myfile.close();

	cout << "Supervisores done" << endl;
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
		myfile << Proponentes[i]->getProjP()->getNome() << endl;
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

void MIEIC::savePrimeiraFase() {
	string filename = "PrimeiraFase";
	string anoS;
	ostringstream convert;
	convert << ano;
	anoS = convert.str();
	filename += anoS;
	filename += ".txt";
	ofstream myfile(filename.c_str());

	vector<Vertex<Pessoa*> *> temp = PriFase.getVertexSet();

	vector<Vertex<Pessoa*> *>::const_iterator it = temp.begin();

	cout << "\n CASAMENTOS \n";
	for (; it != temp.end(); it++) {
		if ((*it)->getInfo()->isMarried()) {
			cout << "\n " << (*it)->getInfo()->getNomeClass()
					<< " esta casado com "
					<< (*it)->getInfo()->getPartner()->getNomeClass();
			cout << " sendo esta a sua "
					<< nrPref((*it), (*it)->getInfo()->getPartner()->getID())
					<< "a opcao\n";
		} else
			cout << "\n " << (*it)->getInfo()->getNomeClass()
					<< " esta solteiro \n";
	}

	cout << "\n----------------\n";

	myfile.close();
}

Graph<Pessoa*> MIEIC::PriGraph() {
	Graph<Pessoa*> retorno;
	PriFase.clone(retorno);

	return retorno;
}

Graph<Pessoa*> MIEIC::SecGraph() {
	Graph<Pessoa*> retorno;
	SecFase.clone(retorno);

	return retorno;
}

void MIEIC::showgraph() {
	gv = new GraphViewer(600, 600, false);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	vector<Vertex<Pessoa*> *> temp1;
	temp1 = PriFase.getVertexSet();

	//adiciona os vertices
	for (unsigned int i = 0; i < temp1.size(); i++)
		if (!gv->addNode(temp1[i]->getInfo()->getID()))
			cout << "Erro ao adicionar á visualizaçao";

	gv->rearrange();
	//adiciona arestas
	vector<Edge<Pessoa*> > edges;
	for (unsigned int i = 0; i < temp1.size(); i++) {
		edges = temp1[i]->getEdges();
		for (unsigned int c = 0; c < edges.size(); c++)
		if (!gv->addEdge(edges[c].getweight(),temp1[i]->getInfo()->getID(),edges[c].getDest()->getID(),EdgeType::UNDIRECTED))
					cout << "Erro ao adicionar á visualizaçao2";
	}
	gv->rearrange();

}

