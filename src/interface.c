/*! \file interface.c
*  \author Barre Romain
*  \version 1
*  \brief Programme contenant toutes les interfaces, que ce soit pour le barman ou le client.  
*/

#include "interface.h"

//Definition d'une macro, permettant de gagner du temps et de l'espace dans le programme.

const char* REMOVE_DATA = "rm -r data/boissonBarman.dat data/boissonBarmantmp.dat data/commandeClient.dat data/cocktail.dat data/cocktailListBoisson.dat data/cocktailListBoissontmp.dat data/cocktailtmp.dat";

int prix = 0;
int idUser = 0; // 1 = Barman ; 2 = Client
int nbBoiss = 0; // nombre boisson ajoutee

/*! \fn void interfaceAccueil()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure principale de l'interface.
*
*  \remarks Cette procédure affiche l'interface d'acceuil principale. L'interface barman et l'interface client sont accessibles depuis cette interface. 
*/

/*  
    Interface principale du programme, c'est celle-ci qui est appelee en premiere lors de l'execution du programme.
    On a le choix sur l'interface a laquelle on veut acceder, et on peut aussi supprimer le fichier de sauvegarde des boissons.
    On demande simplement a l'utilisateur d'entrer un nombre pour acceder a une interface, 
    on effectue ce processus a chaque fois que l'on veut acceder a une interface.
    La logique des interfaces est la suivante : on entre un nombre de 1 a n pour acceder a une des n interfaces, on entre 0 pour revenir en arriere,
    et si un nombre negatif ou un nombre superieur au nombre d'interfaces est entre, alors la fonction de l'interface dans laquelle on se situe est
    tout simplement reafficher.
*/
void interfaceAccueil(){

    idUser = 0;
    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu principal\n\n");
    printf("\t\t1. Interface Barman\n\n");
    printf("\t\t2. Interface Client\n\n");
    printf("\t\t3. Efface entierement le fichier de sauvegarde des boissons\n\n");
    printf("\t\t0. Quitter le programme\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 3){
        while(retour != 1 || numInter < 0 || numInter > 3){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }
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
            printf("Erreur dans le choix de l'interface.\n");
            break;
    }
}

/*! \fn void interfaceBarman()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure principale de l'interface barman.
*
*  \remarks Cette procédure affiche l'interface d'acceuil principale du barman. Il peut accéder à la gestion des boissons, des cocktails et des finances.  
*/

/*  
    Interface principale du barman, on a acces aux differentes fonctionnalites disponibles au barman a partir de cette interface.  
*/
void interfaceBarman(){

    idUser = 1;

    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu barman\n\n");
    printf("\t\t1. Gestion des boissons\n\n");
    printf("\t\t2. Gestion des cocktails\n\n");
    printf("\t\t3. Gestion des finances\n\n");
    printf("\t\t0. Revenir en arriere\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 3){
        while(retour != 1 || numInter < 0 || numInter > 3){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

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

/*! \fn void interfaceClient()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure principale de l'interface client.
*
*  \remarks Cette procédure affiche l'interface d'acceuil principale du client. Il peut accéder aux commandes à partir de cette interface.  
*/

/*
    Interface principale du client, on a acces aux differentes fonctionnalites disponibles au client a partir de cette interface.
*/
void interfaceClient(){

    idUser = 2;

    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu client\n\n");
    printf("\t\t1. Information sur les boissons\n\n");
    printf("\t\t2. Gestion des cocktails\n\n");
    printf("\t\t3. Information sur les paniers\n\n");
    printf("\t\t4. Creer un panier\n\n");
    printf("\t\t5. Supprimer un panier\n\n");
    printf("\t\t6. Modifier un panier\n\n");
    printf("\t\t0. Revenir en arriere\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 6){
        while(retour != 1 || numInter < 0 || numInter > 6){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }
    switch (numInter)
        {
        case 1:
            interfaceInformationBoissonClient();
            break;
        case 2:
            interfaceGestionCocktail();
            break;
        case 3:
            interfaceInformationCommande();
            break;
        case 4:
            interfaceInitCommande();
            break;
        case 5:
            interfaceSuppCommande();
        case 6:
            interfaceModifCommande();
        case 0:
            interfaceAccueil();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
    }
}

/*! \fn void interfaceGestionBoissonBarman()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman d'accéder aux fonctions de gestion des boissons.
*
*  \remarks Cette procédure permet au barman d'accéder à plusieurs interfaces pour gérer les boissons.
*  Il peut afficher toutes les informations sur les boissons, ajouter ou supprimer une boisson, modifier une boisson, gérer le stock des boissons et enfin satisfaire les commandes.  
*/

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
    printf("\t\t5. Satisfaire une commande d'un client\n\n");
    printf("\t\t0. Revenir en arriere\n\n");
    printf("===============================================================\n\n");

    printf("Entrer le numero de l'interface:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 5){
        while(retour != 1 || numInter < 0 || numInter > 5){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    switch (numInter)
        {
        case 1:
            interfaceInformationBoissonBarman();
            break;
        case 2:
            interfaceAjoutOuSuppBoisson();
            break;
        case 3:
            interfaceModifBoisson();
            break;
        case 4:
            interfaceGestionStock();
            break;
        case 5:
            interfaceSatisfactionCommande();
            break;
        case 0:
            interfaceBarman();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
    }
}

/*! \fn void interfaceAjoutOuSuppBoisson()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman d'accéder aux fonctions pour supprimer ou ajouter une boisson.
*
*  \remarks Cette procédure permet au barman d'ajouter une boisson alcoolisée ou non, ou d'en supprimer une.  
*/

/*
    Interface permettant d'ajouter ou de supprimer une boisson. Il est possible d'ajouter une boisson alcoolisee ou non, et de supprimer une boisson.
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
    printf("\t\t0. Revenir en arriere\n\n");
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

    if(retour != 1 || numInter < 0 || numInter > 3){
        while(retour != 1 || numInter < 0 || numInter > 3){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }
    switch (numInter)
        {
        case 1:
            nbBoiss++;
            interfaceAjoutBoissonAlcool();
            break;
        case 2:
            nbBoiss++;
            interfaceAjoutBoissonNonAlcool();
            break;
        case 3:
            nbBoiss--;
            interfaceSuppBoisson();
            break;
        case 0:
            interfaceGestionBoissonBarman();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
}

/*! \fn void interfaceAjoutBoissonAlcool()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman d'ajouter une boisson alcoolisée.
*
*  \remarks Cette procédure permet au barman d'ajouter une boisson alcoolisée. 
*  Il doit entrer toutes les informations de la boisson, puis une fonction sera utilisée pour ajouter cette boisson dans le tableau qui les stocke.  
*/

/*
    Interface pour ajouter une boisson alcoolisee.
*/
void interfaceAjoutBoissonAlcool(){

    boisson nouvBoisson;
    int numInter;

    /*
        On demande a l'utilisateur d'entrer les informations de la boisson une par une, sauf le degre de sucre que l'on met automatiquement a 0, 
        puisqu'il s'agit d'une boisson alcoolisee.
    */
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\tMenu de l'ajout d'une boisson\n\n");

    printf("Entrez 0 pour revenir en arrière.\nEntrez 1 pour ajouter la nouvelle boisson:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 1){
        while(retour != 1 || numInter < 0 || numInter > 1){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    switch (numInter)
    {
    case 0:
        interfaceAjoutOuSuppBoisson();
        break;
    case 1:
        printf("Veuillez entrer le nom de la boisson :");
        getchar();
        retour = scanf("%[^\n]", nouvBoisson.nom);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        printf("Entrer la contenance de la boisson :");
        retour = scanf("%f", &nouvBoisson.contenance);
        if(retour != 1 || nouvBoisson.contenance < 0){
        while(retour != 1 || nouvBoisson.contenance < 0){
                retour = 1;
                printf("Cette contenance est impossible.\n");
                printf("Veuillez entrer une contenance de boisson positive:");
                getchar();
                retour = scanf("%f", &nouvBoisson.contenance);
            }
        }

        printf("Entrer le prix de la boisson :");
        retour = scanf("%f", &nouvBoisson.prix);
        if(retour != 1 || nouvBoisson.prix < 0){
        while(retour != 1 || nouvBoisson.prix < 0){
                retour = 1;
                printf("Ce prix est impossible.\n");
                printf("Veuillez entrer un prix de boisson positif:");
                getchar();
                retour = scanf("%f", &nouvBoisson.prix);
            }
        }

        printf("Entrer la quantite de boisson :");
        retour = scanf("%f", &nouvBoisson.quantite);
        if(retour != 1 || nouvBoisson.quantite < 0){
        while(retour != 1 || nouvBoisson.quantite < 0){
                retour = 1;
                printf("Cette quantite est impossible.\n");
                printf("Veuillez entrer une quantite de boisson positive:");
                getchar();
                retour = scanf("%f", &nouvBoisson.quantite);
            }
        }

        printf("Entrer le degre d'alcool de cette boisson :");
        retour = scanf("%f", &nouvBoisson.degreAlco);
        if(retour != 1 || nouvBoisson.degreAlco < 0){
        while(retour != 1 || nouvBoisson.degreAlco < 0){
                retour = 1;
                printf("Ce degre d'alcool est impossible.\n");
                printf("Veuillez entrer un degre d'alcool positif:");
                getchar();
                retour = scanf("%f", &nouvBoisson.degreAlco);
            }
        }

        ajoutBoissonAlcool(nouvBoisson.nom, nouvBoisson.contenance, nouvBoisson.prix, nouvBoisson.quantite, nouvBoisson.degreAlco);
        break;
    default:
        printf("Erreur dans la saisie de l'interface.");
        break;
    }

}

/*! \fn void interfaceAjoutBoissonNonAlcool()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman d'ajouter une boisson non alcoolisée.
*
*  \remarks Cette procédure permet au barman d'ajouter une boisson non alcoolisée. 
*  Il doit entrer toutes les informations de la boisson, puis une fonction sera utilisée pour ajouter cette boisson dans le tableau qui les stocke.  
*/

/*
    Interface pour ajouter une boisson non alcoolisee.
*/
void interfaceAjoutBoissonNonAlcool(){

    boisson nouvBoisson;

    /*
        On demande a l'utilisateur d'entrer les informations de la boisson une par une, sauf le degre d'alcool que l'on met automatiquement a 0, 
        puisqu'il s'agit d'une boisson non alcoolisee.
    */

    int retour = 0;
    int numInter;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\tMenu de l'ajout d'une boisson\n\n");

    printf("Entrez 0 pour revenir en arrière.\nEntrez 1 pour ajouter la nouvelle boisson:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 1){
        while(retour != 1 || numInter < 0 || numInter > 1){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    switch (numInter)
    {
    case 0:
        interfaceAjoutOuSuppBoisson();
        break;
    case 1:
        printf("Veuillez entrer le nom de la boisson :");
        getchar();
        retour = scanf("%[^\n]", nouvBoisson.nom);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        printf("Entrer la contenance de la boisson :");
        retour = scanf("%f", &nouvBoisson.contenance);
        if(retour != 1 || nouvBoisson.contenance < 0){
        while(retour != 1 || nouvBoisson.contenance < 0){
                retour = 1;
                printf("Cette contenance est impossible.\n");
                printf("Veuillez entrer une contenance de boisson positive:");
                getchar();
                retour = scanf("%f", &nouvBoisson.contenance);
            }
        }

        printf("Entrer le prix de la boisson :");
        retour = scanf("%f", &nouvBoisson.prix);
        if(retour != 1 || nouvBoisson.prix < 0){
        while(retour != 1 || nouvBoisson.prix < 0){
                retour = 1;
                printf("Ce prix est impossible.\n");
                printf("Veuillez entrer un prix de boisson positif:");
                getchar();
                retour = scanf("%f", &nouvBoisson.prix);
            }
        }

        printf("Entrer la quantite de boisson :");
        retour = scanf("%f", &nouvBoisson.quantite);
        if(retour != 1 || nouvBoisson.quantite < 0){
        while(retour != 1 || nouvBoisson.quantite < 0){
                retour = 1;
                printf("Cette quantite est impossible.\n");
                printf("Veuillez entrer une quantite de boisson positive:");
                getchar();
                retour = scanf("%f", &nouvBoisson.quantite);
            }
        }

        printf("Entrer le degre de sucre de cette boisson :");
        retour = scanf("%f", &nouvBoisson.degreScr);
        if(retour != 1 || nouvBoisson.degreScr < 0){
        while(retour != 1 || nouvBoisson.degreScr < 0){
                retour = 1;
                printf("Ce degre d'alcool est impossible.\n");
                printf("Veuillez entrer un degre de sucre positif:");
                getchar();
                retour = scanf("%f", &nouvBoisson.degreScr);
            }
        }

        ajoutBoissonNonAlcool(nouvBoisson.nom, nouvBoisson.contenance, nouvBoisson.prix, nouvBoisson.quantite, nouvBoisson.degreScr);
        break;
    default:
        printf("Erreur dans la saisie du numero de l'interface.");
        break;
    }
}

/*! \fn void interfaceSuppBoisson()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman de supprimer une boisson.
*
*  \remarks Cette procédure permet au barman de supprimer une boisson. 
*  Il doit entrer l'ID de la boisson à supprimer et une fonction est utilisée pour supprimer la boissons du tableau qui les stocke.  
*/

/*
    Interface pour supprimer une boisson.
*/
void interfaceSuppBoisson(){

    // On cree une variable qui correspond a l'ID de la boisson a supprimer.

    int idSupp = 0;
    int retour = 0;

    // On affiche toutes les boissons, ainsi que leurs informations. 

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

     // On demande a l'utilisateur d'entrer l'ID de la boisson qu'il desire supprimer. On verifie aussi s'il y a eu une erreur dans la saisie.
    printf("Entrer l'ID de la boisson a supprimer (0 pour revenir en arriere):");
    retour = scanf("%d", &idSupp);

    if(retour != 1 || idSupp < 0){
        while(retour != 1 || idSupp < 0 || idSupp > tailleTabBarman()){
                retour = 1;
                printf("Cet ID de boisson est impossible.\n");
                printf("Veuillez entrer un ID de boisson possible:");
                getchar();
                retour = scanf("%d", &idSupp);
            }
    }

    // En entrant 0, l'utilisateur a la possibilite de retourner a l'interface precedente.
    // La fonction de suppression s'execute.
    if(idSupp == 0) {
        nbBoiss++;
        interfaceAjoutOuSuppBoisson();
    }else{   
        suppBoisson(idSupp);
    }

}

/*! \fn void interfaceModifBoisson()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman de modifier une boisson.
*
*  \remarks Cette procédure permet au barman de modifier une boisson. 
*  Il doit entrer l'ID de la boisson à modifer puis entrer une à une toutes les informations de la nouvelle boisson, qui sera ensuite actualisée dans le tableau.  
*/

/*
    Interface pour modifier une boisson.
*/
void interfaceModifBoisson(){

    // On cree une variable qui correspond a l'ID de la boisson a modifier.

    int idChange = 0;
    int retour = 0;

    // On affiche toutes les boissons, ainsi que leurs informations.

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    // On demande a l'utilisateur d'entrer l'ID de la boisson qu'il desire modifier.

    printf("Entrez 0 pour revenir en arrière.\nEntrer l'ID de la boisson a modifie :");
    retour = scanf("%d", &idChange);

    if(retour != 1 || idChange < 0){
        while(retour != 1 || idChange < 0){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer un nombre valide pour soit sortir ou selectionner une boisson:");
            getchar();
            retour = scanf("%d", &idChange);
        }
    }

    if(idChange == 0){
        interfaceGestionBoissonBarman();
    }else{
        modifBoisson(idChange);
    }
}

/*! \fn void interfaceGestionStock()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman de gérer le stock des boissons.
*
*  \remarks Cette procédure permet au barman de gérer les stocks des boissons. 
*  Il doit entrer l'ID de la boisson pour laquelle il veut modifer les stocks, puis entrer les stocks entrés et les stocks vendus, qui seront ensuite actualisés dans le tableau.  
*/

/*
    Interface pour gerer le stock de boisson.
*/
void interfaceGestionStock(){
    int idStock = 0;
    float stockV = 0;
    float stockR = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    if(tailleTabBarman() == 0) {
        printf("La liste est vide, il n'y a rien a modifier.\n");
        printf("Entrez 0 pour revenir en arriere : ");
        retour = scanf("%d", &idStock);
        if(retour != 1 || idStock < 0 || idStock > 0){
        while(retour != 1 || idStock < 0 || idStock > 0){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer un nombre valide pour revenir en arriere:");
            getchar();
            retour = scanf("%d", &idStock);
            }
        }
        interfaceGestionBoissonBarman();
    }

    printf("Entrez 0 pour revenir en arrière.\nEntrer l'ID de la boisson pour modifier le stock :");
    retour = scanf("%d", &idStock);

    if(retour != 1 || idStock < 0){
        while(retour != 1 || idStock < 0){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer un nombre valide pour soit sortir ou modifier le stock d'une boisson:");
            getchar();
            retour = scanf("%d", &idStock);
        }
    }

    if(idStock == 0){
        interfaceGestionBoissonBarman();
    }else{
        printf("Entrer la quantite de boisson recue :");
        retour = scanf("%f", &stockR);
        if(retour != 1 || stockR < 0){
            while(retour != 1 || stockR < 0){
                retour = 1;
                printf("Cette quantite est impossible.\n");
                printf("Veuillez entrer une quantite de boisson positive:");
                getchar();
                retour = scanf("%f", &stockR);
            }
        }
        printf("Entrer la quantite de boisson vendue :");
        retour = scanf("%f", &stockV);
        if(retour != 1 || stockV < 0){
            while(retour != 1 || stockV < 0){
                retour = 1;
                printf("Cette quantite est impossible.\n");
                printf("Veuillez entrer une quantite de boisson positive:");
                getchar();
                retour = scanf("%f", &stockV);
            }
        }
    }

    gestionStock(idStock, stockR, stockV);
}

/*! \fn void interfaceSatisfactionCommande()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman de satisfaire une commande.
*
*  \remarks Cette procédure permet au barman de satisfaire une commande. 
*  Il doit entrer l'ID de la commande à satisfaire, puis une fonction est appelée pour gérer les stocks et l'argent obtenue.  
*/

void interfaceSatisfactionCommande(){
    int numPanier = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les commandes\n\n");

    informationCommande();

    printf("=====================================================================================================\n\n");

    printf("Entrez 0 pour revenir en arrière.\nEntrer le numero du panier que vous voulez satisfaire :");
    retour = scanf("%d", &numPanier);

    if(retour != 1 || numPanier < 0 || numPanier > tailleTabPanier()){
        while(retour != 1 || numPanier < 0 || numPanier > tailleTabPanier()){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer un nombre valide pour soit sortir, soit satisfaire une commande :");
            getchar();
            retour = scanf("%d", &numPanier);
        }
    }

    if(numPanier == 0){
        interfaceBarman();
    }else{
        satisfactionCommande(numPanier);
    }
}

/*! \fn void interfaceGestionFinance()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman d'avoir des informations sur ses finances.  
*/

/*
    Interface de gestion des finances. Il permet, pour le moment, d'afficher les recettes journalieres.
*/
void interfaceGestionFinance(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    printf("===============================================================\n\n");
    printf("\t\t\tMenu Gestion Finances\n\n");
    printf("\t\tLa recette des commandes du jour est de : %.2f €.\n\n", recette(prix));
    printf("===============================================================\n\n");

    printf("Entrer 0 pour revenir en arriere :");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter < 0 || numInter > 0){
        while(retour != 1 || numInter < 0 || numInter > 0){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer 0 pour revenir en arriere :");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }
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

/*! \fn void interfaceInformationBoissonBarman()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman d'avoir les informations des boissons.
*/

/*
    Interface affichant les informations sur les boissons, pour le barman. Toutes les boissons sont affichees sous forme de liste. 
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

    if(retour != 1 || numInter > 0 ||numInter < 0){
        while(retour != 1 || numInter > 0 || numInter < 0){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer 0 pour revenir en arriere :");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    switch (numInter)
        {
        case 0:
            interfaceGestionBoissonBarman();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
    }
}

/*! \fn void interfaceInformationBoissonClient()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au client d'avoir les informations des boissons.
*/

/*
    Interface affichant les informations sur les boissons, pour le client. Toutes les boissons sont affichees sous forme de liste.
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

    if(retour != 1 || numInter > 0 || numInter < 0){
        while(retour != 1 || numInter > 0 || numInter < 0){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer 0 pour revenir en arriere :");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

        switch (numInter)
        {
        case 0:
            interfaceClient();
            break;
        
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
}

/*! \fn void interfaceInitCommande()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au client de commander une boisson.
*/

/*
    Interface permemttant de commander une boisson. Le client entre l'ID de la boisson qu'il desire, qui est ensuite traite par la fonction commandeBoissonClient()
*/
void interfaceInitCommande(){

    int reponse = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu commande de boissons et de cocktails\n\n");

    printf("Entrer 1 pour confirmer l'intention de commander.\nEntrer 0 pour annuler la commande:");
    retour = scanf("%d", &reponse);

    if(retour != 1 || reponse < 0 || reponse > 1){
        while(retour != 1 || reponse < 0 || reponse > 1){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer un nombre valide pour soit sortir, soit commander une boisson:");
            getchar();
            retour = scanf("%d", &reponse);
        }
    }

    if(reponse == 0){
        interfaceClient();
    }else{
        demandeCommande();
    }
}

/*! \fn void interfaceInformationCommande()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure affichant l'historique des commandes.
*/

/*
    Interface affichant l'historique des commandes. Toutes les commandes sont affichees en liste. 
*/
void interfaceInformationCommande(){
    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les commandes\n\n");

    informationCommande();

    printf("=====================================================================================================\n\n");

    printf("Entrer 0 pour revenir en arriere:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter > 0 || numInter < 0){
        while(retour != 1 || numInter > 0 || numInter < 0){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer 0 pour revenir en arriere :");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    switch (numInter)
    {
    case 0:
        interfaceClient();
        break;
    default:
        printf("Erreur dans le choix de l'interface.");
        break;
    }
}

/*! \fn void interfaceInformationCommande()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant de supprimer une commande.
*/

/*
    Interface permettant de supprimer une boisson.
*/
void interfaceSuppCommande(){
    int idSupp = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les commandes\n\n");

    informationCommande();

    printf("=====================================================================================================\n\n");

    printf("Entrer le numero du panier a supprimer (0 pour revenir en arriere):");
    retour = scanf("%d", &idSupp);

    if(retour != 1 || idSupp < 0 || idSupp > tailleTabPanier()){
        while(retour != 1 || idSupp < 0 || idSupp > tailleTabPanier()){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer 0 pour revenir en arriere :");
            getchar();
            retour = scanf("%d", &idSupp);
        }
    }

    if(idSupp == 0) {
        interfaceClient();
    }else{   
        supprimerPanier(idSupp);
    }

}

/*! \fn void interfaceModifCommande()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant de modifier une commande.
*/

/*
    Interface permettant de modifier une boisson.
*/
void interfaceModifCommande(){

    // On cree une variable qui correspond au numero du panier a modifier.

    int idChange = 0;
    int retour = 0;

    // On affiche tous les paniers, ainsi que leurs informations.

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les commandes\n\n");

    informationCommande();

    printf("=====================================================================================================\n\n");

    // On demande a l'utilisateur d'entrer le numero du panier qu'il desire modifier.

    printf("Entrez 0 pour revenir en arrière.\nEntrer le numero du panier a modifie :");
    retour = scanf("%d", &idChange);

    if(retour != 1 || idChange < 0 || idChange > tailleTabPanier()){
        while(retour != 1 || idChange < 0 || idChange > tailleTabPanier()){
            retour = 1;
            printf("\nCe nombre n'existe pas.\n");
            printf("Veuillez entrer un nombre valide pour soit sortir ou selectionner un panier:");
            getchar();
            retour = scanf("%d", &idChange);
        }
    }

    if(idChange == 0){
        interfaceClient();
    }else{
        modifPanier(idChange);
        interfaceClient();
    }
}

/*! \fn void interfaceGestionCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant au barman de gérer les cocktails.
*
*  \remarks Cette procédure permet au barman de gérer les cocktails. 
*  Il a accès à différentes interfaces lui permettant de créer un cocktail, supprimer un cocktail et afficher les informations de tous les cocktails.  
*/

/*
    Interface de gestion des cocktails. En fonction de l'interface (barman ou client), des inforamtions differentes sont affichees.
    Pour le barman, il est possible d'avoir les informations sur les cocktails, de creer un coktails (et de supprimer un cocktail).
    Pour le client, il est possible d'avoir les informations sur les cocktails, de creer son propre cocktail et de commander un cocktail deja existant.
*/
void interfaceGestionCocktail(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    if(idUser == 1){
        printf("===============================================================\n\n");
        printf("\t\t\tMenu Gestion des cocktails\n\n");
        printf("\t\t1. Informations sur les cocktails\n\n");
        printf("\t\t2. Creation d'un cocktail\n\n");
        printf("\t\t3. Supprimer un cocktail\n\n");
        printf("\t\t0. Revenir en arriere\n\n");
        printf("===============================================================\n\n");
        printf("Entrer le numero de l'interface:");
        retour = scanf("%d", &numInter);

        if(retour != 1 || numInter < 0 || numInter > 3){
        while(retour != 1 || numInter < 0 || numInter > 3){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
            }
        }else{

            switch (numInter)
            {
                case 1:
                    interfaceInformationCocktail();
                    break;
                case 2:
                    creationCocktailBarman();
                    break;
                case 3:
                    supprimerCocktailDemande();
                    break;
                case 0:
                    interfaceBarman();
                    break;
                default:
                    printf("Erreur dans le choix de l'interface.");
                    break;
            }
        }
    }else{
        printf("===============================================================\n\n");
        printf("\t\t\tMenu Gestion des cocktails\n\n");
        printf("\t\t1. Informations sur les cocktails\n\n");
        printf("\t\t2. Creation d'un cocktail\n\n");
        printf("\t\t0. Revenir en arriere\n\n");
        printf("===============================================================\n\n");
        printf("Entrer le numero de l'interface:");

        retour = scanf("%d", &numInter);

        if(retour != 1 || numInter < 0 || numInter > 3){
        while(retour != 1 || numInter < 0 || numInter > 3){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer un nombre pour le choix de l'interface:");
            getchar();
            retour = scanf("%d", &numInter);
        }
        }else{
            switch (numInter)
            {
                case 1:
                    interfaceInformationCocktailClient();
                    break;
                case 2:
                    creationCocktailClient();
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
}

/*! \fn void interfaceInformationCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant d'afficher les informations des cocktails, côté barman.
*/

/*
    Interface affichant les informations sur les cocktails, cote barman.
*/
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

    if(retour != 1 || numInter > 0 || numInter < 0){
        while(retour != 1 || numInter > 0 || numInter < 0){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer 0 pour revenir en arriere :");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    switch (numInter)
    {
    case 0:
        interfaceGestionCocktail();
        break;
    default:
        printf("Erreur dans le choix de l'interface.");
        break;
    }
}

/*! \fn void interfaceInformationCocktail()
*  \author Barre Romain
*  \version 1
*
*  \brief Procedure permettant d'afficher les informations des cocktails, côté client.
*/

/*
    Interface affichant les informations sur les cocktails, cote client.
*/
void interfaceInformationCocktailClient(){
    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("=======================================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les cocktails\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tNombre_Boisson\n\n");

    informationCocktailClient();

    printf("\n\n=======================================================================================================================\n\n");


    printf("Entrer 0 pour revenir en arriere:");
    retour = scanf("%d", &numInter);

    if(retour != 1 || numInter > 0 || numInter < 0){
        while(retour != 1 || numInter > 0 || numInter < 0){
            retour = 1;
            printf("\nCe numero d'interface n'existe pas.\n");
            printf("Veuillez entrer 0 pour revenir en arriere :");
            getchar();
            retour = scanf("%d", &numInter);
        }
    }

    switch (numInter)
    {
    case 0:
        interfaceGestionCocktail();
        break;
    default:
        printf("Erreur dans le choix de l'interface.");
        break;
    }
}