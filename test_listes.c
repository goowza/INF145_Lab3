// Tests liste
	t_liste liste_test;
	init_liste(&liste_test);

	ajouter_liste_indice(&liste_test,10,1);

	ajouter_liste_indice(&liste_test,11,4);

	ajouter_liste_indice(&liste_test,12,52);

	ajouter_debut(&liste_test,1);
	ajouter_debut(&liste_test,2);
	ajouter_fin(&liste_test,6);
	ajouter_debut(&liste_test,3);
	ajouter_fin(&liste_test,5);

	afficher_liste(&liste_test);
	printf("\n");

	init_liste(&liste_test);
	ajouter_debut(&liste_test,2);

	//printf("element enleve debut : %d\n",enlever_debut(&liste_test));
	//printf("element enleve fin : %d\n",enlever_fin(&liste_test));
	printf("element enleve 3 : %d\n",enlever_liste_indice(&liste_test,3));

	afficher_liste(&liste_test);
	printf("\n");
