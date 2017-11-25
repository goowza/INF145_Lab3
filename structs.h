#ifndef _STRUCTS__
#define _STRUCTS__

#define TAILLE_TITRE	80
#define TAILLE_NOM		30	
#define TAILLE_PRENOM	30

typedef enum { AUCUN = 0, FICTION = 1, HISTOIRE = 2, SCIENCE = 3, ENFANTS = 4, INFORMATIQUE = 5 } t_genre;

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
	int nb_livres_empruntes;
}t_etudiant;

typedef struct
{
	int gneeee;
	//t_liste liste_livres;
}t_biblio_chariot;

typedef struct
{
	t_biblio_chariot * ptr_chariot;
}t_biblio_robot;

typedef struct
{
	t_biblio_robot * ptr_robot;
	t_biblio_chariot * ptr_chariot;
}t_biblio_machine;





#endif

