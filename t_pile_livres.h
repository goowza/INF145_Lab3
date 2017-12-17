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

#pragma once

#ifndef _T_PILE_LIVRES__
#define _T_PILE_LIVRES__

#include "structs.h"
#include "t_bibliotheque.h"

// Cette fonction permet d'initialiser une une pile, la pile est vide et son 
// sommet pointe vers NULL.
void init_pile(t_pile * pile);

// Cette fonction renvoie si une pile est vide ou non. 
// (La fonction renvoie 0 si la pile n'est pas vide)
int pile_vide(t_pile * pile);

// Cette fonction ajoute un element au sommet de la pile.
void push(t_pile * pile, t_element_pile element);

// Cette fonction enleve un element au sommet de la pile.
// La fonction retourne une copie de l'element enleve.
t_element_pile pop(t_pile * pile);

// Cette fonction affiche tous les elements d'une pile depuis son sommet.
void afficher_pile(t_pile * pile);

#endif
