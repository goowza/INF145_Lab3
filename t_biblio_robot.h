// ========================== MODULE T_BIBLIO_ROBOT ===========================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet d'effectuer plusieurs services relatifs a un robot.
//  Un robot contient une pile de livres offrant un stockage temporaire et 
//  un chariot avec lequel opere le robot.
//
//  Le module permet de :
//	- Initialiser le robot.
//  - Ajouter un livre au stockage du robot.
//	- Placer les livres precedemment stockes par le robot dans le chariot avec
//	  lequel il opere.
//=============================================================================
#pragma once

#ifndef _T_BIBLIO_ROBOT__
#define _T_BIBLIO_ROBOT__

#include "structs.h"
#include "t_pile_livres.h"
#include "t_biblio_chariot.h"

// Cette fonction permet d'initialiser les valeurs d'un robot en lui 
// assignant un chariot deja present dans une bibliotheque
// Le robot n'a pas de pile de livre apres son initialisation.
void initialiser_robot(t_biblio_robot * robot, t_bibliotheque * pBibli);

// Cette fonction reçoit un livre et l'empile si le chariot n'est pas là. 
// Si le chariot se trouve au kiosque, le robot l'ajoute directement au chariot 
// sans l'empiler.
void ajouter_livre_robot(t_biblio_robot * robot, t_livre livre);

// Cette fonction permet de vider la pile de livres du robot dans le chariot si
// celui-ci est present au kiosque. Sinon, la fonction ne fait rien.
void placer_livres_chariot(t_biblio_robot * robot);

#endif
