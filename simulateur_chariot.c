#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "t_biblio_chariot.h"

int main()
{
	//t_biblio_chariot chariot;
	//t_liste liste_livres;
	//// Livres de test
	//t_livre livre1;
	//t_livre livre2;
	//t_livre livre3;
	//t_livre livre4;
	//t_livre livre5;

	//t_livre livre_enleve;

	//t_etudiant e1;

	//// bibliotheque
	//t_bibliotheque bibli;

	//// Init livres
	//livre1.genre = INFORMATIQUE;
	//strcpy(livre1.titre, "Les Ninjas de l'Info 2");
	//strcpy(livre1.auteur_prenom, "Yannick");
	//strcpy(livre1.auteur_nom, "Roy");
	//livre1.nb_pages = 252;
	//livre1.isbn = 2000;
	//livre1.bEmprunte = DISPONIBLE;

	//livre2.genre = INFORMATIQUE;
	//strcpy(livre2.titre, "Les fous du code");
	//strcpy(livre2.auteur_prenom, "Hugues");
	//strcpy(livre2.auteur_nom, "Saulnier");
	//livre2.nb_pages = 355;
	//livre2.isbn = 1001;
	//livre2.bEmprunte = DISPONIBLE;

	//livre3.genre = FICTION;
	//strcpy(livre3.titre, "Un tableau de pointeurs");
	//strcpy(livre3.auteur_prenom, "Pasdor");
	//strcpy(livre3.auteur_nom, "Mi");
	//livre3.nb_pages = 180;
	//livre3.isbn = 1234;
	//livre3.bEmprunte = DISPONIBLE;

	//livre4.genre = HISTOIRE;
	//strcpy(livre4.titre, "yee");
	//strcpy(livre4.auteur_prenom, "Jean");
	//strcpy(livre4.auteur_nom, "Jacques");
	//livre4.nb_pages = 256;
	//livre4.isbn = 42;
	//livre4.bEmprunte = DISPONIBLE;

	//initialiser_livre(&livre5);
	//initialiser_livre(&livre_enleve);

	//// init biblio
	//initialiser_bibliotheque(&bibli);
	//lire_fichier(&bibli);

	//// init etudiant
	//e1.annee_inscription = 2049;
	//e1.ID = 1234;
	//e1.livres_empruntes[0] = bibli.livres[1][0];
	//e1.livres_empruntes[1] = bibli.livres[4][0];
	//e1.livres_empruntes[2] = livre5;
	//e1.livres_empruntes[3] = livre5;
	//e1.livres_empruntes[4] = livre5;

	//// init chariot
	//init_liste(&liste_livres);
	//chariot.liste_livres = &liste_livres;
	//chariot.pBibli = &bibli;
	//chariot.position = POS_KIOSQUE;
	//chariot.utilisateur = NULL;
	//
	//ajouter_livre(&chariot, bibli.livres[5][0]);
	//ajouter_livre(&chariot, bibli.livres[5][1]);
	//ajouter_livre(&chariot, bibli.livres[3][0]);

	////bibli.livres[5][0].bEmprunte = EMPRUNT;
	////bibli.livres[5][1].bEmprunte = EMPRUNT;
	////bibli.livres[3][0].bEmprunte = EMPRUNT;

	//

	//gestion_bibliotheque(&bibli);

	//livre_enleve = apporter_livre(&chariot,1234);
	//afficher_info_livre(&livre_enleve);

	//gestion_bibliotheque(&bibli);
	//afficher_liste(chariot.liste_livres);



	//afficher_liste(chariot.liste_livres);
	/*chariot.utilisateur = &e1;*/
	/*emprunter_livre(&chariot);
	afficher_liste(chariot.liste_livres);
	afficher_emprunts(*chariot.utilisateur);*/

	/*afficher_liste(chariot.liste_livres);
	system("PAUSE");
	system("cls");
	gestion_bibliotheque(&bibli);
	retourner_livres(&chariot);
	gestion_bibliotheque(&bibli);
	afficher_liste(chariot.liste_livres);*/

	/*afficher_liste(chariot.liste_livres);

	livre_enleve = retirer_livre_chariot(&chariot, 1234);
	printf("Livre enleve : \n");
	afficher_info_livre(&livre_enleve);
	printf("\n");
	afficher_liste(chariot.liste_livres);*/


	//=============================== Simulateur ==============================

	t_bibliotheque bibli;
	t_biblio_chariot chariot;
	t_liste liste_livres_chariot;
	t_etudiant utilisateur_chariot;

	// livres apportes par le chariot
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;

	// 1
	printf("Initialisation de la bibliotheque et du chariot...\n");
	initialiser_bibliotheque(&bibli);

	chariot.liste_livres = &liste_livres_chariot;
	initialiser_chariot(&chariot,&bibli);
	init_etudiant(&utilisateur_chariot);
	chariot.utilisateur = &utilisateur_chariot;

	super_pause();
	system("cls");
	
	// 2
	gestion_bibliotheque(&bibli);

	// 3 et 4
	printf("Apporter livre1...\n");
	livre1 = apporter_livre(&chariot,1234);
	printf("Apporter livre2...\n");
	livre2 = apporter_livre(&chariot,369);
	printf("Apporter livre3...\n");
	livre3 = apporter_livre(&chariot,555);
	super_pause();
	system("cls");

	// 5
	printf("Ajout livre1 dans le chariot...\n");
	ajouter_livre_chariot(&chariot,livre1);
	printf("Ajout livre2 dans le chariot...\n");
	ajouter_livre_chariot(&chariot,livre2);
	printf("Ajout livre3 dans le chariot...\n");
	ajouter_livre_chariot(&chariot,livre3);
	super_pause();
	system("cls");

	// 6
	emprunter_livre_chariot(&chariot);
	printf("Emprunts de l'utilisateur : \n");
	afficher_emprunts(*chariot.utilisateur);
	super_pause();
	system("cls");

	// 7
	generer_rapport(&bibli);
	afficher_rapport(&bibli.rapport);
	super_pause();

	// 8
	printf("\nRetour des livres dans la bibliotheque...\n");
	retourner_livres(&chariot);
	super_pause();

	// 9
	printf("\n");
	generer_rapport(&bibli);
	afficher_rapport(&bibli.rapport);
	super_pause();

	system("PAUSE");
	return EXIT_SUCCESS;
}
