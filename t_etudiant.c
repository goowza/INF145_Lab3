#include <stdio.h>
#include <stdlib.h>

#include "t_etudiant.h"

void init_etudiant(t_etudiant * etudiant)
{
	int i;
	t_livre livre_init;
	initialiser_livre(&livre_init);

	etudiant->annee_inscription = INVALIDE;
	etudiant->ID = INVALIDE;

	for (i = 0; i<NB_LIVRES_EMPRUNTES_MAX; i++)
	{
		etudiant->livres_empruntes[i] = livre_init;
	}
}

int emprunter_livre_etudiant(t_etudiant * etudiant, t_livre livre)
{
	int i = 0;
	int resultat;
	// verification du nombre d'emprunt
	if (etudiant->livres_empruntes[NB_LIVRES_EMPRUNTES_MAX - 1].isbn != ISBN_INVALIDE)
	{
		resultat = ECHEC;
		printf("Impossible d'emprunter un nouveau livre : limite atteinte\n");
	}
	else
	{
		while (etudiant->livres_empruntes[i].isbn != ISBN_INVALIDE)
		{
			i++;
		}
		// stockage du livre emprunte dans le tableau de l'etudiant
		etudiant->livres_empruntes[i] = livre;
		resultat = SUCCES;
	}
	return resultat;
}

void afficher_emprunts(t_etudiant etudiant)
{
	int i;
	for (i = 0; i < NB_LIVRES_EMPRUNTES_MAX; i++)
	{
		afficher_info_livre(&etudiant.livres_empruntes[i]);
	}
}

