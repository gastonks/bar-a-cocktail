#include "boissonClient.h"


const char* BOISSON_FORMAT_CLIENT_OUT = "\n(%d, %s, %.2f, %.2f, %.2f, %.2f, %.2f)";
const char* BOISSON_FORMAT_CLIENT_EX = "(%d, %s, %.2f, %.2f, %.2f, %.2f, %.2f)";
const char* BOISSON_FORMAT_CLIENT_IN = "(%d, %[^,], %f, %f, %f, %f, %f)";

const char* COMMANDE_FORMAT_CLIENT_OUT = "\n(%d, %s, %.2f, %.2f)";
const char* COMMANDE_FORMAT_CLIENT_IN = "(%d, %[^,], %f, %f)";
const char* COMMANDE_FORMAT_CLIENT_EX = "(%d, %s, %.2f, %.2f)";

void initFileClient(void){
    FILE* file = fopen("data/commandeClient.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    if(ftell(file) == 0){
        fprintf(file, COMMANDE_FORMAT_CLIENT_EX, 0, "Exemple",0,0);
    } 

    fclose(file);
}

int idInitCommande(){
    commande tmp;

    int nID = 0;
    FILE* file = fopen("data/commandeClient.dat", "r");
    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    rewind(file);

    while(!feof(file)){
        
        fscanf(file, COMMANDE_FORMAT_CLIENT_IN, &tmp.id, tmp.nom, &tmp.prix, &tmp.quantite);

        if(fgetc(file) != '\n'){
            break;
        }
    }

    nID = tmp.id + 1;
    fclose(file);   
    return nID;
}

void informationBoissonClient(){

    boisson tmp;

    FILE* file = fopen("data/boissonBarman.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    rewind(file);

    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_CLIENT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);
        if(tmp.quantite > 0){
            printf("\t\t%d", tmp.id);
            printf("\t%s", tmp.nom);
            printf("\t%.2f", tmp.contenance);
            printf("\t\t%.2f", tmp.prix);
            printf("\t%.2f\t", tmp.degreAlco);
            printf("\t%.2f\n", tmp.degreScr);
            if(fgetc(file) != '\n'){
                break;
            }
        }else{
            if(fgetc(file) != '\n'){
                break;
            }
        }
    }

    fclose(file);

}

void commandeBoissonClient(int idBoisson){

    FILE* fileCommande = fopen("data/commandeClient.dat", "a");
    FILE* fileBoisson = fopen("data/boissonBarman.dat", "r");

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


    while(!feof(fileBoisson)){

        fscanf(fileBoisson, BOISSON_FORMAT_CLIENT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);

        if(idBoisson == tmp.id){
            printf("\ntmp.id = %d\n", tmp.id);
            printf("\nidBoisson = %d\n", idBoisson);
            nComm.prix = nComm.quantite * tmp.prix;
            fprintf(fileCommande, COMMANDE_FORMAT_CLIENT_OUT, nComm.id, tmp.nom, nComm.prix, nComm.quantite);
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

    interfaceGestionBoissonClient();
}


void informationCommandeClient(){

    commande tmp;

    FILE* file = fopen("data/commandeClient.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    rewind(file);
    
    while(!feof(file)){
        
        fscanf(file, COMMANDE_FORMAT_CLIENT_IN, &tmp.id, tmp.nom, &tmp.prix, &tmp.quantite);
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

    fclose(file);

}