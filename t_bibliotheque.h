#ifndef _T_BIBLIOTHEQUE__
#define _T_BIBLIOTHEQUE__

#include "structs.h"

// Fonction qui gere le menu et les interactions de l'utilisateur avec celui-ci
void gestion_bibliotheque(t_bibliotheque * bibli);

// Cette fonction permet de saisir le choix entre par l'utilisateur et de
// verifier sa validite.
int demander_choix_menu_bib();

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

// Cette fonction permet de sauvegarder la bibliotheque actuelle dans un
// nouveau fichier texte nomme "sauvegarde_bibliotheque.txt".
void sauvegarder_fichier(t_bibliotheque * pBibli);

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

// Cette fonction permet de compter le nombre de livres de la bibliotheque
// passee en argument.
int compter_livres(t_bibliotheque * pBibli);

// Cette fonction permet d'enlever un saut de ligne d'une chaine de caracteres.
void retirer_sautligne(char * chaine);

// Cette fonction permet de faire une pause apres que l'utilisateur ai fait un
// choix dans le menu.
void super_pause();

// Cette fonction permet d'afficher le menu de la bibliotheque dans la console.
void afficher_menu();

// Cette fonction permet de retirer un livre de la bibliotheque definitivement
void retirer_livre(t_bibliotheque * pBibli);

t_livre * rechercher_livre_isbn(t_bibliotheque * pBibli, int isbn_demande);

#endif
