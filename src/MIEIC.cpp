#include <MIEIC.h>

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
	temp +- ".txt";
	ifstream file (temp.c_str());
	if (!file.is_open())
		return;

	string linha;
	string linha2;
	while (!file.eof()) {
		getline(file,linha);
		getline(file,linha2);
		if(linha != "" && linha2 != "")
			projectos.push_back(Projectos(atoi(linha.c_str()),atoi(linha2.c_str())));
	}
	file.close();

}

void MIEIC ::loadEstudantes(){
	string temp = "Estudantes";
	temp += ano;
	temp +- ".txt";
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
			vector<Projectos> temp;
			do{
				istringstream ss(linha3);
				getline(ss,indice,',');

				temp.push_back(projectos[atoi(indice.c_str())]);


			}while(indice != "");


			estudantes.push_back(Estudantes(linha,temp,atoi(linha2.c_str())));


		}
	}
	file.close();

}



void MIEIC ::loadProponentes(){
	string temp = "Proponentes";
	temp += ano;
	temp +- ".txt";
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
			vector<Estudantes> temp;
			do{
				istringstream ss(linha3);
				getline(ss,indice,',');

				temp.push_back(estudantes[atoi(indice.c_str())]);


			}while(indice != "");


			proponentes.push_back(Proponente(linha,temp,atoi(linha2.c_str())));


		}
	}
	file.close();

}

void MIEIC ::loadSupervisores(){
	string temp = "Supervisores";
	temp += ano;
	temp +- ".txt";
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
			vector<Projectos> temp;
			do{
				istringstream ss(linha3);
				getline(ss,indice,',');

				temp.push_back(projectos[atoi(indice.c_str())]);


			}while(indice != "");


			supervisores.push_back(Supervisores(linha,temp,atoi(linha2.c_str())));


		}
	}
	file.close();

}
