#ifndef MIEIC_H_
#define MIEIC_H_


#include <string>
#include <iostream>
#include <vector>
#include "Projectos.h"
#include "Proponente.h"
#include "Estudantes.h"
#include "Supervisores.h"
#include "Graph.h"


class MIEIC {
	unsigned int ano;
	vector<Projectos> projectos;
	vector<Proponente> proponentes;
	vector<Estudantes> estudantes;
	vector<Supervisores> supervisores;
public:
	MIEIC(unsigned int ano);
	void loadProjectos();
	void loadProponentes();
	void loadEstudantes();
	void loadSupervisores();

};


#endif /* MIEIC_H_ */
