#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "t_biblio_machine.h"


void servir_etudiant(t_biblio_machine * machine,t_etudiant * etudiant)
{
	printf("Bonjour Etudiant No.%d\n", etudiant->ID);
	printf("Comment puis_je vous aider aujourd'hui ?\n");
	printf("=================================\n");
	printf("1 - Chercher livre\n");
	printf("2 - Retourner livre\n");
	printf("3 - Apporter livre\n");
	printf("4 - Voir dossier\n");
	printf("=================================\n");

}

void chercher_livre(t_bibliotheque * pBibli)
{
	int choix_menu;
	int isbn_demande;
	t_liste liste_resultats;
	afficher_menu_chercher_livre();
	choix_menu = demander_choix_menu_machine();

	init_liste(&liste_resultats);

	switch (choix_menu)
	{
	case 1:
		printf("Entrez le numero isbn recherche : \n");
		scanf("%d", &isbn_demande);
		ajouter_debut(&liste_resultats, *rechercher_livre_isbn(pBibli, isbn_demande));
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
	afficher_liste_livres(&liste_resultats);

}

void afficher_menu_chercher_livre()
{
	printf("=================================\n");
	printf("Rechercher le livre par : \n");
	printf("1 - ISBN\n");
	printf("2 - Genre\n");
	printf("3 - Titre\n");
	printf("4 - Nom auteur\n");
	printf("5 - Prenom auteur\n");
	printf("=================================\n");
}

int demander_choix_menu_machine()
{
	int choix;
	do
	{
		scanf("%d", &choix);
	} while (choix > NUM_CHOIX_RECHERCHE_MAX || choix < NUM_CHOIX_RECHERCHE_MIN);

	return choix;
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

void afficher_liste_livres(t_liste * liste)
{
	t_noeud * curseur = liste->tete;
	int compteur = 1;

	if (!liste_vide(liste))
	{
		while (curseur != NULL)
		{

			afficher_info_livre(&curseur->donnee);
			curseur = curseur->suivant;
			compteur++;
		}
	}
}
