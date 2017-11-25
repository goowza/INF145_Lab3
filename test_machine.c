#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "t_biblio_machine.h"


int main()
{
	t_etudiant e1 = { 1245,0,0 };
	t_biblio_machine * machine = NULL;
	t_bibliotheque bibli;
	initialiser_bibliotheque(&bibli);
	gestion_bibliotheque(&bibli);
	chercher_livre(&bibli);

	system("PAUSE");
	return EXIT_SUCCESS;
}
