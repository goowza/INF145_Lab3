#pragma once

#ifndef _T_BIBLIO_CHARIOT__
#define _T_BIBLIO_CHARIOT__

#include "structs.h"
#include "t_liste_livres.h"
#include "t_etudiant.h"
#include "t_bibliotheque.h"

// fonctions publiques
int ajouter_livre_chariot(t_biblio_chariot * chariot, t_livre livre);

t_livre retirer_livre_chariot(t_biblio_chariot * chariot, int isbn);

void emprunter_livre_chariot(t_biblio_chariot * chariot);

void retourner_livres(t_biblio_chariot * chariot);

t_position_chariot get_position(t_biblio_chariot chariot);

t_livre apporter_livre(t_biblio_chariot * chariot, int isbn);

// fonctions privees
void initialiser_chariot(t_biblio_chariot * chariot, t_bibliotheque * pBibli);

int chercher_indice_livre(t_biblio_chariot * chariot, int isbn);

#endif
