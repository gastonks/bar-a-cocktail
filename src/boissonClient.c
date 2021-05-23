/*! \file boissonClient.c
*  \author Barre Romain
*  \version 1
*  \brief Programme contenant toutes les fonctions permettant de gérer les paniers.  
*/

// On inclue le fichier header associé
#include "boissonClient.h"

/*! \fn void initFileClient()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure premettant de vérifier si le fichier des paniers fonctionne correctement.
*
*  \remarks Cette procédure ouvre le fichier contenant les paniers, vérifie si le fichier s'est bien ouvert et le referme ensuite. 
*/

/*
    Fonction permettant d'initialiser le fichier devant contenir tous les paniers et toutes leurs informations associées.
*/
void initFileClient(){

    // On ouvre le fichier
    FILE* file = fopen("data/commandeClient", "ab");

    // On vérifie qu'il s'est bien ouvert, et on affiche un message d'erreur si ce n'est pas le cas
    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    // On referme le fichier
    fclose(file);
}

/*! \fn int idInitPanier()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de donner un ID à un panier.
*
*  \return Cette fonction renvoie un ID.
*
*  \remarks Cette fonction vérifie l'ID du panier le plus récent puis renvoie ce même ID augmenté de 1. 
*/

/*
    Fonction permettant d'initialiser l'ID des paniers.
    Cette fonction renvoie une valeur entière, qui correspond à l'ID du dernier panier plus 1.
    Cette fonction est utile lors de l'ajout d'un panier dans le fichier, permettant ainsi d'attribuer un ID à un nouveau panier.
*/
int idInitPanier(){
   
    // On crée une variable de type panier.    
    panier tmp;

    int nID = 0;
    int taille;

    // On ouvre le fichier contenant les paniers
    FILE* file = fopen("data/commandeClient", "rb");

    // On vérifie que le fichier s'est bien ouvert
    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    // On récupère la le nombre de paniers
    fread(&taille, sizeof(int), 1, file);

    // On lit les paniers jusqu'à ce qu'il n'y en ait plus
    while(fread(&tmp, sizeof(panier), 1, file)) {
        nID = tmp.id;
    }

    // On ferme le fichier
    fclose(file); 

    // On augmente alors l'ID de 1
    nID++;

    return nID;
}

/*! \fn void informationBoissonClient()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant d'afficher les informations des boissons, mais seulement celles étant en stock.
*/

/*
    Fonction premettant d'afficher les informations des boissons, mais seulement celles étant en stock.
*/
void informationBoissonClient(){

    // On crée une variable pour parcourir le tableau, et une qui contient la taille du tableau
    int i;
    int T = tailleTabBarman();

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque boisson, si celle ci est en stock.
    for(i = 0; i<T; i++) {
        if(tab[i].quantite > 0){
            printf("\t\t%d\t%.7s\t%.2f\t\t%.2f\t%.2f\t\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].degreAlco, tab[i].degreScr);
        }
    }

}

/*! \fn void demandeCommande()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de passer une commande.
*
*  \remarks Cette fonction permet à l'utilisateur de passez une commande.
*  Il doit entrer le nombre de commandes, puis pour chaque commmande, entrer le nombre de boissons et leur ID puis le nombre de cocktail et leur ID.
*/

/*
    Fonction premettant de passer une commande.
*/
void demandeCommande(){

    // On crée une variable de type panier, une variable pour récupérer les IDs des boissons et cocktails commandés, et une variable pour récupérer le nombre de cocktails commandés
    panier nPanier;
    int retour;
    int nombreId;
    int nombreCocktail;

    // On initialise l'ID de la commande, et son prix à 0
    nPanier.id = idInitPanier();
    nPanier.prix = 0;

    // On demande à l'utilisateur combien de commande il souhaite effectuer
    printf("Combien de commande voulez vous effectuer :");
    retour = scanf("%d", &nPanier.nbrCommande);

    // On redemande le nombre de commande si la valeur entrée n'est pas correcte
    if(retour != 1 || nPanier.nbrCommande < 0 ){
        while(retour != 1 || nPanier.nbrCommande < 0){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer un nombre valide pour soit sortir, soit commander une boisson:");
            getchar();
            retour = scanf("%d", &nPanier.nbrCommande);
        }
    }

    // On alloue la mémoire pour le nombre de commandes entré précédemmenent, puis on vérifie qu'il n'y a pas eu d'erreur d'allocation
    nPanier.listCommande = (commande*) malloc(nPanier.nbrCommande*sizeof(commande));
    if(nPanier.listCommande == NULL){
        printf("Erreur allocation memoire.");
        exit(-1);
    }

    // On fait une boucle qui va demander les boissons et les cocktails à commander, autant de fois qu'il y a de commandes pour ce panier
    for(int i = 0; i< nPanier.nbrCommande; i++){
        // S'il n'y a pas de boisson, on ne propose pas a l'utilisateur d'en commander
        if(tab == NULL){
            printf("\nAucune boisson disponible.");
            getchar();
        }else{
            // On affiche les informations des boissons disponibles
            system("clear");
            printf("Commande n.%d\n",i+1);
            printf("=====================================================================================================\n\n");
            printf("\t\t\tMenu Information sur les boissons\n\n");
            printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\n\n");

            informationBoissonClient();

            printf("=====================================================================================================\n\n");

            // On demande à l'utilisateur combien de boissons il veut commander, puis on vérifie qu'il n'y a pas eu d'erreur
            printf("\nCombien de boisson se compose votre commande :");
            retour = scanf("%d", &nPanier.listCommande[i].nbrBoisson);

            if(retour != 1 || nPanier.listCommande[i].nbrBoisson < 0){
                while(retour != 1 || nPanier.listCommande[i].nbrBoisson < 0 ){
                    retour = 1;
                    printf("\nCe nombre n'existe pas.\n");
                    printf("Veuillez entrer un nombre valide :");
                    getchar();
                    retour = scanf("%d", &nPanier.listCommande[i].nbrBoisson);
                }
            }

            // S'il a commandé au moins une boisson, on va actualiser le tableau
            if(nPanier.listCommande[i].nbrBoisson != 0){
                
                // On alloue la mémoire pour les boissons à commander
                nPanier.listCommande[i].listBoisson = (listIdBoisson*) malloc(nPanier.listCommande[i].nbrBoisson*sizeof(listIdBoisson));
                if(nPanier.listCommande[i].listBoisson == NULL){
                    printf("Erreur allocation memoire.");
                    exit(-1);
                }

                // On initialise le prix de la commande à 0
                nPanier.listCommande[i].prix = 0;  

                // On fait une boucle pour demander autant de fois qu'il faut la boisson à commander
                for(int j = 0; j<nPanier.listCommande[i].nbrBoisson; j++){

                    // On demande l'ID de la boisson à commander, puis on vérifie qu'il n'y a pas eu d'erreur
                    printf("\nEntrez l'ID de la boisson que vous voulez commander :");
                    retour = scanf("%d", &nombreId);

                    if(retour != 1 || nombreId < 0){
                        while(retour != 1 || nombreId < 0 ){
                            retour = 1;
                            printf("\nCe nombre n'existe pas.\n");
                            printf("Veuillez entrer un nombre :");
                            getchar();
                            retour = scanf("%d", &nombreId);
                        }
                    }

                    // On met l'ID de la boisson dans le tableau de boissons du panier
                    nPanier.listCommande[i].listBoisson[j].idBoisson = nombreId - 1;

                    // On demande la quantité pour cette boisson, puis on vérifie qu'il n'y a pas eu d'erreur
                    printf("\nEntrez la quantite de boisson que vous voulez commander :");
                    retour = scanf("%d", &nPanier.listCommande[i].listBoisson[j].quantiteBoisson);

                    if(retour != 1 || nPanier.listCommande[i].listBoisson[j].quantiteBoisson < 0){
                        while(retour != 1 || nPanier.listCommande[i].listBoisson[j].quantiteBoisson < 0 ){
                            retour = 1;
                            printf("\nCe nombre n'existe pas.\n");
                            printf("Veuillez entrer un nombre valide :");
                            getchar();
                            retour = scanf("%d", &nPanier.listCommande[i].listBoisson[j].quantiteBoisson);
                        }
                    }

                    // On met alors le prix à jour en fonction de la boisson commandée et de la quantité commandée
                    nPanier.listCommande[i].prix = nPanier.listCommande[i].prix + (nPanier.listCommande[i].listBoisson[j].quantiteBoisson*tab[nPanier.listCommande[i].listBoisson[j].idBoisson].prix);
                }
            }
            // Si l'utilisateur ne veut pas commander de boisson, on ne crée alors pas le tableau de boisson
            else{
                nPanier.listCommande[i].prix = nPanier.listCommande[i].prix + 0; 
                nPanier.listCommande[i].nbrBoisson = 0;
            }
        }

        // Le fonctionnement est exactement le meme pour les cocktails
        if(tabCocktail == NULL){
            printf("\nAucun cocktail disponible.\n");
            getchar();
        }else{
            system("clear");
            printf("Commande n.%d\n",i+1);
            printf("=====================================================================================================\n\n");
            printf("\t\t\tMenu Information sur les cocktails\n\n");
            printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tNombre_Boisson\n\n");
            informationCocktailClient();
            printf("=====================================================================================================\n\n");

            printf("\nCombien de cocktail se compose votre commande :");
            retour = scanf("%d", &nombreCocktail);

            if(retour != 1 || nombreCocktail < 0){
                while(retour != 1 || nombreCocktail < 0 ){
                    retour = 1;
                    printf("\nCe nombre n'existe pas.\n");
                    printf("Veuillez entrer un nombre valide :");
                    getchar();
                    retour = scanf("%d", &nPanier.listCommande[i].nbrCocktail);
                }
            }
            
            nPanier.listCommande[i].nbrCocktail = nombreCocktail;

            if(nPanier.listCommande[i].nbrCocktail != 0){
                
                nPanier.listCommande[i].listCocktail = (listIdCocktail*) malloc(nPanier.listCommande[i].nbrCocktail*sizeof(listIdCocktail));
                if(nPanier.listCommande[i].listCocktail == NULL){
                    printf("Erreur allocation memoire.");
                    exit(-1);
                }     

                for(int j = 0; j<nPanier.listCommande[i].nbrCocktail; j++){
                    printf("\nEntrez l'ID du cocktail que vous voulez commander :");
                    retour = scanf("%d", &nombreId);

                    if(retour != 1 || nombreId < 0){
                        while(retour != 1 || nombreId < 0 ){
                            retour = 1;
                            printf("\nCe nombre n'existe pas.\n");
                            printf("Veuillez entrer un nombre :");
                            getchar();
                            retour = scanf("%d", &nombreId);
                        }
                    }

                    nPanier.listCommande[i].listCocktail[j].idCocktail = nombreId - 1;

                    printf("\nEntrez la quantite de cocktail que vous voulez commander :");
                    retour = scanf("%d", &nPanier.listCommande[i].listCocktail[j].quantiteCocktail);

                    if(retour != 1 || nPanier.listCommande[i].listCocktail[j].quantiteCocktail < 0){
                        while(retour != 1 || nPanier.listCommande[i].listCocktail[j].quantiteCocktail < 0 ){
                            retour = 1;
                            printf("\nCe nombre n'existe pas.\n");
                            printf("Veuillez entrer un nombre valide :");
                            getchar();
                            retour = scanf("%d", &nPanier.listCommande[i].listCocktail[j].quantiteCocktail);
                        }
                    }
                    
                    nPanier.listCommande[i].prix = nPanier.listCommande[i].prix + (nPanier.listCommande[i].listCocktail[j].quantiteCocktail*tabCocktail[nPanier.listCommande[i].listCocktail[j].idCocktail].prix);

                }
            }else{
                nPanier.listCommande[i].prix = nPanier.listCommande[i].prix + 0; 
                nPanier.listCommande[i].nbrCocktail = 0;
            }
        }

        nPanier.prix = nPanier.prix + nPanier.listCommande[i].prix;

    }

    // Enfin, on copie les informations du tableau vers le fichier, seulement s'il y a eu au moins une commande
    if(nPanier.nbrCommande != 0){
        initCommande(nPanier);
    }

    // On retourne a l'interface précédente
    interfaceClient();
}

/*! \fn void initCommande(panier nPanier)()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant d'actualiser le tableau de paniers.
*
*  \remarks Cette fonction permet d'actualiser le tableau de paniers.
*  Cette fonction fonctionne de la même manière que pour la gestion des tableaux de boissons et de cocktails, nous avons donc décidé de ne pas la recommenter entièrement. 
*/

/*
    Fonction premettant d'actualiser le tableau de paniers.
*/
void initCommande(panier nPanier){

    int T = tailleTabPanier();
    int nombreCocktail = 1;

    if (T>0) {
        // On cree le tableau temporaire et on y copie toutes les informations du tableau de base.
        panier* tmp = malloc(T*sizeof(panier));
        if(tmp == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }

        for(int i = 0; i<T; i++) {
            tmp[i].id = tabPanier[i].id;
            tmp[i].nbrCommande = tabPanier[i].nbrCommande;
            tmp[i].prix = tabPanier[i].prix;
            tmp[i].listCommande = (commande*) malloc(tabPanier[i].nbrCommande*sizeof(commande));
            if(tmp[i].listCommande == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
            for(int j = 0; j<tabPanier[i].nbrCommande; j++){
                nombreCocktail = tabPanier[i].listCommande[j].nbrCocktail;
                if(tabPanier[i].listCommande[j].nbrBoisson != 0){
                    tmp[i].listCommande[j].nbrBoisson = tabPanier[i].listCommande[j].nbrBoisson;
                    tmp[i].listCommande[j].listBoisson = (listIdBoisson*) malloc(tabPanier[i].listCommande[j].nbrBoisson*sizeof(listIdBoisson));
                    if(tmp[i].listCommande[j].listBoisson == NULL){
                        printf("Erreur allocation mémoire.");
                        exit(-1);
                    }
                    for(int k = 0; k<tabPanier[i].listCommande[j].nbrBoisson; k++){
                        tmp[i].listCommande[j].listBoisson[k].idBoisson = tabPanier[i].listCommande[j].listBoisson[k].idBoisson;
                        tmp[i].listCommande[j].listBoisson[k].quantiteBoisson = tabPanier[i].listCommande[j].listBoisson[k].quantiteBoisson;
                    }
                }else{
                    tmp[i].listCommande[j].nbrBoisson = 0;
                }
                if(nombreCocktail != 0){
                    tmp[i].listCommande[j].nbrCocktail = nombreCocktail;

                    tmp[i].listCommande[j].listCocktail = (listIdCocktail*) malloc(nombreCocktail*sizeof(listIdCocktail));
                    if(tmp[i].listCommande[j].listCocktail == NULL){
                        printf("Erreur allocation mémoire.");
                        exit(-1);
                    }
                    for(int k = 0; k<nombreCocktail; k++){
                        tmp[i].listCommande[j].listCocktail[k].idCocktail = tabPanier[i].listCommande[j].listCocktail[k].idCocktail;
                        tmp[i].listCommande[j].listCocktail[k].quantiteCocktail = tabPanier[i].listCommande[j].listCocktail[k].quantiteCocktail;
                    }
                }else{
                    tmp[i].listCommande[j].nbrCocktail = 0;
                }
                tmp[i].listCommande[j].prix = tabPanier[i].listCommande[j].prix;
            }
        }

        // On libere l'espace du tableau de base et on le cree avec une case supplementaire, puis on y recopie toutes les informations avec la nouvelle commande a la fin.

        for(int i = 0; i<T;i++){
            for(int j = 0; j<tabPanier[i].nbrCommande; j++){
                if(tabPanier[i].listCommande[j].nbrBoisson != 0){
                    free(tabPanier[i].listCommande[j].listBoisson);
                }
                if(tabPanier[i].listCommande[j].nbrCocktail != 0){
                    free(tabPanier[i].listCommande[j].listCocktail);
                }
            }
        }
        for(int i = 0; i<T;i++){
            free(tabPanier[i].listCommande);
        }

        free(tabPanier);

        tabPanier = malloc((T+1)*sizeof(boisson));
        if(tabPanier == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }

        for(int i = 0; i<T; i++) {
            tabPanier[i].id = tmp[i].id;
            tabPanier[i].nbrCommande = tmp[i].nbrCommande;
            tabPanier[i].prix = tmp[i].prix;
            tabPanier[i].listCommande = (commande*) malloc(tmp[i].nbrCommande*sizeof(commande));
            if(tabPanier[i].listCommande == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
            for(int j = 0; j<tmp[i].nbrCommande; j++){
                if(tmp[i].listCommande[j].nbrBoisson != 0){
                    tabPanier[i].listCommande[j].nbrBoisson = tmp[i].listCommande[j].nbrBoisson;
        
                    tabPanier[i].listCommande[j].listBoisson = (listIdBoisson*) malloc(tmp[i].listCommande[j].nbrBoisson*sizeof(listIdBoisson));
                    if(tabPanier[i].listCommande[j].listBoisson == NULL){
                        printf("Erreur allocation mémoire.");
                        exit(-1);
                    }
                    for(int k = 0; k<tmp[i].listCommande[j].nbrBoisson; k++){
                        tabPanier[i].listCommande[j].listBoisson[k].idBoisson = tmp[i].listCommande[j].listBoisson[k].idBoisson;
                        tabPanier[i].listCommande[j].listBoisson[k].quantiteBoisson = tmp[i].listCommande[j].listBoisson[k].quantiteBoisson;

                    }
                }else{
                    tabPanier[i].listCommande[j].nbrBoisson = 0;
                }
                if(tmp[i].listCommande[j].nbrCocktail != 0){
                    tabPanier[i].listCommande[j].nbrCocktail = tmp[i].listCommande[j].nbrCocktail;
                
                    tabPanier[i].listCommande[j].listCocktail = (listIdCocktail*) malloc(tmp[i].listCommande[j].nbrCocktail*sizeof(listIdCocktail));
                    if(tabPanier[i].listCommande[j].listCocktail == NULL){
                        printf("Erreur allocation mémoire.");
                        exit(-1);
                    }
                    for(int k = 0; k<tmp[i].listCommande[j].nbrCocktail; k++){
                        tabPanier[i].listCommande[j].listCocktail[k].idCocktail = tmp[i].listCommande[j].listCocktail[k].idCocktail;
                        tabPanier[i].listCommande[j].listCocktail[k].quantiteCocktail = tmp[i].listCommande[j].listCocktail[k].quantiteCocktail;
                    }
                }else{
                    tabPanier[i].listCommande[j].nbrCocktail = 0;
                   
                }
                tabPanier[i].listCommande[j].prix = tmp[i].listCommande[j].prix;
            }
        }

        tabPanier[T].id = nPanier.id;
        tabPanier[T].nbrCommande = nPanier.nbrCommande;
        tabPanier[T].prix = nPanier.prix;
        tabPanier[T].listCommande = (commande*) malloc(nPanier.nbrCommande*sizeof(commande));
        if(tabPanier[T].listCommande == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }
        for(int j = 0; j<nPanier.nbrCommande; j++){
            if(nPanier.listCommande[j].nbrBoisson != 0){
                tabPanier[T].listCommande[j].nbrBoisson = nPanier.listCommande[j].nbrBoisson;
                
                tabPanier[T].listCommande[j].listBoisson = (listIdBoisson*) malloc(nPanier.listCommande[j].nbrBoisson*sizeof(listIdBoisson));
                if(tabPanier[T].listCommande[j].listBoisson == NULL){
                    printf("Erreur allocation mémoire.");
                    exit(-1);
                }
                for(int k = 0; k<nPanier.listCommande[j].nbrBoisson; k++){
                    tabPanier[T].listCommande[j].listBoisson[k].idBoisson = nPanier.listCommande[j].listBoisson[k].idBoisson;
                    tabPanier[T].listCommande[j].listBoisson[k].quantiteBoisson = nPanier.listCommande[j].listBoisson[k].quantiteBoisson;
                }
            }else{
                tabPanier[T].listCommande[j].nbrBoisson = 0;
            }
            if(nPanier.listCommande[j].nbrCocktail != 0){
                tabPanier[T].listCommande[j].nbrCocktail = nPanier.listCommande[j].nbrCocktail;
                
                tabPanier[T].listCommande[j].listCocktail = (listIdCocktail*) malloc(nPanier.listCommande[j].nbrCocktail*sizeof(listIdCocktail));
                if(tabPanier[T].listCommande[j].listCocktail == NULL){
                    printf("Erreur allocation mémoire.");
                    exit(-1);
                }
                for(int k = 0; k<nPanier.listCommande[j].nbrCocktail; k++){
                    tabPanier[T].listCommande[j].listCocktail[k].idCocktail = nPanier.listCommande[j].listCocktail[k].idCocktail;
                    tabPanier[T].listCommande[j].listCocktail[k].quantiteCocktail = nPanier.listCommande[j].listCocktail[k].quantiteCocktail;
                }
            }else{
                tabPanier[T].listCommande[j].nbrCocktail = 0;
            }

            tabPanier[T].listCommande[j].prix = nPanier.listCommande[j].prix;
        }

        // On libere l'espace du tableau temporaire.
        for(int i = 0; i<T;i++){
            for(int j = 0; j<tmp[i].nbrCommande; j++){
                if(tmp[i].listCommande[j].nbrBoisson != 0){
                    free(tmp[i].listCommande[j].listBoisson);
                }
                if(tmp[i].listCommande[j].nbrCocktail != 0){
                    free(tmp[i].listCommande[j].listCocktail);
                }
            }
        }
        for(int i = 0; i<T;i++){
            free(tmp[i].listCommande);
        }
        free(tmp);
    } 
    // Sinon, si le fichier ne contient aucun panier, on cree un tableau avec une seule case où on y copie le nouveau panier.
    else {
        tabPanier = malloc(1*sizeof(panier));
        if(tabPanier == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }
        
        
        tabPanier[0].id = nPanier.id;
        tabPanier[0].nbrCommande = nPanier.nbrCommande;
        tabPanier[0].prix = nPanier.prix;
        tabPanier[0].listCommande = (commande*) malloc(nPanier.nbrCommande*sizeof(commande));
        if(tabPanier[0].listCommande == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }

        for(int j = 0; j<nPanier.nbrCommande; j++){

            nombreCocktail = nPanier.listCommande[j].nbrCocktail;

            if(nPanier.listCommande[j].nbrBoisson != 0){
                tabPanier[0].listCommande[j].nbrBoisson = nPanier.listCommande[j].nbrBoisson;
                tabPanier[0].listCommande[j].listBoisson = (listIdBoisson*) malloc(nPanier.listCommande[j].nbrBoisson*sizeof(listIdBoisson));
                if(tabPanier[0].listCommande[j].listBoisson == NULL){
                    printf("Erreur allocation mémoire.");
                    exit(-1);
                }
                for(int k = 0; k<nPanier.listCommande[j].nbrBoisson; k++){
                    tabPanier[0].listCommande[j].listBoisson[k].idBoisson = nPanier.listCommande[j].listBoisson[k].idBoisson;
                    tabPanier[0].listCommande[j].listBoisson[k].quantiteBoisson = nPanier.listCommande[j].listBoisson[k].quantiteBoisson;
                }
            }else{
                tabPanier[0].listCommande[j].nbrBoisson = 0;
            }
            
            nPanier.listCommande[j].nbrCocktail = nombreCocktail;

            if(nombreCocktail != 0){
                tabPanier[0].listCommande[j].nbrCocktail = nombreCocktail;

                tabPanier[0].listCommande[j].listCocktail = (listIdCocktail*) malloc(nombreCocktail*sizeof(listIdCocktail));
                if(tabPanier[0].listCommande[j].listCocktail == NULL){
                    printf("Erreur allocation mémoire.");
                    exit(-1);
                }
                for(int k = 0; k<nombreCocktail; k++){
                    tabPanier[0].listCommande[j].listCocktail[k].idCocktail = nPanier.listCommande[j].listCocktail[k].idCocktail;
                    tabPanier[0].listCommande[j].listCocktail[k].quantiteCocktail = nPanier.listCommande[j].listCocktail[k].quantiteCocktail;
                }
            }else{
                tabPanier[0].listCommande[j].nbrCocktail = 0;
            }
            tabPanier[0].listCommande[j].prix = nPanier.listCommande[j].prix;
        }
    }

    // On recopie toutes les informations du tableau dans le fichier, en indicant la taille +1 car on a ajoute un panier.
    initFichierCommande(T+1);
}

/*! \fn void informationCommande()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant d'afficher les informations des paniers.
*/

/*
    Fonction premettant d'afficher les informations des paniers.
*/
void informationCommande(){   

    // On cree des variables, une permettant de parcourir le tableau, l'autre contenant le nombre de paniers.
    int i;
    int T = tailleTabPanier();

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque panier.
    for(i = 0; i<T; i++) {
        
        printf("\tPanier n.%d:\t\tPrix du panier: %.2f euros\n\n", i+1, tabPanier[i].prix);

        for(int l = 0; l<tabPanier[i].nbrCommande; l++){

            printf("\t\tCommande n.%d:\t\tPrix de la commande: %.2f euros\n\n", l+1, tabPanier[i].listCommande[l].prix);
            printf("\t=====================================================================================\n");
            printf("\t\tCette commande est compose de(s) la (les) boisson(s) suivante(s):\n");
            printf("\t");
            if(tabPanier[i].listCommande[l].nbrBoisson != 0){
                for(int j = 0; j<tabPanier[i].listCommande[l].nbrBoisson; j++){
                    printf("%s", tab[tabPanier[i].listCommande[l].listBoisson[j].idBoisson].nom);
                    printf(" x");
                    printf("%d\t", tabPanier[i].listCommande[l].listBoisson[j].quantiteBoisson);
                }
            }else{
                printf("Aucune boisson commande.");
            }
            printf("\n\t=====================================================================================\n\n");
            printf("\t=====================================================================================\n");
            printf("\t\tCette commande est compose du (des) cocktail(s) suivant(s):\n");
            printf("\t");
            if(tabPanier[i].listCommande[l].nbrCocktail != 0){
                for(int j = 0; j<tabPanier[i].listCommande[l].nbrCocktail; j++){
                    printf("%s", tabCocktail[tabPanier[i].listCommande[l].listCocktail[j].idCocktail].nom);
                    printf(" x");
                    printf("%d\t", tabPanier[i].listCommande[l].listCocktail[j].quantiteCocktail);
                }
            }else{
                printf("Aucun cocktail commande.");
            }
            printf("\n\t=====================================================================================\n\n");
        }
    }
}

/*! \fn void supprimerPanier(int idSupp)
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de supprimer un panier.
*
*  \param idSupp : ID du panier à supprimer.
*
*  \remarks Cette fonction permet de supprimer un panier.
*  L'ID du panier à supprimer est récupérée, puis le fonctionnement est similaire à la suppresion d'une boisson ou d'un cocktail.
*  On copie le tableau dans un tableau temporaire, on libère l'espace du tableau de base, on lui alloue de la mémoire mais avec une case en moins car on supprime un panier,
*  et on recopie le tableau temporaire dans le tableau de base, tout en évitant de recopier le panier à supprimer, et enfin on libère l'espace du tableau temporaire.
*/

/*
    Fonction premettant de supprimer un panier.
    L'ID du panier à supprimer est récupérée, puis le fonctionnement est similaire à la suppresion d'une boisson ou d'un cocktail.
*/
void supprimerPanier(int idSupp){

    int T = tailleTabPanier();
    int h = 0;
    int j = 0;
    int nombreCocktail = 1;

    // Si le tableau contient plus d'un panier, on fait l'operation enoncee precedemment, sinon on libere simplement l'espace du tableau.
    if(T>1) {
        // On cree le tableau temporaire et on y copie toutes les informations du tableau de base.
        panier* tmp = malloc(T*sizeof(panier));
        if(tmp == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }

        for(int i = 0; i<T; i++) {
            tmp[i].id = tabPanier[i].id;
            tmp[i].nbrCommande = tabPanier[i].nbrCommande;
            tmp[i].prix = tabPanier[i].prix;
            tmp[i].listCommande = (commande*) malloc(tabPanier[i].nbrCommande*sizeof(commande));
            if(tmp[i].listCommande == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
            for(int j = 0; j<tabPanier[i].nbrCommande; j++){
                nombreCocktail = tabPanier[i].listCommande[j].nbrCocktail;
                if(tabPanier[i].listCommande[j].nbrBoisson != 0){
                    tmp[i].listCommande[j].nbrBoisson = tabPanier[i].listCommande[j].nbrBoisson;
                    
                    tmp[i].listCommande[j].listBoisson = (listIdBoisson*) malloc(tabPanier[i].listCommande[j].nbrBoisson*sizeof(listIdBoisson));
                    if(tmp[i].listCommande[j].listBoisson == NULL){
                        printf("Erreur allocation mémoire.");
                        exit(-1);
                    }
                    for(int k = 0; k<tabPanier[i].listCommande[j].nbrBoisson; k++){
                        tmp[i].listCommande[j].listBoisson[k].idBoisson = tabPanier[i].listCommande[j].listBoisson[k].idBoisson;
                        tmp[i].listCommande[j].listBoisson[k].quantiteBoisson = tabPanier[i].listCommande[j].listBoisson[k].quantiteBoisson;
                    }
                }else{
                    tmp[i].listCommande[j].nbrBoisson = 0;
                }
                if(nombreCocktail != 0){
                    tmp[i].listCommande[j].nbrCocktail = nombreCocktail;

                    tmp[i].listCommande[j].listCocktail = (listIdCocktail*) malloc(nombreCocktail*sizeof(listIdCocktail));
                    if(tmp[i].listCommande[j].listCocktail == NULL){
                        printf("Erreur allocation mémoire.");
                        exit(-1);
                    }
                    for(int k = 0; k<nombreCocktail; k++){
                        tmp[i].listCommande[j].listCocktail[k].idCocktail = tabPanier[i].listCommande[j].listCocktail[k].idCocktail;
                        tmp[i].listCommande[j].listCocktail[k].quantiteCocktail = tabPanier[i].listCommande[j].listCocktail[k].quantiteCocktail;
                    }
                }else{
                    tmp[i].listCommande[j].nbrCocktail = 0;
                }
                tmp[i].listCommande[j].prix = tabPanier[i].listCommande[j].prix;
            }
        }

        // On libere l'espace du tableau de base et on le cree avec une case en moins.

        for(int i = 0; i<T;i++){
            for(int j = 0; j<tabPanier[i].nbrCommande; j++){
                if(tabPanier[i].listCommande[j].nbrBoisson != 0){
                    free(tabPanier[i].listCommande[j].listBoisson);
                }
                if(tabPanier[i].listCommande[j].nbrCocktail != 0){
                    free(tabPanier[i].listCommande[j].listCocktail);
                }
            }
        }
        for(int i = 0; i<T;i++){
            free(tabPanier[i].listCommande);
        }

        free(tabPanier);

        tabPanier = malloc((T-1)*sizeof(boisson));
        if(tabPanier == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }

        // On recopie toutes les informations dans le tableau de base, et si on est situe sur la valeur a supprimer, on ne la recopie tout simplement pas.
        while(j<T) {
            if(j != idSupp-1) {
                tabPanier[h].id = tmp[j].id;
                tabPanier[h].nbrCommande = tmp[j].nbrCommande;
                tabPanier[h].prix = tmp[j].prix;
                tabPanier[h].listCommande = (commande*) malloc(tmp[j].nbrCommande*sizeof(commande));
            if(tabPanier[h].listCommande == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
            for(int l = 0; l<tmp[j].nbrCommande; l++){
                if(tmp[j].listCommande[l].nbrBoisson != 0){
                    tabPanier[h].listCommande[l].nbrBoisson = tmp[j].listCommande[l].nbrBoisson;
        
                    tabPanier[h].listCommande[l].listBoisson = (listIdBoisson*) malloc(tmp[j].listCommande[l].nbrBoisson*sizeof(listIdBoisson));
                    if(tabPanier[h].listCommande[l].listBoisson == NULL){
                        printf("Erreur allocation mémoire.");
                        exit(-1);
                    }
                    for(int k = 0; k<tmp[j].listCommande[l].nbrBoisson; k++){
                        tabPanier[h].listCommande[l].listBoisson[k].idBoisson = tmp[j].listCommande[l].listBoisson[k].idBoisson;
                        tabPanier[h].listCommande[l].listBoisson[k].quantiteBoisson = tmp[j].listCommande[l].listBoisson[k].quantiteBoisson;

                    }
                }else{
                    tabPanier[h].listCommande[l].nbrBoisson = 0;
                }
                if(tmp[j].listCommande[l].nbrCocktail != 0){
                    tabPanier[h].listCommande[l].nbrCocktail = tmp[j].listCommande[l].nbrCocktail;
                
                    tabPanier[h].listCommande[l].listCocktail = (listIdCocktail*) malloc(tmp[j].listCommande[l].nbrCocktail*sizeof(listIdCocktail));
                    if(tabPanier[h].listCommande[l].listCocktail == NULL){
                        printf("Erreur allocation mémoire.");
                        exit(-1);
                    }
                    for(int k = 0; k<tmp[j].listCommande[l].nbrCocktail; k++){
                        tabPanier[h].listCommande[l].listCocktail[k].idCocktail = tmp[j].listCommande[l].listCocktail[k].idCocktail;
                        tabPanier[h].listCommande[l].listCocktail[k].quantiteCocktail = tmp[j].listCommande[l].listCocktail[k].quantiteCocktail;
                    }
                }else{
                    tabPanier[h].listCommande[l].nbrCocktail = 0;
                   
                }
                tabPanier[h].listCommande[l].prix = tmp[j].listCommande[l].prix;
            }
                h++;
                j++;
            }
            else {
                j++;
            }
        }
    } 
    // S'il n'y a qu'un seul panier et que l'ID a supprimer est 1 (le seul possible) alors on libere simplement l'espace du tableau.
    else if (T==1 && idSupp==1) {
        for(int i = 0; i<T;i++){
            for(int j = 0; j<tabPanier[i].nbrCommande; j++){
                if(tabPanier[i].listCommande[j].nbrBoisson != 0){
                    free(tabPanier[i].listCommande[j].listBoisson);
                }
                if(tabPanier[i].listCommande[j].nbrCocktail != 0){
                    free(tabPanier[i].listCommande[j].listCocktail);
                }
            }
        }
        for(int i = 0; i<T;i++){
            free(tabPanier[i].listCommande);
        }

        free(tabPanier);
    }

    // On recopie le tableau dans le fichier
    initFichierCommande(T-1);

}

/*! \fn void modifPanier(int idModif)
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de modifier un panier.
*
*  \param idModif : ID du panier à modifier.
*
*  \remarks Cette fonction permet de modifier un panier.
*  Il est cependant seulement possible de modifier la quantite des boissons ou des cocktails.
*/

/*
    Fonction premettant de modifier un panier.
*/
void modifPanier(int idModif){

    // On crée une variable contenant le nombre de paniers, une pou l'ID de la commande, une pour l'ID de la boisson et sa quantité, et une pour l'ID du cocktail et sa quantité
    int T = tailleTabPanier();
    int retour = 0;
    int idCommande;
    int idBoisson;
    int quantiteBoiss;
    int idCocktail;
    int quantiteCock;

    // On fait une boucle pour passer trouver le panier a modifier
    for (int i = 0; i < T; i++){
        if(i == idModif-1){
            // On affiche les commandes du panier
            system("clear");
            for(int l = 0; l < tabPanier[i].nbrCommande; l ++){
                printf("\t\tCommande n.%d:\t\tPrix de la commande: %.2f euros\n\n", l+1, tabPanier[i].listCommande[l].prix);
                printf("\t=====================================================================================\n");
                printf("\t\tCette commande est compose de(s) la (les) boisson(s) suivante(s):\n");
                printf("\t");
                if(tabPanier[i].listCommande[l].nbrBoisson != 0){
                    for(int j = 0; j<tabPanier[i].listCommande[l].nbrBoisson; j++){
                        printf("%s", tab[tabPanier[i].listCommande[l].listBoisson[j].idBoisson].nom);
                        printf(" x");
                        printf("%d\t", tabPanier[i].listCommande[l].listBoisson[j].quantiteBoisson);
                    }
                }else{
                    printf("Aucune boisson commande.");
                }
                printf("\n\t=====================================================================================\n\n");
                printf("\t=====================================================================================\n");
                printf("\t\tCette commande est compose du (des) cocktail(s) suivant(s):\n");
                printf("\t");
                if(tabPanier[i].listCommande[l].nbrCocktail != 0){
                    for(int j = 0; j<tabPanier[i].listCommande[l].nbrCocktail; j++){
                        printf("%s", tabCocktail[tabPanier[i].listCommande[l].listCocktail[j].idCocktail].nom);
                        printf(" x");
                        printf("%d\t", tabPanier[i].listCommande[l].listCocktail[j].quantiteCocktail);
                    }
                }else{
                    printf("Aucun cocktail commande.");
                }
                printf("\n\t=====================================================================================\n\n");
            }

            // On demande a l'utilisateur le numero de la commande a modifier
            printf("Entrez le numero de la commande a modifie :");
            retour = scanf("%d", &idCommande);
            if(retour != 1 || idCommande < 0 || idCommande > tabPanier[i].nbrCommande){
                while(retour != 1 || idCommande < 0 || idCommande > tabPanier[i].nbrCommande){
                    retour = 1;
                    printf("\nCe nombre n'existe pas.\n");
                    printf("Veuillez entrer un nombre valide pour modifer une commande:");
                    getchar();
                    retour = scanf("%d", &idCommande);
                }
            }

            // On affiche les boissons contenues dans la commande
            for(int l = 0; l < tabPanier[i].nbrCommande; l++){
                if(l == idCommande-1){
                    system("clear");
                    printf("\t=====================================================================================\n");
                    printf("\t\tCette commande est compose de(s) la (les) boisson(s) suivante(s):\n");
                    printf("\t");
                    if(tabPanier[i].listCommande[l].nbrBoisson != 0){
                        for(int j = 0; j<tabPanier[i].listCommande[l].nbrBoisson; j++){
                            printf("%d. %s",j+1, tab[tabPanier[i].listCommande[l].listBoisson[j].idBoisson].nom);
                            printf(" x");
                            printf("%d\t", tabPanier[i].listCommande[l].listBoisson[j].quantiteBoisson);
                        }
                    }else{
                        printf("Aucune boisson commande.\n");
                    }

                    // On demande a l'utilisateur l'ID de la boisson pour laquelle il faut modifier la quantite commandee, et 0 s'il ne veut rien modifier pour les boissons
                    printf("\n\t=====================================================================================\n\n");
                    if(tabPanier[i].listCommande[l].listBoisson != 0){
                        printf("Entrez 0 pour ne rien modifier.\nEntrez le numero de la boisson pour modifier sa quantite commande:");
                        retour = scanf("%d", &idBoisson);
                        if(retour != 1 || idBoisson < 0 || idBoisson > tabPanier[i].listCommande[l].nbrBoisson){
                            while(retour != 1 || idBoisson < 0 || idBoisson > tabPanier[i].listCommande[l].nbrBoisson){
                                retour = 1;
                                printf("\nCe nombre n'existe pas.\n");
                                printf("Veuillez entrer un nombre valide pour selectionner une boisson:");
                                getchar();
                                retour = scanf("%d", &idBoisson);
                            }
                        }

                        if(idBoisson != 0){
                            printf("Entrez la nouvelle quantite de boisson:");
                            retour = scanf("%d", &quantiteBoiss);
                            if(retour != 1 || quantiteBoiss < 0 ){
                                while(retour != 1 || quantiteBoiss < 0){
                                    retour = 1;
                                    printf("\nCe nombre n'existe pas.\n");
                                    printf("Veuillez entrer un nombre valide pour la qauntite de boisson:");
                                    getchar();
                                    retour = scanf("%d", &quantiteBoiss);
                                }
                            }
                            
                            for(int k = 0; k < tabPanier[i].listCommande[l].nbrBoisson; k++){
                                if(k == idBoisson-1){
                                    tabPanier[i].listCommande[l].listBoisson[k].quantiteBoisson = quantiteBoiss;
                                }
                            }
                        }else{
                            printf("\t\nAucune boisson a modifier.");
                            printf("\nAppuyer sur une toucher pour continuer.\n");
                            getchar();
                        }
                    }

                    // On affiche les cocktails
                    system("clear");
                    printf("\t=====================================================================================\n");
                    printf("\t\tCette commande est compose du (des) cocktail(s) suivant(s):\n");
                    printf("\t");
                    if(tabPanier[i].listCommande[l].nbrCocktail != 0){
                        for(int j = 0; j<tabPanier[i].listCommande[l].nbrCocktail; j++){
                            printf("%d. %s",j+1, tabCocktail[tabPanier[i].listCommande[l].listCocktail[j].idCocktail].nom);
                            printf(" x");
                            printf("%d\t", tabPanier[i].listCommande[l].listCocktail[j].quantiteCocktail);
                        }
                    }else{
                        printf("Aucun cocktail commande.\n");
                    }
                    if(tabPanier[i].listCommande[l].nbrCocktail != 0){
                        // On demande a l'utilisateur l'ID du cocktail pour lequel il faut modifier la quantite, et 0 s'il ne veut rien modifier
                        printf("\n\t=====================================================================================\n\n");
                        printf("Entrez 0 pour ne rien modifier.\nEntrez le numero du cocktail pour modifier sa quantite commande:");
                        retour = scanf("%d", &idCocktail);
                        if(retour != 1 || idCocktail < 0 || idCocktail > tabPanier[i].listCommande[l].nbrCocktail){
                            while(retour != 1 || idCocktail < 0 || idCocktail > tabPanier[i].listCommande[l].nbrCocktail){
                                retour = 1;
                                printf("\nCe nombre n'existe pas.\n");
                                printf("Veuillez entrer un nombre valide pour selectionner un cocktail:");
                                getchar();
                                retour = scanf("%d", &idCocktail);
                            }
                        }
                        if(idCocktail != 0){
                            // On demande a l'utilisateur la nouvelle quantite
                            printf("Entrez la nouvelle quantite de cocktail:");
                            retour = scanf("%d", &quantiteCock);
                            if(retour != 1 || quantiteCock < 0 ){
                                while(retour != 1 || quantiteCock < 0){
                                    retour = 1;
                                    printf("\nCe nombre n'existe pas.\n");
                                    printf("Veuillez entrer un nombre valide pour la qauntite de cocktail:");
                                    getchar();
                                    retour = scanf("%d", &quantiteCock);
                                }
                            }
                            
                            for(int k = 0; k < tabPanier[i].listCommande[l].nbrCocktail; k++){
                                if(k == idCocktail-1){
                                    tabPanier[i].listCommande[l].listCocktail[k].quantiteCocktail = quantiteCock;
                                }
                            }
                        }else{
                            printf("\nAucun cocktail a modifier.");
                            printf("\nAppuyer sur une toucher pour continuer.\n");
                            getchar();
                        }
                    }
                }
            }
        }
    }

    // Enfin, on copie les nouvelles informations du tableau dans le fichier
    
    initFichierCommande(T);

}

/*! \fn void suppPanierBoisson(int idBoisson)
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de supprimer un panier si une boisson contenue dans ce panier a été supprimée.
*
*  \param idBoisson : ID de la boisson supprimée.
*
*  \remarks Cette fonction permet de supprimer un panier si l'une des boissons qui le compose a été suprimée.
*/

/*
    Fonction premettant de supprimer un panier si une boisson contenue dans ce panier a été supprimée.
*/
void suppPanierBoisson(int idBoisson){

    int T = tailleTabPanier();

    // On parcours les boissons de chacune des commmandes de chaque panier et si la boisson apparait, on supprime le panier
    if(T > 0){

        for(int i = 0; i < T; i++){
            for(int j = 0; j < tabPanier[i].nbrCommande; j++){
                for(int k = 0; k < tabPanier[i].listCommande[j].nbrBoisson; k++){
                    if(tabPanier[i].listCommande[j].listBoisson[k].idBoisson == idBoisson-1){
                        supprimerPanier(i+1);
                    }
                }
            }
        }
    }
}

/*! \fn void suppPanierCocktail(int idCocktail)
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de supprimer un panier si un cocktail contenu dans ce panier a été supprimé.
*
*  \param idCocktail : ID du cocktail supprimée.
*
*  \remarks Cette fonction permet de supprimer un panier si l'un des cocktails qui le compose a été suprimé.
*/

/*
    Fonction premettant de supprimer un panier si un cocktail contenu dans ce panier a été supprimé.
*/
void suppPanierCocktail(int idCocktail){

    int T = tailleTabPanier();
    
    if(T>0){

        for(int i = 0; i < T; i++){
            for(int j = 0; j < tabPanier[i].nbrCommande; j++){
                for(int k = 0; k < tabPanier[i].listCommande[j].nbrCocktail; k++){
                    if(tabPanier[i].listCommande[j].listCocktail[k].idCocktail == idCocktail-1){
                        supprimerPanier(i+1);
                    }
                }
            }
        }
    }
}

/*! \fn int tailleTabPanier()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant d'obtenir le nombre de paniers.
*
*  \return Cette fonction renvoie le nombre de paniers.
*
*  \remarks Cette fonction permet de récupérer le nombre de paniers, à partir du premier int qui est écrit dans le fichier.
*/

/*
    Fonction premettant d'obtenir le nombre de paniers.
*/
int tailleTabPanier() {

    // On cree une variable pour recuperer la taille.
    int taille = 0;

    // On ouvre le fichier en mode lecture. 
    FILE* file = fopen("data/commandeClient", "rb");

    // On verifie que le fichier s'est bien ouvert. 
    if(file == NULL){

        printf("Fichier non ouvert.");

        exit(-1);

    }

    // On lit la premiere valeur qui apparait, qui correspond au nombre de paniers.
    fread(&taille, sizeof(int), 1, file);

    // On ferme le fichier.
    fclose(file);

    // On retourne le nombre de paniers.
    return taille;

}

/*! \fn int initTabPanier()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant d'initialiser le tableau de paniers.
*/

/*
    Fonction premettant d'initialiser le tableau de paniers.
*/
void initTabPanier() {
    // On cree une variable pour récupérer le nombre de paniers.
    int taille;

    // On ouvre le fichier en mode lecture, avec le parametre "rb".
    FILE* file = fopen("data/commandeClient", "rb");

    // On verifie si le fichier s'est bien ouvert.
    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    // On cree le tableau seulement s'il y a au moins un panier.
    if(fread(&taille, sizeof(int), 1, file)>0) {
        tabPanier = (panier*) malloc(taille*sizeof(panier));
        if(tabPanier == NULL){
            printf("Erreur allocation mémoire. 1");
            exit(-1);
        }

        // On parcoure le fichier et on recopie les informations une par une dans le tableau.
        for(int i=0; i<taille; i++) {
            fread(&tabPanier[i].id, sizeof(int), 1, file);
            fread(&tabPanier[i].nbrCommande, sizeof(int), 1, file);
            fread(&tabPanier[i].prix, sizeof(float), 1, file);
            tabPanier[i].listCommande = (commande*) malloc(tabPanier[i].nbrCommande*sizeof(commande));
            if(tabPanier[i].listCommande == NULL){
                printf("Erreur allocation mémoire. 2");
                exit(-1);
            }
            for(int j = 0; j<tabPanier[i].nbrCommande; j++){
                fread(&tabPanier[i].listCommande[j].nbrBoisson, sizeof(int), 1, file);
                if(tabPanier[i].listCommande[j].nbrBoisson != 0){
                    tabPanier[i].listCommande[j].listBoisson = (listIdBoisson*) malloc(tabPanier[i].listCommande[j].nbrBoisson*sizeof(listIdBoisson));
                    if(tabPanier[i].listCommande[j].listBoisson == NULL){
                        printf("Erreur allocation mémoire. 3");
                        exit(-1);
                    }
                    for(int k = 0; k<tabPanier[i].listCommande[j].nbrBoisson; k++){
                        fread(&tabPanier[i].listCommande[j].listBoisson[k].idBoisson, sizeof(int), 1, file);
                        fread(&tabPanier[i].listCommande[j].listBoisson[k].quantiteBoisson, sizeof(int), 1, file);
                    }
                }else{
                    tabPanier[i].listCommande[j].nbrBoisson = 0;
                }
                fread(&tabPanier[i].listCommande[j].nbrCocktail, sizeof(int), 1, file);
                if(tabPanier[i].listCommande[j].nbrCocktail != 0){
                    tabPanier[i].listCommande[j].listCocktail = (listIdCocktail*) malloc(tabPanier[i].listCommande[j].nbrCocktail*sizeof(listIdCocktail));
                    if(tabPanier[i].listCommande[j].listCocktail == NULL){
                        printf("Erreur allocation mémoire. 4");
                        exit(-1);
                    }
                    for(int k = 0; k<tabPanier[i].listCommande[j].nbrCocktail; k++){
                        fread(&tabPanier[i].listCommande[j].listCocktail[k].idCocktail, sizeof(int), 1, file);
                        fread(&tabPanier[i].listCommande[j].listCocktail[k].quantiteCocktail, sizeof(int), 1, file);
                    }
                }else{
                    tabPanier[i].listCommande[j].nbrCocktail = 0;
                }
                fread(&tabPanier[i].listCommande[j].prix, sizeof(float), 1, file);
            }
        }
    }

    // On ferme le fichier.
    fclose(file);

}

/*! \fn int initTabPanier()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de recopier les informations du tableau vers le fichier.
*
*  \param T : nombre de paniers
*/

/*
    Fonction premettant de recopier les informations du tableau vers le fichier.
*/
void initFichierCommande(int T) {
    // On ouvre le fichier en mode ecriture, avec le parametre "wb". 
    FILE *file = fopen("data/commandeClient","wb");

    // On cree une variable permettant de passer dans tout le tableau et de recopier les informations dans le fichier.
    int i;

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    // On écrit d'abord le nombre de paniers au début du fichier
    fwrite(&T, sizeof(int), 1, file);

    // On parcoure le tableau et on copie les informations dans le fichier.
    for(i=0; i<T; i++) {

        fwrite(&tabPanier[i].id, sizeof(int), 1, file);
        fwrite(&tabPanier[i].nbrCommande, sizeof(int), 1, file);
        fwrite(&tabPanier[i].prix, sizeof(float), 1, file);
        for(int j = 0; j<tabPanier[i].nbrCommande; j++){
            fwrite(&tabPanier[i].listCommande[j].nbrBoisson, sizeof(int), 1, file);
            if(tabPanier[i].listCommande[j].nbrBoisson != 0){
                for(int k = 0; k<tabPanier[i].listCommande[j].nbrBoisson; k++){
                    fwrite(&tabPanier[i].listCommande[j].listBoisson[k].idBoisson, sizeof(int), 1, file);
                    fwrite(&tabPanier[i].listCommande[j].listBoisson[k].quantiteBoisson, sizeof(int), 1, file);
                }
            }
            fwrite(&tabPanier[i].listCommande[j].nbrCocktail, sizeof(int), 1, file);
            if(tabPanier[i].listCommande[j].nbrCocktail != 0){
                for(int k = 0; k<tabPanier[i].listCommande[j].nbrCocktail; k++){
                    fwrite(&tabPanier[i].listCommande[j].listCocktail[k].idCocktail, sizeof(int), 1, file);
                    fwrite(&tabPanier[i].listCommande[j].listCocktail[k].quantiteCocktail, sizeof(int), 1, file);
                }
            }

            fwrite(&tabPanier[i].listCommande[j].prix, sizeof(float), 1, file);
        }
    }

    // On ferme le fichier.
    fclose(file);
}
