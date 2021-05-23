/*! \file boissonBarman.c
*  \author Guillerm François
*  \version 1
*  \brief Programme contenant toutes les fonctions permettant au barman de gérer les boissons.  
*/

/*
    Ce fichier contient toutes les fonctions liées au fonctionnement de l'interface du barman.
*/

// On inclue le fichier header associé
#include "boissonBarman.h"

float recetteBar;

/*! \fn void initFileBarman()
*  \author Guillerm François
*  \version 1
*
*  \brief Procedure premettant de vérifier si le fichier des boissons fonctionne correctement.
*
*  \remarks Cette procédure ouvre le fichier contenant les boissons, vérifie si le fichier s'est bien ouvert et le referme ensuite. 
*/

/*
    Fonction permettant d'initialiser le fichier devant contenir toutes les boissons et toutes leurs informations associées.
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

/*! \fn int idInit()
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant de donner un ID à une boisson.
*
*  \return Cette fonction renvoie un ID.
*
*  \remarks Cette fonction vérifie l'ID de la boisson la plus récente puis renvoie ce même ID augmenté de 1. 
*/

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

/*! \fn void ajoutBoissonAlcool(char nom[], float contenance, float prix, float quantite, float degreAlco)
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant d'ajouter une boisson alcoolisée.
*
*  \param nom : nom de la boisson à ajouter
*  \param contenance : contenance de la boisson à ajouter
*  \param prix : prix de la boisson à ajouter
*  \param quantite : quantité de la boisson à ajouter
*  \param degreAlco : degré d'alcool de la boisson à ajouter
*
*  \remarks Cette fonction permet d'ajouter une boisson alcoolisée au tableau de boisson.
*  Le tableau de boissons est recopié dans un tableau temporaire, on libère son espace, on lui alloue le même espace avec une case en plus pour la nouvelle boisson, on recopie toutes les boisson et enfin on ajoute la nouvelle boisson.
*  Après avoir ajouté la nouvelle boisson, on libère l'espace du tableau temporaire, puis on recopie le contenu du nouveau tableau dans le fichier. 
*/

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
        if(tmp == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }
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
        if(tab == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

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
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

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

/*! \fn void ajoutBoissonNonAlcool(char nom[], float contenance, float prix, float quantite, float degreSrc)
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant d'ajouter une boisson non alcoolisée.
*
*  \param nom : nom de la boisson à ajouter
*  \param contenance : contenance de la boisson à ajouter
*  \param prix : prix de la boisson à ajouter
*  \param quantite : quantité de la boisson à ajouter
*  \param degreSrc : degré de sucre de la boisson à ajouter
*
*  \remarks Cette fonction permet d'ajouter une boisson non alcoolisée au tableau de boisson.
*  La fonction fonctionne exactement de la même manière que la fonction précédente.
*/

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
        if(tmp == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

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
        if(tab == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

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
        tab = malloc(1*sizeof(boisson));
        if(tab == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }
        tab[0].id = nouvBoisson.id;
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

/*! \fn void informationBoissonBarman()
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant d'afficher les informations de toutes les boissons.
*/

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

/*! \fn void suppBoisson(int idSupp)
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant de supprimer une boisson.
*
*  \param idSupp : ID de la boisson à supprimer
*
*  \remarks Cette fonction permet de supprimer une boisson.
*  Cette fonction fonctionne de la même manière que les fonctions pour ajouter des boissons, mais dans le sens inverse.
*  On crée un tableau temporaire pour recopier toutes les boissons, on libère l'espace du tableau de base et on lui alloue le même espace moins un car on supprimer une boisson.
*  Ensuite on recopie les boissons dans le tableau tout en évitant de recopier la boisson à supprimer.
*  Enfin, on recopie le nouveau tableau dans le fichier.
*/

/*
    Fonction permettant de supprimer une boisson.
*/
void suppBoisson(int idSupp){

    /*
        Cette partie est similaire a l'ajout d'une boisson, sauf qu'au lieu d'augmenter la taille du tableau, on la diminue.
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
        if(tmp == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

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
        if(tab == NULL){
            printf("\nErreur d'allocation de memoire. 1\n");
            exit(-1);
        }

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
    suppCocktailBoisson(idSupp);
    suppPanierBoisson(idSupp);
    initFichier(T-1);

    // On retourne a l'interface precedente.
    interfaceAjoutOuSuppBoisson();

}

/*! \fn void modifBoisson(int idChange)
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant de modifier les informations d'une boisson.
*
*  \param idChange : ID de la boisson à changer
*
*  \remarks Cette fonction permet de modifier une boisson.
*  On demande tout simplement au barman d'entrer les nouvelles informations de la boisson, puis on modifie ces valeurs dans le tableau et enfin on recopie le nouveau tableau dans le fichier.
*/

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

/*! \fn void gestionStock(int idStock, float stockR, float stockV)
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant de modifier le stock d'une boisson.
*
*  \param idStock : ID de la boisson au stock à changer
*  \param stockR : stock reçu
*  \param stockV : stock vendu
*/

/*
    Fonction permettant de modifier le stock d'une boisson.
*/
void gestionStock(int idStock, float stockR, float stockV){

    tab[idStock-1].quantite = tab[idStock-1].quantite + fabsf(stockR) - fabsf(stockV);

    initFichier(tailleTabBarman());

    interfaceGestionBoissonBarman();

}

/*! \fn void recette(float prix)
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant de mettre à ajour les recettes du barman.
*
*  \param prix : somme d'argent à ajouter aux recettes totales.
*/

/*
    Fonction permettant de calculer les recettes.
    Cette fonction renvoie un réel.
*/
float recette(float prix){

    recetteBar = recetteBar + prix;

    return recetteBar;

}

/*! \fn void satisfactionCommande(int numPanier)
*  \author Barre Romain
*  \version 1
*
*  \brief Fonction premettant de satisfaire la commande d'un client.
*
*  \param numPanier : ID du panier à satisfaire
*
*  \remarks Le barman choisi la commande qu'il veut satisfaire, la commande et alors supprimée, les stocks sont mis à jour, et les finances du barman aussi. 
*/

/*
    Fonction permettant de satisfaire la commande d'un client.
    La commande est alors supprimée et l'argent générée est alors actualisée dans les finances du barman.
*/
void satisfactionCommande(int numPanier){
    
    // On crée des variables qui récupèrent le nombre de paniers, le nombre de boissons et le nombre de cocktails
    int Tpanier = tailleTabPanier();
    int Tboisson = tailleTabBarman();
    int Tcocktail = tailleTabBarmanCocktail();
    int erreur = 0;

    // On fait une boucle pour parcourir les panier et trouver celui qui nous intéresse
    for(int i = 0; i < Tpanier; i++){
        // On trouve le panier qui nous intéresse 
        if(i == numPanier-1){
            // On crée une boucle pour parcourir les commandes du panier
            for(int j = 0; j<tabPanier[i].nbrCommande; j++){
                // On crée une boucle pour parcourir les boissons des commandes du panier.
                for(int k = 0; k < tabPanier[i].listCommande[j].nbrBoisson; k++){
                    // S'il n'y a pas assez de boissons en stock, on affiche un message d'erreur
                    if(tab[tabPanier[i].listCommande[j].listBoisson[k].idBoisson].quantite - tabPanier[i].listCommande[j].listBoisson[k].quantiteBoisson < 0){
                        printf("\nInformation\n");
                        printf("\nImpossible à satisfaire la demande de boisson.");
                        printf("\nIl manque %.2f de %s dans le stock.", fabs(tab[tabPanier[i].listCommande[j].listBoisson[k].idBoisson].quantite - tabPanier[i].listCommande[j].listBoisson[k].quantiteBoisson), tab[tabPanier[i].listCommande[j].listBoisson[k].idBoisson].nom);
                        printf("\nEntrer une touche pour continuer.");
                        getchar();
                        erreur++;
                    }
                    // Sinon, on met à jour les stocks
                    else{
                        tab[tabPanier[i].listCommande[j].listBoisson[k].idBoisson].quantite = tab[tabPanier[i].listCommande[j].listBoisson[k].idBoisson].quantite - tabPanier[i].listCommande[j].listBoisson[k].quantiteBoisson;
                    }
                }
                // On fait le meme processus pour les cocktails, en mettant à jour les stocks s'il n'y a pas d'erreur
                for(int k = 0; k < tabPanier[i].listCommande[j].nbrCocktail; k++){
                    for(int m = 0; m < tabCocktail[tabPanier[i].listCommande[j].listCocktail[k].idCocktail].tailleListBoisson; m++){
                        if(tab[tabCocktail[tabPanier[i].listCommande[j].listCocktail[k].idCocktail].listIdBoisson[m]].quantite - tabPanier[i].listCommande[j].listCocktail[k].quantiteCocktail < 0){
                            printf("\nInformation\n");
                            printf("\nImpossible à satisfaire la demande de cocktail.");
                            printf("\nIl manque %.2f de %s dans le stock.", fabs(tab[tabCocktail[tabPanier[i].listCommande[j].listCocktail[k].idCocktail].listIdBoisson[m]].quantite - tabPanier[i].listCommande[j].listCocktail[k].quantiteCocktail), tab[tabCocktail[tabPanier[i].listCommande[j].listCocktail[k].idCocktail].listIdBoisson[m]].nom);
                            printf("\nEntrer une touche pour continuer.");
                            getchar();
                            erreur++;
                        }else{
                            tab[tabCocktail[tabPanier[i].listCommande[j].listCocktail[k].idCocktail].listIdBoisson[m]].quantite = tab[tabCocktail[tabPanier[i].listCommande[j].listCocktail[k].idCocktail].listIdBoisson[m]].quantite - tabPanier[i].listCommande[j].listCocktail[k].quantiteCocktail;
                        }
                    }
                }
            }
        }
    }

    // S'il y a eu des erreurs à causes des stocks, un message est affiché et le panier ne peut pas etre satisfait
    if(erreur != 0){
        printf("\n\nLe panier ne peut pas être satisfait.\nIl manque des boissons pour completer les commandes.");
        printf("\nLe panier n'a pas été supprimer.\nVeuillez rajouter des boissons dans le stock pour pouvoir satisfaire le panier.");
        printf("\nEntrer une touche pour continuer.");
        getchar();
        interfaceBarman();
    }
    // Sinon, on met à jour les finances, on supprime le panier satisfait et on met à jour les fichiers de sauvegarde.
    else{
        recette(tabPanier[numPanier-1].prix);
        supprimerPanier(numPanier);
        initFichier(Tboisson);
        initFichierCocktail(Tcocktail);
        interfaceBarman();
    }

}

/*! \fn int tailleTabBarman()
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant de récupérer la taille du tableau de boissons.
*
*  \return La fonction renvoie la taille du tableau de boissons.
*
*  \remarks Cette fonction permet de récupérer la taille du tableau de boissons.
*  On ouvre le fichier contenant les boissons et on lie tout simplement la première valeure de type entier, qui correspond à la taille.
*  On renvoie ensuite la taille du tableau.
*/

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

/*! \fn void initTab()
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant de créer le tableau de boissons.
*
*  \remarks Cette fonction permet de créer le tableau de boissons.
*  On ouvre le fichier, on lit la première valeur pour récupérer le nombre de boissons, on alloue de la mémoire pour le tableau de boissons, on lit toutes les informations des boissons dans un ordre défini pour les mettre dans le tableau et enfin on ferme le fichier.
*/

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

/*! \fn void initFichier(int T)
*  \author Guillerm François
*  \version 1
*
*  \brief Fonction premettant de copier les informations du tableau vers le fichier.
*
*  \param T : taille du tableau
*
*  \remarks Cette fonction permet de copier les informations du tableau vers le fichier.
*  On ouvre le fichier, puis on recopie les informations du tableau une par une dans le fichier dans un ordre défini, tout en commençant par mettre le nombre de boissons au tout début du fichier.
*  Le fichier est binaire car nous avons trouvé plus simple la manipulation des fichiers binaires par rapport aux fichiers classiques.
*/

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