#include <stdio.h>
#include <stdlib.h>
#include "t_file_etudiants.h"

int main()
{
	t_file file_test;
	t_etudiant e1 = { 1,0,0 };
	t_etudiant e2 = { 2,0,0 };
	t_etudiant e3 = { 3,0,0 };
	t_etudiant e4 = { 4,0,0 };
	t_etudiant e5 = { 5,0,0 };
	t_etudiant e6 = { 6,0,0 };
	t_etudiant e7 = { 7,0,0 };
	t_etudiant e8 = { 8,0,0 };

	init_file(&file_test);

	enfiler(&file_test, e1);
	enfiler(&file_test, e4);
	enfiler(&file_test, e3);

	afficher_file(&file_test);
	printf("\n");

	ajout_debut(&file_test, e8);
	enfiler(&file_test, e5);

	afficher_file(&file_test);
	printf("\n");

	printf("Etudiant #%d desenfile\n",desenfiler(&file_test));
	printf("Etudiant #%d desenfile\n", desenfiler(&file_test));
	printf("Etudiant #%d desenfile\n\n", desenfiler(&file_test));
	
	afficher_file(&file_test);
	printf("\n");
	
	system("PAUSE");
	return EXIT_SUCCESS;
}
