#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "t_biblio_robot.h"

void initialiser_robot(t_biblio_robot * robot, t_bibliotheque * pBibli)
{
	t_livre livre_temp;
	initialiser_livre(&livre_temp);

	robot->livre_temp = livre_temp;
	robot->ptr_chariot = &pBibli->chariot;
	robot->pile_livres = NULL;
}

void ajouter_livre_robot(t_biblio_robot * robot, t_livre livre)
{
	if (robot->ptr_chariot->position == POS_KIOSQUE)
	{
		//ajouter sur chariot
		ajouter_livre_chariot(robot->ptr_chariot, livre);
	}
	else
	{
		// ajouter livre dans la pile retour
		push(robot->pile_livres, livre);
	}
}

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
