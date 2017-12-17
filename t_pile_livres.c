// ========================= MODULE T_PILE_LIVRES ============================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet de gerer une pile de livres via differentes fonctions.
//
//  Le module permet de :
//	- Initialiser une pile de livres
//  - Tester si une pile est vide.
//	- Ajouter un livre au sommet de la pile.
//	- Enlever un livre au sommet de la pile.
//	- Afficher la pile.
//  Attention : ce module gere uniquement des piles de t_livres
//=============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "t_pile_livres.h"

//-----------------------------------------------------------------------------
//							Fonction init_pile
// Cette fonction permet d'initialiser une une pile, la pile est vide et son 
// sommet pointe vers NULL.
//
// Parametres : pile = la pile a initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void init_pile(t_pile * pile)
{
	if (pile != NULL)
	{
		pile->sommet = NULL;
		pile->nb_elements = 0;
	}
}

//-----------------------------------------------------------------------------
//							Fonction pile_vide
// Cette fonction renvoie si une pile est vide ou non. 
// (La fonction renvoie 0 si la pile n'est pas vide)
//
// Parametres : pile = la pile a tester
// Retour :		resultat du test
//-----------------------------------------------------------------------------
int pile_vide(t_pile * pile)
{
	return (pile->nb_elements == 0);
}

//-----------------------------------------------------------------------------
//							Fonction push
// Cette fonction ajoute un element au sommet de la pile.
//
// Parametres : pile = la pile ou ajouter l'element
//				element = element a ajouter a la pile
// Retour :		aucun
//-----------------------------------------------------------------------------
void push(t_pile * pile, t_element_pile element)
{
	// pointeur vers l'element a ajouter
	t_noeud_pile * nouveau_noeud = (t_noeud_pile*)malloc(sizeof(t_noeud_pile));

	// Test du malloc (si le malloc n'a pas ete correctement execute, 
	// la fonction ne fait rien
	if (nouveau_noeud != NULL)
	{
		// mise a jour des liens
		nouveau_noeud->donnee = element;
		nouveau_noeud->suivant = pile->sommet;
		pile->sommet = nouveau_noeud;

		// mise a jour nombre d'elements total de la pile
		pile->nb_elements++;
	}
}

//-----------------------------------------------------------------------------
//							Fonction pop
// Cette fonction enleve un element au sommet de la pile.
// La fonction retourne une copie de l'element enleve.
//
// Parametres : pile = la pile ou enlever l'element
// Retour :		element_retire = copie de l'element enleve de la pile
//-----------------------------------------------------------------------------
t_element_pile pop(t_pile * pile)
{
	// element enleve de la pile
	t_element_pile element_retire;
	// pointeur permettant de free la memoire
	t_noeud_pile * tmp;

	// on met un livre initialise dans l'element que l'on va retourner
	initialiser_livre(&element_retire);

	if (!pile_vide(pile))
	{
		// stockage de la donnee
		element_retire = pile->sommet->donnee;

		// mise a jour des liens
		tmp = pile->sommet;
		pile->sommet = pile->sommet->suivant;
		free(tmp);

		// mise a jour nombre d'elements total de la pile
		pile->nb_elements--;
	}
	return element_retire;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_pile
// Cette fonction affiche tous les elements d'une pile depuis son sommet.
//
// Parametres : pile = la pile a afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_pile(t_pile * pile)
{
	t_pile pile_temp;
	t_livre livre_temp;

	init_pile(&pile_temp);

	if (pile != NULL)
	{
		// desempiler la pile pour acceder a ses valeurs
		while (!pile_vide(pile))
		{
			livre_temp = pop(pile);
			afficher_info_livre(&livre_temp);
			push(&pile_temp, livre_temp);
		}
		// re - empiler la pile de sorte a revenir a sa valeur initiale
		while (!pile_vide(&pile_temp))
		{
			livre_temp = pop(&pile_temp);
			push(pile, livre_temp);
		}
	}
}
