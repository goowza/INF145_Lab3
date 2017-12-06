#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t_biblio_robot.h"


int main()
{

	t_bibliotheque bibli;

	t_liste liste_livres_chariot;
	t_pile pile_livres_robot;
	t_etudiant utilisateur_chariot;

	// livres apportes par le chariot
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;

	printf("Initialisation...\n");

	initialiser_bibliotheque(&bibli);

	// init liste du chariot
	init_liste(&liste_livres_chariot);
	bibli.chariot.liste_livres = &liste_livres_chariot;

	// init pile du robot
	init_pile(&pile_livres_robot);
	bibli.robot.pile_livres = &pile_livres_robot;

	init_etudiant(&utilisateur_chariot);
	bibli.chariot.utilisateur = &utilisateur_chariot;

	// 2
	gestion_bibliotheque(&bibli);

	// test ajouter_livre
	livre1 = bibli.livres[5][0];
	livre2 = bibli.livres[5][1];
	livre3 = bibli.livres[3][0];

	// Ajouter des livres (va directement dans le chariot)
	printf("Ajout livre1 au robot...\n");
	ajouter_livre_robot(&bibli.robot, livre1);
	super_pause();
	printf("liste chariot : \n");
	afficher_liste(*bibli.chariot.liste_livres);
	printf("pile robot : \n");
	afficher_pile(bibli.robot.pile_livres);

	super_pause();

	// Le chariot part
	printf("Depart du chariot...\n");
	bibli.chariot.position = POS_DEPLACEMENT;

	super_pause();

	// ajouter 2 autres livres (cette fois dans la pile du robot)
	printf("Ajout livre2 au robot...\n");
	ajouter_livre_robot(&bibli.robot, livre2);
	printf("Ajout livre3 au robot...\n");
	ajouter_livre_robot(&bibli.robot, livre3);
	
	super_pause();

	printf("liste chariot : \n");
	afficher_liste(*bibli.chariot.liste_livres);
	printf("pile robot : \n");
	afficher_pile(bibli.robot.pile_livres);

	super_pause();
	system("cls");

	// Vider la pile du robot dans le chariot
	printf("vidage de la pile du robot (sans chariot)...\n");
	placer_livres_chariot(&bibli.robot);

	super_pause();

	printf("liste chariot : \n");
	afficher_liste(*bibli.chariot.liste_livres);
	printf("pile robot : \n");
	afficher_pile(bibli.robot.pile_livres);

	super_pause();

	// Le chariot revient
	printf("arrivee du chariot au kiosque...\n");
	bibli.chariot.position = POS_KIOSQUE;

	super_pause();

	// re essayer de vider la pile du robot dans le chariot
	printf("vidage de la pile du robot (avec chariot)...\n");
	placer_livres_chariot(&bibli.robot);

	super_pause();

	printf("liste chariot : \n");
	afficher_liste(*bibli.chariot.liste_livres);
	printf("pile robot : \n");
	afficher_pile(bibli.robot.pile_livres);

	super_pause();

	system("cls");
	system("PAUSE");
	return EXIT_SUCCESS;
}
