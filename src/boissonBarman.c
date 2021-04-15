#include "boissonBarman.h"

//const char* BOISSON_FORMAT_OUT = "{\n\t\"id:\": %d,\n\t\"nomBoisson\": \"%s\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f,\n\t\"dgrScr:\": %.2f\n}\n";
//const char* BOISSON_FORMAT_IN = "{\n\t\"id:\": %d,\n\t\"nomBoisson\": \"%[^\"]\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f,\n\t\"dgrScr:\": %.2f\n}";
const char* BOISSON_FORMAT_OUT = "\n(%d, %s, %.2f, %.2f, %.2f, %.2f, %.2f)";
const char* BOISSON_FORMAT_EX = "(%d, %s, %.2f, %.2f, %.2f, %.2f, %.2f)";
const char* BOISSON_FORMAT_IN = "(%d, %[^,], %f, %f, %f, %f, %f)";

const char* COMMANDE_FORMAT_OUT = "\n(%d, %s, %.2f, %.2f)";
const char* COMMANDE_FORMAT_IN = "(%d, %[^,], %f, %f)";
const char* COMMANDE_FORMAT_EX = "(%d, %s, %.2f, %.2f)";

void initFileBarman(){
    FILE* file = fopen("data/boissonBarman.dat", "a");
    FILE* filetmp = fopen("data/boissonBarmantmp.dat", "a");

    if(file == NULL || filetmp == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    if(ftell(file) == 0){
        fprintf(file, BOISSON_FORMAT_EX, 0, "Exemple",0,0,0,0,0);
    } 
    
    fclose(file);
    fclose(filetmp);
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

    FILE* file = fopen("data/boissonBarman.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    fprintf(file, BOISSON_FORMAT_OUT, nouvBoisson.id, nouvBoisson.nom,nouvBoisson.contenance ,nouvBoisson.prix, nouvBoisson.degreAlco, 0.00, nouvBoisson.quantite);
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

    FILE* file = fopen("data/boissonBarman.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    fprintf(file, BOISSON_FORMAT_OUT, nouvBoisson.id, nouvBoisson.nom, nouvBoisson.contenance,nouvBoisson.prix, 0.00, nouvBoisson.degreScr, nouvBoisson.quantite);
    fclose(file);


    interfaceAjoutOuSuppBoisson();

}

void informationBoissonBarman(){

    boisson tmp;

    FILE* file = fopen("data/boissonBarman.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    rewind(file);
 
    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);
        if(tmp.id > 0){
            printf("\t\t%d", tmp.id);
            printf("\t%s", tmp.nom);
            printf("\t%.2f", tmp.contenance);
            printf("\t\t%.2f", tmp.prix);
            printf("\t%.2f\t", tmp.degreAlco);
            printf("\t%.2f\t", tmp.degreScr);
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

int idInit(){
    
    boisson tmp;

    int nID = tmp.id;

    FILE* file = fopen("data/boissonBarman.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    rewind(file);

    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);
        if(fgetc(file) != '\n'){
            break;
        }
    }


    nID = tmp.id + 1;

    fclose(file); 

    return nID;  
}

void suppBoisson(){

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

    boisson tmp;

    FILE* file = fopen("data/boissonBarman.dat", "r");
    FILE* filetmp = fopen("data/boissonBarmantmp.dat", "a");

    if(file == NULL || filetmp == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    rewind(file);
    rewind(filetmp);

    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);

        if(tmp.id == idSupp ){
            if(fgetc(file) != '\n'){
                break;
            }
        }else if(tmp.id == 0){
            fprintf(filetmp, BOISSON_FORMAT_EX, 0, "Exemple",0,0,0,0,0);
            if(fgetc(file) != '\n'){
                break;
            }
        }else{
            fprintf(filetmp, BOISSON_FORMAT_OUT, tmp.id, tmp.nom, tmp.contenance,tmp.prix, tmp.degreAlco, tmp.degreScr, tmp.quantite);
            if(fgetc(file) != '\n'){
                break;
            }
        }
    }

    rename("data/boissonBarman.dat", "data/boissonSupp.dat");
    rename("data/boissonBarmantmp.dat", "data/boissonBarman.dat");

    fclose(file);
    fclose(filetmp);

    remove("data/boissonSupp.dat");


    interfaceAjoutOuSuppBoisson();

}

void modifBoisson(){
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

    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    if(idChange == 0){
        while(idChange == 0 || retour != 1){
            printf("ID impossible a modifie.\nEntrer un nouveau ID :");
            retour = scanf("%d", &idChange);
        }
    }

    boisson tmp;

    FILE* file = fopen("data/boissonBarman.dat", "r");
    FILE* filetmp = fopen("data/boissonBarmantmp.dat", "a");

    if(file == NULL || filetmp == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    rewind(file);
    rewind(filetmp);

    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);

        if(tmp.id == 0){
            fprintf(filetmp, BOISSON_FORMAT_EX, 0, "Exemple",0,0,0,0,0);
            if(fgetc(file) != '\n'){
                break;
            }
        }else if(tmp.id == idChange){

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

            fprintf(filetmp, BOISSON_FORMAT_OUT, tmp.id, tmp.nom, tmp.contenance,tmp.prix, tmp.degreAlco, tmp.degreScr, tmp.quantite);
            if(fgetc(file) != '\n'){
                break;
            }
        }else{
            fprintf(filetmp, BOISSON_FORMAT_OUT, tmp.id, tmp.nom, tmp.contenance,tmp.prix, tmp.degreAlco, tmp.degreScr, tmp.quantite);
            if(fgetc(file) != '\n'){
                break;
            }
        }
    }

    rename("data/boissonBarman.dat", "data/boissonSupp.dat");
    rename("data/boissonBarmantmp.dat", "data/boissonBarman.dat");

    fclose(file);
    fclose(filetmp);

    remove("data/boissonSupp.dat");

    interfaceGestionBoissonBarman();

}
    
void gestionStock(){
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
    }

    boisson tmp;

    FILE* file = fopen("data/boissonBarman.dat", "r");
    FILE* filetmp = fopen("data/boissonBarmantmp.dat", "a");

    if(file == NULL || filetmp == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    rewind(file);
    rewind(filetmp);

    while(!feof(file)){
        
        fscanf(file, BOISSON_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);

        if(tmp.id == idStock){

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
            
            tmp.quantite = tmp.quantite + fabsf(stockR) - fabsf(stockV);

            fprintf(filetmp, BOISSON_FORMAT_OUT, tmp.id, tmp.nom, tmp.contenance,tmp.prix, tmp.degreAlco, tmp.degreScr, tmp.quantite);
            if(fgetc(file) != '\n'){
                break;
            }
        }else if(tmp.id == 0){
            fprintf(filetmp, BOISSON_FORMAT_EX, 0, "Exemple",0,0,0,0,0);
            if(fgetc(file) != '\n'){
                break;
            }
        }else{
            fprintf(filetmp, BOISSON_FORMAT_OUT, tmp.id, tmp.nom, tmp.contenance,tmp.prix, tmp.degreAlco, tmp.degreScr, tmp.quantite);
            if(fgetc(file) != '\n'){
                break;
            }
        }
    }

    rename("data/boissonBarman.dat", "data/boissonSupp.dat");
    rename("data/boissonBarmantmp.dat", "data/boissonBarman.dat");

    fclose(file);
    fclose(filetmp);

    remove("data/boissonSupp.dat");

    interfaceGestionBoissonBarman();

}

float recette(){

    commande tmp;

    float totalJ = 0;

    FILE* fileCommande = fopen("data/commandeClient.dat", "r");

    if(fileCommande == NULL ){
        printf("fichier non ouvert");
        exit(-1);
    }
    rewind(fileCommande);

    while(!feof(fileCommande)){
        
        fscanf(fileCommande, COMMANDE_FORMAT_IN, &tmp.id, tmp.nom, &tmp.prix, &tmp.quantite);

        totalJ = totalJ + tmp.prix;

        if(fgetc(fileCommande) != '\n'){
            break;
        }
    }
    fclose(fileCommande);

    return totalJ;
}

