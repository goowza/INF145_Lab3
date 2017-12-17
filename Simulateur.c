// =============================== SIMULATEUR =================================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce programme permet de tester les modules t_biblio_chariot, 
//  t_biblio_machine, t_biblio_robot, t_bibliotheque via un menu. Des tests
//  unitaires sont effectues afin de s'assurer du bon fonctionnement des 
//  modules.
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "t_bibliotheque.h"

// Cette fonction permet de simuler les fonctions du module t_biblio_chariot.
void simuler_chariot(t_bibliotheque * bibli);

// Cette fonction permet de simuler les fonctions du module t_biblio_robot.
void simuler_robot(t_bibliotheque * bibli);

// Cette fonction permet de simuler les fonctions du module t_biblio_machine.
void simuler_machine(t_bibliotheque * bibli);

// Cette fonction permet de simuler les fonctions du module t_bibliotheque.
void simuler_bibliotheque(t_bibliotheque * bibli);

// Cette fonction permet d'afficher le menu de la simulation en proposant 
// d'executer les differentes fonctions de test definies plus haut.
void afficher_menu_simulation();

// Le main effectue l'initialisation de la bibliotheque, du chariot, du robot 
// et du kiosque puis gere le menu de la simulation en boucle jusqu'a ce que 
// l'utilisateur decide de quitter.
int main()
{

	t_bibliotheque bibli;

	t_liste liste_livres_chariot;
	t_pile pile_livres_robot;
	t_etudiant utilisateur_chariot;

	t_file file_etudiants;

	int choix_simulation;

	srand((unsigned)time(NULL));

	//======================== Initialisation =============================
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

	// init file etudiants
	init_file(&file_etudiants);
	bibli.file_etudiants = &file_etudiants;

	// Charger les livres dans la bibliotheque
	lire_fichier(&bibli);
	super_pause();
	system("cls");

	do
	{
		afficher_menu_simulation();
		choix_simulation = demander_choix_menu(NUM_CHOIX_MIN_SIMU, NUM_CHOIX_MAX_SIMU);
		system("cls");

		switch (choix_simulation)
		{
		case 1 :
			simuler_chariot(&bibli);
			break;
		case 2 : 
			simuler_robot(&bibli);
			break;
		case 3 : 
			simuler_machine(&bibli);
			break;
		case 4 :
			simuler_bibliotheque(&bibli);
			break;
		default:
			break;
		}
		system("cls");
	} while (choix_simulation != 0);

	system("cls");
	system("PAUSE");
	return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
//							Fonction simuler_chariot
// Cette fonction permet de simuler les fonctions du module t_biblio_chariot.
//
// Parametres : bibli = pointeur vers la bibliotheque ou opere le chariot
// Retour :		aucun
//-----------------------------------------------------------------------------
void simuler_chariot(t_bibliotheque * bibli)
{
	// livres apportes par le chariot
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;

	printf("====================== SIMULATION CHARIOT ====================\n");

	// Test apporter_livre
	printf("Apporter livre1 au chariot...\n");
	livre1 = apporter_livre(&bibli->chariot, 1234);
	printf("Apporter livre2 au chariot...\n");
	livre2 = apporter_livre(&bibli->chariot, 369);
	printf("Apporter livre3 au chariot...\n");
	livre3 = apporter_livre(&bibli->chariot, 555);

	printf("\n");
	super_pause();
	system("cls");

	// Test ajouter_livre_chariot
	printf("Ajout livre1 dans le chariot...\n");
	ajouter_livre_chariot(&bibli->chariot, livre1);
	printf("Ajout livre2 dans le chariot...\n");
	ajouter_livre_chariot(&bibli->chariot, livre2);
	printf("Ajout livre3 dans le chariot...\n");
	ajouter_livre_chariot(&bibli->chariot, livre3);

	printf("\n");
	super_pause();
	system("cls");

	// afficher le contenu du chariot
	printf("Liste chariot : \n");
	afficher_liste(*bibli->chariot.liste_livres);

	printf("\n");
	super_pause();
	printf("\n");

	// Test emprunter_livre_chariot
	printf("Rechercher un livre dans le chariot :\n");
	emprunter_livre_chariot(&bibli->chariot);

	printf("\n");
	super_pause();
	system("cls");

	printf("Emprunts de l'utilisateur : \n");
	afficher_emprunts(*bibli->chariot.utilisateur);

	printf("\n");
	super_pause();
	system("cls");

	// Afficher le rapport
	generer_rapport(bibli);
	afficher_rapport(&bibli->rapport);

	printf("\n");
	super_pause();
	system("cls");

	// Test retourner_livres
	printf("\nRetour des livres dans la bibliotheque...\n");
	retourner_livres(&bibli->chariot);

	printf("\n");
	super_pause();
	system("cls");

	// Afficher le rapport
	generer_rapport(bibli);
	afficher_rapport(&bibli->rapport);

	printf("\n");
	super_pause();
	system("cls");
}

//-----------------------------------------------------------------------------
//							Fonction simuler_robot
// Cette fonction permet de simuler les fonctions du module t_biblio_robot.
//
// Parametres : bibli = pointeur vers la bibliotheque ou opere le robot
// Retour :		aucun
//-----------------------------------------------------------------------------
void simuler_robot(t_bibliotheque * bibli)
{
	// livres de test
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;

	// test ajouter_livre
	livre1 = bibli->livres[5][0];
	livre2 = bibli->livres[5][1];
	livre3 = bibli->livres[3][0];

	printf("====================== SIMULATION ROBOT ======================\n");

	// Test ajouter_livre_robot avec le chariot au kiosque
	// (les livres vont directement dans le chariot)
	printf("Ajout livre1 au robot...\n");
	ajouter_livre_robot(&bibli->robot, livre1);

	printf("\n");
	super_pause();
	system("cls");

	// Affichage du contenu du chariot et du robot
	printf("liste chariot : \n");
	afficher_liste(*bibli->chariot.liste_livres);
	printf("pile robot : \n");
	afficher_pile(bibli->robot.pile_livres);

	printf("\n");
	super_pause();
	system("cls");

	// Le chariot part du kiosque
	printf("Depart du chariot...\n");
	bibli->chariot.position = POS_DEPLACEMENT;

	printf("\n");
	super_pause();
	system("cls");

	// Test ajouter_livre_robot sans le chariot au kiosque
	// (les livres vont dans la pile du robot)
	printf("Ajout livre2 au robot...\n");
	ajouter_livre_robot(&bibli->robot, livre2);
	printf("Ajout livre3 au robot...\n");
	ajouter_livre_robot(&bibli->robot, livre3);

	printf("\n");
	super_pause();
	system("cls");

	// Affichage du contenu du chariot et du robot
	printf("liste chariot : \n");
	afficher_liste(*bibli->chariot.liste_livres);
	printf("pile robot : \n");
	afficher_pile(bibli->robot.pile_livres);

	printf("\n");
	super_pause();
	system("cls");

	// Test placer_livres_chariot sans le chariot au kiosque
	// (les livres restent dans la pile du robot)
	printf("vidage de la pile du robot (sans chariot)...\n");
	placer_livres_chariot(&bibli->robot);

	printf("\n");
	super_pause();
	system("cls");

	// Affichage du contenu du chariot et du robot
	printf("liste chariot : \n");
	afficher_liste(*bibli->chariot.liste_livres);
	printf("pile robot : \n");
	afficher_pile(bibli->robot.pile_livres);

	printf("\n");
	super_pause();
	system("cls");

	// Le chariot revient
	printf("arrivee du chariot au kiosque...\n");
	bibli->chariot.position = POS_KIOSQUE;

	printf("\n");
	super_pause();
	system("cls");

	// Test placer_livres_chariot avec le chariot au kiosque
	// (la pile du robot est videe dans le chariot)
	printf("vidage de la pile du robot (avec chariot)...\n");
	placer_livres_chariot(&bibli->robot);

	printf("\n");
	super_pause();
	system("cls");

	// Affichage du contenu du chariot et du robot
	printf("liste chariot : \n");
	afficher_liste(*bibli->chariot.liste_livres);
	printf("pile robot : \n");
	afficher_pile(bibli->robot.pile_livres);
	printf("Rapport : \n");
	generer_rapport(bibli);
	afficher_rapport(&bibli->rapport);

	printf("\n");
	super_pause();
	system("cls");

}

//-----------------------------------------------------------------------------
//							Fonction simuler_machine
// Cette fonction permet de simuler les fonctions du module t_biblio_machine.
//
// Parametres : bibli = pointeur vers la bibliotheque ou opere le kiosque
// Retour :		aucun
//-----------------------------------------------------------------------------
void simuler_machine(t_bibliotheque * bibli)
{
	t_etudiant e1;
	t_etudiant e2;
	t_etudiant e3;

	int compteur_etudiants = 1;
	
	printf("====================== SIMULATION KIOSQUE ====================\n");

	printf("Creation de la file d'etudiants...\n");

	// Generer les etudiants a ajouter a la file du kiosque
	generer_etudiant_aleatoire(&e1);
	generer_etudiant_aleatoire(&e2);
	generer_etudiant_aleatoire(&e3);

	// Ajouter les etudiants dans la file du kiosque
	enfiler(bibli->file_etudiants, e1);
	enfiler(bibli->file_etudiants, e2);
	enfiler(bibli->file_etudiants, e3);

	super_pause();
	system("cls");

	// Test servir_etudiant
	while (!file_vide(bibli->file_etudiants))
	{
		printf("Etudiant #%d\n", compteur_etudiants);
		servir_etudiant(bibli);
		compteur_etudiants++;
		system("cls");
	}
	
}

//-----------------------------------------------------------------------------
//							Fonction simuler_bibliotheque
// Cette fonction permet de simuler les fonctions du module t_bibliotheque.
//
// Parametres : bibli = pointeur vers la bibliotheque a simuler
// Retour :		aucun
//-----------------------------------------------------------------------------
void simuler_bibliotheque(t_bibliotheque * bibli)
{
	t_etudiant e1;
	t_etudiant e2;
	t_etudiant e3;
	t_etudiant e4;

	// Test de la gestion de la bibliotheque
	gestion_bibliotheque(bibli);

	// On genere 4 etudiants aleatoires a ajouter a la file de la bibliotheque
	generer_etudiant_aleatoire(&e1);
	generer_etudiant_aleatoire(&e2);
	generer_etudiant_aleatoire(&e3);
	generer_etudiant_aleatoire(&e4);

	ajouter_etudiant_file(bibli, e1);
	ajouter_etudiant_file(bibli, e2);

	// Test de la fonctionnalite de la file
	printf("Ajout de 2 etudiants a la file d'attente de la bibliotheque...\n\n");
	super_pause();
	system("cls");

	printf("File d'etudiants : \n");
	afficher_file(bibli->file_etudiants);

	super_pause();

	printf("Ajout de e3 a la fin de la file : \n");
	ajouter_etudiant_file(bibli, e3);
	super_pause();

	afficher_file(bibli->file_etudiants);

	super_pause();

	// Servir le premier etudiant (e1)
	servir_etudiant(bibli);

	// ajouter un autre etudiant dans la file
	ajouter_etudiant_file(bibli, e4);

	printf("Ajout d'un autre etudiant a la file d'atente de la bibliotheque...\n\n");
	super_pause();
	system("cls");

	// Servir la fin de la file
	servir_etudiant(bibli);
	servir_etudiant(bibli);

	// Test de l'appel de fonction avec une file vide
	servir_etudiant(bibli);

	// Agrandir la bibliotheque
	system("cls");
	printf("Test de l'agrandissement de la bibliotheque...\n\n");
	super_pause();

	while (bibli->taille == NB_LIVRES_MAX_RANGEE)
	{
		printf("Ajoutez des livres jusqu'a ce qu'une des "
			"etageres soit pleine : \n");
		ajouter_livre(bibli);
		system("cls");
	}

	// Verifier que l'agrandissement de memoire ait fonctionne
	afficher_bibliotheque(bibli);

	printf("\nNouvelle taille : %d\n\n", bibli->taille);
	super_pause();
	system("cls");
}

//-----------------------------------------------------------------------------
//							Fonction afficher_menu_simulation
// Cette fonction permet d'afficher le menu de la simulation en proposant 
// d'executer les differentes fonctions de test definies plus haut.
//
// Parametres : aucun
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_menu_simulation()
{
	printf("====================== MENU SIMULATION =======================\n");
	printf("1 - Simulation chariot\n");
	printf("2 - Simulation robot\n");
	printf("3 - Simulation kiosque\n");
	printf("4 - Simulation bibliotheque\n");
	printf("0 - Quitter\n");
	printf("==============================================================\n");
	printf("Choix : ");
}
