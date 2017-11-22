#include <stdio.h>
#include <stdlib.h>
#include "t_biblio_machine.h"

int main()
{
	t_etudiant e1 = { 1245,0,0 };
	servir_etudiant(&e1);
	system("PAUSE");
	return EXIT_SUCCESS;
}
