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


class MIEIC {
	Graph<Pessoa*> PriFase;
	bool priFaseOk;
	unsigned int ano;
	vector<Proponente> Proponentes;
	vector<Estudante> Estudantes;
	vector<Supervisor> Supervisores;
public:
	MIEIC(unsigned int ano);
	void loadProjectos();
	void loadProponentes();
	void loadEstudantes();
	void loadSupervisores();
	void Menu();
	bool Listagem(string pessoa);
	void PrimeiraFase();
	void SegundaFase();
	void ListProjs();
	void ListPropos();
	void ListEstuds();
	void ListSupervs();
	bool FirstFaseComplete();
	void Criar();
	void EstudantesPref();
	void ProponentesPref();
	void SupervisoresPref();
	void StartPriFase();
	void addEdge(int iDFont, int iDDist, int peso);
	bool verificaPref(int idFont, int idDist);
	bool comparePropPref(Estudante e, Proponente p);
	void Marry();
	bool checkIfAllMarried();
};


#endif /* MIEIC_H_ */
