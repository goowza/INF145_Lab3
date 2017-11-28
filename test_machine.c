#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t_biblio_machine.h"


int main()
{
	// Livres de test
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;
	t_livre livre4;
	t_livre livre5;

	// etudiant test
	t_etudiant e1;

	// machine de test
	t_bibliotheque bibli;
	t_biblio_chariot chariot;
	t_biblio_robot robot;

	t_biblio_machine machine;

	// Init livres
	livre1.genre = INFORMATIQUE;
	strcpy(livre1.titre, "Les Ninjas de l'Info 2");
	strcpy(livre1.auteur_prenom, "Yannick");
	strcpy(livre1.auteur_nom, "Roy");
	livre1.nb_pages = 252;
	livre1.isbn = 369;
	livre1.bEmprunte = EMPRUNT;

	livre2.genre = INFORMATIQUE;
	strcpy(livre2.titre, "Les fous du code");
	strcpy(livre2.auteur_prenom, "Hugues");
	strcpy(livre2.auteur_nom, "Saulnier");
	livre2.nb_pages = 355;
	livre2.isbn = 1001;
	livre2.bEmprunte = EMPRUNT;

	livre3.genre = FICTION;
	strcpy(livre3.titre, "Un tableau de pointeurs");
	strcpy(livre3.auteur_prenom, "Pasdor");
	strcpy(livre3.auteur_nom, "Mi");
	livre3.nb_pages = 180;
	livre3.isbn = 1234;
	livre3.bEmprunte = EMPRUNT;

	initialiser_livre(&livre4);
	initialiser_livre(&livre5);
	
	//t_livre tab_emprunt[NB_LIVRES_EMPRUNTES_MAX] = {livre1,livre2,livre3,livre4,livre5};

	// init etudiant
	e1.annee_inscription = 2049;
	e1.ID = 1234;
	e1.livres_empruntes[0] = livre1;
	e1.livres_empruntes[1] = livre2;
	e1.livres_empruntes[2] = livre3;
	e1.livres_empruntes[3] = livre4;
	e1.livres_empruntes[4] = livre5;
	
	// init machine
	machine.ptr_bibli = &bibli;
	machine.ptr_chariot = &chariot;
	machine.ptr_robot = &robot;

	initialiser_bibliotheque(machine.ptr_bibli);
	gestion_bibliotheque(machine.ptr_bibli);
	//chercher_livre(&machine);
	servir_etudiant(&machine,&e1);

	system("PAUSE");
	return EXIT_SUCCESS;
}
