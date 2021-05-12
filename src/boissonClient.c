/*
    Ce fichier contient toutes les fonctions liées au fonctionnement de l'interface du client.
*/

// On inclue le fichier header associé
#include "boissonClient.h"

// Macros permettant une utilisation plus facile et plus rapide du format dans l'utilisation de fscanf et fprintf, pour les boissons.
const char* BOISSON_FORMAT_CLIENT_OUT = "(%s, %.2f, %.2f, %.2f, %.2f, %.2f)\n";
const char* BOISSON_FORMAT_CLIENT_IN = "(%[^,], %f, %f, %f, %f, %f)";

// Macros permettant une utilisation plus facile et plus rapide du format dans l'utilisation de fscanf et fprintf, pour les commandes.
const char* COMMANDE_FORMAT_CLIENT_OUT = "(%s, %.2f, %.2f)\n";
const char* COMMANDE_FORMAT_CLIENT_IN = "(%[^,], %f, %f)";

/*
    Fonction permettant d'initialiser le fichier commandeClient.dat.
    Cette fonction a pour simple but de vérifier que le fichier a bien été initialisé.
*/
void initFileClient(void){
    // On ouvre le fichier.
    FILE* file = fopen("data/commandeClient.dat", "a");

    // On vérifie que le fichier s'est bien ouvert. 
    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    // On ferme le fichier.
    fclose(file);
}

/*
    Fonction permettant d'afficher les informations des boissons aux clients. 
*/
void informationBoissonClient(){

    // On crée deux variables, une permettant de parcourir le tableau et l'autre étant le nombre de boissons.
    int i;
    int T = tailleTabBarman();

    // On fait une boucle qui passe à travers tout le tableau de boissons et qui les affiche une par une.
    for(i = 0; i<T; i++) {
        // On affiche seulement les boissons qui sont présentes à au moins 1 exemplaire.
        if(tab[i].quantite>0) {
            printf("\t\t%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].quantite, tab[i].degreAlco, tab[i].degreScr);
        }
    }

}

/*
    Fonction permettant au client de commander une boisson.
*/
void commandeBoissonClient(int idBoisson){

    // On crée une variable de type commande.
    commande nComm;
    int retour = 0;

    // On recopie le nom de la boisson choisie dans le nom de la commande.
    strcpy(nComm.nom, tab[idBoisson-1].nom);

    // On affiche le menu.
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\tMenu de commande d'une boisson\n\n");

    // On demande à l'utilisateur d'entrer le nombre de boissons qu'il veut.
    printf("Entrer la quantite de boisson commande :");
    retour = scanf("%f", &nComm.quantite);

    // On vérifie ensuite si la quantité entrée est valide.
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    if(nComm.quantite > tab[idBoisson-1].quantite) {
        printf("La quantité que vous avez entrée est trop élevée.\nVous pouvez entrer une quantité entre %d et %f: ", 1, tab[idBoisson-1].quantite);
        retour = scanf("%f", &nComm.quantite);
    }

    // On calcule le prix de la commande.
    nComm.prix = nComm.quantite * tab[idBoisson-1].prix;

    // On crée une variable correspondant au nombre de commandes déjà enregistrées.
    int T = calcTailleCom();
    
    /*
        S'il existe déjà des commandes, on fait une manipulation similaire à l'ajout une boisson.
        
    */
    if (T>0) {
        commande* tmp = malloc(T*sizeof(commande));
        for(int i = 0; i<T; i++) {
            strcpy(tmp[i].nom, tabCom[i].nom);
            tmp[i].prix = tabCom[i].prix;
            tmp[i].quantite = tabCom[i].quantite;
        }

        free(tabCom);
        tabCom = malloc((T+1)*sizeof(commande));

        for(int i = 0; i<T; i++) {
            strcpy(tabCom[i].nom, tmp[i].nom);
            tabCom[i].prix = tmp[i].prix;
            tabCom[i].quantite = tmp[i].quantite;
        }

        strcpy(tabCom[T].nom, nComm.nom);
        tabCom[T].prix = nComm.prix;
        tabCom[T].quantite = nComm.quantite;

        free(tmp);
    } else {
        tabCom = malloc(1*sizeof(commande));
        strcpy(tabCom[0].nom, nComm.nom);
        tabCom[0].prix = nComm.prix;
        tabCom[0].quantite = nComm.quantite;
    }

    initFichierCom(T+1);

    interfaceGestionBoissonClient();
}


void informationCommandeClient(){

    int i;
    int T = calcTailleCom();

    for(i = 0; i<T; i++) {
        printf("\t\t%d\t%s\t%.2f\t%.2f\n", i+1, tabCom[i].nom, tabCom[i].prix, tabCom[i].quantite);
    }

}

int calcTailleCom() {
    int t = -1;
    boisson tmp;
    FILE* file = fopen("data/commandeClient.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    rewind(file);

    while(!feof(file)) {
        fscanf(file, COMMANDE_FORMAT_CLIENT_IN, tmp.nom, &tmp.prix, &tmp.quantite);
        t++;

        if(fgetc(file) != '\n'){
            break;
        }
    }

    return t;
}

void initTabCom() {
    int i = 0;
    FILE* file = fopen("data/commandeClient.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    if(tailleTabBarman()>0) {
        tabCom = malloc(calcTailleCom()*sizeof(commande));
    }

    rewind(file);

    while(!feof(file)) {
        fscanf(file, COMMANDE_FORMAT_CLIENT_IN, tabCom[i].nom, &tabCom[i].prix, &tabCom[i].quantite);
        i++;

        if(fgetc(file) != '\n'){
            break;
        }
    }

    // for(int j = 0; j<calcTailleCom(); j++) {
    //     printf("%s, %.2f, %.2f\n", tabCom[j].nom, tabCom[j].prix, tabCom[j].quantite);
    // }

    fclose(file);

}

void initFichierCom(int T) {
    FILE *file = fopen("data/commandeClient.dat","w");
    int i;

    for(i=0; i<T; i++) {
        fprintf(file, COMMANDE_FORMAT_CLIENT_OUT, tabCom[i].nom, tabCom[i].prix, tabCom[i].quantite);
    }

    fclose(file);
}