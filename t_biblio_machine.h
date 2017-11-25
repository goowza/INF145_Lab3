#ifndef _T_BIBLIO_MACHINE__
#define _T_BIBLIO_MACHINE__

#include "structs.h"
#include "t_bibliotheque.h"
#include "t_liste_livres.h"

#define NUM_CHOIX_RECHERCHE_MAX	5
#define NUM_CHOIX_RECHERCHE_MIN	1


void servir_etudiant(t_biblio_machine * machine,t_etudiant * etudiant);

void chercher_livre(t_bibliotheque * pBibli);

void afficher_menu_chercher_livre();

int demander_choix_menu_machine();

void afficher_liste_livres(t_liste * liste);

//t_liste * rechercher_isbn(t_bibliotheque * pBibli, int isbn_demande);

#endif

