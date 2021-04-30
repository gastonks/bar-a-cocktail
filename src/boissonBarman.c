#include "boissonBarman.h"

//const char* BOISSON_FORMAT_OUT = "{\n\t\"id:\": %d,\n\t\"nomBoisson\": \"%s\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f,\n\t\"dgrScr:\": %.2f\n}\n";
//const char* BOISSON_FORMAT_IN = "{\n\t\"id:\": %d,\n\t\"nomBoisson\": \"%[^\"]\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f,\n\t\"dgrScr:\": %.2f\n}";
const char* BOISSON_FORMAT_OUT = "(%s, %.2f, %.2f, %.2f, %.2f, %.2f)\n";
const char* BOISSON_FORMAT_EX = "(%s, %.2f, %.2f, %.2f, %.2f, %.2f)";
const char* BOISSON_FORMAT_IN = "(%[^,], %f, %f, %f, %f, %f)";

const char* COMMANDE_FORMAT_OUT = "(%d, %s, %.2f, %.2f)\n";
const char* COMMANDE_FORMAT_IN = "(%d, %[^,], %f, %f)";
const char* COMMANDE_FORMAT_EX = "(%d, %s, %.2f, %.2f)";

void initFileBarman(){
    FILE* file = fopen("data/boissonBarman.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    // if(ftell(file) == 0){
    //     fprintf(file, BOISSON_FORMAT_EX, 0, "Exemple",0,0,0,0,0);
    // } 
    
    fclose(file);
}

void ajoutBoissonAlcool(){

    boisson nouvBoisson;

    int retour = 0;
    system("cls");
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

    nouvBoisson.degreScr = 0.00;

    int T = calcTaille();
    
    if (T>0) {
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            strcpy(tmp[i].nom, tab[i].nom);
            tmp[i].contenance = tab[i].contenance;
            tmp[i].prix = tab[i].prix;
            tmp[i].quantite = tab[i].quantite;
            tmp[i].degreAlco = tab[i].degreAlco;
            tmp[i].degreScr = tab[i].degreScr;
        }

        free(tab);
        tab = malloc((T+1)*sizeof(boisson));

        for(int i = 0; i<T; i++) {
            strcpy(tab[i].nom, tmp[i].nom);
            tab[i].contenance = tmp[i].contenance;
            tab[i].prix = tmp[i].prix;
            tab[i].quantite = tmp[i].quantite;
            tab[i].degreAlco = tmp[i].degreAlco;
            tab[i].degreScr = tmp[i].degreScr;
        }

        strcpy(tab[T].nom, nouvBoisson.nom);
        tab[T].contenance = nouvBoisson.contenance;
        tab[T].prix = nouvBoisson.prix;
        tab[T].quantite = nouvBoisson.quantite;
        tab[T].degreAlco = nouvBoisson.degreAlco;
        tab[T].degreScr = nouvBoisson.degreScr;

        free(tmp);
    } else {
        tab = malloc(1*sizeof(boisson));
        strcpy(tab[0].nom, nouvBoisson.nom);
        tab[0].contenance = nouvBoisson.contenance;
        tab[0].prix = nouvBoisson.prix;
        tab[0].quantite = nouvBoisson.quantite;
        tab[0].degreAlco = nouvBoisson.degreAlco;
        tab[0].degreScr = nouvBoisson.degreScr;
    }

    initFichier(T+1);

    interfaceAjoutOuSuppBoisson();
}

void ajoutBoissonNonAlcool(){

    boisson nouvBoisson;

    int retour = 0;
    system("cls");
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

    int T = calcTaille();
    
    if (T>0) {
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            strcpy(tmp[i].nom, tab[i].nom);
            tmp[i].contenance = tab[i].contenance;
            tmp[i].prix = tab[i].prix;
            tmp[i].quantite = tab[i].quantite;
            tmp[i].degreAlco = tab[i].degreAlco;
            tmp[i].degreScr = tab[i].degreScr;
        }

        free(tab);
        tab = malloc((T+1)*sizeof(boisson));

        for(int i = 0; i<T; i++) {
            strcpy(tab[i].nom, tmp[i].nom);
            tab[i].contenance = tmp[i].contenance;
            tab[i].prix = tmp[i].prix;
            tab[i].quantite = tmp[i].quantite;
            tab[i].degreAlco = tmp[i].degreAlco;
            tab[i].degreScr = tmp[i].degreScr;
        }

        strcpy(tab[T].nom, nouvBoisson.nom);
        tab[T].contenance = nouvBoisson.contenance;
        tab[T].prix = nouvBoisson.prix;
        tab[T].quantite = nouvBoisson.prix;
        tab[T].degreAlco = nouvBoisson.degreAlco;
        tab[T].degreScr = nouvBoisson.degreScr;

        free(tmp);
    } else {
        tab = malloc(1*sizeof(boisson));
        strcpy(tab[0].nom, nouvBoisson.nom);
        tab[0].contenance = nouvBoisson.contenance;
        tab[0].prix = nouvBoisson.prix;
        tab[0].quantite = nouvBoisson.prix;
        tab[0].degreAlco = nouvBoisson.degreAlco;
        tab[0].degreScr = nouvBoisson.degreScr;
    }

    initFichier(T+1);

    interfaceAjoutOuSuppBoisson();

}

void informationBoissonBarman(){
    int i;
    int T = calcTaille();

    for(i = 0; i<T; i++) {
        printf("\t\t%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", i+1, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].quantite, tab[i].degreAlco, tab[i].degreScr);
    }
}

void suppBoisson(){
    int idSupp = 0;
    int retour = 0;

    system("cls");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tQuantité\tDegre Alcool\tDegre Sucre\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    printf("Entrer l'ID de la boisson à supprimer :");
    retour = scanf("%d", &idSupp);

    if(retour != 1){
        printf("Erreur dans la saisie du numero de l'interface.\n");
        exit(-1);
    }

    int T = calcTaille();
    int j = 0;
    int h = 0;

    if(idSupp > T ||idSupp < 1) {
        printf("Cet ID n'existe pas.");
        interfaceAjoutOuSuppBoisson();
    }

    if(T>1) {
        boisson* tmp = malloc(T*sizeof(boisson));
        for(int i = 0; i<T; i++) {
            strcpy(tmp[i].nom, tab[i].nom);
            tmp[i].contenance = tab[i].contenance;
            tmp[i].prix = tab[i].prix;
            tmp[i].quantite = tab[i].quantite;
            tmp[i].degreAlco = tab[i].degreAlco;
            tmp[i].degreScr = tab[i].degreScr;
        }

        free(tab);
        tab = malloc((T-1)*sizeof(boisson));

        while(j<T) {
            if(j != idSupp-1) {
                strcpy(tab[h].nom, tmp[j].nom);
                tab[h].contenance = tmp[j].contenance;
                tab[h].prix = tmp[j].prix;
                tab[h].quantite = tmp[j].quantite;
                tab[h].degreAlco = tmp[j].degreAlco;
                tab[h].degreScr = tmp[j].degreScr;
                h++;
                j++;
            }
            else {
                j++;
            }
        }
    } else if (T==1 && idSupp==1) {
        free(tab);
    }

    initFichier(T-1);

    interfaceAjoutOuSuppBoisson();

}

void modifBoisson(){
    int idChange = 0;
    int retour = 0;

    system("cls");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    if(calcTaille() == 0) {
        printf("La liste est vide, il n'y a rien à modifier.\n");
        printf("Entrez 0 pour revenir en arrière : ");
        retour = scanf("%d", &idChange);
        interfaceGestionBoissonBarman();
    }

    printf("Entrer l'ID de la boisson a modifie :");
    retour = scanf("%d", &idChange);

    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    while(idChange > calcTaille() || idChange < 1 || retour != 1){
        printf("ID impossible a modifie.\nEntrer un nouveau ID :");
        retour = scanf("%d", &idChange);
    }

    printf("Veuillez entrez le nouveau nom de la boisson :");
    getchar();
    retour = scanf("%[^\n]", tab[idChange-1].nom);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer la nouvelle contenance de la boisson :");
    retour = scanf("%f", &tab[idChange-1].contenance);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le nouveau prix de la boisson :");
    retour = scanf("%f", &tab[idChange-1].prix);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer la quantite de boisson :");
    retour = scanf("%f", &tab[idChange-1].quantite);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le nouveau degre d'alcool de cette boisson :");
    retour = scanf("%f", &tab[idChange-1].degreAlco);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    printf("Entrer le nouveau degre de sucre de cette boisson :");
    retour = scanf("%f", &tab[idChange-1].degreScr);
    if(retour != 1){
        printf("\nErreur dans la saisie.\n");
        exit(-1);
    }

    initFichier(calcTaille());

    interfaceGestionBoissonBarman();

}
    
void gestionStock(){
    int idStock = 0;
    float stockV = 0;
    float stockR = 0;
    int retour = 0;

    system("cls");
    printf("=====================================================================================================\n\n");
    printf("\t\t\tMenu Information sur les boissons\n\n");
    printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

    informationBoissonBarman();

    printf("===============================================================\n\n");

    if(calcTaille() == 0) {
        printf("La liste est vide, il n'y a rien à modifier.\n");
        printf("Entrez 0 pour revenir en arrière : ");
        retour = scanf("%d", &idStock);
        interfaceGestionBoissonBarman();
    }

    printf("Entrer l'ID du stock de la boisson a modifie :");
    retour = scanf("%d", &idStock);

    if(retour != 1){
        printf("Erreur dans la saisie l'ID.\n");
        exit(-1);
    }

    while(idStock < 1 || idStock > calcTaille()){
        printf("ID impossible a modifie.\nEntrer un nouveau ID :");
        retour = scanf("%d", &idStock);
    }

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

    tab[idStock-1].quantite = tab[idStock-1].quantite + fabsf(stockR) - fabsf(stockV);

    initFichier(calcTaille());

    interfaceGestionBoissonBarman();

}

float recette(){

    float totalJ = 0;

    for(int i = 0; i<calcTailleCom(); i++) {
        totalJ += tabCom[i].prix;
    }

    return totalJ;
}

int calcTaille() {
    int t = -1;
    boisson tmp;
    FILE* file = fopen("data/boissonBarman.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    rewind(file);

    while(!feof(file)) {
        fscanf(file, BOISSON_FORMAT_IN, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.quantite, &tmp.degreAlco, &tmp.degreScr);
        t++;

        if(fgetc(file) != '\n'){
            break;
        }
    }

    //printf("%d",t);

    return t;
}


void initTab() {
    int i = 0;
    FILE* file = fopen("data/boissonBarman.dat", "r");

    if(file == NULL){
        printf("fichier non ouvert ID");
        exit(-1);
    }

    if(calcTaille()>0) {
        tab = malloc(calcTaille()*sizeof(boisson));
    }

    rewind(file);

    while(!feof(file)) {
        fscanf(file, BOISSON_FORMAT_IN, tab[i].nom, &tab[i].contenance, &tab[i].prix, &tab[i].quantite, &tab[i].degreAlco, &tab[i].degreScr);
        i++;

        if(fgetc(file) != '\n'){
            break;
        }
    }

    fclose(file);

}

void initFichier(int T) {
    FILE *file = fopen("data/boissonBarman.dat","w");
    int i;

    for(i=0; i<T; i++) {
        fprintf(file, BOISSON_FORMAT_OUT, tab[i].nom, tab[i].contenance, tab[i].prix, tab[i].quantite, tab[i].degreAlco, tab[i].degreScr);
    }

    fclose(file);
}