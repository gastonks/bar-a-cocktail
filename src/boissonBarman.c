/*
    Ce fichier contient toutes les fonctions liées au fonctionnement de l'interface du barman.
*/

// On inclue le fichier header associé
#include "boissonBarman.h"

float recetteBar;

/*
    Fonction permettant d'initialiser le fichier devant contenir toutes les boissons et toutes leurs informations associées.
    Cette fonction a pour simple but de vérifier si les deux fichiers ont bien été initialisés.
*/
void initFileBarman(){
    // On crée une variable de type FILE, permettant de manipuler les fichiers, et on l'ouvre avec le paramètre "ab", qui permet d'ajouter des informations
    // directement après le bas du fichier.

    FILE* file = fopen("data/boissonBarman", "ab");

    // On vérifie si le fichier a bien été ouvert, et on arrete le programme s'il y a une erreur. 
    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }
    
    // On ferme le fichier, après avoir vérifié qu'ils étaient bien initialisés.
    fclose(file);
}

/*
    Fonction permettant d'initialiser l'ID des boissons.
    Cette fonction renvoie une valeur entière, qui correspond à l'ID de la dernière boisson plus 1.
    Cette fonction est utile lors de l'ajout d'une boisson dans le fichier, permettant ainsi d'attribuer un ID à une nouvelle boisson.
*/
int idInit(){
    
    // On crée une variable de type boisson.    

    boisson tmp;

    int nID = 0;
    int taille;

    // On ouvre le fichier contenant les boissons avec le paramètres "rb".

    FILE* file = fopen("data/boissonBarman", "rb");

    // On vérifie que le fichier s'est bien ouvert.

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    fread(&taille, sizeof(int), 1, file);

    while(fread(&tmp, sizeof(boisson), 1, file)) {
        nID = tmp.id;
    }

    nID++;

    fclose(file); 

    // On retourne l'ID.

    return nID;  
}

/*
    Fonction permettant d'ajouter une boisson alcoolisée.
*/
void ajoutBoissonAlcool(char nom[], float contenance, float prix, float quantite, float degreAlco){

    // On créer une variable de type boisson, qui sera ajouté au fichier après avoir récupéré toutes ses informations.
    boisson nouvBoisson;

    // On récupère les données en paramétre pour pouvoir les réutiliser par la suite.

    nouvBoisson.id = idInit();
    strcpy(nouvBoisson.nom,nom);
    nouvBoisson.contenance = contenance;
    nouvBoisson.prix = prix;
    nouvBoisson.quantite = quantite;
    nouvBoisson.degreAlco = degreAlco;
    nouvBoisson.degreScr = 0;

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
        if(tab == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }
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
    Fonction permettant d'ajouter une boisson non alcoolisée.
*/
void ajoutBoissonNonAlcool(char nom[], float contenance, float prix, float quantite, float degreSrc){

    // On créer une variable de type boisson, qui sera ajouté au fichier après avoir récupéré toutes ses informations.

    boisson nouvBoisson;

    // On récupère les données en paramétre pour pouvoir les réutiliser par la suite.

    nouvBoisson.id = idInit();
    strcpy(nouvBoisson.nom,nom);
    nouvBoisson.contenance = contenance;
    nouvBoisson.prix = prix;
    nouvBoisson.quantite = quantite;
    nouvBoisson.degreAlco = 0;
    nouvBoisson.degreScr = degreSrc;


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
        printf("\t\t%d\t%s\t%.2f\t\t%.2f\t%.2f\t\t%.2f\t\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].degreAlco, tab[i].degreScr,  tab[i].quantite);
    }
}

/*
    Fonction permettant de supprimer une boisson.
*/
void suppBoisson(int idSupp){

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
void modifBoisson(int idChange){

    int retour;
    int T = tailleTabBarman();

    // On crée dexu variables de type boisson.
    boisson modifBoisson;
    for(int i = 0; i<T+1; i++){
        if(idChange-1 == i){
            if(tab[i].degreScr == 0){
                    printf("Veuillez entrer le nouveau nom de la boisson :");
                    getchar();
                    retour = scanf("%[^\n]", modifBoisson.nom);
                    if(retour != 1){
                        printf("\nErreur dans la saisie.\n");
                        exit(-1);
                    }

                    printf("Entrer la nouvelle contenance de la boisson :");
                    retour = scanf("%f", &modifBoisson.contenance);
                    if(retour != 1 || modifBoisson.contenance < 0){
                    while(retour != 1 || modifBoisson.contenance < 0){
                            retour = 1;
                            printf("Cette contenance est impossible.\n");
                            printf("Veuillez entrer une contenance de boisson positive:");
                            getchar();
                            retour = scanf("%f", &modifBoisson.contenance);
                        }
                    }

                    printf("Entrer le nouveau prix de la boisson :");
                    retour = scanf("%f", &modifBoisson.prix);
                    if(retour != 1 || modifBoisson.prix < 0){
                    while(retour != 1 || modifBoisson.prix < 0){
                            retour = 1;
                            printf("Ce prix est impossible.\n");
                            printf("Veuillez entrer un prix de boisson positif:");
                            getchar();
                            retour = scanf("%f", &modifBoisson.prix);
                        }
                    }

                    printf("Entrer la quantite de boisson :");
                    retour = scanf("%f", &modifBoisson.quantite);
                    if(retour != 1 || modifBoisson.quantite < 0){
                    while(retour != 1 || modifBoisson.quantite < 0){
                            retour = 1;
                            printf("Cette quantite est impossible.\n");
                            printf("Veuillez entrer une quantite de boisson positive:");
                            getchar();
                            retour = scanf("%f", &modifBoisson.quantite);
                        }
                    }

                    printf("Entrer le nouveau degre d'alcool de cette boisson :");
                    retour = scanf("%f", &modifBoisson.degreAlco);
                    if(retour != 1 || modifBoisson.degreAlco < 0){
                    while(retour != 1 || modifBoisson.degreAlco < 0){
                            retour = 1;
                            printf("Ce degre d'alcool est impossible.\n");
                            printf("Veuillez entrer un degre d'alcool de boisson positif:");
                            getchar();
                            retour = scanf("%f", &modifBoisson.degreAlco);
                        }
                    }
                    strcpy(tab[i].nom, modifBoisson.nom);
                    tab[i].prix = modifBoisson.prix;
                    tab[i].contenance = modifBoisson.contenance;
                    tab[i].quantite = modifBoisson.quantite;
                    tab[i].degreAlco = modifBoisson.degreAlco;
                    tab[i].degreScr = 0;

            }else if(tab[i].degreAlco == 0){
                    printf("Veuillez entrer le nouveau nom de la boisson :");
                    getchar();
                    retour = scanf("%[^\n]", modifBoisson.nom);
                    if(retour != 1){
                        printf("\nErreur dans la saisie.\n");
                        exit(-1);
                    }

                    printf("Entrer la nouvelle contenance de la boisson :");
                    retour = scanf("%f", &modifBoisson.contenance);
                    if(retour != 1 || modifBoisson.contenance < 0){
                    while(retour != 1 || modifBoisson.contenance < 0){
                            retour = 1;
                            printf("Cette contenance est impossible.\n");
                            printf("Veuillez entrer une contenance de boisson positive:");
                            getchar();
                            retour = scanf("%f", &modifBoisson.contenance);
                        }
                    }

                    printf("Entrer le nouveau prix de la boisson :");
                    retour = scanf("%f", &modifBoisson.prix);
                    if(retour != 1 || modifBoisson.prix < 0){
                    while(retour != 1 || modifBoisson.prix < 0){
                            retour = 1;
                            printf("Ce prix est impossible.\n");
                            printf("Veuillez entrer un prix de boisson positif:");
                            getchar();
                            retour = scanf("%f", &modifBoisson.prix);
                        }
                    }

                    printf("Entrer la quantite de boisson :");
                    retour = scanf("%f", &modifBoisson.quantite);
                    if(retour != 1 || modifBoisson.quantite < 0){
                    while(retour != 1 || modifBoisson.quantite < 0){
                            retour = 1;
                            printf("Cette quantite est impossible.\n");
                            printf("Veuillez entrer une quantite de boisson positive:");
                            getchar();
                            retour = scanf("%f", &modifBoisson.quantite);
                        }
                    }

                    printf("Entrer le nouveau degre de sucre de cette boisson :");
                    retour = scanf("%f", &modifBoisson.degreScr);
                    if(retour != 1 || modifBoisson.degreScr < 0){
                    while(retour != 1 || modifBoisson.degreScr < 0){
                            retour = 1;
                            printf("Ce degre de sucre est impossible.\n");
                            printf("Veuillez entrer un degre de sucre de boisson positif:");
                            getchar();
                            retour = scanf("%f", &modifBoisson.degreScr);
                        }
                    }

        
                    strcpy(tab[i].nom, modifBoisson.nom);
                    tab[i].prix = modifBoisson.prix;
                    tab[i].contenance = modifBoisson.contenance;
                    tab[i].quantite = modifBoisson.quantite;
                    tab[i].degreAlco = 0;
                    tab[i].degreScr = modifBoisson.degreScr;
                }
            }
        }

    initFichier(T);

    // On revient à l'interface précédente.

    interfaceGestionBoissonBarman();

}

/*
    Fonction permettant de modifier le stock d'une boisson.
    Dans le fonctionnement, cette fonction est similaire à la fonction modifBoisson().
    En effet, on demande l'ID à l'utilisateur, on vérifie si l'ID est correcte, on utilise deux fichiers, on recopie toutes les informations de l'un
    dans l'autre, tout en apportant la modification nécessaire, on renome les deux fichiers, on supprime celui qui n'est plus utile et enfin on 
    retourne à l'interface précédente.
    Le seul changement notable est que l'utilisateur entre en paramètre le nombre de stocks qu'il a reçu ainsi que le nombre de stocks qu'il a vendu.
*/
void gestionStock(int idStock, float stockR, float stockV){

    tab[idStock-1].quantite = tab[idStock-1].quantite + fabsf(stockR) - fabsf(stockV);

    initFichier(tailleTabBarman());

    interfaceGestionBoissonBarman();

}

/*
    Fonction permettant de calculer les recettes.
    Cette fonction renvoie un réel.
*/
float recette(float prix){

    recetteBar = recetteBar + prix;

    return recetteBar;

}

void satisfactionCommande(int nCommande){
    
    interfaceGestionBoissonBarman();
}

/*
    Fonction permettant de calculer le nombre de boissons qu'il y a dans le fichier.
    Cette fonction renvoie un entier.
*/
int tailleTabBarman() {

    // On cree une variable pour recuperer la taille.
    int taille = 0;

    // On ouvre le fichier en mode lecture. 
    FILE* file = fopen("data/boissonBarman", "rb");

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
void initTab() {
    // On cree une variable qui va permettre de recopier les informations du fichier.
    int taille;
    //boisson rboisson;

    // On ouvre le fichier en mode lecture, avec le parametre "rb".
    FILE* file = fopen("data/boissonBarman", "rb");

    // On verifie si le fichier s'est bien ouvert.
    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }


    // On cree le tableau seulement s'il y a au moins une boisson.
    if(fread(&taille, sizeof(int), 1, file)>0) {
        tab = (boisson*) malloc(taille*sizeof(boisson));
        if(tab == NULL){
            printf("Erreur allocation mémoire.");
            exit(-1);
        }

        // On parcoure le fichier et on recopie les informations une par une dans le tableau.
        for(int i = 0; i<taille; i++){
            fread(&tab[i].id, sizeof(int), 1, file);
            fread(tab[i].nom, sizeof(char), 20, file);
            fread(&tab[i].contenance, sizeof(float), 1, file);
            fread(&tab[i].prix, sizeof(float), 1, file);
            fread(&tab[i].quantite, sizeof(float), 1, file);
            fread(&tab[i].degreAlco, sizeof(float), 1, file);
            fread(&tab[i].degreScr, sizeof(float), 1, file);
        }
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
        printf("Fichier non ouvert.");
        exit(-1);
    }

    fwrite(&T, sizeof(int), 1, file);

    // On parcoure le tableau et on copie les informations dans le fichier.
    for(i=0; i<T; i++) {
        fwrite(&tab[i].id, sizeof(int), 1, file);
        fwrite(tab[i].nom, sizeof(char), 20, file);
        fwrite(&tab[i].contenance, sizeof(float), 1, file);
        fwrite(&tab[i].prix, sizeof(float), 1, file);
        fwrite(&tab[i].quantite, sizeof(float), 1, file);
        fwrite(&tab[i].degreAlco, sizeof(float), 1, file);
        fwrite(&tab[i].degreScr, sizeof(float), 1, file);
    }

    // On ferme le fichier.
    fclose(file);
}
