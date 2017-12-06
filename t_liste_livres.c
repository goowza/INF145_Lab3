#include <stdio.h>
#include <stdlib.h>
#include "t_liste_livres.h"


void init_liste(t_liste * liste)
{
	if (liste != NULL)
	{
		liste->tete = NULL;
		liste->nb_elements = 0;
	}
}

int liste_vide(t_liste * liste)
{
	return(liste->nb_elements == 0);
}

int ajouter_debut(t_liste * liste, t_element_liste element)
{
	int resultat;

	// pointeur vers l'element a ajouter
	t_noeud_liste * nouveau_noeud = (t_noeud_liste*)malloc(sizeof(t_noeud_liste));

	// Test du malloc (si le malloc n'a pas ete correctement execute, 
	// la fonction ne fait rien
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

int ajouter_fin(t_liste * liste, t_element_liste element)
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

t_element_liste enlever_debut(t_liste * liste)
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

t_element_liste enlever_fin(t_liste * liste)
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


// Premier element de la liste = numero 1 (ne commence pas a 0)
// Ajoute le livre juste avant l'element precise par l'indice
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
			if (indice == 1)
			{
				ajouter_debut(liste, element);
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
				ajouter_fin(liste, element);
			}
		}
		else
		{
			ajouter_debut(liste, element);
		}
		resultat = SUCCES;
	}
	else
	{
		resultat = ECHEC;
	}
	return resultat;
}

// enleve l'element a la position precisee par l'indice
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
				element_retire = enlever_debut(liste);
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
				element_retire = enlever_fin(liste);
			}
		}
	}
	return element_retire;
}

//int ajouter_croissant(t_liste * liste, t_element_liste element)
//{
//	int resultat;
//	t_noeud_liste * curseur = liste->tete;
//	int indice = 1;
//	while (curseur->suivant->donnee.isbn < element.isbn)
//	{
//		curseur = curseur->suivant;
//		indice++;
//	}
//	resultat = ajouter_liste_indice(liste, element, indice);
//	return resultat;
//}

void afficher_liste(t_liste liste)
{
	t_noeud_liste * curseur = liste.tete;
	int compteur = 1;

	if (!liste_vide(&liste))
	{
		while (curseur != NULL)
		{
			afficher_info_livre(&curseur->donnee);
			//printf("[#%d : %d]\n", compteur, curseur->donnee.isbn);
			//printf("[#%d : %d]\n", compteur,curseur->donnee);
			curseur = curseur->suivant;
			compteur++;
		}
	}
}
