#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "t_biblio_chariot.h"

void initialiser_chariot(t_biblio_chariot * chariot, t_bibliotheque * pBibli)
{
	chariot->liste_livres = NULL;
	chariot->pBibli = pBibli;
	chariot->position = POS_KIOSQUE;
	chariot->utilisateur = NULL;
}

int ajouter_livre_chariot(t_biblio_chariot * chariot, t_livre livre)
{
	int resultat;
	t_noeud_liste * curseur = chariot->liste_livres->tete;
	int indice = 1;

	int btrouve = !LIVRE_TROUVE;

	if (chariot->liste_livres != NULL)
	{
		// si la liste est vide on ajoute au debut
		if (chariot->liste_livres->nb_elements == 0)
		{
			resultat = ajouter_debut(chariot->liste_livres, livre);
		}
		// si la liste n'a qu'un livre on ajoute soit au debut soit a la fin
		else if (chariot->liste_livres->nb_elements == 1)
		{
			if (chariot->liste_livres->tete->donnee.isbn > livre.isbn)
				resultat = ajouter_debut(chariot->liste_livres, livre);
			else
				resultat = ajouter_fin(chariot->liste_livres, livre);
		}
		// si la liste contient au moins 2 elements on ajoute a l'indice determine
		// par le numero isbn du livre
		else
		{
			while (!btrouve)
			{
				if (indice == chariot->liste_livres->nb_elements)
				{
					btrouve = LIVRE_TROUVE;
					resultat = ajouter_fin(chariot->liste_livres, livre);
				}
				if (curseur->donnee.isbn > livre.isbn)
				{
					btrouve = LIVRE_TROUVE;
					resultat = ajouter_debut(chariot->liste_livres, livre);
				}
				else if (curseur->suivant->donnee.isbn > livre.isbn)
				{
					btrouve = LIVRE_TROUVE;
					resultat = ajouter_liste_indice(chariot->liste_livres, livre, indice + 1);
				}
				else
				{
					curseur = curseur->suivant;
					indice++;
				}
			}
		}
		//emprunter_livre_biblio(chariot->pBibli, livre.isbn);
	}
	else
		resultat = ECHEC;

	return resultat;
}

int chercher_indice_livre(t_biblio_chariot * chariot, int isbn)
{
	int indice_trouve = 1;
	t_noeud_liste * curseur = chariot->liste_livres->tete;
	int btrouve = !LIVRE_TROUVE;
	while (!btrouve)
	{
		if (curseur != NULL)
		{
			if (curseur->donnee.isbn != isbn)
			{
				curseur = curseur->suivant;
				indice_trouve++;
			}
			else
				btrouve = LIVRE_TROUVE;
		}
		else
		{
			indice_trouve = INVALIDE;
			btrouve = LIVRE_TROUVE;
		}
	}
	return indice_trouve;
}

t_livre retirer_livre_chariot(t_biblio_chariot * chariot, int isbn)
{
	t_livre livre_retire;
	int indice_livre;

	initialiser_livre(&livre_retire);
	indice_livre = chercher_indice_livre(chariot, isbn);

	if (indice_livre != INVALIDE)
		livre_retire = enlever_liste_indice(chariot->liste_livres, indice_livre);
	else
		printf("Erreur : livre inexistant\n");
	return livre_retire;
}

void emprunter_livre_chariot(t_biblio_chariot * chariot)
{
	int isbn_cherche;
	int indice_livre_trouve;
	int choix_emprunt;
	t_livre livre_emprunte;

	printf("Entrez isbn : \n");
	scanf("%d", &isbn_cherche);
	indice_livre_trouve = chercher_indice_livre(chariot, isbn_cherche);
	if (indice_livre_trouve != INVALIDE)
	{
		printf("Livre trouve ! Voulez vous l'emprunter ?\n");
		printf("1 - OUI || 0 - NON\n");
		choix_emprunt = demander_choix_menu(NE_PAS_EMPRUNTER_LIVRE, EMPRUNTER_LIVRE);
		if (choix_emprunt == EMPRUNTER_LIVRE)
		{
			livre_emprunte = retirer_livre_chariot(chariot, isbn_cherche);
			livre_emprunte.bEmprunte = EMPRUNT;
			emprunter_livre_etudiant(chariot->utilisateur, livre_emprunte);
			emprunter_livre_biblio(chariot->pBibli, isbn_cherche);
		}
	}
	else
	{
		printf("Livre introuvable dans ce chariot !\n");
	}
}

void retourner_livres(t_biblio_chariot * chariot)
{
	t_livre livre_retourne;

	// pointeur vers le livre se trouvant dans la bibliotheque
	t_livre * ptr_livre_biblio;

	chariot->position = POS_DEPLACEMENT;

	// On vide la liste du chariot et on modifie les indicateurs d'emprunt 
	// des livres de la bibliotheque corespondants
	while (!liste_vide(chariot->liste_livres))
	{
		livre_retourne = enlever_debut(chariot->liste_livres);

		ptr_livre_biblio = rechercher_livre_isbn(chariot->pBibli, livre_retourne.isbn);
		ptr_livre_biblio->bEmprunte = DISPONIBLE;
	}
}

t_position_chariot get_position(t_biblio_chariot chariot)
{
	return chariot.position;
}

t_livre apporter_livre(t_biblio_chariot * chariot, int isbn)
{
	t_livre livre_apporte;
	// variable permettant de chercher le livre dans le chariot
	int indice_livre_chariot;

	initialiser_livre(&livre_apporte);

	// si le numero isbn existe
	if (rechercher_livre_isbn(chariot->pBibli, isbn) != NULL)
	{
		indice_livre_chariot = chercher_indice_livre(chariot, isbn);
		// si le livre est present dans la liste du chariot
		if (indice_livre_chariot != INVALIDE)
		{
			// on enleve ce livre du chariot et on le stock dans livre_apporte
			livre_apporte = enlever_liste_indice(chariot->liste_livres, indice_livre_chariot);
		}
		else
		{
			// on envoie le chariot chercher le livre dans la bibliotheque
			chariot->position = POS_DEPLACEMENT;
			livre_apporte = *rechercher_livre_isbn(chariot->pBibli, isbn);
			//emprunter_livre_biblio(chariot->pBibli, isbn);
			chariot->position = POS_KIOSQUE;
		}
	}
	return livre_apporte;
}

