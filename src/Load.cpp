
/*
void AtribuicaoDeProjetos::loadEstudantes() {
	string filename = "Estudantes.txt";
	ifstream myfile(filename.c_str());

	string nome, preferencia, recebido;
	vector<string> preferencias;
	
	
		myfile >> recebido;
		if (recebido != "")
			{nome = recebido;}
		
		while (myfile.good()) {
		myfile >> recebido;
		if (recebido != ""){
			if(recebido == "END"){
			break;}
			else{
			preferencia = recebido;
			preferencias.push_back(recebido);
			}
			
			estudantes.push_back(Esudante(nome, preferencias);

	}
	myfile.close();

}

void AtribuicaoDeProjetos::loadProjetos() {
	string filename = "Projetos.txt";
	ifstream myfile(filename.c_str());

	string nome, proponente, recebido;
	vector<string> preferencias;
	
	
		myfile >> recebido;
		if (recebido != "")
			{nome = recebido;}
		
		myfile >> recebido;
		if (recebido != "")
			{proponente = recebido;}
		
		Projetos.push_back(Projeto(nome, proponente)

	}
	myfile.close();

}

void AtribuicaoDeProjetos::loadProponentes() {
	string filename = "Proponentes.txt";
	ifstream myfile(filename.c_str());

	string nome, tipo, preferencia, recebido;
	vector<string> preferencias;
	
	
		myfile >> recebido;
		if (recebido != "")
			{nome = recebido;}
			
		myfile >> recebido;
		if (recebido != "")
			{tipo = recebido;}
		
		while (myfile.good()) {
		myfile >> recebido;
		if (recebido != ""){
			if(recebido == "END"){
			break;}
			else{
			preferencia = recebido;
			preferencias.push_back(recebido);
			}
			
			proponentes.push_back(Proponente(nome, tipo, preferencias);

	}
	myfile.close();

}

void AtribuicaoDeProjetos::loadSupervisores() {
	string filename = "Proponentes.txt";
	ifstream myfile(filename.c_str());

	string nome, preferencia, recebido;
	int max;
	vector<string> preferencias;
	
	
		myfile >> recebido;
		if (recebido != "")
			{nome = recebido;}
			
		myfile >> recebido;
		if (recebido != "")
			{max = recebido.c_str();}
		
		while (myfile.good()) {
		myfile >> recebido;
		if (recebido != ""){
			if(recebido == "END"){
			break;}
			else{
			preferencia = recebido;
			preferencias.push_back(recebido);
			}
			
			supervisores.push_back(Supervisor(nome, max, preferencias);

	}
	myfile.close();

}
*/
