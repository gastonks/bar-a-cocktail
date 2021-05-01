/*
    Ce fichier contient toutes les fonctions liées au fonctionnement de l'interface du barman.
*/

// On inclue le fichier header associé
#include "boissonBarman.h"

// Macros permettant une utilisation plus facile et plus rapide du format dans l'utilisation de fscanf et fprintf, pour les boissons.
const char* BOISSON_FORMAT_OUT = "(%s, %.2f, %.2f, %.2f, %.2f, %.2f)\n";
const char* BOISSON_FORMAT_IN = "(%[^,], %f, %f, %f, %f, %f)";

// Macros permettant une utilisation plus facile et plus rapide du format dans l'utilisation de fscanf et fprintf, pour les commandes.
const char* COMMANDE_FORMAT_OUT = "(%d, %s, %.2f, %.2f)\n";
const char* COMMANDE_FORMAT_IN = "(%d, %[^,], %f, %f)";

/*
    Fonction permettant d'initialiser le fichier devant contenir toutes les boissons et toutes leurs informations associées.
    Cette fonction a pour simple but de vérifier si le fichier a bien été initialisé.
*/
void initFileBarman(){
    // On crée une variable de type FILE, permettant de manipuler le fichier, et on l'ouvre avec le paramètre "a", qui permet d'ajouter des informations
    // directement après le bas du fichier.
    FILE* file = fopen("data/boissonBarman.dat", "a");

    // On vérifie si le fichier a bien été ouvert, et on arrete le programme s'il y a une erreur. 
    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    
    // On ferme le fichier, après avoir vérifié qu'il était bien initialisé.
    fclose(file);
}

/*
    Fonction permettant d'ajouter une boisson alcoolisée.
*/
void ajoutBoissonAlcool(){

    // On créer une variable de type boisson, qui sera ajouté au fichier après avoir récupéré toutes ses informations.
    boisson nouvBoisson;

    /*
        On demande à l'utilisateur d'entrer les informations de la boisson une par une, sauf le degré de sucre que l'on met automatiquement à 0, 
        puisqu'il s'agit d'une boisson alcoolisée.
    */

    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\tMenu de l'ajout d'une boisson\n\n");

    printf("Veuillez entrer le nom de la boisson :");
    getchar();
    retour = scanf("%[^\n]", nouvBoisson.nom);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer la contenance de la boisson :");
    retour = scanf("%f", &nouvBoisson.contenance);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le prix de la boisson :");
    retour = scanf("%f", &nouvBoisson.prix);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer la quantite de boisson :");
    retour = scanf("%f", &nouvBoisson.quantite);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le degre d'alcool de cette boisson :");
    retour = scanf("%f", &nouvBoisson.degreAlco);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    nouvBoisson.degreScr = 0.00;

    // On récupère le nombre de boissons qu'il existe déjà dans le fichier.
    int T = calcTailleFichier();
    
    // On dissocie deux cas, s'il existe déjà des boissons, ou si le fichier est vide.

    /*
        S'il y a déjà des boissons, on crée un second tableau dynamique où on copie toutes les informations de base, et on recrée le tableau de base 
        avec une case supplémentaire permettant d'ajouter la nouvelle boisson.
    */ 
    if (T>0) {
        // On crée le tableau temporaire et on y copie toutes les informations du tableau de base.
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            strcpy(tmp[i].nom, tab[i].nom);
            tmp[i].contenance = tab[i].contenance;
            tmp[i].prix = tab[i].prix;
            tmp[i].quantite = tab[i].quantite;
            tmp[i].degreAlco = tab[i].degreAlco;
            tmp[i].degreScr = tab[i].degreScr;
        }

        // On libère l'espace du tableau de base et on le crée avec une case supplémentaire, puis on y recopie toutes les informations avec la
        // nouvelle boisson à la fin.
        free(tab);
        tab = malloc((T+1)*sizeof(boisson));

        for(int i = 0; i<T; i++) {
            strcpy(tab[i].nom, tmp[i].nom);
            tab[i].contenance = tmp[i].contenance;
            tab[i].prix = tmp[i].prix;
            tab[i].quantite = tmp[i].quantite;
            tab[i].degreAlco = tmp[i].degreAlco;
            tab[i].degreScr = tmp[i].degreScr;
        }

        strcpy(tab[T].nom, nouvBoisson.nom);
        tab[T].contenance = nouvBoisson.contenance;
        tab[T].prix = nouvBoisson.prix;
        tab[T].quantite = nouvBoisson.quantite;
        tab[T].degreAlco = nouvBoisson.degreAlco;
        tab[T].degreScr = nouvBoisson.degreScr;

        // On libère l'espace du tableau temporaire.
        free(tmp);
    } 
    // Sinon, si le fichier ne contient aucune boisson, on crée un tableau avec une seule case où on y copie la nouvelle boisson.
    else {
        tab = malloc(1*sizeof(boisson));
        strcpy(tab[0].nom, nouvBoisson.nom);
        tab[0].contenance = nouvBoisson.contenance;
        tab[0].prix = nouvBoisson.prix;
        tab[0].quantite = nouvBoisson.quantite;
        tab[0].degreAlco = nouvBoisson.degreAlco;
        tab[0].degreScr = nouvBoisson.degreScr;
    }

    // On recopie toutes les informations du tableau dans le fichier, en indicant la taille +1 car on a ajouté une boisson.
    initFichier(T+1);

    // On retourne à l'interface précédente.
    interfaceAjoutOuSuppBoisson();
}


/*
    Fonction permettant d'ajouter une boisson non alcoolisée.
    Cette fonction procède exactement de la même manière que la fonction permettant d'ajouter une boisson alcoolisée, sauf qu'on demande à l'utilisateur 
    d'entrer le degré de sucre et on met automatiquement le degré d'alcool à 0. 
*/
void ajoutBoissonNonAlcool(){

    boisson nouvBoisson;

    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\tMenu de l'ajout d'une boisson\n\n");

    printf("Veuillez entrer le nom de la boisson :");
    getchar();
    retour = scanf("%[^\n]", nouvBoisson.nom);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer la contenance de la boisson :");
    retour = scanf("%f", &nouvBoisson.contenance);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le prix de la boisson :");
    retour = scanf("%f", &nouvBoisson.prix);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer la quantite de boisson :");
    retour = scanf("%f", &nouvBoisson.quantite);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    nouvBoisson.degreAlco = 0.00;

    printf("Entrer le degre de sucre de cette boisson :");
    retour = scanf("%f", &nouvBoisson.degreScr);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    int T = calcTailleFichier();
    
    if (T>0) {
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            strcpy(tmp[i].nom, tab[i].nom);
            tmp[i].contenance = tab[i].contenance;
            tmp[i].prix = tab[i].prix;
            tmp[i].quantite = tab[i].quantite;
            tmp[i].degreAlco = tab[i].degreAlco;
            tmp[i].degreScr = tab[i].degreScr;
        }

        free(tab);
        tab = malloc((T+1)*sizeof(boisson));

        for(int i = 0; i<T; i++) {
            strcpy(tab[i].nom, tmp[i].nom);
            tab[i].contenance = tmp[i].contenance;
            tab[i].prix = tmp[i].prix;
            tab[i].quantite = tmp[i].quantite;
            tab[i].degreAlco = tmp[i].degreAlco;
            tab[i].degreScr = tmp[i].degreScr;
        }

        strcpy(tab[T].nom, nouvBoisson.nom);
        tab[T].contenance = nouvBoisson.contenance;
        tab[T].prix = nouvBoisson.prix;
        tab[T].quantite = nouvBoisson.prix;
        tab[T].degreAlco = nouvBoisson.degreAlco;
        tab[T].degreScr = nouvBoisson.degreScr;

        free(tmp);
    } else {
        tab = malloc(1*sizeof(boisson));
        strcpy(tab[0].nom, nouvBoisson.nom);
        tab[0].contenance = nouvBoisson.contenance;
        tab[0].prix = nouvBoisson.prix;
        tab[0].quantite = nouvBoisson.prix;
        tab[0].degreAlco = nouvBoisson.degreAlco;
        tab[0].degreScr = nouvBoisson.degreScr;
    }

    initFichier(T+1);

    interfaceAjoutOuSuppBoisson();

}

/*
    Fonction permettant d'afficher les informations des boissons des boissons, pour le barman.
*/
void informationBoissonBarman(){
    // On crée des variables, une permettant de parcourir le tableau et l'autre qui contient le nombre de boissons.
    int i;
    int T = calcTailleFichier();

    // On fait une boucle qui passe à travers tout le tableau et qui affiche chaque information de chaque boisson.
    for(i = 0; i<T; i++) {
        printf("\t\t%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].quantite, tab[i].degreAlco, tab[i].degreScr);
    }
}

/*
    Fonction permettant de supprimer une boisson.
*/
void suppBoisson(){

    // On crée une variable qui correspond à l'ID de la boisson à supprimer.
    int idSupp = 0;
    int retour = 0;

    // On affiche toutes les boissons, ainsi que leurs informations.
    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tQuantité\tDegre Alcool\tDegre Sucre\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    // On demande à l'utilisateur d'entrer l'ID de la boisson qu'il désire supprimer.
    printf("Entrer l'ID de la boisson à supprimer (0 pour revenir en arrière):");
    retour = scanf("%d", &idSupp);

    // On vérifie s'il y a eu une erreur dans la saisie.
    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }

    // En entrant 0, l'utilisateur a la possibilité de retourner à l'interface précédente.
    if(idSupp == 0) {
        interfaceAjoutOuSuppBoisson();
    }

    // Si l'utilisateur a entré un ID n'existant pas, il a la possibilité d'en entrer un nouveau.
    while (idSupp < 1 || idSupp > calcTailleFichier()) {
        printf("ID impossible a supprimer.\nEntrer un nouveau ID :");
        retour = scanf("%d", &idSupp);
        if(idSupp == 0) {
            interfaceAjoutOuSuppBoisson();
        }
    }

    /*
        Cette partie est similaire à l'ajout d'une boisson, sauf qu'au lieu d'augmenter la taille du tableau, on la dominue.
        On crée un tableau temporaire où on copie toutes les informations du tableau de base, on recrée le tableau de base avec une case en moins, 
        puis on recopie toutes les informations dans le tableau de base sans la boisson à supprimer.
    */

    // On crée des variables pour stocker la taille du tableau et pour gérer la boucle permettant de recopier les valeurs d'un tableau à l'autre.
    int T = calcTailleFichier();
    int j = 0;
    int h = 0;

    // Si le tableau contient plus d'une boisson, on fait l'opération énoncée précédemment, sinon on libère simplement l'espace du tableau.
    if(T>1) {
        // On crée le tableau temporaire et on y copie toutes les informations du tableau de base.
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            strcpy(tmp[i].nom, tab[i].nom);
            tmp[i].contenance = tab[i].contenance;
            tmp[i].prix = tab[i].prix;
            tmp[i].quantite = tab[i].quantite;
            tmp[i].degreAlco = tab[i].degreAlco;
            tmp[i].degreScr = tab[i].degreScr;
        }

        // On libère l'espace du tableau de base et on le recrée avec une case en moins.
        free(tab);
        tab = malloc((T-1)*sizeof(boisson));

        // On recopie toutes les informations dans le tableau de base, et si on est situé sur la valeur à supprimer, on ne la recopie tout simplement pas.
        while(j<T) {
            if(j != idSupp-1) {
                strcpy(tab[h].nom, tmp[j].nom);
                tab[h].contenance = tmp[j].contenance;
                tab[h].prix = tmp[j].prix;
                tab[h].quantite = tmp[j].quantite;
                tab[h].degreAlco = tmp[j].degreAlco;
                tab[h].degreScr = tmp[j].degreScr;
                h++;
                j++;
            }
            else {
                j++;
            }
        }
    } 
    // S'il n'y a qu'une seule boisson et que l'ID à supprimer est 1 (le seul possible) alors on libère simplement l'espace du tableau.
    else if (T==1 && idSupp==1) {
        free(tab);
    }

    // On recopie le tableau dans le fichier
    initFichier(T-1);

    // On retourne à l'interface précédente.
    interfaceAjoutOuSuppBoisson();

}

/*
    Fonction permettant de modifier une boisson.
*/ 
void modifBoisson(){

    // On crée une variable qui correspond à l'ID de la boisson à modifier.
    int idChange = 0;
    int retour = 0;

    // On affiche toutes les boissons, ainsi que leurs informations.
    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    // Si le fichier est vide, on indique à l'utilisateur qu'il n'y a rien à modifier, et on lui indique qu'il peut revenir à l'interface précédente.
    if(calcTailleFichier() == 0) {
        printf("La liste est vide, il n'y a rien à modifier.\n");
        printf("Entrez 0 pour revenir en arrière : ");
        retour = scanf("%d", &idChange);
        interfaceGestionBoissonBarman();
    }

    // On demande à l'utilisateur d'entrer l'ID de la boisson qu'il désire modifier.
    printf("Entrer l'ID de la boisson a modifie (0 pour revenir en arrière):");
    retour = scanf("%d", &idChange);

    // On vérifie s'il y a eu une erreur dans la saisie.
    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    // En entrant 0, l'utilisateur a la possibilité de retourner à l'interface précédente.
    if(idChange == 0) {
        interfaceGestionBoissonBarman();
    }

    // Si l'utilisateur a entré un ID n'existant pas, il a la possibilité d'en entrer un nouveau.
    while (idChange < 1 || idChange > calcTailleFichier()) {
        printf("ID inexistant.\nEntrer un nouveau ID :");
        retour = scanf("%d", &idChange);
        if(idChange == 0) {
            interfaceGestionBoissonBarman();
        }
    }

    // On demande à l'utilisateur d'entrer les nouvelles informations une par une.
    printf("Veuillez entrez le nouveau nom de la boisson :");
    getchar();
    retour = scanf("%[^\n]", tab[idChange-1].nom);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer la nouvelle contenance de la boisson :");
    retour = scanf("%f", &tab[idChange-1].contenance);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le nouveau prix de la boisson :");
    retour = scanf("%f", &tab[idChange-1].prix);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer la quantite de boisson :");
    retour = scanf("%f", &tab[idChange-1].quantite);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le nouveau degre d'alcool de cette boisson :");
    retour = scanf("%f", &tab[idChange-1].degreAlco);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le nouveau degre de sucre de cette boisson :");
    retour = scanf("%f", &tab[idChange-1].degreScr);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    // On recopie les nouvelles informations dans le fichier.
    initFichier(calcTailleFichier());

    // On remet l'interface modifBoisson(), si l'utilisateur souhaite modifier une autre boisson.
    modifBoisson();

}

/*
    Fonction permettant de modifier le stock d'une boisson.
    Dans le fonctionnement, cette fonction est similaire à la fonction modifBoisson().
    En effet, on demande l'ID à l'utilisateur, on vérifie si l'ID est correcte, on demande à l'utilisateur d'entrer le stock qu'il a reçu et celui
    qu'il a vendu et on a actualise les informations dans le fichier.
*/
void gestionStock(){
    int idStock = 0;
    float stockV = 0;
    float stockR = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    if(calcTailleFichier() == 0) {
        printf("La liste est vide, il n'y a rien à modifier.\n");
        printf("Entrez 0 pour revenir en arrière : ");
        retour = scanf("%d", &idStock);
        interfaceGestionBoissonBarman();
    }

    printf("Entrer l'ID du stock du stock à modifier (0 pour revenir en arrière):");
    retour = scanf("%d", &idStock);

    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    if(idStock == 0) {
        interfaceGestionBoissonBarman();
    }

    while(idStock < 1 || idStock > calcTailleFichier()){
        printf("ID impossible a modifie.\nEntrer un nouveau ID :");
        retour = scanf("%d", &idStock);
    }

    printf("Entrer la quantite de boisson recue :");
    retour = scanf("%f", &stockR);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }
    printf("Entrer la quantite de boisson vendue :");
    retour = scanf("%f", &stockV);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    tab[idStock-1].quantite = tab[idStock-1].quantite + fabsf(stockR) - fabsf(stockV);

    initFichier(calcTailleFichier());

    // On remet l'interface gestionStock(), si l'utilisateur souhaite modifier le stock d'une autre boisson.
    gestionStock();

}

/*
    SUREMENT A REVOIR PUISQUE IL FAUT AJOUTER DES CHOSES
    Fonction permettant de calculer les recettes.
    Cette fonction renvoie un réel.
*/
float recette(){

    // On crée une variable qui correspond à la recette totale.
    float totalJ = 0;

    // On parcours le fichier de commande et on additionne l'argent générée par chaque commande. 
    for(int i = 0; i<calcTailleCom(); i++) {
        totalJ += tabCom[i].prix;
    }

    // On renvoie la recette.
    return totalJ;
}

/*
    Fonction permettant de calculer le nombre de boissons qu'il y a dans le fichier.
    Cette fonction renvoie un entier.
*/
int calcTailleFichier() {
    // On crée une variable de type entier pour compter la taille, initialisée à -1 car la boucle est effectuée au moins une fois, 
    // et une variable de type boisson.
    int t = -1;
    boisson tmp;

    // On ouvre le fichier contenant les boissons.
    FILE* file = fopen("data/boissonBarman.dat", "r");

    // On vérifie que le fichier est bien ouvert.
    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    // On retourne au début du fichier.
    rewind(file);

    // On lit toutes les valeurs du fichiers et on augmente la taille de 1 à chaque valeur lue.
    while(!feof(file)) {
        fscanf(file, BOISSON_FORMAT_IN, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.quantite, &tmp.degreAlco, &tmp.degreScr);
        t++;

        if(fgetc(file) != '\n'){
            break;
        }
    }

    // On renvoie le nombre de boissons ainsi calculé.
    return t;
}

// à revoir
/*
int calcTailleTab() {
    int i=0;
    while(tab[i].prix > 0) i++;
    return i;
}
*/

/*
    Fonction permettant d'initialiser le tableau contenant les boissons.
*/
void initTab() {
    // On crée une variable qui va permettre de recopier les informations du fichier.
    int i = 0;

    // On ouvre le fichier en mode lecture, avec le paramètre "r".
    FILE* file = fopen("data/boissonBarman.dat", "r");

    // On vérifie si le fichier s'est bien ouvert.
    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    // On crée le tableau seulement s'il y a au moins une boisson.
    if(calcTailleFichier()>0) {
        tab = malloc(calcTailleFichier()*sizeof(boisson));
    }

    // On retourne au début du fichier.
    rewind(file);

    // On parcoure le fichier et on recopie les informations une par une dans le tableau.
    while(!feof(file)) {
        fscanf(file, BOISSON_FORMAT_IN, tab[i].nom, &tab[i].contenance, &tab[i].prix, &tab[i].quantite, &tab[i].degreAlco, &tab[i].degreScr);
        i++;

        if(fgetc(file) != '\n'){
            break;
        }
    }

    // On ferme le fichier.
    fclose(file);

}

/*
    Fonction permettant d'initialiser le fichier.
    Elle est utilisée souvent après avoir modifier une informations dans le tableau.
*/
void initFichier(int T) {
    // On ouvre le fichier en mode écriture, avec le paramètre "w", permettant de supprimer le contenu du fichier puis d'écrire. 
    FILE *file = fopen("data/boissonBarman.dat","w");

    // On crée une variable permettant de passer dans tout le tableau et de recopier les informations dans le fichier.
    int i;

    // On parcoure le tableau et on copie les informations dans le fichier.
    for(i=0; i<T; i++) {
        fprintf(file, BOISSON_FORMAT_OUT, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].quantite, tab[i].degreAlco, tab[i].degreScr);
    }

    // On ferme le fichier.
    fclose(file);
}