#pragma once

#ifndef _T_BIBLIO_MACHINE__
#define _T_BIBLIO_MACHINE__

#include "structs.h"
#include "t_bibliotheque.h"
#include "t_liste_livres.h"

#define NUM_CHOIX_RECHERCHE_MAX	5
#define NUM_CHOIX_RECHERCHE_MIN	1

#define NUM_CHOIX_SERVIR_MAX	4
#define NUM_CHOIX_SERVIR_MIN	0


void servir_etudiant(t_biblio_machine * machine, t_etudiant * etudiant);

void chercher_livre(t_biblio_machine * machine);

void retourner_livre(t_biblio_machine * machine);

void afficher_menu_servir(t_etudiant * etudiant);

void afficher_menu_chercher_livre();

void afficher_menu_retourner_livre(t_etudiant etudiant);

int demander_choix(int borne_inf, int borne_sup);

void afficher_liste_livres(t_liste * liste);

//t_liste * rechercher_isbn(t_bibliotheque * pBibli, int isbn_demande);

#endif
