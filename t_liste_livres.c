#include <stdio.h>
#include <stdlib.h>
#include "t_liste_livres.h"


void init_liste(t_liste * liste)
{
	liste->tete = NULL;
	liste->nb_elements = 0;
}

int liste_vide(t_liste * liste)
{
	return(liste->tete == NULL);
}

void ajouter_debut(t_liste * liste, t_element element)
{
	// pointeur vers l'element a ajouter
	t_noeud * nouveau_noeud = (t_noeud*)malloc(sizeof(t_noeud));

	// mise a jour des liens
	nouveau_noeud->donnee = element;
	nouveau_noeud->suivant = liste->tete;
	liste->tete = nouveau_noeud;

	// mise a jour nombre d'elements total de la liste
	liste->nb_elements++;
}

t_element enlever_debut(t_liste * liste)
{
	// element enleve de la liste
	t_element element_retire;
	// pointeur permettant de free la memoire
	t_noeud * tmp;

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

		return element_retire;
	}
}


// Premier element de la liste = numero 1 (ne commence pas a 0)
// Ajoute le livre juste avant l'element precise par l'indice
void ajouter_liste_indice(t_liste * liste, t_element element, int indice)
{
	int i;
	// pointeur permettent de se placer a l'indice desire
	t_noeud * curseur = liste->tete;
	// pointeur vers l'element a ajouter
	t_noeud * nouveau_noeud = (t_noeud*)malloc(sizeof(t_noeud));

	if (indice <= liste->nb_elements + 1)
	{
		if (!liste_vide(liste))
		{
			if (liste->tete->suivant != NULL && indice > 1)
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
			else
			{
				ajouter_debut(liste, element);
			}
		}
		else
		{
			ajouter_debut(liste, element);
		}
	}
	
}

// enleve l'element a la position precisee par l'indice
t_element enlever_liste_indice(t_liste * liste, int indice)
{
	int i;
	// pointeur permettent de se placer a l'indice desire
	t_noeud * curseur = liste->tete;
	// pointeur positionne juste avant le curseur
	t_noeud * suiveur = curseur;

	// element enleve de la liste
	t_element element_retire;
	// pointeur permettant de free la memoire
	t_noeud * tmp;

	if (indice <= liste->nb_elements)
	{
		if (!liste_vide(liste))
		{
			if (liste->tete->suivant != NULL && indice > 1)
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
			else
			{
				element_retire = enlever_debut(liste);
			}
		}
		return element_retire;
	}
}

void afficher_liste(t_liste * liste)
{
	t_noeud * curseur = liste->tete;
	int compteur = 1;

	if (!liste_vide(liste))
	{
		while (curseur != NULL)
		{
			printf("[#%d : %d]\n", compteur, curseur->donnee.isbn);
			curseur = curseur->suivant;
			compteur++;
		}
	}
}
