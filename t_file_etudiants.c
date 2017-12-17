// ========================= MODULE T_FILE_ETUDIANT ===========================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet de gerer une file d'etudiants via differentes fonctions.
//
//  Le module permet de :
//	- Initialiser une file d'etudiants
//  - Tester si une file est vide
//	- Ajouter un etudiant a la file
//	- Enlever un etudiant de la file
//	- Afficher la file.
//  Attention : ce module gere uniquement des files de t_etudiants.
//=============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "t_file_etudiants.h"

// ==================== Declaration des fonctions privees =====================

// Cette fonction ajoute un element au debut de la file
void ajout_debut_file(t_file * file, t_element_file element);

// ============================================================================

//-----------------------------------------------------------------------------
//							Fonction init_file
// Cette fonction permet d'initialiser une file, la file est vide et sa tete
// pointe vers NULL.
//
// Parametres : file = la file a initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void init_file(t_file * file)
{
	if (file != NULL)
	{
		file->tete = NULL;
		file->nb_elements = 0;
	}
}

//-----------------------------------------------------------------------------
//							Fonction file_vide
// Cette fonction renvoie si une file est vide ou non. 
// (La fonction renvoie 0 si la file n'est pas vide)
//
// Parametres : file = la file a tester
// Retour :		resultat du test
//-----------------------------------------------------------------------------
int file_vide(const t_file * file)
{
	return(file->nb_elements == 0);
}

//-----------------------------------------------------------------------------
//							Fonction ajout_debut_file
// Cette fonction ajoute un element au debut de la file
//
// Parametres : file = la file ou ajouter l'element
//				element = element a ajouter a la file
// Retour :		aucun
//-----------------------------------------------------------------------------
void ajout_debut_file(t_file * file, t_element_file element)
{
	t_noeud_file * nouveau_noeud = (t_noeud_file*)malloc(sizeof(t_noeud_file));
	// Test du malloc (si le malloc n'a pas ete correctement execute, 
	// la fonction ne fait rien)
	if (nouveau_noeud != NULL)
	{
		nouveau_noeud->donnee = element;
		nouveau_noeud->suivant = file->tete;
		file->tete = nouveau_noeud;
		file->nb_elements++;
	}
}

//-----------------------------------------------------------------------------
//							Fonction enfiler
// Cette fonction ajoute un element a la fin de la file
//
// Parametres : file = la file ou ajouter l'element
//				element = element a ajouter a la file
// Retour :		aucun
//-----------------------------------------------------------------------------
void enfiler(t_file * file, t_element_file element)
{
	// pointeur permettant de parcourir la file
	t_noeud_file * curseur = file->tete;

	// pointeur vers le noeud a ajouter dans la file
	t_noeud_file * nouveau_noeud = (t_noeud_file*)malloc(sizeof(t_noeud_file));
	nouveau_noeud->donnee = element;

	if (nouveau_noeud != NULL)
	{
		if (!file_vide(file))
		{
			// aller a la fin de la file
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
			ajout_debut_file(file, element);
		}
	}
}

//-----------------------------------------------------------------------------
//							Fonction desenfiler
// Cette fonction enleve un element au debut de la file (le premier arrive dans
// la file). Si le file est vide, on retourne un etudiant initialise.
//
// Parametres : file = la file ou enlever l'element
// Retour :		element_retire = copie de l'element enleve de la file
//-----------------------------------------------------------------------------
t_element_file desenfiler(t_file * file)
{
	t_element_file element_retire;
	init_etudiant(&element_retire);

	// pointeur permettant de liberer la memoire
	t_noeud_file * tmp = file->tete;

	if (!file_vide(file))
	{
		element_retire = file->tete->donnee;
		file->tete = file->tete->suivant;
		free(tmp);
		file->nb_elements--;
	}
	return element_retire;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_file
// Cette fonction affiche tous les elements d'une file dans l'ordre de sortie
// (soit premier arrive premier sorti).
//
// Parametres : file = la file a afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_file(t_file * file)
{
	t_noeud_file * curseur = file->tete;
	int compteur = 1;

	if (!file_vide(file))
	{
		printf("nombre d'elements : %d\n", file->nb_elements);
		while (curseur != NULL)
		{
			afficher_infos_etudiant(curseur->donnee);
			curseur = curseur->suivant;
			compteur++;
		}
	}
}
