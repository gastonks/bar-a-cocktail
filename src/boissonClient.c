#include "boissonClient.h"

const char* BOISSON_FORMAT_CLIENT_OUT = "(%s, %.2f, %.2f, %.2f, %.2f, %.2f)\n";
const char* BOISSON_FORMAT_CLIENT_EX = "(%s, %.2f, %.2f, %.2f, %.2f, %.2f)";
const char* BOISSON_FORMAT_CLIENT_IN = "(%[^,], %f, %f, %f, %f, %f)";

const char* COMMANDE_FORMAT_CLIENT_OUT = "(%s, %.2f, %.2f)\n";
const char* COMMANDE_FORMAT_CLIENT_IN = "(%[^,], %f, %f)";
const char* COMMANDE_FORMAT_CLIENT_EX = "(%s, %.2f, %.2f)";

void initFileClient(void){
    FILE* file = fopen("data/commandeClient.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    fclose(file);
}

void informationBoissonClient(){

    int i;
    int T = calcTaille();

    for(i = 0; i<T; i++) {
        if(tab[i].quantite>0) {
            printf("\t\t%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].quantite, tab[i].degreAlco, tab[i].degreScr);
        }
    }

}

void commandeBoissonClient(int idBoisson){

    commande nComm;

    strcpy(nComm.nom, tab[idBoisson-1].nom);

    int retour = 0;
    system("cls");
    printf("===============================================================\n\n");
    printf("\t\tMenu de commande d'une boisson\n\n");


    printf("Entrer la quantite de boisson commande :");
    retour = scanf("%f", &nComm.quantite);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    nComm.prix = nComm.quantite * tab[idBoisson-1].prix;

    int T = calcTailleCom();
    
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

    if(calcTaille()>0) {
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