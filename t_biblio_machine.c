#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "t_biblio_machine.h"

void initialiser_machine(t_biblio_machine * machine, t_bibliotheque * pBibli)
{
	machine->ptr_bibli = pBibli;
	machine->ptr_chariot = &pBibli->chariot;
	machine->ptr_robot = &pBibli->robot;
	machine->utilisateur = NULL;
}

void servir_etudiant(t_biblio_machine * machine, t_etudiant * etudiant)
{
	int choix_menu;

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
			break;
		case 4:
			break;
		default:
			break;
		}
	} while (choix_menu != 0);
}

void chercher_livre(t_biblio_machine * machine)
{
	int choix_menu;
	int isbn_demande;
	t_liste liste_resultats;
	t_livre * livre_trouve;

	afficher_menu_chercher_livre();
	choix_menu = demander_choix_menu(NUM_CHOIX_RECHERCHE_MIN, NUM_CHOIX_RECHERCHE_MAX);
	init_liste(&liste_resultats);

	switch (choix_menu)
	{
	case 1:
		printf("Entrez le numero isbn recherche : \n");
		scanf("%d", &isbn_demande);
		livre_trouve = rechercher_livre_isbn(machine->ptr_bibli, isbn_demande);
		if (livre_trouve != NULL)
			ajouter_debut(&liste_resultats, *livre_trouve);
		else
			printf("Livre introuvable ! Veuillez verifier l'isbn entre\n");
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}

	printf("\nResultats de la recherche :\n");
	afficher_liste(liste_resultats);
	super_pause();

}

void retourner_livre(t_biblio_machine * machine)
{
	int choix_livre;
	afficher_menu_retourner_livre(*machine->utilisateur);
	choix_livre = demander_choix_menu(NUM_LIVRES_EMPRUNTE_MIN, NUM_LIVRES_EMPRUNTE_MAX);

	if (machine->utilisateur->livres_empruntes[choix_livre - 1].isbn != ISBN_INVALIDE)
	{
		// Donner le livre au robot
		machine->ptr_robot->livre_temp =
			machine->utilisateur->livres_empruntes[choix_livre - 1];
		// Ramener le livre dans la bibliotheque
		ramener_livre_biblio(machine->ptr_bibli,
			machine->utilisateur->livres_empruntes[choix_livre - 1].isbn);
		// Retirer le livre des emprunts de l'utilisateur
		initialiser_livre(&machine->utilisateur->livres_empruntes[choix_livre - 1]);
	}
	else
	{
		printf("Erreur : ce livre n'existe pas\n");
	}
	super_pause();
}

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

//int demander_choix(int borne_inf, int borne_sup)
//{
//	int choix;
//	do
//	{
//		scanf("%d", &choix);
//	} while (choix > borne_sup || choix < borne_inf);
//
//	return choix;
//}

int apporter_livre_machine(t_biblio_machine * machine, int isbn)
{
	int resultat;
	t_livre livre_apporte;
	livre_apporte = apporter_livre(machine->ptr_chariot, isbn);
	if (livre_apporte.isbn != ISBN_INVALIDE)
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

void voir_dossier(t_biblio_machine machine)
{
	printf("========================= Dossier =========================\n");
	printf("Annee inscription : %d\n", machine.utilisateur->annee_inscription);
	printf("Identifiant : %d\n", machine.utilisateur->ID);
	printf("Emprunts : \n");
	afficher_emprunts(*machine.utilisateur);
	printf("===========================================================\n");
}

//t_liste * rechercher_isbn(t_bibliotheque * pBibli, int isbn_demande)
//{
//	t_liste liste_res;
//	init_liste(&liste_res);
//	int i, j;
//	for (i = 0; i < NB_GENRES; i++)
//	{
//		for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
//		{
//			if (pBibli->livres[i][j].isbn == isbn_demande)
//			{
//				ajouter_debut(&liste_res, pBibli->livres[i][j]);
//			}
//		}
//	}
//	return &liste_res;	
//}
//
//void afficher_liste_livres(t_liste * liste)
//{
//	t_noeud * curseur = liste->tete;
//	int compteur = 1;
//
//	if (!liste_vide(liste))
//	{
//		while (curseur != NULL)
//		{
//
//			afficher_info_livre(&curseur->donnee);
//			curseur = curseur->suivant;
//			compteur++;
//		}
//	}
//}
