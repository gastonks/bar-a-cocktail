#include "boissonClient.h"


void initFileClient(void){
    FILE* file = fopen("data/commandeClient", "ab");

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    fclose(file);
}

int idInitCommande(){
    commande tmp;

    int nID = 0;
    int taille;
    FILE* file = fopen("data/commandeClient", "rb");

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    fread(&taille, sizeof(int), 1, file);

    while(fread(&tmp, sizeof(commande), 1, file)) {
        nID = tmp.id;
    }

    nID++;

    fclose(file); 
    
    nID = tmp.id + 1;
    fclose(file);   
    return nID;
}

void informationBoissonClient(){

    boisson tmp;
    int i;
    int T = tailleTabBarman();

    FILE* file = fopen("data/boissonBarman", "rb");

    if(file == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    // On fait une boucle qui passe a travers tout le tableau et qui affiche chaque information de chaque boisson.
    for(i = 0; i<T; i++) {
        printf("\t\t%d\t%s\t%.2f\t\t%.2f\t%.2f\t\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].degreAlco, tab[i].degreScr);
    }

}

void commandeBoissonClient(int idBoisson){

    FILE* fileCommande = fopen("data/commandeClient", "ab");
    FILE* fileBoisson = fopen("data/boissonBarman", "rb");

    if(fileCommande == NULL || fileBoisson == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    commande nComm;
    boisson tmp;

    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\tMenu de commande d'une boisson\n\n");


    printf("Entrer la quantite de boisson commande :");
    retour = scanf("%f", &nComm.quantite);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    nComm.id = idInitCommande();

/*
    while(!feof(fileBoisson)){
        fscanf(fileBoisson, BOISSON_FORMAT_CLIENT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);

        if(idBoisson == tmp.id){
            nComm.prix = nComm.quantite * tmp.prix;
            nComm.idBoisson = idBoisson;
            fprintf(fileCommande, COMMANDE_FORMAT_CLIENT_OUT, nComm.id, nComm.idBoisson, tmp.nom, nComm.prix, nComm.quantite);
            if(fgetc(fileBoisson) != '\n'){
                break;
            }
        }
        if(fgetc(fileBoisson) != '\n'){
                break;
        }
    }

    fclose(fileCommande);
    fclose(fileBoisson);
*/
    interfaceGestionBoissonClient();
}

void informationCommandeClient(){

    commande tmp;

    FILE* file = fopen("data/commandeClient.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
/*
    rewind(file);
    
    while(!feof(file)){
        
        fscanf(file, COMMANDE_FORMAT_CLIENT_IN, &tmp.id, &tmp.idBoisson, tmp.nom, &tmp.prix, &tmp.quantite);
        if(tmp.id > 0){
            printf("\t\t%d", tmp.id);
            printf("\t%s", tmp.nom);
            printf("\t%.2f", tmp.prix);
            printf("\t%.2f\n", tmp.quantite);

            if(fgetc(file) != '\n'){
                break;
            }
        }else{
            if(fgetc(file) != '\n'){
                break;
            }
        }
    }
    */

    fclose(file);

}
