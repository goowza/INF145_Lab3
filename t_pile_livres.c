#include <stdio.h>
#include <stdlib.h>

#include "t_pile_livres.h"


void init_pile(t_pile * pile)
{
	if (pile != NULL)
	{
		pile->sommet = NULL;
		pile->nb_elements = 0;
	}
}

int pile_vide(t_pile * pile)
{
	return (pile->nb_elements == 0);
}

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

		// mise a jour nombre d'elements total de la liste
		pile->nb_elements++;
	}

}

t_element_pile pop(t_pile * pile)
{
	// element enleve de la liste
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

		// mise a jour nombre d'elements total de la liste
		pile->nb_elements--;
	}
	return element_retire;
}

void afficher_pile(t_pile * pile)
{
	t_pile pile_temp;
	t_livre livre_temp;

	init_pile(&pile_temp);

	if (pile != NULL)
	{
		while (!pile_vide(pile))
		{
			livre_temp = pop(pile);
			afficher_info_livre(&livre_temp);
			push(&pile_temp, livre_temp);
		}
		while (!pile_vide(&pile_temp))
		{
			livre_temp = pop(&pile_temp);
			push(pile, livre_temp);
		}
	}
}
