#pragma once

#include "structs.h"
#include "t_bibliotheque.h"

#ifndef _T_ETUDIANT__
#define _T_ETUDIANT__

void init_etudiant(t_etudiant * etudiant);

void emprunter_livre_etudiant(t_etudiant * etudiant, t_livre livre);

void afficher_emprunts(t_etudiant etudiant);
#endif
