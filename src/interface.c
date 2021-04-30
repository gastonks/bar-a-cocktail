#include "interface.h"

const char* REMOVE_DATA = "rm -r data/boissonBarman.dat data/boissonBarmantmp.dat data/commandeClient.dat data/cocktail.dat data/cocktailListBoisson.dat data/cocktailListBoissontmp.dat data/cocktailtmp.dat";

int prix = 0;
int idUser = 0; // 1 = Barman ; 2 = Client
int nbBoiss = 0; // nombre boisson ajoutee

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
            system(REMOVE_DATA);
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
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}

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
}

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
}

void interfaceAjoutBoissonAlcool(){

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

    ajoutBoissonAlcool(nouvBoisson.nom, nouvBoisson.contenance, nouvBoisson.prix, nouvBoisson.quantite, nouvBoisson.degreAlco);
}

void interfaceAjoutBoissonNonAlcool(){

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

    printf("Entrer le degre de sucre de cette boisson :");
    retour = scanf("%f", &nouvBoisson.degreScr);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }
    
    ajoutBoissonNonAlcool(nouvBoisson.nom, nouvBoisson.contenance, nouvBoisson.prix, nouvBoisson.quantite, nouvBoisson.degreScr);
}

void interfaceSuppBoisson(){

    int idSupp = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    printf("Entrer l'ID de la boisson a supprimer :");
    retour = scanf("%d", &idSupp);

    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    if(idSupp == 0){
        while(idSupp == 0){
            printf("ID impossible a supprimer.\nEntrer un nouveau ID :");
            retour = scanf("%d", &idSupp);
        }
    }

    suppBoisson(idSupp);

}

void interfaceModifBoisson(){
    int idChange = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    printf("Entrer l'ID de la boisson a modifie :");
    retour = scanf("%d", &idChange);
/*
    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }
*/
    if(idChange == 0){
        while(idChange == 0 || retour != 1){
            getchar();
            printf("ID impossible a modifie.\nEntrer un nouveau ID :");
            retour = scanf("%d", &idChange);
        }
    }else{

        boisson tmp;

        printf("Veuillez entrer le nouveu nom de la boisson :");
        getchar();
        retour = scanf("%[^\n]", tmp.nom);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        printf("Entrer la nouvelle contenance de la boisson :");
        retour = scanf("%f", &tmp.contenance);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        printf("Entrer le nouveau prix de la boisson :");
        retour = scanf("%f", &tmp.prix);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        printf("Entrer la quantite de boisson :");
        retour = scanf("%f", &tmp.quantite);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        printf("Entrer le nouveau degre d'alcool de cette boisson :");
        retour = scanf("%f", &tmp.degreAlco);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        printf("Entrer le nouveau degre de sucre de cette boisson :");
        retour = scanf("%f", &tmp.degreScr);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }

        modifBoisson(idChange, tmp.nom, tmp.contenance, tmp.prix, tmp.quantite, tmp.degreAlco, tmp.degreScr);
    }
}

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

    printf("Entrer l'ID du stock de la boisson a modifie :");
    retour = scanf("%d", &idStock);

    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    if(idStock == 0){
        while(idStock == 0){
            printf("ID impossible a modifie.\nEntrer un nouveau ID :");
            retour = scanf("%d", &idStock);
        }
    }else{
        printf("Entrer la quantite de boisson recue :");
        retour = scanf("%f", &stockR);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }
        printf("Entrer la quantite de boisson vendue :");
        retour = scanf("%f", &stockV);
        if(retour != 1){
            printf("\nErreur dans la saisie.\n");
            exit(-1);
        }
    }

    gestionStock(idStock, stockR, stockV);
}

void interfaceSatisfactionCommande(){
    int nCommande = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tPrix\tQuantite_Commande\n\n");

    informationCommandeClient();

    printf("=====================================================================================================\n\n");

    printf("Entrer l'ID de la commande que vous voulez satisfaire:");
    retour = scanf("%d", &nCommande);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }

    satisfactionCommande(nCommande);
}

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
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }

}

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
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }

}

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
        }else{
            commandeBoissonClient(numInter);
        }
    }  
} 

void interfaceInformationCommandeClient(){
    int numInter = 0;
    int retour = 0;

    system("clear");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les commandes\n\n");
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
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }

}

void interfaceGestionCocktail(){

    int numInter = 0;
    int retour = 0;
    system("clear");
    if(idUser == 1){
        printf("===============================================================\n\n");
        printf("\t\t\tMenu Gestion des cocktails\n\n");
        printf("\t\t1. Informations sur les cocktails\n\n");
        printf("\t\t2. Création d'un cocktail\n\n");
        printf("\t\t3. Supprimer un cocktail\n\n");
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
                    creationCocktailClient();
                    break;
                case 3:
                    printf("commande cocktail");
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
            break;
        default:
            printf("Erreur dans le choix de l'interface.");
            break;
        }
    }
}
