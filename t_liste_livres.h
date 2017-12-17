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

#pragma once

#ifndef _T_LISTE_LIVRES__
#define _T_LISTE_LIVRES__

#include "structs.h"
#include "t_bibliotheque.h"

// Cette fonction permet d'initialiser une une liste, la liste est vide et sa 
// tete pointe vers NULL.
void init_liste(t_liste * liste);

// Cette fonction renvoie si une liste est vide ou non. 
// (La fonction renvoie 0 si la liste n'est pas vide)
int liste_vide(t_liste * liste);

// Cette fonction ajoute un element au debut de la liste.
// La fonction retourne SUCCES si l'element a bien ete ajoute, ECHEC sinon.
int ajout_debut_liste(t_liste * liste, t_element_liste element);

// Cette fonction ajoute un element a la fin de la liste.
// La fonction retourne SUCCES si l'element a bien ete ajoute, ECHEC sinon.
int ajout_fin_liste(t_liste * liste, t_element_liste element);

// Cette fonction enleve un element au debut de la liste. La fonction retourne
// une copie de l'element retire. Si la liste est vide, on retourne un livre 
// initialise.
t_element_liste enlever_debut_liste(t_liste * liste);

// Cette fonction enleve un element a la fin de la liste. La fonction retourne
// une copie de l'element retire. Si la liste est vide, on retourne un livre 
// initialise.
t_element_liste enlever_fin_liste(t_liste * liste);

// Cette fonction ajoute un element a une position donnee de la liste. 
// La fonction retourne SUCCES si l'element a bien ete ajoute, ECHEC sinon.
// Si la position entree est inferieure a 1, on ajoute au debut de la liste.
// Si la position entree est superieure au nombre d'elements de la liste, on 
// ajoute a la fin de la liste.
// Le premier element de la liste est a l'indice 1.
int ajouter_liste_indice(t_liste * liste, t_element_liste element, int indice);

// Cette fonction enleve un element a une position donnee de la liste. 
// Si la position entree est inferieure a 1, on enleve au debut de la liste.
// Si la position entree est superieure au nombre d'elements de la liste, on 
// enleve a la fin de la liste.
// Le premier element de la liste est a l'indice 1.
t_element_liste enlever_liste_indice(t_liste * liste, int indice);

// Cette fonction affiche tous les elements d'une liste en partant de l'element
// a la position 1.
void afficher_liste(t_liste liste);


#endif



