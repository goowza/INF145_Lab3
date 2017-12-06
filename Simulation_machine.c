#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t_biblio_machine.h"


int main()
{
	//// Livres de test
	//t_livre livre1;
	//t_livre livre2;
	//t_livre livre3;
	//t_livre livre4;
	//t_livre livre5;

	//// etudiant test
	//t_etudiant e1;

	//// machine de test
	//t_bibliotheque bibli;
	//t_biblio_chariot chariot;
	//t_biblio_robot robot;

	//t_biblio_machine machine;

	//// Init livres
	//livre1.genre = INFORMATIQUE;
	//strcpy(livre1.titre, "Les Ninjas de l'Info 2");
	//strcpy(livre1.auteur_prenom, "Yannick");
	//strcpy(livre1.auteur_nom, "Roy");
	//livre1.nb_pages = 252;
	//livre1.isbn = 369;
	//livre1.bEmprunte = EMPRUNT;

	//livre2.genre = INFORMATIQUE;
	//strcpy(livre2.titre, "Les fous du code");
	//strcpy(livre2.auteur_prenom, "Hugues");
	//strcpy(livre2.auteur_nom, "Saulnier");
	//livre2.nb_pages = 355;
	//livre2.isbn = 1001;
	//livre2.bEmprunte = EMPRUNT;

	//livre3.genre = FICTION;
	//strcpy(livre3.titre, "Un tableau de pointeurs");
	//strcpy(livre3.auteur_prenom, "Pasdor");
	//strcpy(livre3.auteur_nom, "Mi");
	//livre3.nb_pages = 180;
	//livre3.isbn = 1234;
	//livre3.bEmprunte = EMPRUNT;

	//initialiser_livre(&livre4);
	//initialiser_livre(&livre5);

	////t_livre tab_emprunt[NB_LIVRES_EMPRUNTES_MAX] = {livre1,livre2,livre3,livre4,livre5};

	//// init etudiant
	//e1.annee_inscription = 2049;
	//e1.ID = 1234;
	//e1.livres_empruntes[0] = livre1;
	//e1.livres_empruntes[1] = livre2;
	//e1.livres_empruntes[2] = livre3;
	//e1.livres_empruntes[3] = livre4;
	//e1.livres_empruntes[4] = livre5;

	//// init machine
	//machine.ptr_bibli = &bibli;
	//machine.ptr_chariot = &chariot;
	//machine.ptr_robot = &robot;

	//initialiser_bibliotheque(machine.ptr_bibli);
	//gestion_bibliotheque(machine.ptr_bibli);
	////chercher_livre(&machine);
	//servir_etudiant(&machine, &e1);

	t_bibliotheque bibli;
	//t_biblio_chariot chariot;
	//t_biblio_robot robot;
	//t_biblio_machine machine;
	t_liste liste_livres_chariot;
	t_etudiant utilisateur_chariot;

	// livres apportes par le chariot
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;

	printf("Initialisation de la bibliotheque et du chariot...\n");
	/*chariot.liste_livres = &liste_livres_chariot;*/

	/*bibli.chariot = chariot;
	bibli.robot = robot;
	bibli.machine = machine;*/

	initialiser_bibliotheque(&bibli);

	init_liste(&liste_livres_chariot);
	bibli.chariot.liste_livres = &liste_livres_chariot;

	init_etudiant(&utilisateur_chariot);
	bibli.chariot.utilisateur = &utilisateur_chariot;

	// 2
	gestion_bibliotheque(&bibli);

	// 3 et 4
	printf("Apporter livre1...\n");
	livre1 = apporter_livre(&bibli.chariot, 1234);
	printf("Apporter livre2...\n");
	livre2 = apporter_livre(&bibli.chariot, 369);
	printf("Apporter livre3...\n");
	livre3 = apporter_livre(&bibli.chariot, 555);
	super_pause();
	system("cls");

	// 5
	printf("Ajout livre1 dans le chariot...\n");
	ajouter_livre_chariot(&bibli.chariot, livre1);
	printf("Ajout livre2 dans le chariot...\n");
	ajouter_livre_chariot(&bibli.chariot, livre2);
	printf("Ajout livre3 dans le chariot...\n");
	ajouter_livre_chariot(&bibli.chariot, livre3);
	super_pause();

	printf("Liste chariot : \n");
	afficher_liste(*bibli.chariot.liste_livres);
	super_pause();
	system("cls");

	// 6
	emprunter_livre_chariot(&bibli.chariot);
	printf("Emprunts de l'utilisateur : \n");
	afficher_emprunts(*bibli.chariot.utilisateur);
	
	super_pause();
	printf("Liste chariot : \n");
	afficher_liste(*bibli.chariot.liste_livres);
	super_pause();
	system("cls");

	// 7
	generer_rapport(&bibli);
	afficher_rapport(&bibli.rapport);
	super_pause();

	// 8
	printf("\nRetour des livres dans la bibliotheque...\n");
	retourner_livres(&bibli.chariot);
	super_pause();

	// 9
	printf("\n");
	generer_rapport(&bibli);
	afficher_rapport(&bibli.rapport);
	super_pause();


	system("cls");
	system("PAUSE");
	return EXIT_SUCCESS;
}
