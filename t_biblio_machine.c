#include <stdio.h>
#include <stdlib.h>
#include "t_biblio_machine.h"

void servir_etudiant(t_etudiant * etudiant)
{
	printf("Bonjour Etudiant No.%d.\n",	etudiant->ID);
	printf("Comment puis_je vous aider aujourd'hui ?\n");
	printf("=================================\n");
	printf("1 - Chercher livre\n");
	printf("2 - Retourner livre\n");
	printf("3 - Apporter livre\n");
	printf("4 - Voir dossier\n");
	printf("=================================\n");

}

void chercher_livre()
{

}
