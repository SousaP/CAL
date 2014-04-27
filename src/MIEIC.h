#ifndef MIEIC_H_
#define MIEIC_H_

#include <string>
#include <iostream>
#include <vector>
#include "Projecto.h"
#include "Proponente.h"
#include "Estudante.h"
#include "Supervisor.h"
#include "Graph.h"
#include "Pessoa.h"

/*
 * A classe MIEIC gere os dois grafos bem como os processos de atribuição de projectos e os várioa elementos da estrutura
 * (Proponentes, estudantes, supervisores e projectos)
 */
class MIEIC {
	Graph<Pessoa*> PriFase;
	Graph<Pessoa*> SecFase;
	bool priFaseOk;
	bool secFaseOk;
	unsigned int ano;
	vector<Proponente*> Proponentes;
	vector<Estudante*> Estudantes;
	vector<Supervisor*> Supervisores;
	vector<Projecto*> Projectos;

public:
	MIEIC(unsigned int ano);
	~MIEIC();
	void loadProjectos();
	void loadProponentes();
	void loadEstudantes();
	void loadSupervisores();
	void saveProjectos();
	void saveProponentes();
	void saveEstudantes();
	void saveSupervisores();
	void savePrimeiraFase();
	void Menu();
	bool Listagem(string pessoa);
	void PrimeiraFase();
	void SegundaFase();
	void ListProjs();
	void ListPropos();
	void ListEstuds();
	void ListSupervs();
	void ListGrafo();
	bool FirstFaseComplete();
	void Criar();
	void EstudantesPref();
	void ProponentesPref();
	void SupervisoresPref();
	void StartPriFase();
	bool addEdge(int iDFont, int iDDist, int peso, int grafo);
	bool verificaPref(int idFont, int idDist,int grafo);
	bool comparePropPref(Estudante *e, Proponente *p);
	void Marry();
	bool checkStudents();
	bool checkPropns();
	void solteirar(int id);
	void MarrySuperv();
	void StartSecFase();
	void setpropofree();
	bool checkIfAllMarried2();
	bool preferencesOccupied(string nomeProj);
	bool checkPreferences();
	void tryMarrySuperv(Supervisor* s);
	unsigned int nrPref(Vertex<Pessoa*> *p, unsigned int id);
	void showWedd();
	void showSupervProjs();
	Graph<Pessoa*> PriGraph();
	Graph<Pessoa*> SecGraph();

};

#endif /* MIEIC_H_ */
