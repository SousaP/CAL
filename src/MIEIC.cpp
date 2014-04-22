#include "MIEIC.h"

#include <sstream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;



MIEIC :: MIEIC(unsigned int ano){

	this->ano = ano;
	void loadProjectos();
	void loadEstudantes();
	void loadProponentes();
	void loadSupervisores();
}

void MIEIC ::loadProjectos(){
	string temp = "Projectos";
	temp += ano;
	temp += ".txt";
	ifstream file (temp.c_str());
	if (!file.is_open())
		return;

	string linha;
	string linha2;
	while (!file.eof()) {
		getline(file,linha);
		getline(file,linha2);
		if(linha != "" && linha2 != "")
			Projectos.push_back(Projecto(linha,atoi(linha2.c_str())));
	}
	file.close();

}

void MIEIC ::loadEstudantes(){
	string temp = "Estudantes";
	temp += ano;
	temp += ".txt";
	ifstream file (temp.c_str());
	if (!file.is_open())
		return;

	string linha;
	string linha2;
	string linha3;
	while (!file.eof()) {
		getline(file,linha);
		getline(file,linha2);


		if(linha != "" && linha2 != "")
		{

			string indice;
			vector<Projecto> temp;
			do{
				istringstream ss(linha2);
				getline(ss,indice,',');

				//temp.push_back(Projectos[atoi(indice.c_str())]);


			}while(indice != "");


			//Estudantes.push_back(Estudantes(linha,temp));


		}
	}
	file.close();

}

void MIEIC ::loadProponentes(){
	string temp = "Proponentes";
	temp += ano;
	temp += ".txt";
	ifstream file (temp.c_str());
	if (!file.is_open())
		return;

	string linha;
	string linha2;
	string linha3;
	while (!file.eof()) {
		getline(file,linha);
		getline(file,linha2);
		getline(file,linha3);


		if(linha != "" && linha2 != ""&& linha3 != "")
		{

			string indice;
			vector<Estudante> temp;
			do{
				istringstream ss(linha3);
				getline(ss,indice,',');

				//temp.push_back(Estudantes[atoi(indice.c_str())]);


			}while(indice != "");


			//proponentes.push_back(Proponente(linha,temp,atoi(linha2.c_str())));


		}
	}
	file.close();

}

void MIEIC ::loadSupervisores(){
	string temp = "Supervisores";
	temp += ano;
	temp += ".txt";
	ifstream file (temp.c_str());
	if (!file.is_open())
		return;

	string linha;
	string linha2;
	string linha3;
	while (!file.eof()) {
		getline(file,linha);
		getline(file,linha2);
		getline(file,linha3);


		if(linha != "" && linha2 != ""&& linha3 != "")
		{

			string indice;
			vector<Projecto> temp;
			do{
				istringstream ss(linha3);
				getline(ss,indice,',');

				//temp.push_back(projectos[atoi(indice.c_str())]);


			}while(indice != "");


//			supervisores.push_back(Supervisores(linha,temp,atoi(linha2.c_str())));


		}
	}
	file.close();

}





void MIEIC :: ListPorjs(){

	cout << "\n||||| LISTAGEM PROJETOS  |||||\n";

	vector<Projecto>::iterator it = Projectos.begin();

	for(; it != Projectos.end(); it++)
		cout << (*it) << endl;

	cout << "----------------------------------";
}

void MIEIC :: ListPropos(){

	cout << "\n||||| LISTAGEM PROPONENTES  |||||\n";
	vector<Proponente> ::iterator it = Proponentes.begin();

	for(; it != Proponentes.end(); it++)
			cout << (*it) << endl;

	cout << "----------------------------------";
}

void MIEIC :: ListEstuds(){

	cout << "\n||||| LISTAGEM ESTUDANTES |||||\n";
		vector<Estudante> ::iterator it = Estudantes.begin();

		for(; it != Estudantes.end(); it++)
				cout << (*it) << endl;

		cout << "----------------------------------";

}

void MIEIC :: ListSupervs(){

	cout << "\n||||| LISTAGEM SUPERVISORES |||||\n";
	vector<Supervisor> ::iterator it = Supervisores.begin();

	for(; it != Supervisores.end(); it++)
		cout << (*it) << endl;

	cout << "----------------------------------";

}

void MIEIC :: Listagem(string pessoa){

	if(pessoa == "Projectos")
		ListPorjs();
	else if(pessoa == "Proponentes")
		ListPropos();
	else if(pessoa == "Estudantes")
		ListEstuds();
	else if(pessoa == "Supervisores")
		ListSupervs();
}


void MIEIC :: PrimeiraFase(){
	string escolha = "";

	cout << "1. Escolhas dos Estudantes\n";
	cout << "2. Escolhas dos Proponentes\n";
	cout << "3. Atribuir Projectos\n";
	cin >> escolha;



}

void MIEIC :: SegundaFase(){

}


void MIEIC :: Menu(){

	string escolha = "";

	while(escolha != "Sair" && escolha != "sair" &&escolha != "4"){

	cout << "1. Listagem\n2. Primeira fase.\n3. Segunda Fase.\n4. Sair";
	cin >> escolha;

	if(escolha != "Listagem" && escolha != "listagem" &&escolha != "1")
	{


	}

	else if(escolha != "Primeira" && escolha != "primeira" &&escolha != "2")
	PrimeiraFase();

	else if(escolha != "Segunda" && escolha != "segunda" &&escolha != "3")
		SegundaFase();
	else if(escolha != "Sair" && escolha != "sair" &&escolha != "4")
		return;

	}


}
