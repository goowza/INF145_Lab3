// ========================= MODULE T_FILE_ETUDIANT ===========================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet de gerer une file d'etudiants via differentes fonctions.
//
//  Le module permet de :
//	- Initialiser une file d'etudiants
//  - Tester si une file est vide
//	- Ajouter un etudiant a la file
//	- Enlever un etudiant de la file
//	- Afficher la file.
//  Attention : ce module gere uniquement des files de t_etudiants.
//=============================================================================

#pragma once

#ifndef _T_FILE_ETUDIANTS__
#define _T_FILE_ETUDIANTS__

#include "structs.h"
#include "t_etudiant.h"

// Cette fonction permet d'initialiser une file, la file est vide et sa tete
// pointe vers NULL.
void init_file(t_file * file);

// Cette fonction renvoie si une file est vide ou non. 
// (La fonction renvoie 0 si la file n'est pas vide)
int file_vide(const t_file * file);

// Cette fonction ajoute un element au debut de la file
void enfiler(t_file * file, t_element_file element);

// Cette fonction ajoute un element a la fin de la file
t_element_file desenfiler(t_file * file);

// Cette fonction enleve un element au debut de la file (le premier arrive dans
// la file).
void afficher_file(t_file * file);

#endif


