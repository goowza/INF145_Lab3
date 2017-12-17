// ========================= MODULE T_BIBLIO_CHARIOT ==========================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet d'effectuer plusieurs services relatifs a un chariot
//  Un chariot contient une liste dynamique de livres representant les livres 
//  stockes temporairement sur celui-ci, ainsi qu'un utilisateur courant, une
//  position (le chariot se deplace dans la bibliotheque) et la bibliotheque
// dans laquelle opere le chariot.
//
//  Le module permet de :
//	- Initialiser le chariot.
//  - Ajouter un livre au chariot, dans l'ordre de numero isbn croissant.
//	- Retirer un livre du chariot en conservant l'ordre de la liste.
//	- Emprumter un livre directement au chariot
//	- Retourner tous les livres du chariot dans la bibliotheque.
//	- Apporter un livre en envoyant le chariot le chercher dans la 
//	  bibliotheque.
//	- Connaitre la position du chariot dans la bibliotheque.
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "t_biblio_chariot.h"

//-----------------------------------------------------------------------------
//							Fonction initialiser_chariot
// Cette fonction permet d'initialiser les valeurs d'un chariot en lui 
// assignant une bibliotheque et en le placant au kiosque.
// Le chariot n'a pas de liste ni d'utilisateur apres son initialisation.
//
// Parametres : chariot = chariot a initialiser
//				pBibli = pointeur vers la bibliotheque a assigner au chariot
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_chariot(t_biblio_chariot * chariot, t_bibliotheque * pBibli)
{
	chariot->liste_livres = NULL;
	chariot->pBibli = pBibli;
	chariot->position = POS_KIOSQUE;
	chariot->utilisateur = NULL;
}

//-----------------------------------------------------------------------------
//							Fonction ajouter_livre_chariot
// Cette fonction permet d'ajouter un livre dans le chariot, soit d'ajouter un
// livre dans la liste dynamique du chariot.
// On considere un livre comme emprunte lorsque il est dans le chariot.
// (renvoie SUCCES si tout s'est bien deroule, ECHEC sinon).
//
// Parametres : chariot = chariot dans lequel ajouter le livre
//				livre = livre a ajouter au chariot
// Retour :		resultat = resultat de l'execution de la fonction
//-----------------------------------------------------------------------------
int ajouter_livre_chariot(t_biblio_chariot * chariot, t_livre livre)
{
	int resultat;

	t_noeud_liste * curseur = chariot->liste_livres->tete;
	int indice = 1;

	// Variable booleenne indiquant si le livre a ete trouve dans le chariot
	// (permet d'arreter la recherche)
	int btrouve = !LIVRE_TROUVE;

	if (chariot->liste_livres != NULL)
	{
		livre.bEmprunte = EMPRUNT;
		// si la liste est vide on ajoute au debut
		if (chariot->liste_livres->nb_elements == 0)
		{
			resultat = ajout_debut_liste(chariot->liste_livres, livre);
		}
		// si la liste n'a qu'un livre on ajoute soit au debut soit a la fin
		else if (chariot->liste_livres->nb_elements == 1)
		{
			if (chariot->liste_livres->tete->donnee.isbn > livre.isbn)
				resultat = ajout_debut_liste(chariot->liste_livres, livre);
			else
				resultat = ajout_fin_liste(chariot->liste_livres, livre);
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
					resultat = ajout_fin_liste(chariot->liste_livres, livre);
				}
				if (curseur->donnee.isbn > livre.isbn)
				{
					btrouve = LIVRE_TROUVE;
					resultat = ajout_debut_liste(chariot->liste_livres, livre);
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
	}
	else
		resultat = ECHEC;

	return resultat;
}

//-----------------------------------------------------------------------------
//							Fonction chercher_indice_livre
// Cette fonction permet de trouver l'indice d'un livre (precise par son isbn)
// dans la liste dynamique du chariot.
// (renvoie INDICE_INVALIDE si le livre n'est pas dans le chariot)
//
// Parametres : chariot = chariot dans lequel chercher le livre
//				isbn = numero isbn du livre cherche
// Retour :		indice_trouve = position du livre dans la liste du chariot		
//-----------------------------------------------------------------------------
int chercher_indice_livre(t_biblio_chariot * chariot, int isbn)
{
	int indice_trouve = 1;
	t_noeud_liste * curseur = chariot->liste_livres->tete;

	// Variable booleenne indiquant si le livre a ete trouve dans le chariot
	// (permet d'arreter la recherche)
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
		// Si le livre n'a pas ete trouve
		else
		{
			indice_trouve = INVALIDE;
			btrouve = LIVRE_TROUVE;
		}
	}
	return indice_trouve;
}

//-----------------------------------------------------------------------------
//							Fonction retirer_livre_chariot
// Cette fonction permet de retirer un livre de la liste du chariot. La 
// fonction renvoie une copie du livre. Si le livre est introuvable dans le
// chariot, la fonction renvoie un livre initialise.
//
// Parametres : chariot = chariot dans lequel retirer le livre
//				isbn = numero isbn du livre a retirer
// Retour :		livre_retire = copie du livre retire			
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//							Fonction emprunter_livre_chariot
// Cette fonction permet a un utilisateur d'emprunter un livre directement
// depuis le chariot. La fonction demande a l'utilisateur d'entrer le numero
// isbn du livre a emprunter. Si le livre est present dans le chariot, on
// propose a l'utilisateur de l'emprunter.
//
// Parametres : chariot = chariot dans lequel chercher/emprunter le livre
// Retour :		aucun		
//-----------------------------------------------------------------------------
void emprunter_livre_chariot(t_biblio_chariot * chariot)
{
	int isbn_cherche;
	int indice_livre_trouve;
	int choix_emprunt;
	t_livre livre_emprunte;

	isbn_cherche = demander_isbn();

	indice_livre_trouve = chercher_indice_livre(chariot, isbn_cherche);

	// si le livre a ete trouve dans le chariot
	if (indice_livre_trouve != INVALIDE)
	{
		// proposer l'emprunt a l'utilisateur
		afficher_menu_emprunt();
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

//-----------------------------------------------------------------------------
//							Fonction retourner_livres
// Cette fonction permet de ramener tous les livres du chariot dans la 
// bibliotheque. Une fois la fonction executee, la liste du chariot est vide.
//
// Parametres : chariot = chariot a vider
// Retour :		aucun		
//-----------------------------------------------------------------------------
void retourner_livres(t_biblio_chariot * chariot)
{
	t_livre livre_retourne;

	chariot->position = POS_DEPLACEMENT;

	// On vide la liste du chariot et on modifie les indicateurs d'emprunt 
	// des livres de la bibliotheque corespondants
	while (!liste_vide(chariot->liste_livres))
	{
		livre_retourne = enlever_debut_liste(chariot->liste_livres);
		rendre_livre_biblio(chariot->pBibli, livre_retourne.isbn);
	}
}

//-----------------------------------------------------------------------------
//							Fonction get_position
// Cette fonction permet de connaitre la position actuelle du chariot dans la
// bibliotheque.
//
// Parametres : chariot = chariot dont on veut connaitre la position
// Retour :		position du chariot		
//-----------------------------------------------------------------------------
t_position_chariot get_position(t_biblio_chariot chariot)
{
	return chariot.position;
}

//-----------------------------------------------------------------------------
//							Fonction apporter_livre
// Cette fonction permet d'envoyer le chariot chercher un livre, soit dans sa 
// liste soit dans la bibliotheque si le livre n'est pas dans le chariot.
// La fonction retourne une copie du livre apporte, et retourne un livre
// initialise si le livre n'a pas ete trouve.
//
// Parametres : chariot = chariot a envoyer chercher le livre
// Retour :		livre_apporte = copie du livre apporte par le chariot		
//-----------------------------------------------------------------------------
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
			livre_apporte.bEmprunte = DISPONIBLE;
		}
		else 
		{
			// on envoie le chariot chercher le livre dans la bibliotheque
			chariot->position = POS_DEPLACEMENT;
			livre_apporte = *rechercher_livre_isbn(chariot->pBibli, isbn);
			chariot->position = POS_KIOSQUE;
		}
	}
	return livre_apporte;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_menu_emprunt
// Cette fonction permet d'afficher le menu proposant a l'utilisateur 
// d'emprunter un livre dans le chariot.
//
// Parametres : aucun
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_menu_emprunt()
{
	printf("Livre trouve ! Voulez vous l'emprunter ?\n");
	printf("1 - OUI || 0 - NON\n");
}
