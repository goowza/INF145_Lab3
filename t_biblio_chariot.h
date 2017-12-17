// ========================= MODULE T_BIBLIO_CHARIOT ==========================
// Auteurs : Paul Meis (MEIP12039708) 
//			(paul.meis.1@ens.etsmtl.ca)
//			 Hervé Neugang (NEUR14027708) 
//			(rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)
//
//  Date : decembre 2017
//
//  Description : 
//  Ce module permet d'effectuer plusieurs services relatifs a un chariot
//  Un chariot contient une liste dynamique de livres representant les livres 
//  stockes temporairement sur celui-ci, ainsi qu'un utilisateur courant, une
//  position (le chariot se deplace dans la bibliotheque) et la bibliotheque
// dans laquelle opere le chariot.
//
//  Le module permet de :
//	- Initialiser le chariot.
//  - Ajouter un livre au chariot, dans l'ordre de numero isbn croissant.
//	- Retirer un livre du chariot en conservant l'ordre de la liste.
//	- Emprumter un livre directement au chariot
//	- Retourner tous les livres du chariot dans la bibliotheque.
//	- Apporter un livre en envoyant le chariot le chercher dans la 
//	  bibliotheque.
//	- Connaitre la position du chariot dans la bibliotheque.
//=============================================================================

#pragma once

#ifndef _T_BIBLIO_CHARIOT__
#define _T_BIBLIO_CHARIOT__

#include "structs.h"
#include "t_liste_livres.h"
#include "t_etudiant.h"
#include "t_bibliotheque.h"

// Cette fonction permet d'initialiser les valeurs d'un chariot en lui 
// assignant une bibliotheque et en le placant au kiosque.
// Le chariot n'a pas de liste ni d'utilisateur apres son initialisation.
void initialiser_chariot(t_biblio_chariot * chariot, t_bibliotheque * pBibli);

// Cette fonction permet d'ajouter un livre dans la liste dynamique du chariot.
int ajouter_livre_chariot(t_biblio_chariot * chariot, t_livre livre);

// Cette fonction permet de retirer un livre de la liste du chariot. La 
// fonction renvoie une copie du livre. Si le livre est introuvable dans le
// chariot, la fonction renvoie un livre initialise.
t_livre retirer_livre_chariot(t_biblio_chariot * chariot, int isbn);

// Cette fonction permet a un utilisateur d'emprunter un livre directement
// depuis le chariot. Si le livre demande par l'utilisateur est present dans
// le chariot, on propose a l'utilisateur de l'emprunter.
void emprunter_livre_chariot(t_biblio_chariot * chariot);

// Cette fonction permet de ramener tous les livres du chariot dans la 
// bibliotheque. Une fois la fonction executee, la liste du chariot est vide.
void retourner_livres(t_biblio_chariot * chariot);

// Cette fonction permet de connaitre la position actuelle du chariot dans la
// bibliotheque.
t_position_chariot get_position(t_biblio_chariot chariot);

// Cette fonction permet d'envoyer le chariot chercher un livre, soit dans sa 
// liste soit dans la bibliotheque si le livre n'est pas dans le chariot.
// La fonction retourne une copie du livre apporte, et retourne un livre
// initialise si le livre n'a pas ete trouve.
t_livre apporter_livre(t_biblio_chariot * chariot, int isbn);

// Cette fonction permet de trouver l'indice d'un livre (precise par son isbn)
// dans la liste dynamique du chariot.
// (renvoie INDICE_INVALIDE si le livre n'est pas dans le chariot)
int chercher_indice_livre(t_biblio_chariot * chariot, int isbn);

// Cette fonction permet d'afficher le menu proposant a l'utilisateur 
// d'emprunter un livre dans le chariot.
void afficher_menu_emprunt();

#endif


