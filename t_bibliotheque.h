// ========================== MODULE T_BIBLIOTHEQUE ===========================
//  Auteur:		Yannick Roy
//
//  Modifié par : Paul Meis (MEIP12039708) 
//				 (paul.meis.1@ens.etsmtl.ca)
//				  Hervé Neugang (NEUR14027708) 
//				 (rodrigue-herve.neugang-tchientche.1@ens.etsmtl.ca)

//  Date : decembre 2017
//
//  Description : 
//  Ce module permet d'effectuer plusieurs services relatifs a une bibliotheque.
//  Une bibliotheque contient un tableau 2D dynamique de livres ainsi qu'un 
//  robot, un chariot, un kiosque et une file d'etudiants.
//
//  Le module permet de :
//	- Initialiser la bibliotheque en creant son tableau de livre, son robot, 
//	  son chariot,...
//  - Gerer la bibliotheque via un menu offrant les services suivants :  
//		1) Afficher Bibliotheque : Affiche tous les livres de la bibliotheque. 
//		2) Lire Fichier Bibliotheque : Initialise la bibliotheque à partir d'un 
//									   fichier texte.
//		3) Modifier Livre : Permet de modifier les informations (champs) 
//							d'un livre. 							  
//		4) Retirer Livre : Permet de retirer un livre de la bibliotheque.
//		5) Generer Rapport : Genere un rapport sur le nombre de livres et 
//							 emprunts. 
//		6) Sauvegarder Bibliotheque : Sauvegarde la bibliotheque dans un fichier 
//									  texte. 
//		7) Quitter : Permet de quitter l'application.
//	- Agrandir l'etagere : doubler la taille de la bibliotheque afin de pouvoir
//	  stocker plus de livres
//	- Servir le premier etudiant de sa file d'attente grace au kiosque 
//	  intelligent de la bibliotheque.
//=============================================================================

#pragma once

#ifndef _T_BIBLIOTHEQUE__
#define _T_BIBLIOTHEQUE__

#include "structs.h"
#include "t_biblio_chariot.h"
#include "t_biblio_machine.h"
#include "t_biblio_robot.h"
#include "t_file_etudiants.h"

// Fonction qui gere le menu et les interactions de l'utilisateur avec celui-ci
void gestion_bibliotheque(t_bibliotheque * bibli);

// Cette fonction permet de saisir le choix entre par l'utilisateur et de
// verifier sa validite.
int demander_choix_menu(int borne_inf, int borne_sup);

// Cette fonction initialise la bibliotheque en mettant tout les compteurs du 
// tableau nb_livres a 0, en remplissant toutes les cases du tableau 2D
// contenant les livres avec des livres initialises par la fonction 
// initialiser_livre et en initialisant le rapport avec la fonction 
// initialiser_rapport.
void initialiser_bibliotheque(t_bibliotheque * pBibli);

// Cette fonction initialise un livre en mettant son genre a "AUCUN", 
// son isbn a -1, son nombre de pages a 0, le nom et prenom de l'auteur
// a "N/A", le titre du livre a "N/A" et son sa disponibilite a "DISPONIBLE".
void initialiser_livre(t_livre * pLivre);

// Cette fonction initialise le rapport en mettant le nombre de livres total et
// le nombre de livres empruntes a 0.
void initialiser_rapport(t_rapport * pRapport);

// Cette fonction permet de remplir le tableau correspondant a la bibliotheque
// a partir d'un fichier texte ou d'une simulation (en fonction de la valeur de
// la constante SIMULATION).
void lire_fichier(t_bibliotheque * pBibli);

// Cette fonction permet d'afficher tout les livres de la bibliotheque passee
// en argument.
void afficher_bibliotheque(t_bibliotheque * pBibli);

// Cette fonction permet d'afficher le rapport passe en argument.
void afficher_rapport(t_rapport *rapport);

// Cette fonction permet de generer et afficher le rapport. Le rapport contient
// le nombre de livres de la bibliotheque passee en argument et le nombre de 
// livres empruntes.
void generer_rapport(t_bibliotheque *pBibli);

// Cette fonction affiche dans la console toutes les informations d'un livre.
void afficher_info_livre(t_livre * pLivre);

// Cette fonction permet de modifier tous les champs d'un livre de la 
// bibliotheque choisi par l'utilisateur sauf son numero isbn.
// Les informations sont entrees par l'utilisateur.
void modifier_livre(t_bibliotheque * pBibli);

// Cette fonction permet de faire une pause apres que l'utilisateur ai fait un
// choix dans le menu.
void super_pause();

// Cette fonction permet de chercher un livre dont on connait le numero isbn
// dans la bibliotheque.
t_livre * rechercher_livre_isbn(t_bibliotheque * pBibli, int isbn_demande);

// Cette fonction change la valeur du bemprunte du livre a EMPRUNT 
// dans la bibliotheque
void emprunter_livre_biblio(t_bibliotheque * pBibli, int isbn);

// Cette fonction change la valeur du bemprunte du livre a DISPONIBLE 
// dans la bibliotheque
void rendre_livre_biblio(t_bibliotheque * pBibli, int isbn);

// Cette fonction permet de doubler la taille de la deuxieme dimension de 
// la bibliotheque. Les nouveaux emplacement sont remplis avec des livres
// initialises.
void agrandir_etagere(t_bibliotheque * pBibli);

// Cette fonction permet d'ajouter un etudiant dans la file de la bibliotheque.
void ajouter_etudiant_file(t_bibliotheque * pBibli, t_etudiant etudiant);

// Cette fonction permet de servir le premier etudiant de la file d'attente.
// L'etudiant est retire de la file d'attente.
void servir_etudiant(t_bibliotheque * pBibli);


// Cette fonction permet d'ajouter un livre dans la bibliotheque en renseignant
// les valeurs des champs manuellement.
void ajouter_livre(t_bibliotheque * pBibli);

// Cette fonction permet d'enlever un saut de ligne d'une chaine de caracteres.
void retirer_sautligne(char * chaine);

#endif


