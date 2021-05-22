
#include "cocktail.h"


void initFileCocktail(){
    FILE* fileCocktail = fopen("data/cocktail", "ab");

    if(fileCocktail == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }
    
    fclose(fileCocktail);
}

int idInitCocktail(){
    cocktail tmp;

    int nID = 0;
    int taille;

    FILE* file = fopen("data/cocktail", "rb");
    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    
    fread(&taille, sizeof(int), 1, file);

    while(fread(&tmp, sizeof(cocktail), 1, file)) {
        nID = tmp.id;
    }

    nID++;

    fclose(file);   
    return nID;
}

void creationCocktailBarman(){

    cocktail nCocktail;

    int nbBoisson = 0;
    int idBoisson = 0;
    int retour = 0;
    int T = tailleTabBarmanCocktail();

    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu creation d'un cocktail\n\n");

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

    nCocktail.prix = 0;
    nCocktail.contenance = 0;
    nCocktail.degreAlco = 0;
    nCocktail.degreScr = 0;
    nCocktail.tailleListBoisson = nbBoisson;

    nCocktail.listIdBoisson = (int*) malloc(nbBoisson*sizeof(int));

    if(nCocktail.listIdBoisson == NULL){
        printf("\nErreur d'allocation de memoire. 1\n");
        exit(-1);
    }

    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("=====================================================================================================\n");

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
            nCocktail.listIdBoisson[i] = idBoisson-1;

            nCocktail.prix = nCocktail.prix + tab[idBoisson-1].prix;

            nCocktail.contenance= nCocktail.contenance + tab[idBoisson-1].contenance;
            
            nCocktail.degreAlco = nCocktail.degreAlco + tab[idBoisson-1].degreAlco;
            
            nCocktail.degreScr = nCocktail.degreScr + tab[idBoisson-1].degreScr;
   
        }
    }

    nCocktail.prix = nCocktail.prix + 0.10 * nCocktail.prix;

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

        // On libere l'espace du tableau de base et on le cree avec une case supplementaire, puis on y recopie toutes les informations avec la
        // nouvelle boisson a la fin.
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
    // Sinon, si le fichier ne contient aucune boisson, on cree un tableau avec une seule case où on y copie la nouvelle boisson.
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
}

void creationCocktailClient(){

    cocktail nCocktail;

    int nbBoisson = 0;
    int idBoisson = 0;
    int retour = 0;
    int T = tailleTabBarmanCocktail();

    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu creation d'un cocktail\n\n");

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
        // On cree le tableau temporaire et on y copie toutes les informations du tableau de base.
        cocktail* tmp = (cocktail*) malloc(T*sizeof(cocktail));
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

        // On libere l'espace du tableau de base et on le cree avec une case supplementaire, puis on y recopie toutes les informations avec la
        // nouvelle boisson a la fin.
        free(tabCocktail);
        tabCocktail = malloc((T+1)*sizeof(cocktail));

        for(int i = 0; i<T; i++) {
            tabCocktail[i].id = tmp[i].id;
            strcpy(tabCocktail[i].nom, tmp[i].nom);
            tabCocktail[i].contenance = tmp[i].contenance;
            tabCocktail[i].prix = tmp[i].prix;
            tabCocktail[i].tailleListBoisson = tmp[i].tailleListBoisson;
            tabCocktail[i].degreAlco = tmp[i].degreAlco;
            tabCocktail[i].degreScr = tmp[i].degreScr;
            tabCocktail[i].listIdBoisson = (int*) malloc(tmp[i].tailleListBoisson*sizeof(int));
            if(tabCocktail[i].listIdBoisson){
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

        // On libere l'espace du tableau temporaire.
        free(tmp);
    } 
    // Sinon, si le fichier ne contient aucune boisson, on cree un tableau avec une seule case où on y copie la nouvelle boisson.
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
        if(tabCocktail[0].listIdBoisson){
                printf("Erreur allocation mémoire.");
                exit(-1);
            }
        for(int j = 0; j<nCocktail.tailleListBoisson; j++){
            tabCocktail[0].listIdBoisson[j] = nCocktail.listIdBoisson[j];
        }
    } 

    // On recopie toutes les informations du tableau dans le fichier, en indicant la taille +1 car on a ajoute une boisson.
    initFichierCocktail(T+1);



    interfaceGestionCocktail();
}

void informationCocktail(){

    // On cree des variables, une permettant de parcourir le tableau et l'autre qui contient le nombre de boissons.
    int i;
    int j;
    int T = tailleTabBarmanCocktail();

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque boisson.
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

void informationCocktailClient(){

    // On cree des variables, une permettant de parcourir le tableau et l'autre qui contient le nombre de boissons.
    int i;
    int quantiteZero = 0;
    int T = tailleTabBarmanCocktail();

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque boisson.
    for(i = 0; i<T; i++) {
        for(int j = 0; j<tabCocktail[i].tailleListBoisson; j++){
            quantiteZero = 0;
            if(tab[tabCocktail[i].listIdBoisson[j]].quantite == 0){
                quantiteZero++;
            }
        }
        if(quantiteZero != 0 ){
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


void supprimerCocktail(int idCocktail){

    /*
        Cette partie est similaire a l'ajout d'une boisson, sauf qu'au lieu d'augmenter la taille du tableau, on la dominue.
        On cree un tableau temporaire où on copie toutes les informations du tableau de base, on recree le tableau de base avec une case en moins, 
        puis on recopie toutes les informations dans le tableau de base sans la boisson a supprimer.
    */

    // On cree des variables pour stocker la taille du tableau et pour gerer la boucle permettant de recopier les valeurs d'un tableau a l'autre.
    int T = tailleTabBarmanCocktail();
    int j = 0;
    int h = 0;

    // Si le tableau contient plus d'une boisson, on fait l'operation enoncee precedemment, sinon on libere simplement l'espace du tableau.
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
    // S'il n'y a qu'une seule boisson et que l'ID a supprimer est 1 (le seul possible) alors on libere simplement l'espace du tableau.
    }   else if (T==1 && idCocktail==1) {
        free(tabCocktail);
    }

    // On recopie le tableau dans le fichier
    initFichierCocktail(T-1);

    // On retourne a l'interface precedente.
    interfaceGestionCocktail();


}


void supprimerCocktailDemande(){

    int idSupp = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les cocktails\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationCocktail();

    printf("=====================================================================================================\n\n");

    printf("Entrer l'ID du cocktail a supprimer :");
    retour = scanf("%d", &idSupp);

    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    if(idSupp == 0){
        while(idSupp == 0){
            printf("ID impossible a supprimer.\nEntrer un nouveau ID :");
            retour = scanf("%d", &idSupp);
        }
    }

    supprimerCocktail(idSupp);

    //interfaceGestionCocktail();

}

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
/*
    Fonction permettant d'initialiser le tableau contenant les boissons.
*/
void initTabCocktail() {
    // On cree une variable qui va permettre de recopier les informations du fichier.
    //int i = 0;
    int taille;
    //cocktail initCocktail;

    // On ouvre le fichier en mode lecture, avec le parametre "rb".
    FILE* file = fopen("data/cocktail", "rb");

    // On verifie si le fichier s'est bien ouvert.
    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    // On cree le tableau seulement s'il y a au moins une boisson.
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