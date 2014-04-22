#include "MIEIC.h"
#include <stdlib.h>
int main ()  {

	string ano = "";

do{
	cout << "Ano do Mieic: ";

	cin >> ano;

}while(atoi(ano.c_str()) > 1994 && atoi(ano.c_str()) <= 2014);


MIEIC MIEIC2013(atoi(ano.c_str()));

	return 0;
}
