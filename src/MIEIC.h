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
	vector<Projecto> Projectos;
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
	void Listagem();
	void PrimeiraFase();

};


#endif /* MIEIC_H_ */
