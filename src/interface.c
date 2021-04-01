#include "interface.h"

int interface(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t1. Interface Barman\n\n");
    printf("\t\t2. Interface Client\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numéro de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        while(retour != 1){                
            printf("Entrer un chiffre.");
            exit(-1);
        }
    }
    if(numInter < 1 || numInter > 2){
        while(numInter < 1 || numInter > 2){                
            printf("Entrer un numéro valide d'interface:");
            retour = scanf("%d", &numInter);

        }
    }
    return numInter;
}
