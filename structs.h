#pragma once

#ifndef _STRUCTS__
#define _STRUCTS__

// livre
#define TAILLE_TITRE	80
#define TAILLE_NOM		30	
#define TAILLE_PRENOM	30

// bibliotheque
#define NB_LIVRES_MAX_RANGEE        100
#define NB_GENRES                   6
#define BIBLIO_FICHIER		    "biblio.txt"
#define BIBLIO_SAUVEGARDE	    "sauvegarde_bibliotheque.txt"

#define MAX_ISBN		9999
#define ISBN_INVALIDE	-1
#define SIMULATION      0

#define EMPRUNT         1
#define DISPONIBLE      0

#define NUM_CHOIX_MENU_MIN	0
#define NUM_CHOIX_MENU_MAX	6

// Etudiant
#define NB_LIVRES_EMPRUNTES_MAX		5
#define NUM_LIVRES_EMPRUNTE_MIN		1
#define NUM_LIVRES_EMPRUNTE_MAX		5

// Chariot
#define EMPRUNTER_LIVRE			1
#define NE_PAS_EMPRUNTER_LIVRE	0


// General
#define INVALIDE	-1
#define SUCCES	1
#define ECHEC	0

typedef enum { AUCUN = 0, FICTION = 1, HISTOIRE = 2, SCIENCE = 3, ENFANTS = 4, INFORMATIQUE = 5 } t_genre;

typedef enum {POS_KIOSQUE, POS_DEPLACEMENT}t_position_chariot;

typedef struct
{
	t_genre genre;
	int nb_pages;
	char auteur_prenom[TAILLE_PRENOM];
	char auteur_nom[TAILLE_NOM];
	char titre[TAILLE_TITRE];
	int isbn;
	int bEmprunte; // 1: Le livre a ete emprunte, 0: le livre est disponible.
} t_livre;

typedef struct
{
	int ID;
	int annee_inscription;
	t_livre livres_empruntes[NB_LIVRES_EMPRUNTES_MAX];
}t_etudiant;

//========================= Liste =============================================
//changer cette déclaration pour obtenir des listes d'un autre type
typedef t_livre t_element_liste;

typedef struct t_noeud_liste
{
	t_element_liste donnee;
	struct t_noeud_liste * suivant;
}t_noeud_liste;

typedef struct
{
	t_noeud_liste * tete;
	int nb_elements;
}t_liste;

//=============================================================================

//========================= File ==============================================
//changer cette déclaration pour obtenir des files d'un autre type
typedef t_etudiant t_element_file;

typedef struct t_noeud_file
{
	t_element_file donnee;
	struct t_noeud_file * suivant;
}t_noeud_file;

typedef struct
{
	t_noeud_file * tete;
	int nb_elements;
}t_file;

//=============================================================================

typedef struct
{
	int nb_livres;
	int nb_livres_empruntes;
} t_rapport;

typedef struct
{
	// tableau de t_livre
	t_livre livres[NB_GENRES][NB_LIVRES_MAX_RANGEE];
	int nb_livres[NB_GENRES];
	t_rapport rapport;

	/*t_biblio_machine machine;
	t_biblio_robot robot;
	t_biblio_chariot chariot;
	t_file file_etudiants;*/
	
} t_bibliotheque;

// chariot
typedef struct
{
	t_liste * liste_livres;
	t_etudiant * utilisateur;
	t_position_chariot position;
	t_bibliotheque * pBibli;
}t_biblio_chariot;

// robot
typedef struct
{
	t_biblio_chariot * ptr_chariot;
	t_livre livre_temp;
}t_biblio_robot;

// Kiosque
typedef struct
{
	t_bibliotheque * ptr_bibli;
	t_biblio_robot * ptr_robot;
	t_biblio_chariot * ptr_chariot;
	t_etudiant utilisateur;
}t_biblio_machine;

#endif
