#include "interface.h"

//Définition d'une macro, permemttant de gagner du temps et de l'espace dans le programme.
const char* REMOVE_DATA = "rm -r data/boissonBarman.dat data/boissonBarmantmp.dat data/commandeClient.dat data/cocktail.dat data/cocktailListBoisson.dat";

int idUser = 0; // 1 = Barman ; 2 = Client
int nbBoiss = 0; // nombre boisson ajoutee


/*  
    Interface principale du programme, c'est celle-ci qui est appelée en première lors de l'exécution du programme.
    On a le choix sur l'interface à laquelle on veut accéder, et on peut aussi supprimer le fichier de sauvegarde des boissons.
    On demande simplement à l'utilisateur d'entrer un nombre pour accéder à une interface, 
    on effectue ce processus à chaque fois que l'on veut accéder à une interface.

    La logique des interfaces est la suivante : on entre un nombre de 1 à n pour accéder à une des n interfaces, on entre 0 pour revenir en arrière,
    et si un nombre négatif ou un nombre supérieur au nombre d'interfaces est entré, alors la fonction de l'interface dans laquelle on se situe est
    tout simplement reafficher.
*/
void interfaceAccueil(){

    idUser = 0;
    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Principal\n\n");
    printf("\t\t1. Interface Barman\n\n");
    printf("\t\t2. Interface Client\n\n");
    printf("\t\t3. Efface entierement le fichier de sauvegarde des boissons\n\n");
    printf("\t\t0. Quitter le programme\n\n");
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
            interfaceBarman();
            break;
        case 2:
            interfaceClient();
            break;
        case 3:
            system(REMOVE_DATA);
            printf("Le fichier de sauvegarde des boissons a bien ete supprimee s'il existe.\n");
            break;

        case 0:
            printf("Sortie du programme.\n");
            break;
        
        default:
            interfaceAccueil();
            break;
        }
    }
}

/*  
    Interface principale du barman, on a accès aux différentes fonctionnalités disponibles au barman à partir de cette interface.  
*/
void interfaceBarman(){

    idUser = 1;

    int numInter = 0;
    int retour = 0;
    system("clear");
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
        /*
        case 2:
            interfaceGestionCocktail();
            break;
        */
        case 3:
            interfaceGestionFinance();
            break;
        case 0:
            interfaceAccueil();
            break;
        
        default:
            interfaceBarman();
            break;
        }
    }
}

/*
    Interface principale du client, on a accès aux différentes fonctionnalités disponibles au client à partir de cette interface.
*/
void interfaceClient(){

    idUser = 2;

    int numInter = 0;
    int retour = 0;

    system("clear");
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
        /*
        case 2:
            interfaceGestionCocktail();
            break;
        */
        case 0:
            interfaceAccueil();
            break;
        
        default:
            interfaceClient();
            break;
        }
    }
}

/*
    Interface permettant principalement au client d'accéder à l'interface de commande d'une boisson.
    Il a aussi accès aux informations sur les boissons et aux informations sur les commandes.
*/
void interfaceGestionBoissonClient(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion des boissons\n\n");
    printf("\t\t1. Informations sur les boissons\n\n");
    printf("\t\t2. Information sur les commandes\n\n");
    printf("\t\t3. Commander une boisson\n\n");
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
            interfaceInformationBoissonClient();
            break;
        case 2:
            interfaceInformationCommandeClient();
        case 3:
            interfaceCommandeBoisson();
            break;
        case 0:
            interfaceClient();
            break;
        
        default:
            interfaceGestionBoissonClient();
            break;
        }
    }
}

/*
    Interface de gestion des boisson du barman. Cette interface lui permet d'avoir toutes les inforamtions sur les boissons, ajouter/supprimer une boisson,
    modifier une boisson et modifier le stock d'une boisson.
*/
void interfaceGestionBoissonBarman(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion des boissons\n\n");
    printf("\t\t1. Informations sur les boissons\n\n");
    printf("\t\t2. Ajouter ou supprimer une boisson\n\n");
    printf("\t\t3. Modifie une boisson\n\n");
    printf("\t\t4. Gestion du stock de boisson\n\n");
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
            interfaceInformationBoissonBarman();
            break;
        case 2:
            interfaceAjoutOuSuppBoisson();
            break;
        case 3:
            modifBoisson();
            break;
        case 4:
            gestionStock();
            break;
        case 0:
            interfaceBarman();
            break;
        
        default:
            interfaceGestionBoissonBarman();
            break;
        }
    }
}

/*
    Interface permettant d'ajouter ou de supprimer une boisson. Il est possible d'ajouter une boisson alcoolisée ou non, et de supprimer une boisson.
*/
void interfaceAjoutOuSuppBoisson(){

    int numInter = 0;
    int retour = 0;
    system("clear");
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
            interfaceAjoutOuSuppBoisson();
            break;
        }

    }
}

/*
    A COMPLETER AVEC LA NOUVELLE VERSION
    Interface de gestion des finances. Il permet, pour le moment, d'afficher les recettes journalières.
*/
void interfaceGestionFinance(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion Finances\n\n");
    printf("\t\tLa recette des commandes du jour est de : %.2f €.\n\n", recette());
    printf("===============================================================\n\n");

    printf("Entrer 0 pour revenir en arriere :");
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
            interfaceGestionFinance();
            break;
        }
    }


}

/*
    Interface affichant les informations sur les boissons, pour le barman. Toutes les boissons sont affichées sous forme de liste. 
*/
void interfaceInformationBoissonBarman(){
    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("=====================================================================================================\n\n");

    printf("Entrer 0 pour revenir en arriere:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 0:
            interfaceGestionBoissonBarman();
            break;
        
        default:
            interfaceInformationBoissonBarman();
            break;
        }
    }

}

/*
    Interface affichant les informations sur les boissons, pour le client. Toutes les boissons sont affichées sous forme de liste.
*/
void interfaceInformationBoissonClient(){
    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\n\n");

    informationBoissonClient();

    printf("=====================================================================================================\n\n");

    printf("Entrer 0 pour revenir en arriere:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 0:
            interfaceGestionBoissonClient();
            break;
        
        default:
            interfaceInformationBoissonClient();
            break;
        }
    }

}

/*
    Interface permemttant de commander une boisson. Le client entre l'ID de la boisson qu'il désire, qui est ensuite traité par la fonction commandeBoissonClient()
*/
void interfaceCommandeBoisson(){
    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu commande d'une boisson\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\n\n");

    informationBoissonClient();

    printf("=====================================================================================================\n\n");

    printf("Entrer l'ID de la boisson que vous voulez commander.\nEntrer 0 pour annuler la commande:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{
        if(numInter == 0){
            interfaceGestionBoissonClient();
        }else if(numInter > calcTailleFichier() || numInter<0){
            interfaceCommandeBoisson();
        }else{
            commandeBoissonClient(numInter);
        }
    }  
} 

/*
    Interface affichant l'historique des commandes. Toutes les commandes sont affichées en liste. 
*/
void interfaceInformationCommandeClient(){
    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tPrix\tQuantite_Commande\n\n");

    informationCommandeClient();

    printf("=====================================================================================================\n\n");

    printf("Entrer 0 pour revenir en arriere:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 0:
            interfaceGestionBoissonClient();
            break;
        
        default:
            interfaceInformationCommandeClient();
            break;
        }
    }

}


/*
    SUREMENT A MODIFIER OU COMPLETER
    Interface de gestion des cocktails. En fonction de l'interface (barman ou client), des inforamtions différentes sont affichées.
    Pour le barman, il est possible d'avoir les informations sur les cocktails, de créer un coktails (et de supprimer un cocktail).
    Pour le client, il est possible d'avoir les informations sur les cocktails, de créer son propre cocktail et de commander un cocktail déjà existant.
*/
/*
void interfaceGestionCocktail(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    if(idUser == 1){
        printf("===============================================================\n\n");
        printf("\t\t\tMenu Gestion des cocktails\n\n");
        printf("\t\t1. Informations sur les cocktails\n\n");
        printf("\t\t2. Création d'un cocktail\n\n");
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
                    interfaceInformationCocktail();
                    break;
                case 2:
                    creationCocktailBarman();
                    break;
                case 0:
                    interfaceBarman();
                    break;
                default:
                    interfaceGestionCocktail();
                    break;
            }
        }
    }else{
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
                    interfaceInformationCocktail();
                    break;
                case 2:
                    printf("création cocktail");
                    break;
                case 3:
                    printf("commande cocktail");
                    break;
                case 0:
                    interfaceClient();
                    break;
                
                default:
                    interfaceGestionCocktail();
                    break;
            }
        } 
    }
}
*/

/*
    Interface affichant les informations sur les cocktails.
*/
/*
void interfaceInformationCocktail(){
    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("=======================================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les cocktails\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tNombre_Boisson\n\n");

    informationCocktail();

    printf("\n\n=======================================================================================================================\n\n");


    printf("Entrer 0 pour revenir en arriere:");
    retour = scanf("%d", &numInter);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }else{

        switch (numInter)
        {
        case 0:
            interfaceGestionCocktail();
        default:
            interfaceInformationCocktail();
            break;
        }
    }
}
*/