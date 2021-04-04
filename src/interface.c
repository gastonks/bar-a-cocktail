//TODO: Faire comme un chemin de fichier pour savoir ou l'on se trouve dans l'interface.

#include "interface.h"

void interfaceAccueil(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Principal\n\n");
    printf("\t\t1. Interface Barman\n\n");
    printf("\t\t2. Interface Client\n\n");
    printf("\t\t0. Quitter le programme\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.");
        exit(-1);
    }else{
        switch (numInter)
        {
        case 1:
            interfaceBarman();
            break;
        case 2:
            interfaceClient();
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
    printf("\t\t\tMenu Barman\n\n");
    printf("\t\t1. Gestion des boissons\n\n");
    printf("\t\t2. Gestion des cocktails\n\n");
    printf("\t\t3. Gestion des finances\n\n");
    printf("\t\t0. Quitter l'interface\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 1:
            interfaceGestionBoisson();
            break;
        case 2:
            printf("gestion cocktail");
            break;
        case 3:
            printf("gestion finances");
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

void interfaceClient(){

    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Client\n\n");
    printf("\t\t1. Gestion des boissons\n\n");
    printf("\t\t2. Gestion des cocktails\n\n");
    printf("\t\t0. Quitter l'interface\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.");
        exit(-1);
    }else{
        switch (numInter)
        {
        case 1:
            interfaceGestionBoisson();
            break;
        case 2:
            printf("gestion cocktail");
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

void interfaceGestionBoisson(){
    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion des boissons\n\n");
    printf("\t\t1. Informations sur la boisson\n\n");
    printf("\t\t2. Commander un boisson\n\n");
    printf("\t\t0. Quitter l'interface\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 1:
            printf("info boisson");
            break;
        case 2:
            printf("commande boisson");
            break;
        case 0:
            printf("Sortie du l'interface.\n");
            interfaceBarman();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}