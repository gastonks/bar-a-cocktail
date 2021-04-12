#include "interaction.h"
#include "interface.h"

const char* BOISSON_ALCOOL_FORMAT_OUT = "{\n\t\"nomBoisson\": \"%s\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f\n}\n";
const char* BOISSON_NON_ALCOOL_FORMAT_OUT = "{\n\t\"nomBoisson\": \"%s\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrScr:\": %.2f\n}\n";


void ajoutBoissonAlcool(){

    boissonAlcool nouvBoisson;

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

    // Interaction avec un fichier de sauvegarde

    FILE* file = fopen("data/boisson.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    fprintf(file, BOISSON_ALCOOL_FORMAT_OUT, nouvBoisson.nom,nouvBoisson.contenance ,nouvBoisson.prix, nouvBoisson.quantite, nouvBoisson.degreAlco);
    fseek(file, 0, SEEK_SET);
    fclose(file);


    interfaceAjoutOuSuppBoisson();
}

void ajoutBoissonNonAlcool(){

    boissonScr nouvBoisson;

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

    printf("Entrer le degre de sucre de cette boisson :");
    retour = scanf("%f", &nouvBoisson.degreScr);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    FILE* file = fopen("data/boisson.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    fprintf(file, BOISSON_NON_ALCOOL_FORMAT_OUT, nouvBoisson.nom, nouvBoisson.contenance,nouvBoisson.prix, nouvBoisson.quantite, nouvBoisson.degreScr);
    fseek(file, 0, SEEK_SET);
    fclose(file);


    interfaceAjoutOuSuppBoisson();

}
