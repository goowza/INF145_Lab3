// ========================= MODULE T_BIBLIO_MACHINE ==========================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet d'effectuer plusieurs services relatifs a un kiosque.
//  Un kiosque contient la bibliotheque dans laquelle opere le chariot, le
//  robot et le chariot avec lesquels opere le kiosque et l'utilisateur 
//  courant du kiosque.
//
//  Le module permet de :
//	- Initialiser le kiosque.
//  - Servir l'utilisateur du kiosque en lui proposant differents services :
//		1) Chercher un livre dans la bibliotheque et afficher les resultats.
//		2) Retourner un des livres emprunte par l'utilisateur.
//		3) Apporter un livre a l'utilisateur sans passer par la recherche.
//		4) Voir le dossier de l'utilisateur.
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t_biblio_machine.h"

// ==================== Declaration des fonctions privees =====================

// Cette fonction permet d'afficher le menu principal du kiosque.
void afficher_menu_servir(t_etudiant * etudiant);

// Cette fonction permet d'afficher le menu principal de recherche de livres.
// L'utilisateur choisit quel type de recherche il desire effectuer.
void afficher_menu_chercher_livre();

// Cette fonction permet d'afficher le menu de retour des livres, autrement dit
// les emprunts de l'utilisateur.
void afficher_menu_retourner_livre(t_etudiant etudiant);

// Cette fonction permet de "tasser" le tableau d'emprunts : on enleve les 
// trous eventuellement presents dans le tableau d'emprunts de l'utilisateur.
void ranger_emprunts(t_biblio_machine * machine);

// ============================================================================

//-----------------------------------------------------------------------------
//							Fonction afficher_menu_servir
// Cette fonction permet d'afficher le menu principal du kiosque.
//
// Parametres : etudiant = etudiant utilisant la machine
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_menu_servir(t_etudiant * etudiant)
{
	printf("Bonjour Etudiant No.%d\n", etudiant->ID);
	printf("Comment puis-je vous aider aujourd'hui ?\n");
	printf("=================================\n");
	printf("1 - Chercher livre\n");
	printf("2 - Retourner livre\n");
	printf("3 - Apporter livre\n");
	printf("4 - Voir dossier\n");
	printf("0 - Quitter\n");
	printf("=================================\n");
}

//-----------------------------------------------------------------------------
//							Fonction afficher_menu_chercher_livre
// Cette fonction permet d'afficher le menu principal de recherche de livres.
// L'utilisateur choisit quel type de recherche il desire effectuer.
//
// Parametres : aucun
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_menu_chercher_livre()
{
	system("cls");
	printf("=================================\n");
	printf("Rechercher le livre par : \n");
	printf("1 - ISBN\n");
	printf("2 - Genre\n");
	printf("3 - Titre\n");
	printf("4 - Nom auteur\n");
	printf("5 - Prenom auteur\n");
	printf("=================================\n");
}

//-----------------------------------------------------------------------------
//							Fonction afficher_menu_retourner_livre
// Cette fonction permet d'afficher le menu de retour des livres, autrement dit
// les emprunts de l'utilisateur.
//
// Parametres : etudiant = etudiant dont on veut afficher les emprunts
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_menu_retourner_livre(t_etudiant etudiant)
{
	int i;
	system("cls");
	printf("=================================\n");
	printf("Quel livre voulez-vous retourner aujourd'hui ?\n\n");
	for (i = 0; i<NB_LIVRES_EMPRUNTES_MAX; i++)
	{
		printf("%d :\n", i + 1);
		if (etudiant.livres_empruntes[i].isbn != ISBN_INVALIDE)
			afficher_info_livre(&etudiant.livres_empruntes[i]);
		else
			printf(" \n");
	}
	printf("=================================\n");
}

//-----------------------------------------------------------------------------
//							Fonction initialiser_machine
// Cette fonction permet d'initialiser les valeurs d'un kiosque en lui 
// assignant une bibliotheque, le chariot et le robot de cette bibliotheque.
// Le kiosque n'a pas d'utilisateur apres son initialisation.
//
// Parametres : machine = machine a initialiser
//				pBibli = pointeur vers la bibliotheque a assigner a la machine
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_machine(t_biblio_machine * machine, t_bibliotheque * pBibli)
{
	machine->ptr_bibli = pBibli;
	machine->ptr_chariot = &pBibli->chariot;
	machine->ptr_robot = &pBibli->robot;
	machine->utilisateur = NULL;
}

//-----------------------------------------------------------------------------
//							Fonction servir_etudiant_machine
// Cette fonction permet de servir l'utilisateur courant du kiosque. Le kiosque
// propose plusieurs services a l'etudiant via un menu : il est possible de 
// chercher un livre dans la bibliotheque et de l'emprunter, de retourner des 
// livres empruntes precedemment, d'emprunter un livre via son numero isbn et
// de consulter le dossier de l'utilisateur.
//
// Parametres : machine = machine effectuant le service
//				etudiant = pointeur vers l'etudiant a servir
// Retour :		aucun
//-----------------------------------------------------------------------------
void servir_etudiant_machine(t_biblio_machine * machine, t_etudiant * etudiant)
{
	int choix_menu;
	int isbn_demande;
	machine->utilisateur = etudiant;

	do
	{
		system("cls");
		afficher_menu_servir(etudiant);
		choix_menu = demander_choix_menu(NUM_CHOIX_SERVIR_MIN, NUM_CHOIX_SERVIR_MAX);

		switch (choix_menu)
		{
		case 1:
			chercher_livre(machine);
			break;
		case 2:
			retourner_livre(machine);
			break;
		case 3:
			isbn_demande = demander_isbn();
			if (apporter_livre_machine(machine, isbn_demande))
			{
				printf("Vous avez emprunte le livre de numero isbn %d\n",
					isbn_demande);
			}
			else
				printf("Erreur : livre introuvable ou indisponible\n");
			break;
		case 4:
			voir_dossier(*machine);
			break;
		default:
			break;
		}
		super_pause();
	} while (choix_menu != 0);

	machine->utilisateur = NULL;
}

//-----------------------------------------------------------------------------
//							Fonction chercher_livre
// Cette fonction permet de chercher un livre dans la base de donnee de la
// bibliotheque ou fonctionne la machine. On peut effectuer une recherche par 
// numero isbn, par genre, par titre, par nom ou prenom d'auteur. 
// La fonction affiche tous les resultats et propose a l'etudiant d'emprunter 
// le livre.
//
// Parametres : machine = machine effectuant le service
// Retour :		aucun
//-----------------------------------------------------------------------------
void chercher_livre(t_biblio_machine * machine)
{
	int choix_menu;
	char buffer;
	int i, j;

	// Variables qui vont etre renseignees par l'utilisateur
	int isbn_demande;
	int genre_demande;
	char titre_demande[TAILLE_TITRE];
	char nom_auteur_demande[TAILLE_NOM];
	char prenom_auteur_demande[TAILLE_PRENOM];

	// liste dans laquelle sont stockes les resultats de la recherche
	t_liste liste_resultats;

	t_livre * livre_trouve = NULL;
	t_livre livre_emprunte;

	afficher_menu_chercher_livre();
	choix_menu = demander_choix_menu(NUM_CHOIX_RECHERCHE_MIN, NUM_CHOIX_RECHERCHE_MAX);
	init_liste(&liste_resultats);

	switch (choix_menu)
	{
		// Recherche par ISBN
	case 1:
		isbn_demande = demander_isbn();
		livre_trouve = rechercher_livre_isbn(machine->ptr_bibli, isbn_demande);
		if (livre_trouve != NULL)
			ajout_debut_liste(&liste_resultats, *livre_trouve);
		else
			printf("Livre introuvable ! Veuillez verifier l'isbn entre\n");
		break;

		// Recherche par genre
	case 2:
		printf("Entrez le genre du livre : ");
		scanf("%d", &genre_demande);
		if (genre_demande >= 0 && genre_demande < NB_GENRES)
		{
			for (j = 0; j < machine->ptr_bibli->taille; j++)
			{
				if (machine->ptr_bibli->livres[genre_demande][j].isbn !=
					ISBN_INVALIDE)
				{
					ajout_debut_liste(&liste_resultats,
						machine->ptr_bibli->livres[genre_demande][j]);
				}
			}
		}
		break;

		// Recherche par titre
	case 3:
		scanf("%c", &buffer);
		printf("Entrez le titre du livre : ");
		fgets(titre_demande, TAILLE_TITRE, stdin);
		retirer_sautligne(titre_demande);
		for (i = 0; i < NB_GENRES; i++)
		{
			for (j = 0; j < machine->ptr_bibli->taille; j++)
			{
				if (machine->ptr_bibli->livres[i][j].isbn != ISBN_INVALIDE
					&& strstr(machine->ptr_bibli->livres[i][j].titre, titre_demande) != NULL)
				{
					ajout_debut_liste(&liste_resultats,
						machine->ptr_bibli->livres[i][j]);
				}
			}
		}
		break;

	// Recherche par nom d'auteur
	case 4:
		scanf("%c", &buffer);
		printf("Entrez le nom de l'auteur du livre : ");
		fgets(nom_auteur_demande, TAILLE_NOM, stdin);
		retirer_sautligne(nom_auteur_demande);
		for (i = 0; i < NB_GENRES; i++)
		{
			for (j = 0; j < machine->ptr_bibli->taille; j++)
			{
				if (machine->ptr_bibli->livres[i][j].isbn != ISBN_INVALIDE
					&& strstr(machine->ptr_bibli->livres[i][j].auteur_nom,
						nom_auteur_demande) != NULL)
				{
					ajout_debut_liste(&liste_resultats,
						machine->ptr_bibli->livres[i][j]);
				}
			}
		}
		break;

	// Recherche par prenom d'auteur
	case 5:
		scanf("%c", &buffer);
		printf("Entrez le prenom de l'auteur du livre : ");
		fgets(prenom_auteur_demande, TAILLE_PRENOM, stdin);
		retirer_sautligne(prenom_auteur_demande);
		for (i = 0; i < NB_GENRES; i++)
		{
			for (j = 0; j < machine->ptr_bibli->taille; j++)
			{
				if (machine->ptr_bibli->livres[i][j].isbn != ISBN_INVALIDE
					&& strstr(machine->ptr_bibli->livres[i][j].auteur_prenom,
						prenom_auteur_demande) != NULL)
				{
					ajout_debut_liste(&liste_resultats,
						machine->ptr_bibli->livres[i][j]);
				}
			}
		}
		break;
	default:
		break;
	}

	printf("\nResultats de la recherche :\n");
	afficher_liste(liste_resultats);

	// Si la recherche amene au moins un resultat, on demande a l'utilisateur de 
	// choisir le livre qu'il veut emprunter
	if (liste_resultats.nb_elements > 0)
	{
		printf("Quel livre voulez-vous emprunter ?\n");
		scanf("%d", &choix_menu);
		if (choix_menu > 0 && choix_menu <= liste_resultats.nb_elements)
		{
			livre_emprunte = enlever_liste_indice(&liste_resultats,choix_menu);
			if (livre_emprunte.bEmprunte == DISPONIBLE)
			{
				emprunter_livre_biblio(machine->ptr_bibli, livre_emprunte.isbn);
				emprunter_livre_etudiant(machine->utilisateur, livre_emprunte);
			}
			else
			{
				printf("Desole, ce livre n'est pas disponible\n");
			}
		}
		else
		{
			printf("Desole, ce livre n'existe pas ! \n");
		}
	}
}

//-----------------------------------------------------------------------------
//							Fonction retourner_livre
// Cette fonction permet de rendre un livre precedemment emprunte par 
// l'utilisateur de la machine. La fonction affiche les emprunts de l'etudiant
// et celui-ci choisit le livre qu'il desire rendre.
//
// Parametres : machine = machine effectuant le service
// Retour :		aucun
//-----------------------------------------------------------------------------
void retourner_livre(t_biblio_machine * machine)
{
	int choix_livre;
	afficher_menu_retourner_livre(*machine->utilisateur);
	choix_livre = demander_choix_menu(NUM_LIVRES_EMPRUNTE_MIN, NUM_LIVRES_EMPRUNTE_MAX);

	if (machine->utilisateur->livres_empruntes[choix_livre - 1].isbn != ISBN_INVALIDE)
	{
		// Donner le livre au robot
		ajouter_livre_robot(machine->ptr_robot, 
			machine->utilisateur->livres_empruntes[choix_livre - 1]);

		// Ramener le livre dans la bibliotheque via le chariot
		retourner_livres(machine->ptr_chariot);

		// Retirer le livre des emprunts de l'utilisateur
		initialiser_livre(&machine->utilisateur->livres_empruntes[choix_livre - 1]);
		machine->utilisateur->nb_livres_empruntes--;
		ranger_emprunts(machine);
	}
	else
	{
		printf("Erreur : ce livre n'existe pas\n");
	}
}

//-----------------------------------------------------------------------------
//							Fonction apporter_livre_machine
// Cette fonction reçoit le ISBN du livre a apporter et envoie le chariot 
// chercher ce livre. Cette fonction permet à l'étudiant qui sait quel livre 
// il veut emprunter, d'envoyer le chariot intelligent chercher le livre sans
// passer par le menu "chercher".
// La fonction retourne 1 si le chariot a trouvé le livre et l'a remis à l'étudiant
// ou 0 si le chariot n'a pas pu remettre le livre à l'étudiant.
//
// Parametres : machine = machine effectuant le service
//				isbn = numero du livre a apporter
// Retour :		resultat = resultat de l'execution de la fonction
//-----------------------------------------------------------------------------
int apporter_livre_machine(t_biblio_machine * machine, int isbn)
{
	int resultat;
	t_livre livre_apporte;
	livre_apporte = apporter_livre(machine->ptr_chariot, isbn);
	if (livre_apporte.isbn != ISBN_INVALIDE && livre_apporte.bEmprunte != EMPRUNT)
	{
		// remettre le livre a l'etudiant
		resultat = emprunter_livre_etudiant(machine->utilisateur, livre_apporte);
		// enlever le livre de la bibliotheque
		emprunter_livre_biblio(machine->ptr_bibli, isbn);
	}
	else
	{
		resultat = ECHEC;
	}
	return resultat;
}

//-----------------------------------------------------------------------------
//							Fonction voir_dossier
// Cette fonction affiche le dossier de l'étudiant, soit les informations 
// generales et les livres empruntes.
//
// Parametres : machine = machine effectuant le service
// Retour :		aucun
//-----------------------------------------------------------------------------
void voir_dossier(t_biblio_machine machine)
{
	printf("========================= Dossier =========================\n");
	printf("Annee inscription : %d\n", machine.utilisateur->annee_inscription);
	printf("Identifiant : %d\n", machine.utilisateur->ID);
	printf("Emprunts : \n");
	afficher_emprunts(*machine.utilisateur);
	printf("===========================================================\n");
}

//-----------------------------------------------------------------------------
//							Fonction demander_isbn
// Cette fonction demande a l'utilisateur d'entrer un numero isbn et retourne
// la valeur entree si elle est valide.
//
// Parametres : machine = machine effectuant le service
// Retour :		aucun
//-----------------------------------------------------------------------------
int demander_isbn()
{
	int isbn_entre;
	do
	{
		printf("Veuillez entrer un numero isbn : \n");
		scanf("%d", &isbn_entre);
	} while (isbn_entre < 0 && isbn_entre > MAX_ISBN);
	
	return isbn_entre;
}


//-----------------------------------------------------------------------------
//							Fonction ranger_emprunts
// Cette fonction permet de "tasser" le tableau d'emprunts : on enleve les 
// trous eventuellement presents dans le tableau d'emprunts de l'utilisateur.
// Par exemple, si l'utilisateur avait emprunte 3 livres et avait rendu le 
// livre stocke a l'indice 1 du tableau, la fonction decale le livre stocke a
// l'indice 2 du tableau dans la case 1.
//
// Parametres : machine = machine effectuant le service
// Retour :		aucun
//-----------------------------------------------------------------------------
void ranger_emprunts(t_biblio_machine * machine)
{
	int compteur = 0;
	int i;

	while (compteur < machine->utilisateur->nb_livres_empruntes)
	{
		if (machine->utilisateur->livres_empruntes[compteur].isbn != ISBN_INVALIDE)
		{
			compteur++;
		}
		else
		{
			for (i = compteur; i < NB_LIVRES_EMPRUNTES_MAX - 1; i++)
				machine->utilisateur->livres_empruntes[i] =
				machine->utilisateur->livres_empruntes[i + 1];
			initialiser_livre(
				&machine->utilisateur->livres_empruntes[NB_LIVRES_EMPRUNTES_MAX - 1]);
		}
	}
}
