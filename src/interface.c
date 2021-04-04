#include "interface.h"

void interfaceAccueil(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t1. Interface Barman\n\n");
    printf("\t\t2. Interface Client\n\n");
    printf("\t\t0. Quitter le programme\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numéro de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numéro de l'interface.");
        exit(-1);
    }else{
        switch (numInter)
        {
        case 1:
            interfaceBarman();
            break;
        case 2:
            printf("interface client");
            break;

        case 0:
            printf("Sortie du programme.\n");
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}

void interfaceBarman(){
    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t1. Gestion des boissons\n\n");
    printf("\t\t2. Gestion des cocktails\n\n");
    printf("\t\t3. Gestion des finances\n\n");
    printf("\t\t0. Quitter l'interface\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numéro de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numéro de l'interface.");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 1:
            printf("gestion boisson");
            break;
        case 2:
            printf("gestion cocktail");
            break;
        case 3:
            printf("gestionfinacaes");
            break;
        case 0:
            printf("Sortie du l'interface.\n");
            interfaceAccueil();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}
