// ========================= MODULE T_LISTE_LIVRES ============================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet de gerer une liste de livres via differentes fonctions.
//
//  Le module permet de :
//	- Initialiser une liste de livres
//  - Tester si une liste est vide.
//	- Ajouter un livre au debut de la liste.
//	- Ajouter un livre a la fin de la liste.
//	- Enlever un livre au debut de la liste.
//	- Enlever un livre a la fin de la liste.
//	- Ajouter un livre a une position demandee de la liste.
//	- Enelever un livre a une position demandee de la liste.
//	- Afficher la Liste.
//  Attention : ce module gere uniquement des listes de t_livres
//=============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "t_liste_livres.h"

//-----------------------------------------------------------------------------
//							Fonction init_liste
// Cette fonction permet d'initialiser une une liste, la liste est vide et sa 
// tete pointe vers NULL.
//
// Parametres : liste = la liste a initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void init_liste(t_liste * liste)
{
	if (liste != NULL)
	{
		liste->tete = NULL;
		liste->nb_elements = 0;
	}
}

//-----------------------------------------------------------------------------
//							Fonction liste_vide
// Cette fonction renvoie si une liste est vide ou non. 
// (La fonction renvoie 0 si la liste n'est pas vide)
//
// Parametres : liste = la liste a tester
// Retour :		resultat du test
//-----------------------------------------------------------------------------
int liste_vide(t_liste * liste)
{
	return(liste->nb_elements == 0);
}


//-----------------------------------------------------------------------------
//							Fonction ajout_debut_liste
// Cette fonction ajoute un element au debut de la liste.
// La fonction retourne SUCCES si l'element a bien ete ajoute, ECHEC sinon.
//
// Parametres : liste = la liste ou ajouter l'element
//				element = element a ajouter a la liste
// Retour :		resultat = resultat de l'execution de la fonction
//-----------------------------------------------------------------------------
int ajout_debut_liste(t_liste * liste, t_element_liste element)
{
	int resultat;

	// pointeur vers l'element a ajouter
	t_noeud_liste * nouveau_noeud = (t_noeud_liste*)malloc(sizeof(t_noeud_liste));

	// Test du malloc (si le malloc n'a pas ete correctement execute, 
	// la fonction ne fait rien)
	if (nouveau_noeud != NULL)
	{
		// mise a jour des liens
		nouveau_noeud->donnee = element;
		nouveau_noeud->suivant = liste->tete;
		liste->tete = nouveau_noeud;

		// mise a jour nombre d'elements total de la liste
		liste->nb_elements++;
		resultat = SUCCES;
	}
	else
		resultat = ECHEC;

	return resultat;
}

//-----------------------------------------------------------------------------
//							Fonction ajout_fin_liste
// Cette fonction ajoute un element a la fin de la liste.
// La fonction retourne SUCCES si l'element a bien ete ajoute, ECHEC sinon.
//
// Parametres : liste = la liste ou ajouter l'element
//				element = element a ajouter a la liste
// Retour :		resultat = resultat de l'execution de la fonction
//-----------------------------------------------------------------------------
int ajout_fin_liste(t_liste * liste, t_element_liste element)
{
	int resultat;
	// pointeur vers l'element a ajouter
	t_noeud_liste * nouveau_noeud = (t_noeud_liste*)malloc(sizeof(t_noeud_liste));

	t_noeud_liste * curseur = liste->tete;

	// Test pour verifier l'existence de la liste
	if (liste != NULL)
	{
		// Test du malloc (si le malloc n'a pas ete correctement execute, 
		// la fonction ne fait rien
		if (nouveau_noeud != NULL)
		{
			while (curseur->suivant != NULL)
			{
				curseur = curseur->suivant;
			}

			// mise a jour des liens et stockage de la donnee
			nouveau_noeud->donnee = element;
			nouveau_noeud->suivant = NULL;
			curseur->suivant = nouveau_noeud;

			// mise a jour nombre d'elements total de la liste
			liste->nb_elements++;
			resultat = SUCCES;
		}
		else
			resultat = ECHEC;
	}
	else
		resultat = ECHEC;

	return resultat;
}

//-----------------------------------------------------------------------------
//							Fonction enlever_debut_liste
// Cette fonction enleve un element au debut de la liste. La fonction retourne
// une copie de l'element retire. Si la liste est vide, on retourne un livre 
// initialise.
//
// Parametres : liste = la liste ou enlever l'element
// Retour :		element_retire = copie de l'element enleve de la liste
//-----------------------------------------------------------------------------
t_element_liste enlever_debut_liste(t_liste * liste)
{
	// element enleve de la liste
	t_element_liste element_retire;
	// pointeur permettant de free la memoire
	t_noeud_liste * tmp;

	// on met un livre initialise dans l'element que l'on va retourner
	initialiser_livre(&element_retire);

	if (!liste_vide(liste))
	{
		// stockage de la donnee
		element_retire = liste->tete->donnee;

		// mise a jour des liens
		tmp = liste->tete;
		liste->tete = liste->tete->suivant;
		free(tmp);

		// mise a jour nombre d'elements total de la liste
		liste->nb_elements--;
	}
	return element_retire;
}

//-----------------------------------------------------------------------------
//							Fonction enlever_fin_liste
// Cette fonction enleve un element a la fin de la liste. La fonction retourne
// une copie de l'element retire. Si la liste est vide, on retourne un livre 
// initialise.
//
// Parametres : liste = la liste ou enlever l'element
// Retour :		element_retire = copie de l'element enleve de la liste
//-----------------------------------------------------------------------------
t_element_liste enlever_fin_liste(t_liste * liste)
{
	// element enleve de la liste
	t_element_liste element_retire;

	t_noeud_liste * curseur = liste->tete;
	t_noeud_liste * suiveur = curseur;

	// on met un livre initialise dans l'element que l'on va retourner
	initialiser_livre(&element_retire);

	if (!liste_vide(liste))
	{
		while (curseur->suivant != NULL)
		{
			suiveur = curseur;
			curseur = curseur->suivant;
		}

		// stockage de la donnee
		element_retire = curseur->donnee;

		// mise a jour des liens
		suiveur->suivant = NULL;
		free(curseur);

		// mise a jour nombre d'elements total de la liste
		liste->nb_elements--;
	}
	return element_retire;
}

//-----------------------------------------------------------------------------
//							Fonction ajouter_liste_indice
// Cette fonction ajoute un element a une position donnee de la liste. 
// La fonction retourne SUCCES si l'element a bien ete ajoute, ECHEC sinon.
// Si la position entree est inferieure a 1, on ajoute au debut de la liste.
// Si la position entree est superieure au nombre d'elements de la liste, on 
// ajoute a la fin de la liste.
// Le premier element de la liste est a l'indice 1.
//
// Parametres : liste = la liste ou ajouter l'element
//				element = element a ajouter a la liste
//				indice = position ou ajouter l'element
// Retour :		resultat = resultat de l'execution de la fonction
//-----------------------------------------------------------------------------
int ajouter_liste_indice(t_liste * liste, t_element_liste element, int indice)
{
	int i;
	int resultat;
	// pointeur permettent de se placer a l'indice desire
	t_noeud_liste * curseur = liste->tete;
	// pointeur vers l'element a ajouter
	t_noeud_liste * nouveau_noeud = (t_noeud_liste*)malloc(sizeof(t_noeud_liste));

	// Test du malloc (si le malloc n'a pas ete correctement execute, 
	// la fonction ne fait rien
	if (nouveau_noeud != NULL)
	{
		if (!liste_vide(liste))
		{
			if (indice <= 1)
			{
				ajout_debut_liste(liste, element);
			}
			else if ((indice <= liste->nb_elements) && indice > 1)
			{
				// postionnement du curseur a l'indice voulu
				for (i = 1; i < indice - 1; i++)
				{
					curseur = curseur->suivant;
				}
				// mise a jour des liens
				nouveau_noeud->donnee = element;
				nouveau_noeud->suivant = curseur->suivant;
				curseur->suivant = nouveau_noeud;

				// mise a jour nombre d'elements total de la liste
				liste->nb_elements++;
			}

			else if (indice > liste->nb_elements)
			{
				ajout_fin_liste(liste, element);
			}
		}
		else
		{
			ajout_debut_liste(liste, element);
		}
		resultat = SUCCES;
	}
	else
	{
		resultat = ECHEC;
	}
	return resultat;
}

//-----------------------------------------------------------------------------
//							Fonction enlever_liste_indice
// Cette fonction enleve un element a une position donnee de la liste. 
// La fonction retourne une copie de l'element retire. Si la liste est vide,
// on retourne un livre initialise.
// Si la position entree est inferieure a 1, on enleve au debut de la liste.
// Si la position entree est superieure au nombre d'elements de la liste, on 
// enleve a la fin de la liste.
// Le premier element de la liste est a l'indice 1.
//
// Parametres : liste = la liste ou enlever l'element
//				indice = position de l'element a enlever
// Retour :		element_retire = copie de l'element retire de la liste
//-----------------------------------------------------------------------------
t_element_liste enlever_liste_indice(t_liste * liste, int indice)
{
	int i;
	// pointeur permettent de se placer a l'indice desire
	t_noeud_liste * curseur = liste->tete;
	// pointeur positionne juste avant le curseur
	t_noeud_liste * suiveur = curseur;

	// element enleve de la liste
	t_element_liste element_retire;

	// pointeur permettant de free la memoire
	t_noeud_liste * tmp;

	// on met un livre initialise dans l'element que l'on va retourner
	initialiser_livre(&element_retire);

	if (liste != NULL)
	{
		if (!liste_vide(liste))
		{
			if (indice == 1)
			{
				element_retire = enlever_debut_liste(liste);
			}
			else if ((indice < liste->nb_elements) && (indice > 1))
			{
				// postionnement du curseur a l'indice voulu
				for (i = 1; i < indice; i++)
				{
					suiveur = curseur;
					curseur = curseur->suivant;
				}

				tmp = curseur;
				element_retire = curseur->donnee;
				suiveur->suivant = curseur->suivant;
				free(tmp);
				liste->nb_elements--;
			}
			else if (indice >= liste->nb_elements)
			{
				element_retire = enlever_fin_liste(liste);
			}
		}
	}
	return element_retire;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_liste
// Cette fonction affiche tous les elements d'une liste en partant de l'element
// a la position 1.
//
// Parametres : liste = la liste a afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_liste(t_liste liste)
{
	t_noeud_liste * curseur = liste.tete;
	int compteur = 1;

	if (!liste_vide(&liste))
	{
		while (curseur != NULL)
		{
			afficher_info_livre(&curseur->donnee);
			curseur = curseur->suivant;
			compteur++;
		}
	}
}
