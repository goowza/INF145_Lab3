#ifndef _T_LISTE_LIVRES__
#define _T_LISTE_LIVRES__

#include "structs.h"

//changer cette déclaration pour obtenir des listes d'un autre type
typedef t_livre t_element;

typedef struct t_noeud
{
	t_element donnee;
	struct t_noeud * suivant;
}t_noeud;

typedef struct
{
	t_noeud * tete;
	int nb_elements;
}t_liste;

void init_liste(t_liste * liste);

int liste_vide(t_liste * liste);

void ajouter_debut(t_liste * liste, t_element element);

t_element enlever_debut(t_liste * liste);

void ajouter_liste_indice(t_liste * liste, t_element element, int indice);

t_element enlever_liste_indice(t_liste * liste, int indice);

void afficher_liste(t_liste * liste);

#endif
