#pragma once

#ifndef _T_BIBLIO_ROBOT__
#define _T_BIBLIO_ROBOT__

#include "structs.h"
#include "t_pile_livres.h"
#include "t_biblio_chariot.h"

void initialiser_robot(t_biblio_robot * robot, t_bibliotheque * pBibli);

void ajouter_livre_robot(t_biblio_robot * robot, t_livre livre);

void placer_livres_chariot(t_biblio_robot * robot);

#endif
