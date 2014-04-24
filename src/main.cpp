#include "MIEIC.h"
#include <stdlib.h>
int main() {

	string ano;

	do {
		cout << "\nAno do Mieic: ";

		cin >> ano;

	} while (atoi(ano.c_str()) < 1994 || atoi(ano.c_str()) > 2014);

	MIEIC MIEIC(atoi(ano.c_str()));

	MIEIC.Menu();

	return 0;
}
