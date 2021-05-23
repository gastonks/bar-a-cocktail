/*! \file cocktail.c
*  \author Barre Romain
*  \version 1
*  \brief Programme contenant toutes les fonctions permettant au barman de gérer les cocktails.  
*/

// On inclue le fichier header associé
#include "cocktail.h"

/*! \fn void initFileCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure premettant de vérifier si le fichier des cocktails fonctionne correctement.
*
*  \remarks Cette procédure ouvre le fichier contenant les cocktails, vérifie si le fichier s'est bien ouvert et le referme ensuite. 
*/

/*
    Fonction permettant d'initialiser le fichier devant contenir tous les cocktails et toutes leurs informations associées.
*/
void initFileCocktail(){

    // On ouvre le fichier
    FILE* fileCocktail = fopen("data/cocktail", "ab");

    // On vérifie que le fichier s'est bien ouvert, et on affiche un message d'erreur si ce n'est pas le cas.
    if(fileCocktail == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }
    
    // On ferme le fichier
    fclose(fileCocktail);
}

/*! \fn int idInitCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de donner un ID à un cocktail.
*
*  \return Cette fonction renvoie un ID.
*
*  \remarks Cette fonction vérifie l'ID du cocktail le plus récent puis renvoie ce même ID augmenté de 1. 
*/

/*
    Fonction permettant d'initialiser l'ID des cocktails.
    Cette fonction renvoie une valeur entière, qui correspond à l'ID du dernier cocktail plus 1.
    Cette fonction est utile lors de l'ajout d'un cocktail dans le fichier, permettant ainsi d'attribuer un ID à un nouveau cocktail.
*/
int idInitCocktail(){

    // On crée une variable de type cocktail
    cocktail tmp;

    int nID = 0;
    int taille;

    // On ouvre le fichier et on vérifie qu'il s'est bien ouvert
    FILE* file = fopen("data/cocktail", "rb");
    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    
    // On récupère le nombre de cocktails qui se situ au début du fichier
    fread(&taille, sizeof(int), 1, file);

    // On lie les ID jusqu'à ce qu'on ne puisse plus en lire
    while(fread(&tmp, sizeof(cocktail), 1, file)) {
        nID = tmp.id;
    }

    // On augmente alors l'ID de 1
    nID++;

    // On ferme le fichier
    fclose(file); 

    // On renvoie le nouvel ID  
    return nID;
}

/*! \fn void creationCocktailBarman()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de créer un cocktail, côté barman.
*
*  \remarks Cette fonction permet de créer un cocktail à partir de plusieurs boissons que l'on peut choisir. 
*/

/*
    Fonction permettant de créer un cocktail, côté barman.
*/
void creationCocktailBarman(){

    // On crée une variable de type cocktail qui correspond au cocktail à créer.
    cocktail nCocktail;

    // On crée des variables correspondant aux futurs informations du cocktail
    int nbBoisson = 0;
    int idBoisson = 0;

    int retour = 0;
    int numInter;
    int T = tailleTabBarmanCocktail();

    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu creation d'un cocktail\n\n");

    // On donne le choix à l'utilisateur de revenir en arrière s'il a fait une erreur
    printf("Entrez 0 pour revenir en arrière.\nEntrez 1 pour ajouter le nouveau cocktail:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 1){
        while(retour != 1 || numInter < 0 || numInter > 1){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    if(numInter==0){

        // S'il a entré 0, il revient à l'interface précédente
        interfaceGestionCocktail();

    }else if(numInter == 1){
        
        // Sinon, il entre dans l'interface lui permettant de créer un cocktail

        // On donne un ID au nouveau cocktail
        nCocktail.id = idInitCocktail();

        // On demande à l'utilisateur d'entrer le nom du cocktail
        printf("Veuillez entrer le nom du cocktail :");
        getchar();
        retour = scanf("%[^\n]", nCocktail.nom);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        // On demande à l'utilisateur d'entrer le nombre de boissons composant le cocktail
        printf("Combien de boisson votre cocktail est-il compose :");
        retour = scanf("%d", &nbBoisson);
        if(retour != 1 || nbBoisson < 1){
            while(retour != 1 || nbBoisson < 1){
                retour = 1;
                printf("\nCe nombre de boisson est impossible.\n");
                printf("Veuillez entrer un nombre positif:");
                getchar();
                retour = scanf("%d", &nbBoisson);
            }
        }

        // On initialise toutes les autres informations du cocktail à 0
        nCocktail.prix = 0;
        nCocktail.contenance = 0;
        nCocktail.degreAlco = 0;
        nCocktail.degreScr = 0;
        nCocktail.tailleListBoisson = nbBoisson;

        // On alloue la mémoire pour le tableau contenant les ID des boissons composant le cocktails
        nCocktail.listIdBoisson = (int*) malloc(nbBoisson*sizeof(int));

        if(nCocktail.listIdBoisson == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

        // On affiche toutes les boissons pour que l'utilisateur choisisse les boissons de son cocktail
        printf("=====================================================================================================\n\n");
        printf("\t\t\tMenu Information sur les boissons\n\n");
        printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

        informationBoissonBarman();

        printf("=====================================================================================================\n");

        // On demande à l'utilisateur d'entrer les ID des boissons qu'il veut
        for(int i = 0; i < nbBoisson; i++){
            printf("\nEntrer l'ID de la boisson :");
            retour = scanf("%d", &idBoisson);
            if(retour != 1 || idBoisson < 1 || idBoisson > tailleTabBarman()){
                while(retour != 1 || idBoisson < 1 || idBoisson > tailleTabBarman()){
                    retour = 1;
                    printf("\nCe ID de boisson est impossible.\n");
                    printf("Veuillez entrer un ID de boisson possible:");
                    getchar();
                    retour = scanf("%d", &nbBoisson);
                }
            }else{

                // On ajoute ensuite les informations du cocktails par rapport aux informations des boissons

                nCocktail.listIdBoisson[i] = idBoisson-1;

                nCocktail.prix = nCocktail.prix + tab[idBoisson-1].prix;

                nCocktail.contenance= nCocktail.contenance + tab[idBoisson-1].contenance;
                
                nCocktail.degreAlco = nCocktail.degreAlco + tab[idBoisson-1].degreAlco;
                
                nCocktail.degreScr = nCocktail.degreScr + tab[idBoisson-1].degreScr;
    
            }
        }

        // On augmente ensuite le prix du cocktail de 10% comme demandé dans le projet
        nCocktail.prix = nCocktail.prix + 0.10 * nCocktail.prix;

        /*
            S'il y a deja des cocktails, on cree un second tableau dynamique où on copie toutes les informations de base, et on recree le tableau de base 
            avec une case supplementaire permettant d'ajouter la nouvelle boisson.
        */ 
        if (T>0) {
            // On cree le tableau temporaire et on y copie toutes les informations du tableau de base.
            cocktail* tmp = (cocktail*) malloc(T*sizeof(cocktail));
            if(tmp == NULL){
                    printf("Erreur allocation mémoire. 2");
                    exit(-1);
                }
            for(int i = 0; i<T; i++) {
                tmp[i].id = tabCocktail[i].id;
                strcpy(tmp[i].nom, tabCocktail[i].nom);
                tmp[i].contenance = tabCocktail[i].contenance;
                tmp[i].prix = tabCocktail[i].prix;
                tmp[i].tailleListBoisson = tabCocktail[i].tailleListBoisson;
                tmp[i].degreAlco = tabCocktail[i].degreAlco;
                tmp[i].degreScr = tabCocktail[i].degreScr;
                tmp[i].listIdBoisson = (int*) malloc(tabCocktail[i].tailleListBoisson*sizeof(int));
                if(tmp[i].listIdBoisson == NULL){
                    printf("Erreur allocation mémoire. 3");
                    exit(-1);
                }
                for(int j = 0; j<tabCocktail[i].tailleListBoisson; j++){
                    tmp[i].listIdBoisson[j] = tabCocktail[i].listIdBoisson[j];
                }
            }

            // On libere l'espace du tableau de base et on le cree avec une case supplementaire, puis on y recopie toutes les informations avec le nouveau cocktail

            for(int i = 0;i<T; i++){
                free(tabCocktail[i].listIdBoisson);
            }
            free(tabCocktail);

            tabCocktail = malloc((T+1)*sizeof(cocktail));
            if(tabCocktail == NULL){
                    printf("Erreur allocation mémoire. 4");
                    exit(-1);
                }

            for(int i = 0; i<T; i++) {
                tabCocktail[i].id = tmp[i].id;
                strcpy(tabCocktail[i].nom, tmp[i].nom);
                tabCocktail[i].contenance = tmp[i].contenance;
                tabCocktail[i].prix = tmp[i].prix;
                tabCocktail[i].degreAlco = tmp[i].degreAlco;
                tabCocktail[i].tailleListBoisson = tmp[i].tailleListBoisson;
                tabCocktail[i].degreScr = tmp[i].degreScr;
                tabCocktail[i].listIdBoisson = (int*) malloc(tmp[i].tailleListBoisson*sizeof(int));
                if( tabCocktail[i].listIdBoisson == NULL){
                    printf("Erreur allocation mémoire. 5");
                    exit(-1);
                }
                for(int j = 0; j<tmp[i].tailleListBoisson; j++){
                    tabCocktail[i].listIdBoisson[j] = tmp[i].listIdBoisson[j];
                }
            }

            tabCocktail[T].id = nCocktail.id;
            strcpy(tabCocktail[T].nom, nCocktail.nom);
            tabCocktail[T].contenance = nCocktail.contenance;
            tabCocktail[T].prix = nCocktail.prix;
            tabCocktail[T].tailleListBoisson = nCocktail.tailleListBoisson;
            tabCocktail[T].degreAlco = nCocktail.degreAlco;
            tabCocktail[T].degreScr = nCocktail.degreScr;
            tabCocktail[T].listIdBoisson = (int*) malloc(nCocktail.tailleListBoisson*sizeof(int));
            if(tabCocktail[T].listIdBoisson == NULL){
                    printf("Erreur allocation mémoire. 6");
                    exit(-1);
            }
            for(int j = 0; j<nCocktail.tailleListBoisson; j++){
                tabCocktail[T].listIdBoisson[j] = nCocktail.listIdBoisson[j];
            }

            // On libere l'espace du tableau temporaire.
            for(int i = 0;i<T; i++){
                free(tmp[i].listIdBoisson);
            }
            free(tmp);
        } 
        // Sinon, si le fichier ne contient aucune boisson, on cree un tableau avec une seule case où on y copie le nouveau cocktail.
        else {
            tabCocktail = (cocktail*) malloc(1*sizeof(cocktail));
            if(tabCocktail == NULL){
                printf("Erreur allocation mémoire. 7");
                exit(-1);
            }
            tabCocktail[0].id = nCocktail.id;
            strcpy(tabCocktail[0].nom, nCocktail.nom);
            tabCocktail[0].contenance = nCocktail.contenance;
            tabCocktail[0].prix = nCocktail.prix;
            tabCocktail[0].tailleListBoisson = nCocktail.tailleListBoisson;
            tabCocktail[0].degreAlco = nCocktail.degreAlco;
            tabCocktail[0].degreScr = nCocktail.degreScr;
            tabCocktail[0].listIdBoisson = (int*) malloc(nCocktail.tailleListBoisson*sizeof(int));
            if(tabCocktail[0].listIdBoisson == NULL){
                    printf("Erreur allocation mémoire. 8");
                    exit(-1);
                }
            for(int j = 0; j<nCocktail.tailleListBoisson; j++){
                tabCocktail[0].listIdBoisson[j] = nCocktail.listIdBoisson[j];
            }
        }

        // On recopie toutes les informations du tableau dans le fichier, en indicant la taille +1 car on a ajoute une boisson.
        initFichierCocktail(T+1);
        

        interfaceGestionCocktail();
    }else{
        printf("Erreur dans le choix de l'interface.");
        exit(-1);
    }
}

/*! \fn void creationCocktailClient()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de créer un cocktail, côté client.
*
*  \remarks Cette fonction permet de créer un cocktail à partir de plusieurs boissons que l'on peut choisir. 
*  Cette fonction est exactement la même que creationCocktailBarman, à la seule différence que le client ne voit que les boissons qui sont en stock, au moment où il doit choisir les boissons de son cocktail.
*/

/*
    Fonction permettant de créer un cocktail, côté client.
    Cette fonction est exactement la même que creationCocktailBarman, à la seule différence que le client ne voit que les boissons qui sont en stock, au moment où il doit choisir les boissons de son cocktail.
*/
void creationCocktailClient(){

    cocktail nCocktail;

    int nbBoisson = 0;
    int idBoisson = 0;

    int retour = 0;
    int numInter;
    int T = tailleTabBarmanCocktail();

    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu creation d'un cocktail\n\n");
    
    printf("Entrez 0 pour revenir en arrière.\nEntrez 1 pour ajouter le nouveau cocktail:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 1){
        while(retour != 1 || numInter < 0 || numInter > 1){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    if(numInter==0){

        interfaceGestionCocktail();

    }else if(numInter == 1){

    nCocktail.id = idInitCocktail();

    printf("Veuillez entrer le nom du cocktail :");
    getchar();
    retour = scanf("%[^\n]", nCocktail.nom);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Combien de boisson votre cocktail est-il compose :");

    retour = scanf("%d", &nbBoisson);
    if(retour != 1 || nbBoisson < 1){
        while(retour != 1 || nbBoisson < 1){
            retour = 1;
            printf("\nCe nombre de boisson est impossible.\n");
            printf("Veuillez entrer un nombre positif:");
            getchar();
            retour = scanf("%d", &nbBoisson);
        }
    }

    nCocktail.prix = 0,
    nCocktail.contenance = 0,
    nCocktail.degreAlco = 0,
    nCocktail.degreScr = 0;

    nCocktail.listIdBoisson = (int*) malloc(nbBoisson*sizeof(int));

    nCocktail.tailleListBoisson = nbBoisson;

    if(nCocktail.listIdBoisson){
        printf("\nErreur d'allocation de memoire.\n");
        exit(-1);
    }

    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\n\n");

    informationBoissonClient();

    printf("=====================================================================================================\n");

    for(int i = 0; i < nbBoisson; i++){
        printf("\nEntrer l'ID de la boisson :");
        retour = scanf("%d", &idBoisson);
        if(retour != 1 || idBoisson < 1){
            while(retour != 1 || idBoisson < 1){
                retour = 1;
                printf("\nCe ID de boisson est impossible.\n");
                printf("Veuillez entrer un ID de boisson possible:");
                getchar();
                retour = scanf("%d", &nbBoisson);
            }
        }else{
            nCocktail.listIdBoisson[i] = idBoisson-1;
            nCocktail.prix = nCocktail.prix + tab[idBoisson-1].prix;
            nCocktail.contenance= nCocktail.contenance + tab[idBoisson-1].contenance;
            nCocktail.degreAlco = nCocktail.degreAlco + tab[idBoisson-1].degreAlco;
            nCocktail.degreScr = nCocktail.degreScr + tab[idBoisson-1].degreScr;
        }
    }

   
    nCocktail.prix = nCocktail.prix + 0.10 * nCocktail.prix;

    if (T>0) {
        cocktail* tmp = (cocktail*) malloc(T*sizeof(cocktail));
        if(tmp == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

        for(int i = 0; i<T; i++) {
            tmp[i].id = tabCocktail[i].id;
            strcpy(tmp[i].nom, tabCocktail[i].nom);
            tmp[i].contenance = tabCocktail[i].contenance;
            tmp[i].prix = tabCocktail[i].prix;
            tmp[i].tailleListBoisson = tabCocktail[i].tailleListBoisson;
            tmp[i].degreAlco = tabCocktail[i].degreAlco;
            tmp[i].degreScr = tabCocktail[i].degreScr;
            tmp[i].listIdBoisson = (int*) malloc(tabCocktail[i].tailleListBoisson*sizeof(int));
            if(tmp[i].listIdBoisson == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
            for(int j = 0; j<tabCocktail[i].tailleListBoisson; j++){
                tmp[i].listIdBoisson[j] = tabCocktail[i].listIdBoisson[j];
            }
        }

        free(tabCocktail);
        tabCocktail = malloc((T+1)*sizeof(cocktail));
        if(tabCocktail == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

        for(int i = 0; i<T; i++) {
            tabCocktail[i].id = tmp[i].id;
            strcpy(tabCocktail[i].nom, tmp[i].nom);
            tabCocktail[i].contenance = tmp[i].contenance;
            tabCocktail[i].prix = tmp[i].prix;
            tabCocktail[i].tailleListBoisson = tmp[i].tailleListBoisson;
            tabCocktail[i].degreAlco = tmp[i].degreAlco;
            tabCocktail[i].degreScr = tmp[i].degreScr;
            tabCocktail[i].listIdBoisson = (int*) malloc(tmp[i].tailleListBoisson*sizeof(int));
            if(tabCocktail[i].listIdBoisson == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
            for(int j = 0; j<tmp[i].tailleListBoisson; j++){
                tabCocktail[i].listIdBoisson[j] = tmp[i].listIdBoisson[j];
            }
        }

        tabCocktail[T].id = nCocktail.id;
        strcpy(tabCocktail[T].nom, nCocktail.nom);
        tabCocktail[T].contenance = nCocktail.contenance;
        tabCocktail[T].prix = nCocktail.prix;
        tabCocktail[T].tailleListBoisson = nCocktail.tailleListBoisson;
        tabCocktail[T].degreAlco = nCocktail.degreAlco;
        tabCocktail[T].degreScr = nCocktail.degreScr;
        tabCocktail[T].listIdBoisson = (int*) malloc(nCocktail.tailleListBoisson*sizeof(int));
        if(tabCocktail[T].listIdBoisson == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
        }
        for(int j = 0; j<nCocktail.tailleListBoisson; j++){
            tabCocktail[T].listIdBoisson[j] = nCocktail.listIdBoisson[j];
        }

        free(tmp);
    } 
    else {
        tabCocktail = malloc(1*sizeof(cocktail));
        if(tabCocktail == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }
        tabCocktail[0].id = nCocktail.id;
        strcpy(tabCocktail[0].nom, nCocktail.nom);
        tabCocktail[0].contenance = nCocktail.contenance;
        tabCocktail[0].prix = nCocktail.prix;
        tabCocktail[0].tailleListBoisson = nCocktail.tailleListBoisson;
        tabCocktail[0].degreAlco = nCocktail.degreAlco;
        tabCocktail[0].degreScr = nCocktail.degreScr;
        tabCocktail[0].listIdBoisson = (int*) malloc(nCocktail.tailleListBoisson*sizeof(int));
        if(tabCocktail[0].listIdBoisson == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
        for(int j = 0; j<nCocktail.tailleListBoisson; j++){
            tabCocktail[0].listIdBoisson[j] = nCocktail.listIdBoisson[j];
        }
    } 

    initFichierCocktail(T+1);

    interfaceGestionCocktail();
    }else{
        printf("Erreur dans le choix de l'interface.");
        exit(-1);
    }
}

/*! \fn void informationCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant d'afficher les cocktails et leurs informations.
*/

/*
    Fonction permettant d'afficher les informations des cocktails
*/
void informationCocktail(){

    // On cree des variables permettant de parcourir le tableau de cocktails, et les tableaux de boissons associée aux cocktails.
    int i;
    int j;
    int T = tailleTabBarmanCocktail();

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque cocktail.
    for(i = 0; i<T; i++) {
        printf("\t\t%d\t%s\t%.2f\t\t%.2f\t%.2f\t\t%.2f\t\t%.2d\n", i+1, tabCocktail[i].nom, tabCocktail[i].contenance, tabCocktail[i].prix, tabCocktail[i].degreAlco, tabCocktail[i].degreScr,  tabCocktail[i].tailleListBoisson);

        printf("\t\t=====================================================================================\n");
        printf("\t\t\tCe cocktail est compose de(s) la (les) boisson(s) suivante(s):\n");
        printf("\t\t");
        for(j = 0; j<tabCocktail[i].tailleListBoisson; j++){
            printf("%s\t",tab[tabCocktail[i].listIdBoisson[j]].nom);
        }
        printf("\n\t\t=====================================================================================\n\n");
    }
}

/*! \fn void informationCocktailClient()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant d'afficher les cocktails et leurs informations, à la seule différence que seule les cocktails ayant du stock sont affichés.
*/

/*
    Fonction premettant d'afficher les cocktails et leurs informations, à la seule différence que seule les cocktails ayant du stock sont affichés
*/
void informationCocktailClient(){

    int i;
    int quantiteZero = 0;
    int T = tailleTabBarmanCocktail();

    for(i = 0; i<T; i++) {
        quantiteZero = 0;
        for(int j = 0; j<tabCocktail[i].tailleListBoisson; j++){
            if(tab[tabCocktail[i].listIdBoisson[j]].quantite == 0){
                quantiteZero++;
            }
        }
        if(quantiteZero == 0 ){
            printf("\t\t%d\t%s\t%.2f\t\t%.2f\t%.2f\t\t%.2f\t\t%.2d\n", i+1, tabCocktail[i].nom, tabCocktail[i].contenance, tabCocktail[i].prix, tabCocktail[i].degreAlco, tabCocktail[i].degreScr,  tabCocktail[i].tailleListBoisson);
        
            printf("\t\t=====================================================================================\n");
            printf("\t\t\tCe cocktail est compose de(s) la (les) boisson(s) suivante(s):\n");
            printf("\t\t");
            for(int j = 0; j<tabCocktail[i].tailleListBoisson; j++){
                printf("%s\t",tab[tabCocktail[i].listIdBoisson[j]].nom);
            }
            printf("\n\t\t=====================================================================================\n\n");
        }
    }
}

/*! \fn void supprimerCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de supprimer un cocktail.
*
*  \param idCocktail : ID du cocktail à supprimer
*
*  \remarks Cette fonction permet de supprimer un cocktail. 
*/

/*
    Fonction permettant de supprimer un cocktail.
*/
void supprimerCocktail(int idCocktail){

    /*
        Cette partie est similaire a l'ajout d'une boisson, sauf qu'au lieu d'augmenter la taille du tableau, on la diminue.
        On cree un tableau temporaire où on copie toutes les informations du tableau de base, on recree le tableau de base avec une case en moins, 
        puis on recopie toutes les informations dans le tableau de base sans le cocktail a supprimer.
    */

    // On cree des variables pour stocker la taille du tableau et pour gerer la boucle permettant de recopier les valeurs d'un tableau a l'autre.
    int T = tailleTabBarmanCocktail();
    int j = 0;
    int h = 0;

    // Si le tableau contient plus d'un cocktail, on fait l'operation enoncee precedemment, sinon on libere simplement l'espace du tableau.
    if(T>1) {
        // On cree le tableau temporaire et on y copie toutes les informations du tableau de base.
        cocktail* tmp = (cocktail*) malloc(T*sizeof(cocktail));
        if(tmp == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
        }
        for(int i = 0; i<T; i++) {
            tmp[i].id = tabCocktail[i].id;
            strcpy(tmp[i].nom, tabCocktail[i].nom);
            tmp[i].contenance = tabCocktail[i].contenance;
            tmp[i].prix = tabCocktail[i].prix;
            tmp[i].tailleListBoisson = tabCocktail[i].tailleListBoisson;
            tmp[i].degreAlco = tabCocktail[i].degreAlco;
            tmp[i].degreScr = tabCocktail[i].degreScr;
            tmp[i].listIdBoisson = (int*) malloc(tabCocktail[i].tailleListBoisson*sizeof(int));
            if( tmp[i].listIdBoisson == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
            for(int j = 0; j<tabCocktail[i].tailleListBoisson; j++){
                tmp[i].listIdBoisson[j] = tabCocktail[i].listIdBoisson[j];
            }
        }

        // On libere l'espace du tableau de base et on le recree avec une case en moins.
        free(tabCocktail);
        tabCocktail = (cocktail*) malloc((T-1)*sizeof(cocktail));
        if(tabCocktail == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

        // On recopie toutes les informations dans le tableau de base, et si on est situe sur la valeur a supprimer, on ne la recopie tout simplement pas.
        while(j<T) {
            if(j != idCocktail-1) {
                
                tabCocktail[h].id = tmp[j].id;
                strcpy(tabCocktail[h].nom, tmp[j].nom);
                tabCocktail[h].contenance = tmp[j].contenance;
                tabCocktail[h].prix = tmp[j].prix;
                tabCocktail[h].tailleListBoisson = tmp[j].tailleListBoisson;
                tabCocktail[h].degreAlco = tmp[j].degreAlco;
                tabCocktail[h].degreScr = tmp[j].degreScr;
                tabCocktail[h].listIdBoisson = (int*) malloc(tmp[j].tailleListBoisson*sizeof(int));
                if(tabCocktail[h].listIdBoisson == NULL){
                    printf("Erreur allocation mémoire.");
                    exit(-1);
                }
                for(int k = 0; k<tmp[j].tailleListBoisson; k++){
                    tabCocktail[h].listIdBoisson[k] = tmp[j].listIdBoisson[k];
                }
                h++;
                j++;
            } else {
                j++;
            }
        }
    // S'il n'y a qu'un seul cocktail et que l'ID a supprimer est 1 (le seul possible) alors on libere simplement l'espace du tableau.
    }   else if (T==1 && idCocktail==1) {
        free(tabCocktail);
    }

    suppPanierCocktail(idCocktail);

    // On recopie le tableau dans le fichier
    initFichierCocktail(T-1);

}

/*! \fn void supprimerCocktailDemande()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant choisir le cocktail à supprimer.
*
*  \remarks Cette fonction permet de choisir le cocktail à supprimer. 
*/

/*
    Fonction premettant choisir le cocktail à supprimer.
*/
void supprimerCocktailDemande(){

    int idSupp = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les cocktails\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationCocktail();

    printf("=====================================================================================================\n\n");

    // On demande a l'utilisateur d'entrer l'ID du cocktail qu'il desire supprimer. On verifie aussi s'il y a eu une erreur dans la saisie.
    printf("Entrer l'ID de la boisson a supprimer (0 pour revenir en arriere):");
    retour = scanf("%d", &idSupp);

    if(retour != 1 || idSupp < 0){
        while(retour != 1 || idSupp < 0 || idSupp > tailleTabBarman()){
                retour = 1;
                printf("Cet ID de boisson est impossible.\n");
                printf("Veuillez entrer un ID de boisson possible:");
                getchar();
                retour = scanf("%d", &idSupp);
            }
    }

    // En entrant 0, l'utilisateur a la possibilite de retourner a l'interface precedente.
    // Sinon, la fonction de suppression s'execute.
    if(idSupp == 0) {
        interfaceGestionCocktail();
    }else{   
        supprimerCocktail(idSupp);
    }
}

/*! \fn void suppCocktailBoisson(int idBoisson)
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de supprimer un cocktail si une des boissons qui le compoe a été supprimée.
*
*  \param idCocktail : ID de la boisson supprimée.
*
*  \remarks Cette fonction permet de supprimer un cocktail si l'une des boissons qui le compose a été suprimée.
*/

/*
    Fonction premettant de supprimer un cocktail si une des boissons qui le compoe a été supprimée.
*/
void suppCocktailBoisson(int idBoisson){

    int T = tailleTabBarmanCocktail();

    if(T > 0){

        for(int i = 0; i < T; i++){
            for(int j = 0; j < tabCocktail[i].tailleListBoisson; j++){
                if(tabCocktail[i].listIdBoisson[j] == idBoisson-1){
                    supprimerCocktail(i+1);
                }
            }
        }
    }
}

/*! \fn int tailleTabBarmanCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de récupérer le nombre de cocktails à partir du fichier de sauvegarde des cocktails.
*
*  \return Cette fonction renvoie le nombre de cocktails.
*/

/*
    Fonction permettant de calculer le nombre de cocktail qu'il y a dans le fichier.
    Cette fonction renvoie un entier.
*/
int tailleTabBarmanCocktail() {

    // On cree une variable pour recuperer la taille.
    int taille = 0;

    // On ouvre le fichier en mode lecture. 
    FILE* file = fopen("data/cocktail", "rb");

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

/*! \fn int initTabCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de créer le tableau de cocktails.
*
*  \remarks Cette fonction permet de créer le tableau de cocktails, en récupérant le nombre de cocktails au début du fichier puis en lisant toutes les informations du fichier.
*/

/*
    Fonction permettant d'initialiser le tableau contenant les cocktails.
*/
void initTabCocktail() {

    // On crée une variable qui va contenir la taille.
    int taille;
    
    // On ouvre le fichier en mode lecture, avec le parametre "rb".
    FILE* file = fopen("data/cocktail", "rb");

    // On verifie si le fichier s'est bien ouvert.
    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    // On cree le tableau seulement s'il y a au moins un cocktail.
    if(fread(&taille, sizeof(int), 1, file)>0) {
        tabCocktail = (cocktail*) malloc(taille*sizeof(cocktail));
        if(tabCocktail == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }

        // On parcoure le fichier et on recopie les informations une par une dans le tableau.
        for(int k = 0; k<taille; k++){
            fread(&tabCocktail[k].id, sizeof(int), 1, file);
            fread(tabCocktail[k].nom, sizeof(char), N, file);
            fread(&tabCocktail[k].tailleListBoisson, sizeof(int), 1, file);
            tabCocktail[k].listIdBoisson = (int*) malloc(tabCocktail[k].tailleListBoisson*sizeof(int));
            if(tabCocktail[k].listIdBoisson == NULL){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
            for (int l = 0; l < tabCocktail[k].tailleListBoisson; l++)
            {
                fread(&tabCocktail[k].listIdBoisson[l], sizeof(int), 1, file);
            }
            
            
            fread(&tabCocktail[k].contenance, sizeof(float), 1, file);
            fread(&tabCocktail[k].prix, sizeof(float), 1, file);
            fread(&tabCocktail[k].degreAlco, sizeof(float), 1, file);
            fread(&tabCocktail[k].degreScr, sizeof(float), 1, file);

        }
    }

    // On ferme le fichier.
    fclose(file);

}

/*! \fn int initFichierCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de recopier les informations du tableau vers le fichier.
*
*  \param T : nombre de cocktails
*
*  \remarks Cette fonction permet de recopier les informations du tableau de cocktails vers le fichier de sauvegarde.
*/

/*
    Fonction permettant d'initialiser le fichier.
    Elle est utilisee souvent apres avoir modifier une informations dans le tableau.
*/
void initFichierCocktail(int T) {
    // On ouvre le fichier en mode ecriture, avec le parametre "wb", permettant de supprimer le contenu du fichier puis d'ecrire. 
    FILE *file = fopen("data/cocktail","wb");

    // On cree une variable permettant de passer dans tout le tableau et de recopier les informations dans le fichier.
    int i;

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    fwrite(&T, sizeof(int), 1, file);


    // On parcoure le tableau et on copie les informations dans le fichier.
    for(i=0; i<T; i++) {
        fwrite(&tabCocktail[i].id, sizeof(int), 1, file);
        fwrite(&tabCocktail[i].nom, sizeof(char), N, file);
        fwrite(&tabCocktail[i].tailleListBoisson, sizeof(int), 1, file);
        for (int l = 0; l < tabCocktail[i].tailleListBoisson; l++)
        {
            fwrite(&tabCocktail[i].listIdBoisson[l], sizeof(int), 1, file);
        }   
        fwrite(&tabCocktail[i].contenance, sizeof(float), 1, file);
        fwrite(&tabCocktail[i].prix, sizeof(float), 1, file);
        fwrite(&tabCocktail[i].degreAlco, sizeof(float), 1, file);
        fwrite(&tabCocktail[i].degreScr, sizeof(float), 1, file);
    }

    // On ferme le fichier.
    fclose(file);
}