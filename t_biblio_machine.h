// ========================= MODULE T_BIBLIO_MACHINE ==========================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet d'effectuer plusieurs services relatifs a un kiosque.
//  Un kiosque contient la bibliotheque dans laquelle opere le chariot, le
//  robot et le chariot avec lesquels opere le kiosque et l'utilisateur 
//  courant du kiosque.
//
//  Le module permet de :
//	- Initialiser le kiosque.
//  - Servir l'utilisateur du kiosque en lui proposant differents services :
//		1) Chercher un livre dans la bibliotheque et afficher les resultats.
//		2) Retourner un des livres emprunte par l'utilisateur.
//		3) Apporter un livre a l'utilisateur sans passer par la recherche.
//		4) Voir le dossier de l'utilisateur.
//=============================================================================

#pragma once

#ifndef _T_BIBLIO_MACHINE__
#define _T_BIBLIO_MACHINE__

#include "structs.h"
#include "t_bibliotheque.h"
#include "t_liste_livres.h"
#include "t_biblio_chariot.h"
#include "t_etudiant.h"

// Cette fonction permet d'initialiser les valeurs d'un kiosque en lui 
// assignant une bibliotheque, le chariot et le robot de cette bibliotheque.
// Le kiosque n'a pas d'utilisateur apres son initialisation.
void initialiser_machine(t_biblio_machine * machine, t_bibliotheque * pBibli);

// Cette fonction permet de servir l'utilisateur courant du kiosque. Le kiosque
// propose plusieurs services a l'etudiant via un menu.
void servir_etudiant_machine(t_biblio_machine * machine, t_etudiant * etudiant);

// Cette fonction permet de chercher un livre dans la base de donnee de la
// bibliotheque ou fonctionne la machine. On peut effectuer une recherche par 
// numero isbn, par genre, par titre, par nom ou prenom d'auteur. 
// La fonction affiche tous les resultats et propose a l'etudiant d'emprunter 
// le livre.
void chercher_livre(t_biblio_machine * machine);

// Cette fonction permet de rendre un livre precedemment emprunte par 
// l'utilisateur de la machine. La fonction affiche les emprunts de l'etudiant
// et celui-ci choisit le livre qu'il desire rendre.
void retourner_livre(t_biblio_machine * machine);

// Cette fonction affiche le dossier de l'étudiant, soit les informations 
// generales et les livres empruntes.
void voir_dossier(t_biblio_machine machine);

// Cette fonction reçoit le ISBN du livre a apporter et envoie le chariot 
// chercher ce livre.
// La fonction retourne 1 si le chariot a trouvé le livre et l'a remis à l'étudiant
// ou 0 si le chariot n'a pas pu remettre le livre à l'étudiant.
int apporter_livre_machine(t_biblio_machine * machine, int isbn);

// Cette fonction demande a l'utilisateur d'entrer un numero isbn et retourne
// la valeur entree si elle est valide.
int demander_isbn();

#endif
