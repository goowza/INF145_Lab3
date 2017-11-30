#pragma once

#ifndef _T_LISTE_LIVRES__
#define _T_LISTE_LIVRES__

#include "structs.h"
#include "t_bibliotheque.h"

void init_liste(t_liste * liste);

int liste_vide(t_liste * liste);

int ajouter_debut(t_liste * liste, t_element_liste element);

int ajouter_fin(t_liste * liste, t_element_liste element);

t_element_liste enlever_debut(t_liste * liste);

t_element_liste enlever_fin(t_liste * liste);

int ajouter_liste_indice(t_liste * liste, t_element_liste element, int indice);

t_element_liste enlever_liste_indice(t_liste * liste, int indice);

//int ajouter_croissant(t_liste * liste, t_element_liste element);

void afficher_liste(t_liste * liste);


#endif
