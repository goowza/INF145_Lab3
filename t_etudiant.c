// ========================== MODULE T_ETUDIANT ===========================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet d'effectuer plusieurs services relatifs a un etudiant.
//  Un etudiant contient un identifiant personnel, une annee d'inscription
//  et un tableau de livres empruntes par l'etudiant.
//
//  Le module permet de :
//	- Initialiser l'etudiant.
//  - Emprunter un livre (met a jour les emprunts de l'etudiant)
//	- Afficher les emprunts de l'etudiant.
//	- Generer un etudiant aleatoire pour effectuer les tests.
//	- Afficher les informations relatives a un etudiant.
//=============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "t_etudiant.h"

//-----------------------------------------------------------------------------
//							Fonction init_etudiant
// Cette fonction permet d'initialiser les valeurs d'un etudiant en mettant
// son annee d'inscription et son identifiant a INVALIDE, en mettant son
// nombre d'emprunt a 0 et en remplissant son tableau d'emprunts avec des 
// livres initialises 
//
// Parametres : etudiant = etudiant a initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void init_etudiant(t_etudiant * etudiant)
{
	int i;
	t_livre livre_init;
	initialiser_livre(&livre_init);

	etudiant->annee_inscription = INVALIDE;
	etudiant->ID = INVALIDE;
	etudiant->nb_livres_empruntes = 0;

	for (i = 0; i<NB_LIVRES_EMPRUNTES_MAX; i++)
	{
		etudiant->livres_empruntes[i] = livre_init;
	}
}


//-----------------------------------------------------------------------------
//							Fonction emprunter_livre_etudiant
// Cette fonction permet de mettre a jour les emprunts d'un etudiant qui vient
// d'emprunter un livre. Si l'etudiant a deja emprunte le nombre maximum de
// livres (NB_LIVRES_EMPRUNTES_MAX), la fonction renvoie ECHEC. Sinon, la 
// fonction renvoie SUCCES
//
// Parametres : etudiant = etudiant empruntant le livre
//				livre = livre emprunte par l'etudiant
// Retour :		resultat = resultat de l'execution de la fonction
//-----------------------------------------------------------------------------
int emprunter_livre_etudiant(t_etudiant * etudiant, t_livre livre)
{
	int i = 0;
	int resultat;
	// verification du nombre d'emprunt
	if (etudiant->nb_livres_empruntes == NB_LIVRES_EMPRUNTES_MAX)
	{
		resultat = ECHEC;
		printf("Impossible d'emprunter un nouveau livre : limite atteinte\n");
	}
	else
	{
		// stockage du livre emprunte dans le tableau de l'etudiant
		etudiant->livres_empruntes[etudiant->nb_livres_empruntes] = livre;
		etudiant->livres_empruntes[etudiant->nb_livres_empruntes].bEmprunte = EMPRUNT;
		etudiant->nb_livres_empruntes++;
		resultat = SUCCES;
	}
	return resultat;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_emprunts
// Cette fonction permet d'afficher les livres empruntes par l'etudiant.
//
// Parametres : etudiant = etudiant dont on veut afficher les emprunts
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_emprunts(t_etudiant etudiant)
{
	int i;
	for (i = 0; i < NB_LIVRES_EMPRUNTES_MAX; i++)
	{
		if (etudiant.livres_empruntes[i].isbn != ISBN_INVALIDE)
			afficher_info_livre(&etudiant.livres_empruntes[i]);
	}
}

//-----------------------------------------------------------------------------
//							Fonction generer_etudiant_aleatoire
// Cette fonction genere un identifiant et une annee d'inscription aleatoires
// a stocker dans l'etudiant passe en parametre.
// 
// Parametres : etudiant = etudiant genere
// Retour :		aucun
//-----------------------------------------------------------------------------
void generer_etudiant_aleatoire(t_etudiant * etudiant)
{
	long ID;
	int annee_inscription;

	init_etudiant(etudiant);

	// On genere un nombre aleatoire entre 1 et NUM_ID_MAX + 1
	ID = (rand()*rand()) % NUM_ID_MAX + 1;

	// On genere une annee d'inscription entre MILLENAIRE et 
	// INTERVALLE_ANNEE_INSCRIPTION + MILLENAIRE
	annee_inscription = rand() % INTERVALLE_ANNEE_INSCRIPTION + MILLENAIRE;

	// stocker les valeurs generees dans l'etudiant
	etudiant->annee_inscription = annee_inscription;
	etudiant->ID = ID;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_infos_etudiant
// Cette fonction affiche les infos d'un etudiant comme son identifiant, annee
// d'inscription et nombre d'emprunts.
// 
// Parametres : etudiant = etudiant a afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_infos_etudiant(t_etudiant etudiant)
{
	printf("------------------------------------\n");
	printf("ID : %d\n", etudiant.ID);
	printf("Annee inscription : %d\n", etudiant.annee_inscription);
	printf("Nombre d'emprunts : %d\n", etudiant.nb_livres_empruntes);
	printf("------------------------------------\n");
}
