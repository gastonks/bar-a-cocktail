#include "boissonClient.h"


void initFileClient(){
    FILE* file = fopen("data/commandeClient", "ab");

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    fclose(file);
}

int idInitPanier(){
   
    // On crée une variable de type panier.    

    panier tmp;

    int nID = 0;
    int taille;

    FILE* file = fopen("data/commandeClient", "rb");

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    fread(&taille, sizeof(int), 1, file);

    while(fread(&tmp, sizeof(panier), 1, file)) {
        nID = tmp.id;
    }

    nID++;

    fclose(file); 
    
    nID = tmp.id + 1;
    fclose(file);  
    return nID;
    
}

void informationBoissonClient(){

    int i;
    int T = tailleTabBarman();

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque boisson.
    for(i = 0; i<T; i++) {
        if(tab[i].quantite > 0){
            printf("\t\t%d\t%s\t%.2f\t\t%.2f\t%.2f\t\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].degreAlco, tab[i].degreScr);
        }
    }

}

void demandeCommande(){

    panier nPanier;
    int retour;
    int nombreId;
    int nombreCocktail;

    nPanier.id = idInitPanier();
    nPanier.prix = 0;

    printf("Combien de commande voulez vous effectuer :");
    retour = scanf("%d", &nPanier.nbrCommande);

    if(retour != 1 || nPanier.nbrCommande < 0 ){
        while(retour != 1 || nPanier.nbrCommande < 0){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer un nombre valide pour soit sortir, soit commander une boisson:");
            getchar();
            retour = scanf("%d", &nPanier.nbrCommande);
        }
    }

    nPanier.listCommande = (commande*) malloc(nPanier.nbrCommande*sizeof(commande));
    if(nPanier.listCommande == NULL){
        printf("Erreur allocation memoire.");
        exit(-1);
    }

    for(int i = 0; i< nPanier.nbrCommande; i++){

        system("clear");
        printf("Commande n.%d\n",i+1);
        printf("=====================================================================================================\n\n");
        printf("\t\t\tMenu Information sur les boissons\n\n");
        printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\n\n");

        informationBoissonClient();

        printf("=====================================================================================================\n\n");

        printf("\nCombien de boisson voulez vous commander :");
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
        if(nPanier.listCommande[i].nbrBoisson != 0){
            
            nPanier.listCommande[i].listBoisson = (listIdBoisson*) malloc(nPanier.listCommande[i].nbrBoisson*sizeof(listIdBoisson));
            if(nPanier.listCommande[i].listBoisson == NULL){
                printf("Erreur allocation memoire.");
                exit(-1);
            }

            nPanier.listCommande[i].prix = 0;  

            for(int j = 0; j<nPanier.listCommande[i].nbrBoisson; j++){

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

                nPanier.listCommande[i].listBoisson[j].idBoisson = nombreId - 1;

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

                nPanier.listCommande[i].prix = nPanier.listCommande[i].prix + (nPanier.listCommande[i].listBoisson[j].quantiteBoisson*tab[nPanier.listCommande[i].listBoisson[j].idBoisson].prix);
            }
        }else{
            nPanier.listCommande[i].prix = nPanier.listCommande[i].prix + 0; 
            nPanier.listCommande[i].nbrBoisson = 0;
        }

        system("clear");
        printf("Commande n.%d\n",i+1);
        printf("=====================================================================================================\n\n");
        printf("\t\t\tMenu Information sur les cocktails\n\n");
        printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tNombre_Boisson\n\n");
        informationCocktailClient();
        printf("=====================================================================================================\n\n");

        printf("\nCombien de cocktail voulez vous commander :");
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

        nPanier.prix = nPanier.prix + nPanier.listCommande[i].prix;
    }

    initCommande(nPanier);

    interfaceClient();
}

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

        // On libere l'espace du tableau de base et on le cree avec une case supplementaire, puis on y recopie toutes les informations avec la
        // nouvelle commande a la fin.


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
    // Sinon, si le fichier ne contient aucune boisson, on cree un tableau avec une seule case où on y copie la nouvelle boisson.
    else {
        tabPanier = malloc(1*sizeof(panier));
        if(tab == NULL){
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
                //nPanier.listCommande[j].nbrCocktail != 0  d'ici
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
            
            //nPanier.listCommande[j].nbrCocktail == 0 à partir d'ici
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

    // On recopie toutes les informations du tableau dans le fichier, en indicant la taille +1 car on a ajoute une boisson.
    initFichierCommande(T+1);
}

void informationCommande(){   

    // On cree des variables, une permettant de parcourir le tableau.
    int i;
    int T = tailleTabPanier();

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque boisson.
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

void modifPanier(int idModif){
    int T = tailleTabPanier();
    int retour = 0;
    int idCommande;
    int idBoisson;
    int quantiteBoiss;
    int idCocktail;
    int quantiteCock;


    for (int i = 0; i < T; i++){
        if(i == idModif-1){
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

            for(int l = 0; l < tabPanier[i].nbrCommande; l++){
                if(l == idCommande-1){
                    system("clear");
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
                    if(tabPanier[i].listCommande[l].listBoisson != 0){
                        printf("Entrez le numero de la boisson pour modifier sa quantite commande:");
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
                        printf("\nAucune boisson a modifier.");
                        printf("\nAppuyer sur une toucher pour continuer.\n");
                        getchar();
                    }

                    system("clear");
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
                    if(tabPanier[i].listCommande[l].nbrCocktail != 0){
                        printf("\n\t=====================================================================================\n\n");
                        printf("Entrez le numero du cocktail pour modifier sa quantite commande:");
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
    
    initFichierCommande(T);


}

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

    // On lit la premiere valeur qui apparait, qui correspond au nombre de boissons.
    fread(&taille, sizeof(int), 1, file);

    // On ferme le fichier.
    fclose(file);

    // On retourne le nombre de boissons.
    return taille;

}

void initTabPanier() {
    // On cree une variable qui va permettre de recopier les informations du fichier.
    int taille;
    //boisson rboisson;

    // On ouvre le fichier en mode lecture, avec le parametre "rb".
    FILE* file = fopen("data/commandeClient", "rb");

    // On verifie si le fichier s'est bien ouvert.
    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }


    // On cree le tableau seulement s'il y a au moins une boisson.
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

void initFichierCommande(int T) {
    // On ouvre le fichier en mode ecriture, avec le parametre "wb", permettant de supprimer le contenu du fichier puis d'ecrire. 
    FILE *file = fopen("data/commandeClient","wb");

    // On cree une variable permettant de passer dans tout le tableau et de recopier les informations dans le fichier.
    int i;

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

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
