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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "t_bibliotheque.h"

// ==================== Declaration des fonctions privees =====================

// Cette fonction permet de sauvegarder la bibliotheque actuelle dans un
// nouveau fichier texte nomme "sauvegarde_bibliotheque.txt".
void sauvegarder_fichier(t_bibliotheque * pBibli);

// Cette fonction permet de compter le nombre de livres de la bibliotheque
// passee en argument.
int compter_livres(t_bibliotheque * pBibli);

// Cette fonction permet d'afficher le menu de la bibliotheque dans la console.
void afficher_menu();

// Cette fonction permet de retirer un livre de la bibliotheque definitivement
void retirer_livre(t_bibliotheque * pBibli);

//=============================================================================

//-----------------------------------------------------------------------------
//							Fonction gestion_bibliotheque
// Cette fonction permet de gerer le fonctionnement d'un menu qui offre
// differents services a l'utilisateur afin de gerer la bibliotheque.
//
// Parametres : pBibli = pointeur vers la bibliotheque a gerer
// Retour :		aucun
//-----------------------------------------------------------------------------
void gestion_bibliotheque(t_bibliotheque * bibli)
{
	// Déclaration des variables.
	int choix_menu;

	// Initialisation de la fonction rand()
	srand(time(NULL));

	do
	{
		afficher_menu();

		// Gestion du menu.
		choix_menu = demander_choix_menu(NUM_CHOIX_MENU_MIN, NUM_CHOIX_MENU_MAX);

		switch (choix_menu)
		{
		case 1: afficher_bibliotheque(bibli); break;
		case 2: lire_fichier(bibli); break;
		case 3: modifier_livre(bibli); break;
		case 4: retirer_livre(bibli); break;
		case 5: generer_rapport(bibli);
			afficher_rapport(&bibli->rapport);
			break;
		case 6: sauvegarder_fichier(bibli); break;
		case 0: break; // Quitter.
		default: break;
		}

		super_pause();
		system("cls");

	} while (choix_menu != 0);
}

//-----------------------------------------------------------------------------
//							Fonction lire_fichier
// Cette fonction permet de remplir le tableau correspondant a la bibliotheque
// a partir d'un fichier texte ou d'une simulation (en focntion de la valeur de
// la constante SIMULATION)
//
// Parametres : pBibli = pointeur vers le tableau de t_bibliotheque a remplir
// Retour :		aucun
//-----------------------------------------------------------------------------
void lire_fichier(t_bibliotheque * pBibli)
{
	FILE *fentree;

	// Variables permettant d'enregistrer un livre
	int nb_livres;
	t_genre genre;
	char titre[TAILLE_TITRE];
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	int nb_pages;
	int isbn;
	int emprunt;

	int i;

	// Variable permettant de sauter les lignes vides et les sauts de ligne
	// lors de l'utilisation de fgets et fscanf
	char buffer;

	// Remplissage de la bibliotheque a partir d'un fichier texte
	fentree = fopen(BIBLIO_FICHIER, "rt");
	if (fentree == NULL)
	{
		printf("Erreur a l'ouverture du fichier\n");
		super_pause();
	}
	else
	{
		fscanf(fentree, "%d", &nb_livres);
		fscanf(fentree, "%c", &buffer);

		for (i = 0; i<nb_livres; i++)
		{
			// Enregistrement des valeurs du fichier texte dans les variables
			fscanf(fentree, "%d", &genre);
			fscanf(fentree, "%c", &buffer);
			fgets(titre, TAILLE_TITRE, fentree);
			fgets(prenom, TAILLE_PRENOM, fentree);
			fgets(nom, TAILLE_NOM, fentree);
			fscanf(fentree, "%d", &nb_pages);
			fscanf(fentree, "%d", &isbn);
			fscanf(fentree, "%d", &emprunt);

			// Enlever les sauts de lignes en trop a la fin des chaines
			retirer_sautligne(titre);
			retirer_sautligne(prenom);
			retirer_sautligne(nom);

		
			// Si l'etagere est remplie, on double sa taille avant d'ajouter 
			// un livre
			if (pBibli->nb_livres[genre] == pBibli->taille)
			{
				agrandir_etagere(pBibli);
			}

			// Mise a jour d'un livre de la bibliotheque
			pBibli->livres[genre][pBibli->nb_livres[genre]].genre = genre;
			strcpy(pBibli->livres[genre][pBibli->nb_livres[genre]].titre, titre);
			strcpy(pBibli->livres[genre][pBibli->nb_livres[genre]].auteur_prenom, prenom);
			strcpy(pBibli->livres[genre][pBibli->nb_livres[genre]].auteur_nom, nom);
			pBibli->livres[genre][pBibli->nb_livres[genre]].nb_pages = nb_pages;
			pBibli->livres[genre][pBibli->nb_livres[genre]].isbn = isbn;
			pBibli->livres[genre][pBibli->nb_livres[genre]].bEmprunte = emprunt;
			pBibli->nb_livres[genre]++;

		}
		printf("Livres charges\n");
		fclose(fentree);
	}
}

//-----------------------------------------------------------------------------
//							Fonction super_pause
// Cette fonction permet de faire une pause apres que l'utilisateur ai fait un
// choix dans le menu.
//
// Parametres : aucun
// Retour :		aucun
//-----------------------------------------------------------------------------
void super_pause()
{
	printf("Appuyez sur une touche pour continuer! \n");
	_getch();
}

//-----------------------------------------------------------------------------
//							Fonction retirer_sautligne
// Cette fonction permet d'enlever un saut de ligne d'une chaine de caracteres
//
// Parametres : chaine = pointeur vers la chaine dans laquelle on enleve le saut 
// Retour :		aucun
//-----------------------------------------------------------------------------
void retirer_sautligne(char * chaine)
{
	int pos = strlen(chaine) - 1;
	if (chaine != NULL && chaine[pos] == '\n')
		chaine[pos] = '\0'; // Si on trouve \n à la fin, on le remplace par \0
}

//-----------------------------------------------------------------------------
//							Fonction Initialiser_bibliotheque
// Cette fonction initialise la bibliotheque en mettant tout les compteurs du 
// tableau nb_livres a 0, en generant le tableau de livres et en remplissant 
// toutes ses case avec des livres initialises par la fonction 
// initialiser_livre et en initialisant le rapport avec la fonction 
// initialiser_rapport
//
// Parametres : pBibli = pointeur vers le t_bibliotheque que l'on veut initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_bibliotheque(t_bibliotheque * pBibli)
{
	t_biblio_chariot chariot;
	t_biblio_robot robot;
	t_biblio_machine machine;

	int i, j;

	pBibli->taille = NB_LIVRES_MAX_RANGEE;

	// Initialisation des compteurs de livres a 0
	for (i = 0; i < NB_GENRES; i++)
	{
		pBibli->nb_livres[i] = 0;
	}

	pBibli->livres = (t_livre**)malloc(NB_GENRES * sizeof(t_livre*));

	// Test de fonctionnement du malloc
	if (pBibli->livres != NULL)
	{
		// Remplir tableau livres
		for (i = 0; i < NB_GENRES; i++)
		{
			pBibli->livres[i] = (t_livre*)malloc(NB_LIVRES_MAX_RANGEE * sizeof(t_livre));

			// Test de fonctionnement du malloc
			if (pBibli->livres[i] != NULL)
			{
				for (j = 0; j < NB_LIVRES_MAX_RANGEE; j++)
				{
					initialiser_livre(&pBibli->livres[i][j]);
				}
			}
		}
	}

	// Initialiser le rapport a 0
	initialiser_rapport(&(pBibli->rapport));

	// initialiser le chariot
	initialiser_chariot(&chariot, pBibli);
	pBibli->chariot = chariot;

	// initialiser le robot
	initialiser_robot(&robot, pBibli);
	pBibli->robot = robot;

	// initialiser la machine
	initialiser_machine(&machine, pBibli);
	pBibli->machine = machine;
}

//-----------------------------------------------------------------------------
//							Fonction demander_choix_menu
// Cette fonction permet de saisir le choix entre par l'utilisateur et de
// verifier sa validite.
//
// Parametres : borne_inf : borne inferieure de l'intervalle dans lequel se
//							trouve le choix
//				borne_sup : borne superieure de l'intervalle dans lequel se
//							trouve le choix
// Retour :		choix = valeur entree par l'utilisateur
//-----------------------------------------------------------------------------
int demander_choix_menu(int borne_inf, int borne_sup)
{
	int choix;
	do
	{
		scanf("%d", &choix);
	} while (choix > borne_sup || choix < borne_inf);

	return choix;
}

//-----------------------------------------------------------------------------
//							Fonction Initialiser_livre
// Cette fonction initialise un livre en mettant son genre a "AUCUN", 
// son isbn a -1, son nombre de pages a 0, le nom et prenom de l'auteur
// a "N/A", le titre du livre a "N/A" et son sa disponibilite a "DISPONIBLE"
//
// Parametres : pLivre = pointeur vers le t_livre que l'on veut initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_livre(t_livre * pLivre)
{
	pLivre->genre = AUCUN;
	pLivre->isbn = ISBN_INVALIDE;
	pLivre->nb_pages = 0;
	strcpy(pLivre->auteur_nom, "N/A");
	strcpy(pLivre->auteur_prenom, "N/A");
	strcpy(pLivre->titre, "N/A");
	pLivre->bEmprunte = DISPONIBLE;
}

//-----------------------------------------------------------------------------
//							Fonction Initialiser_rapport
// Cette fonction initialise le rapport en mettant le nombre de livres total,
// le nombre de livres empruntes a 0 et le nombre de livres sur le chariot a 0.
//
// Parametres : pRapport = pointeur vers le t_rapport que l'on veut initialiser
// Retour :		aucun
//-----------------------------------------------------------------------------
void initialiser_rapport(t_rapport * pRapport)
{
	pRapport->nb_livres = 0;
	pRapport->nb_livres_empruntes = 0;
	pRapport->nb_livres_chariot = 0;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_info_livre
// Cette fonction affiche dans la console toutes les informations d'un livre
//
// Parametres : pLivre = pointeur vers le t_livre que l'on veut afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_info_livre(t_livre * pLivre)
{
	printf("-------------------------------------------------------------------");
	printf("\nTitre : ");
	printf(pLivre->titre);
	printf("\nAuteur : ");
	printf(pLivre->auteur_prenom);
	printf(" ");
	printf(pLivre->auteur_nom);
	printf("\nGenre : %d", pLivre->genre);
	printf("\nPages : %d", pLivre->nb_pages);
	printf("\nISBN : %d", pLivre->isbn);
	printf("\nEmprunte : %d\n", pLivre->bEmprunte);
	printf("-------------------------------------------------------------------");
	printf("\n");
}

//-----------------------------------------------------------------------------
//							Fonction rechercher_isbn
// Cette fonction permet de chercher un livre dont on connait le numero isbn
// dans la bibliotheque.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle se trouve 
//						 le livre
//				isbn_demande = numero isbn du livre recherche
// Retour :		livre_trouve = pointeur vers le livre trouve
//-----------------------------------------------------------------------------
t_livre * rechercher_livre_isbn(t_bibliotheque * pBibli, int isbn_demande)
{
	t_livre * livre_trouve = NULL;
	int i, j;
	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < pBibli->taille; j++)
		{
			if (pBibli->livres[i][j].isbn == isbn_demande)
			{
				livre_trouve = &pBibli->livres[i][j];
			}
		}
	}
	return livre_trouve;
}

//-----------------------------------------------------------------------------
//							Fonction modifier_livre
// Cette fonction permet de modifier tous les champs d'un livre de la 
// bibliotheque choisi par l'utilisateur sauf son numero isbn.
// Les informations sont entrees par l'utilisateur.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle se trouve 
//						 le livre
// Retour :		aucun
//-----------------------------------------------------------------------------
void modifier_livre(t_bibliotheque * pBibli)
{
	// Caractere permettant d'enlever le enter a la saisie du titre
	char buffer;
	int isbn;
	t_livre livre_modifie;
	t_livre * livre_trouve;
	t_genre genre_livre;

	initialiser_livre(&livre_modifie);


	// Recherche du livre a modifier
	printf("Entrez le isbn du livre a modifier : ");
	scanf("%d", &isbn);

	livre_trouve = rechercher_livre_isbn(pBibli, isbn);
	if (livre_trouve != NULL)
	{
		livre_modifie = *livre_trouve;

		// Enlever le precedent livre du tableau
		initialiser_livre(livre_trouve);

		// Actualiser compteur de genres
		pBibli->nb_livres[livre_modifie.genre]--;

		// Enregistrer le nouveau livre avec les nouvelles infos
		printf("Entrez le nouveau genre du livre : \n");
		scanf("%d", &genre_livre);
		livre_modifie.genre = genre_livre;
		printf("Entrez le nouveau titre du livre : \n");
		gets_s(&buffer, 1);
		gets_s(livre_modifie.titre, TAILLE_TITRE);
		printf("Entrez le nouveau prenom de l'auteur : \n");
		gets_s(livre_modifie.auteur_prenom, TAILLE_PRENOM);
		printf("Entrez le nouveau nom de l'auteur : \n");
		gets_s(livre_modifie.auteur_nom, TAILLE_NOM);
		printf("Entrez le nouveau nombre de page : \n");
		scanf("%d", &livre_modifie.nb_pages);
		livre_modifie.isbn = isbn;

		// Ranger le livre au bon endroit dans la bibliotheque
		pBibli->livres[genre_livre][pBibli->nb_livres[genre_livre]] =
			livre_modifie;

		// Actualiser compteur genre
		pBibli->nb_livres[genre_livre]++;

		printf("Vous avez modifie le livre de numero isbn %d\n", isbn);
	}
	else
	{
		printf("Numero isbn entre inexistant dans cette bibliotheque\n");
	}

}

//-----------------------------------------------------------------------------
//							Fonction retirer_livre
// Cette fonction permet de retirer un livre de la bibliotheque definitivement
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle se trouve 
//						 le livre a enlever
// Retour :		aucun
//-----------------------------------------------------------------------------
void retirer_livre(t_bibliotheque * pBibli)
{
	int isbn;
	t_livre * livre_retire;

	printf("Entrez le numero isbn du livre a retirer : \n");
	scanf("%d", &isbn);
	livre_retire = rechercher_livre_isbn(pBibli, isbn);
	if (livre_retire != NULL)
	{
		initialiser_livre(livre_retire);
		printf("Vous avez retire le livre de numero isbn %d\n", isbn);
	}
	else
	{
		printf("Numero isbn entre inexistant dans cette bibliotheque\n");
	}
}

//-----------------------------------------------------------------------------
//							Fonction sauvegarder_fichier
// Cette fonction permet de sauvegarder la bibliotheque actuelle dans un
// nouveau fichier texte nomme "sauvegarde_bibliotheque.txt".
//
// Parametres : pBibli = pointeur vers la bibliotheque a sauvegarder
// Retour :		aucun
//-----------------------------------------------------------------------------
void sauvegarder_fichier(t_bibliotheque * pBibli)
{

	FILE * sauvegarde = fopen(BIBLIO_SAUVEGARDE, "wt");
	int i, j;
	int nb_total_livres = compter_livres(pBibli);

	if (sauvegarde == NULL)
	{
		printf("Erreur a l'ouverture du fichier de sauvegarde");
		super_pause();
	}
	else
	{
		fprintf(sauvegarde, "%d\n\n", nb_total_livres);

		for (i = 0; i < NB_GENRES; i++)
		{
			for (j = 0; j < pBibli->taille; j++)
			{
				if (pBibli->livres[i][j].isbn != ISBN_INVALIDE)
				{
					fprintf(sauvegarde, "%d\n", pBibli->livres[i][j].genre);
					fprintf(sauvegarde, "%s\n", pBibli->livres[i][j].titre);
					fprintf(sauvegarde, "%s\n", pBibli->livres[i][j].auteur_prenom);
					fprintf(sauvegarde, "%s\n", pBibli->livres[i][j].auteur_nom);
					fprintf(sauvegarde, "%d\n", pBibli->livres[i][j].nb_pages);
					fprintf(sauvegarde, "%d\n", pBibli->livres[i][j].isbn);
					fprintf(sauvegarde, "%d\n\n", pBibli->livres[i][j].bEmprunte);
				}
			}
		}
		printf("Bibliotheque sauvegardee\n");
		fclose(sauvegarde);
	}
}

//-----------------------------------------------------------------------------
//							Fonction compter_livres
// Cette fonction permet de compter le nombre de livres de la bibliotheque
// passee en argument.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle compter
// Retour :		nb_livres = nombre de livres dans la bibliotheque
//-----------------------------------------------------------------------------
int compter_livres(t_bibliotheque * pBibli)
{
	int i, j;
	int nb_livres = 0;

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < pBibli->taille; j++)
		{
			if (pBibli->livres[i][j].isbn != ISBN_INVALIDE)
			{
				nb_livres++;
			}
		}
	}
	return nb_livres;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_bibliotheque
// Cette fonction permet d'afficher tout les livres de la bibliotheque passee
// en argument.
//
// Parametres : pBibli = pointeur vers la bibliotheque a afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_bibliotheque(t_bibliotheque * pBibli)
{
	int i, j;
	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < pBibli->taille; j++)
		{
			if (pBibli->livres[i][j].isbn != ISBN_INVALIDE)
			{
				afficher_info_livre(&pBibli->livres[i][j]);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//							Fonction generer_rapport
// Cette fonction permet de generer et afficher le rapport. Le rapport contient
// le nombre de livres de la bibliotheque passee en argument et le nombre de 
// livres empruntes.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle on veut 
//						 faire le rapport
// Retour :		aucun
//-----------------------------------------------------------------------------
void generer_rapport(t_bibliotheque *pBibli)
{
	int i, j;
	int nb_livres_empruntes = 0;
	int nb_livres = 0;
	int nb_livres_chariot = 0;

	for (i = 0; i < NB_GENRES; i++)
	{
		for (j = 0; j < pBibli->taille; j++)
		{
			if (pBibli->livres[i][j].bEmprunte != DISPONIBLE)
			{
				nb_livres_empruntes++;
			}
			if (pBibli->livres[i][j].isbn != ISBN_INVALIDE)
			{
				nb_livres++;
			}
		}
	}

	nb_livres_chariot = pBibli->chariot.liste_livres->nb_elements;

	// actualisation des valeurs du rapport avec les nouvelles valeurs
	pBibli->rapport.nb_livres_empruntes = nb_livres_empruntes;
	pBibli->rapport.nb_livres = nb_livres;
	pBibli->rapport.nb_livres_chariot = nb_livres_chariot;
}

//-----------------------------------------------------------------------------
//							Fonction afficher_rapport
// Cette fonction permet d'afficher le rapport passe en argument.
//
// Parametres : rapport = pointeur vers le rapport a afficher
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_rapport(t_rapport *rapport)
{
	printf("#####################################\n");
	printf("Nombre de livres : %d\n", rapport->nb_livres);
	printf("Nombre de livres sur le chariot : %d\n", rapport->nb_livres_chariot);
	printf("Nombre de livres empruntes : %d\n", rapport->nb_livres_empruntes);
	printf("#####################################\n");
}

//-----------------------------------------------------------------------------
//							Fonction afficher_menu
// Cette fonction permet d'afficher le menu de la bibliotheque dans la console.
//
// Parametres : aucun	
// Retour :		aucun
//-----------------------------------------------------------------------------
void afficher_menu()
{
	printf("================================================================");
	printf("=============");
	printf("\n                             Bibliotheque 145 inc.\n");
	printf("================================================================");
	printf("=============\n");
	printf("1 - Afficher bibliotheque\n");
	printf("2 - Lire fichier bibliotheque\n");
	printf("3 - Modifier livre\n");
	printf("4 - Retirer livre\n");
	printf("5 - Generer rapport\n");
	printf("6 - Sauvegarder bibliotheque\n");
	printf("0 - Quitter\n");
	printf("================================================================");
	printf("=============\n");
}

//-----------------------------------------------------------------------------
//							Fonction emprunter_livre_biblio
// Cette fonction permet de mettre a jour le champs bemprunte d'un livre dans 
// la bibliotheque dont le numero isbn est precise en parametre.
// Le champs bEmprunte est mit a EMPRUNT 
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle le livre 
//						 est stocké
//				isbn   = numero isbn du livre a emprunter
// Retour :		aucun
//-----------------------------------------------------------------------------
void emprunter_livre_biblio(t_bibliotheque * pBibli, int isbn)
{
	rechercher_livre_isbn(pBibli, isbn)->bEmprunte = EMPRUNT;
}

//-----------------------------------------------------------------------------
//							Fonction rendre_livre_biblio
// Cette fonction permet de mettre a jour le champs bemprunte d'un livre dans 
// la bibliotheque dont le numero isbn est precise en parametre.
// Le champs bEmprunte est mit a DISPONIBLE
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle le livre 
//						 est stocké
//				isbn   = numero isbn du livre a rendre
// Retour :		aucun
//-----------------------------------------------------------------------------
void rendre_livre_biblio(t_bibliotheque * pBibli, int isbn)
{
	rechercher_livre_isbn(pBibli, isbn)->bEmprunte = DISPONIBLE;
}

//-----------------------------------------------------------------------------
//							Fonction agrandir_etagere
// Cette fonction permet de doubler la taille de la deuxieme dimension de 
// la bibliotheque. Les nouveaux emplacement sont remplis avec des livres
// initialises.
//
// Parametres : pBibli = pointeur vers la bibliotheque a agrandir
// Retour :		aucun
//-----------------------------------------------------------------------------
void agrandir_etagere(t_bibliotheque * pBibli)
{
	int i, j;
	int nouvelle_taille = pBibli->taille * FACTEUR_AGRANDISSEMENT;
	for (i = 0; i < NB_GENRES; i++)
	{
		pBibli->livres[i] = (t_livre*)realloc(pBibli->livres[i],
			nouvelle_taille * sizeof(t_livre));

		if (pBibli->livres[i] != NULL)
		{
			for (j = pBibli->taille; j < nouvelle_taille; j++)
			{
				initialiser_livre(&pBibli->livres[i][j]);
			}
		}
	}
	pBibli->taille = nouvelle_taille;
}

//-----------------------------------------------------------------------------
//							Fonction ajouter_etudiant_file
// Cette fonction permet d'ajouter un etudiant dans la file de la bibliotheque.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle se trouve
//						 la file
//				etudiant = etudiant a ajouter a la file
// Retour :		aucun
//-----------------------------------------------------------------------------
void ajouter_etudiant_file(t_bibliotheque * pBibli, t_etudiant etudiant)
{
	enfiler(pBibli->file_etudiants, etudiant);
}

//-----------------------------------------------------------------------------
//							Fonction servir_etudiant
// Cette fonction permet de servir le premier etudiant de la file d'attente.
// Le kiosque propose differentes actions a l'etudiant via un menu (voir la
// fonction servir_etudiant_machine) et il est retire de la file d'attente.
//
// Parametres : pBibli = pointeur vers la bibliotheque dans laquelle se trouve
//						 la file
// Retour :		aucun
//-----------------------------------------------------------------------------
void servir_etudiant(t_bibliotheque * pBibli)
{
	t_etudiant etudiant;

	if (pBibli->file_etudiants != NULL)
	{
		if (!file_vide(pBibli->file_etudiants))
		{
			etudiant = desenfiler(pBibli->file_etudiants);
			pBibli->machine.utilisateur = &etudiant;
			servir_etudiant_machine(&pBibli->machine, &etudiant);
		}
	}
}

//-----------------------------------------------------------------------------
//							Fonction ajouter_livre
// Cette fonction permet d'ajouter un livre dans la bibliotheque en renseignant
// les valeurs des champs manuellement.
//
// Parametres : pBibli = pointeur vers le tableau de t_bibliotheque a remplir
// Retour :		aucun
//-----------------------------------------------------------------------------
void ajouter_livre(t_bibliotheque * pBibli)
{
	// Variables permettant d'enregistrer un livre
	t_genre genre;
	char titre[TAILLE_TITRE];
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	int nb_pages;
	int isbn;
	int emprunt;
	char buffer;

	// Enregistrement des valeurs du fichier texte dans les variables
	printf("Entrez le genre du livre : ");
	scanf("%d", &genre);
	fscanf(stdin, "%c", &buffer);
	printf("\nEntrez le titre du livre : ");
	fgets(titre, TAILLE_TITRE,stdin);
	printf("\nEntrez le prenom de l'auteur du livre : ");
	fgets(prenom, TAILLE_PRENOM,stdin);
	printf("\nEntrez le nom de l'auteur du livre : ");
	fgets(nom, TAILLE_NOM,stdin);
	printf("\nEntrez le nombre de pages du livre : ");
	scanf("%d", &nb_pages);
	printf("\nEntrez le numero isbn du livre : ");
	scanf("%d", &isbn);
	printf("\nEntrez la disponibilite du livre : ");
	scanf("%d", &emprunt);

	// Enlever les sauts de lignes en trop a la fin des chaines
	retirer_sautligne(titre);
	retirer_sautligne(prenom);
	retirer_sautligne(nom);

	// Si l'etagere est remplie, on double sa taille avant d'ajouter 
	// un livre
	if (pBibli->nb_livres[genre] == pBibli->taille)
	{
		agrandir_etagere(pBibli);
	}

	// Mise a jour d'un livre de la bibliotheque
	pBibli->livres[genre][pBibli->nb_livres[genre]].genre = genre;
	strcpy(pBibli->livres[genre][pBibli->nb_livres[genre]].titre, titre);
	strcpy(pBibli->livres[genre][pBibli->nb_livres[genre]].auteur_prenom, prenom);
	strcpy(pBibli->livres[genre][pBibli->nb_livres[genre]].auteur_nom, nom);
	pBibli->livres[genre][pBibli->nb_livres[genre]].nb_pages = nb_pages;
	pBibli->livres[genre][pBibli->nb_livres[genre]].isbn = isbn;
	pBibli->livres[genre][pBibli->nb_livres[genre]].bEmprunte = emprunt;
	pBibli->nb_livres[genre]++;
}
