#ifndef _T_FILE_ETUDIANTS__
#define _T_FILE_ETUDIANTS__

#include "structs.h"

typedef t_etudiant t_element;

typedef struct t_noeud
{
	t_element donnee;
	struct t_noeud * suivant;
}t_noeud;

typedef struct
{
	t_noeud * tete;
	int nb_elements;
}t_file;

void init_file(t_file * file);

int file_vide(const t_file * file);

void ajout_debut(t_file * file, t_element element);

void enfiler(t_file * file, t_element element);

t_element desenfiler(t_file * file);

void afficher_file(t_file * file);

#endif

