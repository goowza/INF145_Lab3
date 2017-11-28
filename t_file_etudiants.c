#include <stdio.h>
#include <stdlib.h>
#include "t_file_etudiants.h"

void init_file(t_file * file)
{
	if (file != NULL)
	{
		file->tete = NULL;
		file->nb_elements = 0;
	}
}

int file_vide(const t_file * file)
{
	return(file->nb_elements == 0);
}

void ajout_debut(t_file * file, t_element element)
{
	t_noeud * nouveau_noeud = (t_noeud*)malloc(sizeof(t_noeud));
	if (nouveau_noeud != NULL)
	{
		nouveau_noeud->donnee = element;
		nouveau_noeud->suivant = file->tete;
		file->tete = nouveau_noeud;
		file->nb_elements++;
	}
}

void enfiler(t_file * file, t_element element)
{
	// pointeur permettant de parcourir la file
	t_noeud * curseur = file->tete;

	// pointeur vers le noeud a ajouter dans la file
	t_noeud * nouveau_noeud = (t_noeud*)malloc(sizeof(t_noeud));
	nouveau_noeud->donnee = element;

	if (nouveau_noeud != NULL)
	{
		if(!file_vide(file))
		{
			// aller a la fin de la liste
			while (curseur->suivant != NULL)
			{
				curseur = curseur->suivant;
			}

			// Mise a jour des liens
			curseur->suivant = nouveau_noeud;
			nouveau_noeud->suivant = NULL;

			// mise a jour du nombre d'elements de la file
			file->nb_elements++;
		}
		else
		{
			ajout_debut(file, element);
		}
	}
}

t_element desenfiler(t_file * file)
{
	t_element element_retire;
	// pointeur permettant de liberer la memoire
	t_noeud * tmp = file->tete;

	if (!file_vide(file))
	{
		element_retire = file->tete->donnee;
		file->tete = file->tete->suivant;
		free(tmp);
		file->nb_elements--;
	}
	else
	{
		element_retire.annee_inscription = INVALIDE;
		element_retire.ID = INVALIDE;
	}
	return element_retire;
}

void afficher_file(t_file * file)
{
	t_noeud * curseur = file->tete;
	int compteur = 1;

	if (!file_vide(file))
	{
		printf("nombre d'elements : %d\n", file->nb_elements);
		while (curseur != NULL)
		{
			printf("[#%d : %d]\n", compteur, curseur->donnee.ID);
			curseur = curseur->suivant;
			compteur++;
		}
	}
}
