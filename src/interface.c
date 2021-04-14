#include "interface.h"
#include "interaction.h"

int idUser = 0; // 1 = Barman ; 2 = Client
int nbBoiss = 0; // nombre boisson ajoutee

void interfaceAccueil(){

    idUser = 0;
    int numInter = 0;
    int retour = 0;
    system("cls");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Principal\n\n");
    printf("\t\t1. Interface Barman\n\n");
    printf("\t\t2. Interface Client\n\n");
    printf("\t\t3. Efface entirement le fichier de sauvegarde des boissons\n\n");
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
        case 3: 
            system("del data/boisson.dat");
            printf("Le fichier de sauvegarde des boissons a bien ete supprimee s'il existe.\n");
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

    idUser = 1;

    int numInter = 0;
    int retour = 0;
    system("cls");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Barman\n\n");
    printf("\t\t1. Gestion des boissons\n\n");
    printf("\t\t2. Gestion des cocktails\n\n");
    printf("\t\t3. Gestion des finances\n\n");
    printf("\t\t0. Revenir en arrière\n\n");
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
            interfaceGestionBoissonBarman();
            break;
        case 2:
            interfaceGestionCocktail();
            break;
        case 3:
            interfaceGestionFinance();
            break;
        case 0:
            interfaceAccueil();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}

void interfaceClient(){

    idUser = 2;

    int numInter = 0;
    int retour = 0;

    system("cls");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Client\n\n");
    printf("\t\t1. Gestion des boissons\n\n");
    printf("\t\t2. Gestion des cocktails\n\n");
    printf("\t\t0. Revenir en arrière\n\n");
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
            interfaceGestionBoissonClient();
            break;
        case 2:
            interfaceGestionCocktail();
            break;
        case 0:
            interfaceAccueil();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}

void interfaceGestionBoissonClient(){

    int numInter = 0;
    int retour = 0;
    system("cls");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion des boissons\n\n");
    printf("\t\t1. Informations sur les boissons\n\n");
    printf("\t\t2. Commander une boisson\n\n");
    printf("\t\t0. Revenir en arrière\n\n");
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
            interfaceInformationBoisson();
            break;
        case 2:
            printf("commande boisson");
            break;
        case 0:
            interfaceClient();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}

void interfaceGestionBoissonBarman(){

    int numInter = 0;
    int retour = 0;
    system("cls");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion des boissons\n\n");
    printf("\t\t1. Informations sur les boissons\n\n");
    printf("\t\t2. Ajouter ou supprimer une boisson\n\n");
    printf("\t\t3. Gestion du stock de boisson\n\n");
    printf("\t\t0. Revenir en arrière\n\n");
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
            interfaceInformationBoisson();
            break;
        case 2:
            interfaceAjoutOuSuppBoisson();
            break;
        case 3:
            printf("gestion stock boisson");
            break;
        case 0:
            interfaceBarman();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}

void interfaceAjoutOuSuppBoisson(){
    int numInter = 0;
    int retour = 0;
    system("cls");
    puts("");
    // for(int j = 0; j<calcTaille(); j++) {
    //     printf("%s, %.2f, %.2f, %.2f, %.2f, %.2f\n", tab[j].nom, tab[j].contenance, tab[j].prix, tab[j].quantite, tab[j].degreAlco, tab[j].degreScr);
    // }
    puts("");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Ajout ou suppression de boisson\n\n");
    printf("\t\t1. Ajouter une boisson alcoolisee\n\n");
    printf("\t\t2. Ajouter une boisson non alcoolisee\n\n");
    printf("\t\t3. Supprimer une boisson\n\n");
    printf("\t\t0. Revenir en arrière\n\n");
    printf("===============================================================\n\n");

    switch (nbBoiss)
    {
    case 0:
        printf("Aucune boisson a ete ajoutee recemment.\n\n");
        break;
    case 1:
        printf("Une boisson a ete ajoutee recemment.\n\n");
        break;
    
    default:
        printf("%d boissons ont ete ajoutees recemment.\n\n", nbBoiss);
        break;
    }

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{
        switch (numInter)
        {
        case 1:
            nbBoiss++;
            ajoutBoissonAlcool();
            break;
        case 2:
            nbBoiss++;
            ajoutBoissonNonAlcool();
            break;
        case 3:
            suppBoisson();
            break;
        case 0:
            interfaceGestionBoissonBarman();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }

    }
}

void interfaceGestionCocktail(){

    int numInter = 0;
    int retour = 0;
    system("cls");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion des cocktails\n\n");
    printf("\t\t1. Informations sur les cocktails\n\n");
    printf("\t\t2. Création d'un cocktail\n\n");
    printf("\t\t3. Commander un cocktail\n\n");
    printf("\t\t0. Revenir en arrière\n\n");
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
            printf("info cocktail");
            break;
        case 2:
            printf("création cocktail");
            break;
        case 3:
            printf("commande cocktail");
            break;
        case 0:
            if(idUser == 1){
                interfaceBarman();
            }else{
                interfaceClient();
            }
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    } 
}

void interfaceGestionFinance(){

    int numInter = 0;
    int retour = 0;
    system("cls");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion Finances\n\n");
    printf("\t\tLa recette du jour est de : 0 €\n\n");
    printf("\t\tLe bar a généré %.2f € par rapport à hier.\n\n", -0.2);
    printf("===============================================================\n\n");

    printf("Entrer 0 pour revenir en arrière:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 0:
            interfaceBarman();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }


}

void interfaceInformationBoisson(){
    int numInter = 0;
    int retour = 0;

    system("cls");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tQuantité\tDegre Alcool\tDegre Sucre\n\n");

    informationBoisson();

    printf("===============================================================\n\n");

    printf("Entrer 0 pour revenir en arrière:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 0:
            if(idUser == 1){
                interfaceGestionBoissonBarman();
            }else{
                interfaceGestionBoissonClient();
            }
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }

}