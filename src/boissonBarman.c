/*
    Ce fichier contient toutes les fonctions liees au fonctionnement de l'interface du barman.
*/

// On inclue le fichier header associe
#include "boissonBarman.h"

/*
    Fonction permettant d'initialiser le fichier contenant toutes les boissons et toutes leurs informations associees.
    Cette fonction a pour simple but de verifier si le fichier a bien ete initialise.
*/
void initFileBarman(){
    // On cree une variable de type FILE, permettant de manipuler le fichier, et on l'ouvre avec le parametre "ab", qui permet d'ajouter des informations
    // directement apres le bas du fichier.
    FILE* file = fopen("data/boissonBarman", "ab");

    // On verifie si le fichier a bien ete ouvert, et on arrete le programme s'il y a une erreur. 
    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    
    // On ferme le fichier, apres avoir verifie qu'il etait bien initialise.
    fclose(file);
}

/*
    Fonction permettant d'initiliser l'ID d'une boisson.
    L'ID de la boisson nous permet de mieux gerer la creation de cocktails par la suite.
*/
int idInit(){
    
    // On cree 3 variables, une temporaire de type boisson et deux entiers 
    boisson tmp;
    int taille;
    int nID = 0;

    // On ouvre le fichier en mode lecture avec le parametre "rb"
    FILE* file = fopen("data/boissonBarman", "rb");

    // On verifie que le fichier s'est bien ouvert
    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    // On lit le nombre de boissson, qui se situe ou tout debut du fichier
    fread(&taille, sizeof(int), 1, file);

    // On lit les boissons jusqu'a ce qu'il n'y en ait plus, et on recupere ainsi l'ID de la derniere boisson
    while(fread(&tmp, sizeof(boisson), 1, file)) {
        nID = tmp.id;
    }

    // On ajoute 1 a l'ID, puisqu'on a recupere l'ID de la derniere boisson juste avant
    nID++;

    // On ferme le fichier
    fclose(file); 

    // On retourne le nouvel ID
    return nID;  
}

/*
    Fonction permettant d'ajouter une boisson alcoolisee.
*/
void ajoutBoissonAlcool(){

    // On creer une variable de type boisson, qui sera ajoute au fichier apres avoir recupere toutes ses informations.
    boisson nouvBoisson;

    /*
        On demande a l'utilisateur d'entrer les informations de la boisson une par une, sauf le degre de sucre que l'on met automatiquement a 0, 
        puisqu'il s'agit d'une boisson alcoolisee.
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

    nouvBoisson.id = idInit();

    // On recupere le nombre de boissons qu'il existe deja dans le fichier.
    int T = tailleTabBarman();
    
    // On dissocie deux cas, s'il existe deja des boissons, ou si le fichier est vide.

    /*
        S'il y a deja des boissons, on cree un second tableau dynamique où on copie toutes les informations de base, et on recree le tableau de base 
        avec une case supplementaire permettant d'ajouter la nouvelle boisson.
    */ 
    if (T>0) {
        // On cree le tableau temporaire et on y copie toutes les informations du tableau de base.
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            tmp[i].id = tab[i].id;
            strcpy(tmp[i].nom, tab[i].nom);
            tmp[i].contenance = tab[i].contenance;
            tmp[i].prix = tab[i].prix;
            tmp[i].quantite = tab[i].quantite;
            tmp[i].degreAlco = tab[i].degreAlco;
            tmp[i].degreScr = tab[i].degreScr;
        }

        // On libere l'espace du tableau de base et on le cree avec une case supplementaire, puis on y recopie toutes les informations avec la
        // nouvelle boisson a la fin.
        free(tab);
        tab = malloc((T+1)*sizeof(boisson));

        for(int i = 0; i<T; i++) {
            tab[i].id = tmp[i].id;
            strcpy(tab[i].nom, tmp[i].nom);
            tab[i].contenance = tmp[i].contenance;
            tab[i].prix = tmp[i].prix;
            tab[i].quantite = tmp[i].quantite;
            tab[i].degreAlco = tmp[i].degreAlco;
            tab[i].degreScr = tmp[i].degreScr;
        }

        tab[T].id = nouvBoisson.id;
        strcpy(tab[T].nom, nouvBoisson.nom);
        tab[T].contenance = nouvBoisson.contenance;
        tab[T].prix = nouvBoisson.prix;
        tab[T].quantite = nouvBoisson.quantite;
        tab[T].degreAlco = nouvBoisson.degreAlco;
        tab[T].degreScr = nouvBoisson.degreScr;

        // On libere l'espace du tableau temporaire.
        free(tmp);
    } 
    // Sinon, si le fichier ne contient aucune boisson, on cree un tableau avec une seule case où on y copie la nouvelle boisson.
    else {
        tab = malloc(1*sizeof(boisson));
        tab[0].id = nouvBoisson.id;
        strcpy(tab[0].nom, nouvBoisson.nom);
        tab[0].contenance = nouvBoisson.contenance;
        tab[0].prix = nouvBoisson.prix;
        tab[0].quantite = nouvBoisson.quantite;
        tab[0].degreAlco = nouvBoisson.degreAlco;
        tab[0].degreScr = nouvBoisson.degreScr;
    }

    // On recopie toutes les informations du tableau dans le fichier, en indicant la taille +1 car on a ajoute une boisson.
    initFichier(T+1);

    // On retourne a l'interface precedente.
    interfaceAjoutOuSuppBoisson();
}


/*
    Fonction permettant d'ajouter une boisson non alcoolisee.
    Cette fonction procede exactement de la meme maniere que la fonction permettant d'ajouter une boisson alcoolisee, sauf qu'on demande a l'utilisateur 
    d'entrer le degre de sucre et on met automatiquement le degre d'alcool a 0. 
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

    nouvBoisson.id = idInit();

    int T = tailleTabBarman();
    
    if (T>0) {
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            tmp[i].id = tab[i].id;
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
            tab[i].id = tmp[i].id;
            strcpy(tab[i].nom, tmp[i].nom);
            tab[i].contenance = tmp[i].contenance;
            tab[i].prix = tmp[i].prix;
            tab[i].quantite = tmp[i].quantite;
            tab[i].degreAlco = tmp[i].degreAlco;
            tab[i].degreScr = tmp[i].degreScr;
        }
        
        tab[T].id = nouvBoisson.id;
        strcpy(tab[T].nom, nouvBoisson.nom);
        tab[T].contenance = nouvBoisson.contenance;
        tab[T].prix = nouvBoisson.prix;
        tab[T].quantite = nouvBoisson.prix;
        tab[T].degreAlco = nouvBoisson.degreAlco;
        tab[T].degreScr = nouvBoisson.degreScr;

        free(tmp);
    } else {
        tab[0].id = nouvBoisson.id;
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
    // On cree des variables, une permettant de parcourir le tableau et l'autre qui contient le nombre de boissons.
    int i;
    int T = tailleTabBarman();

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque boisson.
    for(i = 0; i<T; i++) {
        printf("\t\t%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].quantite, tab[i].degreAlco, tab[i].degreScr);
    }
}

/*
    Fonction permettant de supprimer une boisson.
*/
void suppBoisson(){

    // On cree une variable qui correspond a l'ID de la boisson a supprimer.
    int idSupp = 0;
    int retour = 0;

    // On affiche toutes les boissons, ainsi que leurs informations.
    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tQuantite\tDegre Alcool\tDegre Sucre\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    // On demande a l'utilisateur d'entrer l'ID de la boisson qu'il desire supprimer.
    printf("Entrer l'ID de la boisson a supprimer (0 pour revenir en arriere):");
    retour = scanf("%d", &idSupp);

    // On verifie s'il y a eu une erreur dans la saisie.
    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }

    // En entrant 0, l'utilisateur a la possibilite de retourner a l'interface precedente.
    if(idSupp == 0) {
        interfaceAjoutOuSuppBoisson();
    }

    // Si l'utilisateur a entre un ID n'existant pas, il a la possibilite d'en entrer un nouveau.
    while (idSupp < 1 || idSupp > tailleTabBarman()) {
        printf("ID impossible a supprimer.\nEntrer un nouveau ID :");
        retour = scanf("%d", &idSupp);
        if(idSupp == 0) {
            interfaceAjoutOuSuppBoisson();
        }
    }

    /*
        Cette partie est similaire a l'ajout d'une boisson, sauf qu'au lieu d'augmenter la taille du tableau, on la dominue.
        On cree un tableau temporaire où on copie toutes les informations du tableau de base, on recree le tableau de base avec une case en moins, 
        puis on recopie toutes les informations dans le tableau de base sans la boisson a supprimer.
    */

    // On cree des variables pour stocker la taille du tableau et pour gerer la boucle permettant de recopier les valeurs d'un tableau a l'autre.
    int T = tailleTabBarman();
    int j = 0;
    int h = 0;

    // Si le tableau contient plus d'une boisson, on fait l'operation enoncee precedemment, sinon on libere simplement l'espace du tableau.
    if(T>1) {
        // On cree le tableau temporaire et on y copie toutes les informations du tableau de base.
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            tmp[i].id = tab[i].id;
            strcpy(tmp[i].nom, tab[i].nom);
            tmp[i].contenance = tab[i].contenance;
            tmp[i].prix = tab[i].prix;
            tmp[i].quantite = tab[i].quantite;
            tmp[i].degreAlco = tab[i].degreAlco;
            tmp[i].degreScr = tab[i].degreScr;
        }

        // On libere l'espace du tableau de base et on le recree avec une case en moins.
        free(tab);
        tab = malloc((T-1)*sizeof(boisson));

        // On recopie toutes les informations dans le tableau de base, et si on est situe sur la valeur a supprimer, on ne la recopie tout simplement pas.
        while(j<T) {
            if(j != idSupp-1) {
                tab[h].id = tmp[j].id;
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
    // S'il n'y a qu'une seule boisson et que l'ID a supprimer est 1 (le seul possible) alors on libere simplement l'espace du tableau.
    else if (T==1 && idSupp==1) {
        free(tab);
    }

    // On recopie le tableau dans le fichier
    initFichier(T-1);

    // On retourne a l'interface precedente.
    interfaceAjoutOuSuppBoisson();

}

/*
    Fonction permettant de modifier une boisson.
*/ 
void modifBoisson(){

    // On cree une variable qui correspond a l'ID de la boisson a modifier.
    int idChange = 0;
    int retour = 0;

    // On affiche toutes les boissons, ainsi que leurs informations.
    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    // Si le fichier est vide, on indique a l'utilisateur qu'il n'y a rien a modifier, et on lui indique qu'il peut revenir a l'interface precedente.
    if(tailleTabBarman() == 0) {
        printf("La liste est vide, il n'y a rien a modifier.\n");
        printf("Entrez 0 pour revenir en arriere : ");
        retour = scanf("%d", &idChange);
        interfaceGestionBoissonBarman();
    }

    // On demande a l'utilisateur d'entrer l'ID de la boisson qu'il desire modifier.
    printf("Entrer l'ID de la boisson a modifie (0 pour revenir en arriere):");
    retour = scanf("%d", &idChange);

    // On verifie s'il y a eu une erreur dans la saisie.
    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    // En entrant 0, l'utilisateur a la possibilite de retourner a l'interface precedente.
    if(idChange == 0) {
        interfaceGestionBoissonBarman();
    }

    // Si l'utilisateur a entre un ID n'existant pas, il a la possibilite d'en entrer un nouveau.
    while (idChange < 1 || idChange > tailleTabBarman()) {
        printf("ID inexistant.\nEntrer un nouveau ID :");
        retour = scanf("%d", &idChange);
        if(idChange == 0) {
            interfaceGestionBoissonBarman();
        }
    }

    // On demande a l'utilisateur d'entrer les nouvelles informations une par une.
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
    initFichier(tailleTabBarman());

    // On remet l'interface modifBoisson(), si l'utilisateur souhaite modifier une autre boisson.
    modifBoisson();

}

/*
    Fonction permettant de modifier le stock d'une boisson.
    Dans le fonctionnement, cette fonction est similaire a la fonction modifBoisson().
    En effet, on demande l'ID a l'utilisateur, on verifie si l'ID est correcte, on demande a l'utilisateur d'entrer le stock qu'il a recu et celui
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

    if(tailleTabBarman() == 0) {
        printf("La liste est vide, il n'y a rien a modifier.\n");
        printf("Entrez 0 pour revenir en arriere : ");
        retour = scanf("%d", &idStock);
        interfaceGestionBoissonBarman();
    }

    printf("Entrer l'ID du stock du stock a modifier (0 pour revenir en arriere):");
    retour = scanf("%d", &idStock);

    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    if(idStock == 0) {
        interfaceGestionBoissonBarman();
    }

    while(idStock < 1 || idStock > tailleTabBarman()){
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

    initFichier(tailleTabBarman());

    // On remet l'interface gestionStock(), si l'utilisateur souhaite modifier le stock d'une autre boisson.
    gestionStock();

}

/*
    SUREMENT A REVOIR PUISQUE IL FAUT AJOUTER DES CHOSES
    Fonction permettant de calculer les recettes.
    Cette fonction renvoie un reel.
*/
float recette(){

    // On cree une variable qui correspond a la recette totale.
    float totalJ = 0;

    // On parcours le fichier de commande et on additionne l'argent generee par chaque commande. 
    for(int i = 0; i<calcTailleCom(); i++) {
        totalJ += tabCom[i].prix;
    }

    // On renvoie la recette.
    return totalJ;
}

/*
    Fonction permettant de recuperer le nombre de boisson a partir du fichier.
*/
int tailleTabBarman() {

    // On cree une variable pour recuperer la taille.
    int taille = 0;

    // On ouvre le fichier en mode lecture. 
    FILE* file = fopen("data/boissonBarman", "rb");

    // On verifie que le fichier s'est bien ouvert. 
    if(file == NULL){
        printf("fichier non ouvert ID");
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
void initTab() {
    // On cree une variable qui va permettre de recopier les informations du fichier.
    int i = 0;
    int taille;
    boisson boisson;

    // On ouvre le fichier en mode lecture, avec le parametre "rb".
    FILE* file = fopen("data/boissonBarman", "rb");

    // On verifie si le fichier s'est bien ouvert.
    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    // On cree le tableau seulement s'il y a au moins une boisson.
    if(fread(&taille, sizeof(int), 1, file)>0) {
        tab = malloc(taille*sizeof(boisson));
    }

    // On parcoure le fichier et on recopie les informations une par une dans le tableau, tant qu'il y en a.
    while(fread(&boisson, sizeof(boisson), 1, file)) {
        tab[i] = boisson;
        i++;
    }

    // On ferme le fichier.
    fclose(file);

}

/*
    Fonction permettant d'initialiser le fichier.
    Elle est utilisee souvent apres avoir modifier une informations dans le tableau.
*/
void initFichier(int T) {
    // On ouvre le fichier en mode ecriture, avec le parametre "wb", permettant de supprimer le contenu du fichier puis d'ecrire. 
    FILE *file = fopen("data/boissonBarman","wb");

    // On cree une variable permettant de passer dans tout le tableau et de recopier les informations dans le fichier.
    int i;

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    fwrite(&T, sizeof(int), 1, file);

    // On parcoure le tableau et on copie les informations dans le fichier.
    for(i=0; i<T; i++) {
        fwrite(&tab[i], sizeof(boisson), 1, file);
    }

    // On ferme le fichier.
    fclose(file);
}