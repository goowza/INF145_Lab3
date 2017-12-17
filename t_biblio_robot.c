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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "t_biblio_robot.h"

//-----------------------------------------------------------------------------
//							Fonction initialiser_robot
// Cette fonction permet d'initialiser les valeurs d'un robot en lui 
// assignant un chariot deja present dans une bibliotheque
// Le robot n'a pas de pile de livre apres son initialisation.
//
// Parametres : robot = robot a initialiser
//				pBibli = pointeur vers la bibliotheque ou se trouve le chariot
//						 a assigner au robot
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_robot(t_biblio_robot * robot, t_bibliotheque * pBibli)
{
	robot->ptr_chariot = &pBibli->chariot;
	robot->pile_livres = NULL;
}

//-----------------------------------------------------------------------------
//							Fonction ajouter_livre_robot
// Cette fonction reçoit un livre et l'empile si le chariot n'est pas là. 
// Si le chariot se trouve au kiosque, le robot l'ajoute directement au chariot 
// sans l'empiler.
// 
// Parametres : robot = robot effectuant la tache
//				livre = livre donne au robot
// Retour :		aucun
//-----------------------------------------------------------------------------
void ajouter_livre_robot(t_biblio_robot * robot, t_livre livre)
{
	if (robot->ptr_chariot->position == POS_KIOSQUE)
	{
		// ajouter sur chariot
		ajouter_livre_chariot(robot->ptr_chariot, livre);
	}
	else
	{
		// ajouter livre dans la pile retour
		push(robot->pile_livres, livre);
	}
}

//-----------------------------------------------------------------------------
//							Fonction placer_livres_chariot
// Cette fonction permet de vider la pile de livres du robot dans le chariot si
// celui-ci est present au kiosque. Sinon, la fonction ne fait rien.
// 
// Parametres : robot = robot effectuant la tache
// Retour :		aucun
//-----------------------------------------------------------------------------
void placer_livres_chariot(t_biblio_robot * robot)
{
	t_livre livre_temp;
	if (robot->ptr_chariot->position == POS_KIOSQUE)
	{
		while (!pile_vide(robot->pile_livres))
		{
			livre_temp = pop(robot->pile_livres);
			ajouter_livre_chariot(robot->ptr_chariot, livre_temp);
		}
	}
}
