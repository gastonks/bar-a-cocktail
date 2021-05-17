/*
    Ce fichier contient toutes les fonctions liées au fonctionnement de l'interface du client.
*/

// On inclue le fichier header associé
#include "boissonClient.h"

/*
    Fonction permettant d'initialiser le fichier commandeClient.dat.
    Cette fonction a pour simple but de vérifier que le fichier a bien été initialisé.
*/
void initFileClient(void){
    // On ouvre le fichier.
    FILE* file = fopen("data/commandeClient", "a");

    // On vérifie que le fichier s'est bien ouvert. 
    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    // On ferme le fichier.
    fclose(file);
}

int idInitCommande(){
    
    // On cree 3 variables, une temporaire de type boisson et deux entiers 
    commande tmp;
    int taille;
    int nID = 0;

    // On ouvre le fichier en mode lecture avec le parametre "rb"
    FILE* file = fopen("data/commandeClient", "rb");

    // On verifie que le fichier s'est bien ouvert
    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    // On lit le nombre de boissson, qui se situe ou tout debut du fichier
    fread(&taille, sizeof(int), 1, file);

    // On lit les boissons jusqu'a ce qu'il n'y en ait plus, et on recupere ainsi l'ID de la derniere boisson
    while(fread(&tmp, sizeof(commande), 1, file)) {
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
void commandeBoissonClient(int idBoisson, int recom){

    // On crée une variable de type commande.
    int quantite;
    int prix;
    int ID;
    int retour = 0;
    int choix;
    int i;
    int j;

    // On affiche le menu.
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\tMenu de commande d'une boisson\n\n");

    // On demande à l'utilisateur d'entrer le nombre de boissons qu'il veut.
    printf("Entrer la quantite de boisson commande :");
    retour = scanf("%d", &quantite);

    // On vérifie ensuite si la quantité entrée est valide.
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    if(quantite > tab[idBoisson-1].quantite) {
        printf("La quantité que vous avez entrée est trop élevée.\nVous pouvez entrer une quantité entre %d et %f: ", 1, tab[idBoisson-1].quantite);
        retour = scanf("%d", &quantite);
    }

    // On calcule le prix de la commande.
    prix = quantite * tab[idBoisson-1].prix;

    ID = posTOid(idBoisson);

    // On crée une variable correspondant au nombre de commandes déjà enregistrées.
    int T = tailleTabCom();

    if(recom == 0) {
        if (T>0) {
            commande* tmp = malloc(T*sizeof(commande));
            for(i = 0; i<T; i++) {
                tmp[i].id = tabCom[i].id;
                tmp[i].nbBoisson = tabCom[i].nbBoisson;
                tmp[i].tabCommandeBoisson = malloc(tmp[i].nbBoisson*sizeof(int*));
                for(j = 0; j<tmp[i].nbBoisson; j++) {
                    tmp[i].tabCommandeBoisson[j] = malloc(2*sizeof(int));
                    tmp[i].tabCommandeBoisson[j][0] = tabCom[i].tabCommandeBoisson[j][0];
                    tmp[i].tabCommandeBoisson[j][1] = tabCom[i].tabCommandeBoisson[j][1];
                }
                tmp[i].prix = tabCom[i].prix;
            }

            for(i=0; i<T; i++) {
                for(j = 0; j<tabCom[i].nbBoisson; i++) {
                    free(tabCom[i].tabCommandeBoisson[j]);
                }
                free(tabCom[i].tabCommandeBoisson);
            }

            free(tabCom);

            tabCom = malloc((T+1)*sizeof(commande));

            tabCom[T].nbBoisson = 1;

            for(i = 0; i<T; i++) {
                tabCom[i].id = tmp[i].id;
                tabCom[i].nbBoisson = tmp[i].nbBoisson;
                tabCom[i].tabCommandeBoisson = malloc(tabCom[i].nbBoisson*sizeof(int*));
                for(j = 0; j<tabCom[i].nbBoisson; j++) {
                    tabCom[i].tabCommandeBoisson[j] = malloc(2*sizeof(int));
                    tabCom[i].tabCommandeBoisson[j][0] = tmp[i].tabCommandeBoisson[j][0];
                    tabCom[i].tabCommandeBoisson[j][1] = tmp[i].tabCommandeBoisson[j][1];
                }
                tabCom[i].prix = tmp[i].prix;
            }
            tabCom[T].id = idInitCommande();
            tabCom[T].nbBoisson = 1;
            tabCom[T].tabCommandeBoisson = malloc(tabCom[i].nbBoisson*sizeof(int*));
            for(j = 0; j<tabCom[i].nbBoisson; j++) {
                    tabCom[i].tabCommandeBoisson[j] = malloc(2*sizeof(int));
                    tabCom[T].tabCommandeBoisson[j][0] = ID;
                    tabCom[T].tabCommandeBoisson[j][1] = quantite;
                }
            tabCom[T].prix = prix;

            for(i=0; i<T; i++) {
                for(j = 0; j<tmp[i].nbBoisson; i++) {
                    free(tmp[i].tabCommandeBoisson[j]);
                }
                free(tmp[i].tabCommandeBoisson);
            }

            free(tmp);

        } else {
            tabCom = malloc(1*sizeof(commande));
            tabCom[0].id = idInitCommande();
            tabCom[0].nbBoisson = 1;
            tabCom[0].tabCommandeBoisson = malloc(tabCom[0].nbBoisson*sizeof(int*));
            for(j = 0; j<tabCom[0].nbBoisson; j++) {
                    tabCom[0].tabCommandeBoisson[j] = malloc(2*sizeof(int));
                    tabCom[0].tabCommandeBoisson[j][0] = ID;
                    tabCom[0].tabCommandeBoisson[j][1] = quantite;
                }
            tabCom[0].prix = prix;
        }
    }
    else {
        int** tmp = malloc((tabCom[T-1].nbBoisson)*sizeof(int*));
        for(i = 0; i<tabCom[T-1].nbBoisson; i++) {
            tmp[i] = malloc(2*sizeof(int));
            tmp[i][0] = tabCom[T-1].tabCommandeBoisson[i][0];
            tmp[i][1] = tabCom[T-1].tabCommandeBoisson[i][1];
        }

        for(i = 0; i<tabCom[i].nbBoisson; i++) {
            free(tabCom[T-1].tabCommandeBoisson[i]);
        }
        free(tabCom[T-1].tabCommandeBoisson);

        tabCom[T-1].nbBoisson++;
        tabCom[T-1].tabCommandeBoisson = malloc(tabCom[T-1].nbBoisson*sizeof(int*));

        for(i = 0; i<tabCom[T-1].nbBoisson-1; i++) {
            tabCom[T-1].tabCommandeBoisson[i] = malloc(2*sizeof(int));
            tabCom[T-1].tabCommandeBoisson[i][0] = tmp[i][0];
            tabCom[T-1].tabCommandeBoisson[i][1] = tmp[i][1];
        }

        tabCom[T-1].tabCommandeBoisson[tabCom[T-1].nbBoisson-1] = malloc(2*sizeof(int));
        tabCom[T-1].tabCommandeBoisson[tabCom[T-1].nbBoisson-1][0] = ID;
        tabCom[T-1].tabCommandeBoisson[tabCom[T-1].nbBoisson-1][1] = quantite;
        tabCom[T-1].prix += quantite * tab[idBoisson-1].prix;
    }

    initFichierCom(T+1);

    printf("Voulez-vous commander une autre boisson ou un autre cocktail ? (0 : non / 1 : oui");
    retour = scanf("%d", &choix);

    if(choix == 0) {
        interfaceCommandeBoisson(0);
    }
    else{
        interfaceCommandeBoisson(1);
    }

    interfaceGestionBoissonClient();
}


void informationCommandeClient(){

    int i;
    int j;
    int T = tailleTabCom();

    for(i = 0; i<T; i++) {
        printf("%d\n", tabCom[i].nbBoisson);
        for(j = 0; j<tabCom[i].nbBoisson; j++) {
            printf("\t\t%d\t%s\t%d\t%.2f\n", i+1, tab[idTOpos(tabCom[i].tabCommandeBoisson[j][0])].nom, tabCom[i].tabCommandeBoisson[j][1], tabCom[i].prix);
        }
        puts("");
    }
}

int tailleTabCom() {
    // On cree une variable pour recuperer la taille.
    int taille = 0;

    // On ouvre le fichier en mode lecture. 
    FILE* file = fopen("data/commandeClient", "rb");

    // On verifie que le fichier s'est bien ouvert. 
    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    // On lit la premiere valeur qui apparait, qui correspond au nombre de commandes.
    fread(&taille, sizeof(int), 1, file);

    // On ferme le fichier.
    fclose(file);
    
    // On retourne le nombre de boissons.
    return taille;
}

void initTabCom() {
    // On cree une variable qui va permettre de recopier les informations du fichier.
    int i = 0;
    int taille = 0;

    // On ouvre le fichier en mode lecture, avec le parametre "rb".
    FILE* file = fopen("data/commandeClient", "rb");

    // On verifie si le fichier s'est bien ouvert.
    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    // On cree le tableau seulement s'il y a au moins une boisson.
    if(fread(&taille, sizeof(int), 1, file)>0) {
        tabCom = malloc(taille*sizeof(commande));
    }

    for(i = 0; i<taille; i++) {
        fread(&tabCom[i].id, sizeof(int), 1, file);
        fread(&tabCom[i].nbBoisson, sizeof(int), 1, file);
        tabCom[i].tabCommandeBoisson = malloc(tabCom[i].nbBoisson*sizeof(int*));
        for(int j = 0; j<tabCom[i].nbBoisson; j++) {
            tabCom[i].tabCommandeBoisson[j] = malloc(2*sizeof(int));
            fread(&tabCom[i].tabCommandeBoisson[j][0], sizeof(int), 1, file);
            fread(&tabCom[i].tabCommandeBoisson[j][1], sizeof(int), 1, file);
        }
        fread(&tabCom[i].prix, sizeof(float), 1, file);
    }

    // On ferme le fichier.
    fclose(file);

}

void initFichierCom(int T) {
    // On ouvre le fichier en mode ecriture, avec le parametre "wb", permettant de supprimer le contenu du fichier puis d'ecrire. 
    FILE *file = fopen("data/commandeClient","wb");

    // On cree une variable permettant de passer dans tout le tableau et de recopier les informations dans le fichier.
    int i;

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    fwrite(&T, sizeof(int), 1, file);

    for(i=0; i<T; i++) {
        fwrite(&tabCom[i].id, sizeof(int), 1, file);
        fwrite(&tabCom[i].nbBoisson, sizeof(int), 1, file);
        for(int j = 0; j<tabCom[i].nbBoisson; j++) {
            fwrite(&tabCom[i].tabCommandeBoisson[j][0], sizeof(int), 1, file);
            fwrite(&tabCom[i].tabCommandeBoisson[j][1], sizeof(int), 1, file);
        }
        fwrite(&tabCom[i].prix, sizeof(float), 1, file);
    }

    // On ferme le fichier.
    fclose(file);
}

int idTOpos(int id) {
    int i;
    int pos;

    for (i = 0; i<tailleTabBarman(); i++) {
        if(tab[i].id == id) {
            pos = i;
        }
    }

    return pos;
}

int posTOid(int pos) {
    return(tab[pos-1].id);
}