// TODO : réparer l'affiche d'élément vide pour les infos des boissons

#include "interaction.h"
#include "interface.h"

//const char* BOISSON_FORMAT_OUT = "{\n\t\"id:\": %d,\n\t\"nomBoisson\": \"%s\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f,\n\t\"dgrScr:\": %.2f\n}\n";
//const char* BOISSON_FORMAT_IN = "{\n\t\"id:\": %d,\n\t\"nomBoisson\": \"%[^\"]\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f,\n\t\"dgrScr:\": %.2f\n}";
const char* BOISSON_FORMAT_OUT = "(%d, %s, %.2f, %.2f, %.2f, %.2f, %.2f)\n";
const char* BOISSON_FORMAT_IN = "(%d, %[^,], %f, %f, %f, %f, %f)";

void initFile(void){
    FILE* file = fopen("data/boisson.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    fclose(file);
}

void ajoutBoissonAlcool(){

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

    printf("Entrer le degre d'alcool de cette boisson :");
    retour = scanf("%f", &nouvBoisson.degreAlco);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    nouvBoisson.id = idInit();

    //nouvBoisson.id = idInit();
    //printf("\nID : %d\n", nouvBoisson.id);

    // Interaction avec un fichier de sauvegarde

    FILE* file = fopen("data/boisson.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    fprintf(file, BOISSON_FORMAT_OUT, nouvBoisson.id, nouvBoisson.nom,nouvBoisson.contenance ,nouvBoisson.prix, nouvBoisson.quantite, nouvBoisson.degreAlco, 0.00);
    fclose(file);

    interfaceAjoutOuSuppBoisson();
}

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

    FILE* file = fopen("data/boisson.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    fprintf(file, BOISSON_FORMAT_OUT, nouvBoisson.id, nouvBoisson.nom, nouvBoisson.contenance,nouvBoisson.prix, nouvBoisson.quantite, 0.00, nouvBoisson.degreScr);
    fclose(file);


    interfaceAjoutOuSuppBoisson();

}

void informationBoisson(){

    boisson tmp;

    FILE* file = fopen("data/boisson.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    rewind(file);
    // while(!= '\n')
    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.quantite, &tmp.degreAlco, &tmp.degreScr);
        printf("\t\t%d", tmp.id);
        printf("\t%s", tmp.nom);
        printf("\t%.2f", tmp.contenance);
        printf("\t\t%.2f", tmp.prix);
        printf("\t%.2f", tmp.quantite);
        printf("\t\t%.2f", tmp.degreAlco);
        printf("\t\t%.2f\n", tmp.degreScr);
        if(fgetc(file) != '\n'){
            break;
        }
    }

    fclose(file);

}

int idInit(){
    
    boisson tmp;

    int nID = tmp.id;

    FILE* file = fopen("data/boisson.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    rewind(file);

    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.quantite, &tmp.degreAlco, &tmp.degreScr);
/*
        if(nID == 0){
            nID++;
            printf("\ntmp.id : %d\n", tmp.id);
            printf("\nnID: %d\n", nID);
            return tmp.id;
        }else{
            while(tmp.id == nID){
                nID++;
            }
            printf("\ntmp.id : %d\n", tmp.id);
            printf("\nnID: %d\n", nID);
            return nID;
        }
*/

        if(fgetc(file) != '\n'){
            break;
        }
    }


    nID = tmp.id + 1;


    return nID;

    fclose(file);   
}

void suppBoisson(){

    int idSupp = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tQuantité\tDegre Alcool\tDegre Sucre\n\n");

    informationBoisson();

    printf("===============================================================\n\n");

    printf("Entrer l'ID de la boisson à supprimer :");
    retour = scanf("%d", &idSupp);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }

    boisson tmp;

    FILE* file = fopen("data/boisson.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    rewind(file);

    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.quantite, &tmp.degreAlco, &tmp.degreScr);

        if(tmp.id == idSupp){
            fprintf(file, BOISSON_FORMAT_OUT, 0, 0, 0, 0, 0, 0, 0);
        }

        if(fgetc(file) != '\n'){
            break;
        }
    }
    fclose(file);

    interfaceAjoutOuSuppBoisson();

}
