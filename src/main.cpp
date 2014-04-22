#include "MIEIC.h"
#include <stdlib.h>
int main ()  {

	string ano = "";

while(atoi(ano.c_str()) > 1994 && atoi(ano.c_str()) <= 2014){
	cout << "Ano do Mieic: ";

	cin >> ano;

}
	MIEIC MIEIC2013(atoi(ano.c_str()));

}
