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

#pragma once

#include "structs.h"
#include "t_bibliotheque.h"

#ifndef _T_ETUDIANT__
#define _T_ETUDIANT__

// Cette fonction permet d'initialiser les valeurs d'un etudiant en mettant
// son annee d'inscription et son identifiant a INVALIDE, en mettant son
// nombre d'emprunt a 0 et en remplissant son tableau d'emprunts avec des 
// livres initialises 
void init_etudiant(t_etudiant * etudiant);

// Cette fonction permet de mettre a jour les emprunts d'un etudiant qui vient
// d'emprunter un livre. Si l'etudiant a deja emprunte le nombre maximum de
// livres (NB_LIVRES_EMPRUNTES_MAX), la fonction renvoie ECHEC. Sinon, la 
// fonction renvoie SUCCES
int emprunter_livre_etudiant(t_etudiant * etudiant, t_livre livre);

// Cette fonction permet d'afficher les livres empruntes par l'etudiant.
void afficher_emprunts(t_etudiant etudiant);

// Cette fonction genere un identifiant et une annee d'inscription aleatoires
// a stocker dans l'etudiant passe en parametre.
void generer_etudiant_aleatoire(t_etudiant * etudiant);

// Cette fonction affiche les infos d'un etudiant comme son identifiant, annee
// d'inscription et nombre d'emprunts.
void afficher_infos_etudiant(t_etudiant etudiant);

#endif

