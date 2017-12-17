
// ================================ STRUCT.H ====================================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//				 
//  Date : decembre 2017
//
// Fichier de definition de toutes les constantes et types utilises dans 
// les modules
// ==============================================================================

#pragma once

#ifndef _STRUCTS__
#define _STRUCTS__

// constantes liees aux livres
#define TAILLE_TITRE	80
#define TAILLE_NOM		30	
#define TAILLE_PRENOM	30

#define MAX_ISBN		9999
#define ISBN_INVALIDE	-1

#define EMPRUNT         1
#define DISPONIBLE      0

// constantes liees a la bibliotheque
#define NB_LIVRES_MAX_RANGEE        5
#define NB_GENRES                   6
#define BIBLIO_FICHIER		    "biblio.txt"
#define BIBLIO_SAUVEGARDE	    "sauvegarde_bibliotheque.txt"
#define FACTEUR_AGRANDISSEMENT		2

// Constantes de gestion du menu de la bibliotheque
#define NUM_CHOIX_MENU_MIN	0
#define NUM_CHOIX_MENU_MAX	6

// Constantes de gestion des menus du kiosque
#define NUM_CHOIX_RECHERCHE_MAX	5
#define NUM_CHOIX_RECHERCHE_MIN	1

#define NUM_CHOIX_SERVIR_MAX	4
#define NUM_CHOIX_SERVIR_MIN	0

// constantes liees aux etudiants
#define NB_LIVRES_EMPRUNTES_MAX			5
#define NUM_LIVRES_EMPRUNTE_MIN			1
#define NUM_LIVRES_EMPRUNTE_MAX			5
#define NUM_ID_MAX						1000000
#define INTERVALLE_ANNEE_INSCRIPTION	18
#define MILLENAIRE						2000

// constantes liees au chariot
#define EMPRUNTER_LIVRE				1
#define NE_PAS_EMPRUNTER_LIVRE		0
#define LIVRE_TROUVE				1

// Constantes de gestion du menu de la simulation
#define NUM_CHOIX_MAX_SIMU			4
#define NUM_CHOIX_MIN_SIMU			0

// General
#define INVALIDE	-1
#define SUCCES		1
#define ECHEC		0

typedef enum { AUCUN = 0, FICTION = 1, HISTOIRE = 2, SCIENCE = 3, ENFANTS = 4, INFORMATIQUE = 5 } t_genre;

typedef enum { POS_KIOSQUE, POS_DEPLACEMENT }t_position_chariot;

//================================= Livre =====================================
// Un livre contient :
//	- un genre 
//	- un nombre de pages
//  - Les noms et prenoms de son auteur
//	- son titre
//	- son numero isbn
//	- un indicateur d'emprunt (vaut soit EMPRUNT, soit DISPONIBLE)
typedef struct
{
	t_genre genre;
	int nb_pages;
	char auteur_prenom[TAILLE_PRENOM];
	char auteur_nom[TAILLE_NOM];
	char titre[TAILLE_TITRE];
	int isbn;
	int bEmprunte; // 
} t_livre;
//=============================================================================

//=============================== Etudiant ====================================
// Un etudiant contient :
//	- un identifiant 
//	- une annee d'inscription
//  - un tableau statique contenant ses emprunts
//	- un nombre de livres empruntes par l'etudiant
typedef struct
{
	int ID;
	int annee_inscription;
	t_livre livres_empruntes[NB_LIVRES_EMPRUNTES_MAX];
	int nb_livres_empruntes;
}t_etudiant;
//=============================================================================

//================================ Liste ======================================
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

//================================ File =======================================
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

//================================ Pile =======================================
typedef t_livre t_element_pile;

typedef struct t_noeud_pile
{
	t_element_pile donnee;
	struct t_noeud_pile * suivant;
}t_noeud_pile;

typedef struct
{
	t_noeud_pile * sommet;
	int nb_elements;
}t_pile;

//=============================================================================

struct biblio;
typedef struct biblio t_bibliotheque;

//=============================== Chariot =====================================
// Un chariot contient :
//	- un pointeur vers une liste de livres dynamique
//	- un pointeur vers l'utilisateur courant du chariot 
//  - une position dans la bibliotheque
//	- un pointeur vers la bibliotheque dans laquelle opere le chariot
typedef struct
{
	t_liste * liste_livres;
	t_etudiant * utilisateur;
	t_position_chariot position;
	t_bibliotheque * pBibli;
}t_biblio_chariot;
//=============================================================================

//================================= Robot =====================================
// Un robot contient :
//	- un pointeur vers un chariot avec lequel opere le robot
//	- un pointeur vers une pile de livres que stock le robot lorsque le chariot
//	  n'est pas disponible
typedef struct
{
	t_biblio_chariot * ptr_chariot;
	t_pile * pile_livres;
}t_biblio_robot;
//=============================================================================

//================================ Kiosque ====================================
// Un kiosque contient :
//	- un pointeur vers la bibliotheque dans laquelle opere le kiosque
//	- un pointeur vers un robot avec lequel opere le kiosque
//	- un pointeur vers un chariot avec lequel opere le kiosque
//	- un pointeur vers l'utilisateur courant du kiosque 
typedef struct
{
	t_bibliotheque * ptr_bibli;
	t_biblio_robot * ptr_robot;
	t_biblio_chariot * ptr_chariot;
	t_etudiant * utilisateur;
}t_biblio_machine;
//=============================================================================

//================================ Rapport ====================================
// Un rapport contient :
//	- le nombre de livres total de la bibliotheque
//	- le nombre de livres empruntes dans la bibliotheque
//	- le nombre de livres presents sur le chariot
typedef struct
{
	int nb_livres;
	int nb_livres_empruntes;
	int nb_livres_chariot;
} t_rapport;
//=============================================================================

//============================= Bibliotheque ==================================
// Une bibliotheque contient :
//	- une taille  qui correspond a la deuxieme dimension du tableau de livres 
//	  dynamique
//	- un tableau de t_livre dynamique
//	- un tableau comptant le nombre de livres par genre
//  - un rapport 
//  - Une machine (kiosque) operant dans la bibliotheque
//	- un robot operant dans la bibliotheque
//  - un chariot operant dans la bibliotheque
//	- un pointeur vers une file d'etudiants dynamique representant la file 
//	  d'attente de la bibliotheque
struct biblio
{
	int taille;
	t_livre ** livres;
	int nb_livres[NB_GENRES];
	t_rapport rapport;

	t_biblio_machine machine;
	t_biblio_robot robot;
	t_biblio_chariot chariot;
	t_file * file_etudiants;
};
//=============================================================================
#endif
