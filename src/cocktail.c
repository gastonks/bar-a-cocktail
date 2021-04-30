// #include "cocktail.h"

// const char* BOISSON_COCKTAIL_FORMAT_IN = "(%d, %[^,], %f, %f, %f, %f, %f)";

// const char* COCKTAIL_FORMAT_OUT = "\n(%d, %s, %.2f, %.2f, %.2f, %.2f, %d)";
// const char* COCKTAIL_FORMAT_EX = "(%d, %s, %d, %.2f, %.2f, %.2f, %d)";
// const char* COCKTAIL_FORMAT_IN = "(%d, %[^,], %f, %f, %f, %f, %d)";

// void initFileCocktail(){
//     FILE* fileCocktail = fopen("data/cocktail.dat", "a");
//     FILE* fileListBoisson = fopen("data/cocktailListBoisson.dat", "a");

//     if(fileCocktail == NULL || fileListBoisson == NULL){
//         printf("fichier non ouvert");
//         exit(-1);
//     }
//     if(ftell(fileCocktail) == 0){
//         fprintf(fileCocktail, COCKTAIL_FORMAT_EX, 0, "Exemple",0,0,0,0, 0);
//     }
//     if(ftell(fileListBoisson) == 0){
//         fprintf(fileListBoisson, "%d", 0);
//     }
//     fclose(fileCocktail);
//     fclose(fileListBoisson);
// }

// int idInitCocktail(){
//     cocktail tmp;

//     int nID = 0;
//     FILE* file = fopen("data/cocktail.dat", "r");
//     if(file == NULL){
//         printf("fichier non ouvert");
//         exit(-1);
//     }
//     rewind(file);

//     while(!feof(file)){
        
//         fscanf(file, COCKTAIL_FORMAT_IN, &tmp.id, tmp.nom, &tmp.listIdBoisson, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr);

//         if(fgetc(file) != '\n'){
//             break;
//         }
//     }

//     nID = tmp.id + 1;
//     fclose(file);   
//     return nID;
// }

// void creationCocktailBarman(){

//     cocktail nCocktail;

//     int nbBoisson = 0;
//     int idBoisson = 0;
//     int retour = 0;
//     system("cls");
//     printf("===============================================================\n\n");
//     printf("\t\t\tMenu creation d'un cocktail\n\n");

//     nCocktail.id = idInitCocktail();

//     printf("Veuillez entrer le nom du cocktail :");
//     getchar();
//     retour = scanf("%[^\n]", nCocktail.nom);
//     if(retour != 1){
//         printf("\nErreur dans la saisie.\n");
//         exit(-1);
//     }

//     printf("Combien de boisson votre cocktail est il compose :");

//     retour = scanf("%d", &nbBoisson);
//     if(retour != 1){
//         printf("\nErreur dans la saisie du numero de l'interface.\n");
//         exit(-1);
//     }else{
//         nCocktail.listIdBoisson = (int*) malloc(nbBoisson*sizeof(int));

//         nCocktail.tailleList = nbBoisson;

//         if(nCocktail.listIdBoisson == NULL){
//             printf("\nErreur d'allocation de memoire.\n");
//             exit(-1);
//         }
//     }

//     printf("=====================================================================================================\n\n");
//     printf("\t\t\tMenu Information sur les boissons\n\n");
//     printf("\t\tID\tNom\tContenance\tPrix\tDegre_Alcool\tDegre_Sucre\tQuantite\n\n");

//     informationBoissonBarman();

//     printf("=====================================================================================================\n");

//     for(int i = 0; i < nbBoisson; i++){
//         printf("\nEntrer l'ID de la boisson :");
//         retour = scanf("%d", &idBoisson);
//         if(retour != 1){
//             printf("\nErreur dans la saisie du numero de l'interface.\n");
//             exit(-1);
//         }else{
//             nCocktail.listIdBoisson[i] = idBoisson;
//         }
//     }

//     boisson tmp;

//     nCocktail.prix = 0,
//     nCocktail.contenance = 0,
//     nCocktail.degreAlco = 0,
//     nCocktail.degreScr = 0;
    
//     FILE* fileCocktail = fopen("data/cocktail.dat", "a");
//     FILE* fileListBoisson = fopen("data/cocktailListBoisson.dat", "a");
//     FILE* fileBoisson = fopen("data/boissonBarman.dat", "r");

//     for(int i = 0; i < nbBoisson; i++){
//         rewind(fileBoisson);
//         while(!feof(fileBoisson)){
            
//             fscanf(fileBoisson, BOISSON_COCKTAIL_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.quantite);

//             if(nCocktail.listIdBoisson[i] == tmp.id){
//                 nCocktail.prix = nCocktail.prix + tmp.prix;
//                 nCocktail.contenance= nCocktail.contenance + tmp.contenance;
//                 nCocktail.degreAlco = nCocktail.degreAlco + tmp.degreAlco;
//                 nCocktail.degreScr = nCocktail.degreScr + tmp.degreScr;
//             }


//             if(fgetc(fileBoisson) != '\n'){
//                     break;
//             }
            
//         }
//     }

//     nCocktail.prix = nCocktail.prix + 0.10 * nCocktail.prix;

//     fprintf(fileCocktail, COCKTAIL_FORMAT_OUT, nCocktail.id, nCocktail.nom, nCocktail.contenance, nCocktail.prix, nCocktail.degreAlco, nCocktail.degreScr, nCocktail.tailleList );

//     fprintf(fileListBoisson,"\n%d",nCocktail.id);
//     for(int i = 0; i<nCocktail.tailleList; i++){
//         fprintf(fileListBoisson," %d",nCocktail.listIdBoisson[i]);
//     }

//     fclose(fileCocktail);
//     fclose(fileBoisson);
//     fclose(fileListBoisson);

//     interfaceGestionCocktail();
// }

// void informationCocktail(){

//     cocktail tmp;
//     boisson boiss;

//     int idCocktailComp = 0;
//     int idBoissonAff = 0;

//     FILE* fileCocktail = fopen("data/cocktail.dat", "r");
//     FILE* fileBoisson = fopen("data/boissonBarman.dat", "r");
//     FILE* fileListBoisson = fopen("data/cocktailListBoisson.dat", "r");

//     if(fileCocktail == NULL || fileBoisson == NULL || fileListBoisson == NULL){
//         printf("fichier non ouvert");
//         exit(-1);
//     }


//     rewind(fileCocktail);
//     rewind(fileListBoisson);
//     while(!feof(fileCocktail)){
        
//         fscanf(fileCocktail, COCKTAIL_FORMAT_IN, &tmp.id, tmp.nom, &tmp.contenance, &tmp.prix, &tmp.degreAlco, &tmp.degreScr, &tmp.tailleList);
//         fscanf(fileListBoisson, "%d", &idCocktailComp);
//         if(tmp.id > 0 && idCocktailComp > 0){
//             printf("\t\t%d", tmp.id);
//             printf("\t%s", tmp.nom);
//             printf("\t%.2f", tmp.contenance);
//             printf("\t\t%.2f", tmp.prix);
//             printf("\t%.2f\t", tmp.degreAlco);
//             printf("\t%.2f\t", tmp.degreScr);
//             printf("\t%d\n", tmp.tailleList);
//             printf("\t\t=====================================================================================\n");
//             printf("\t\t\tCe cocktail est compose de(s) la (les) boisson(s) suivante(s):\n");
//             printf("\t\t");
//             rewind(fileBoisson);
//             for(int i = 0; i < tmp.tailleList; i++){
//                 fscanf(fileListBoisson, " %d", &idBoissonAff);
//                 while(!feof(fileBoisson)){
//                     fscanf(fileBoisson, BOISSON_COCKTAIL_FORMAT_IN, &boiss.id, boiss.nom, &boiss.contenance, &boiss.prix, &boiss.degreAlco, &boiss.degreScr, &boiss.quantite);
//                     if(boiss.id == idBoissonAff){
//                         printf("\t\t%s", boiss.nom);
//                         if(fgetc(fileBoisson) != '\n'){
//                             break;
//                         }
//                     }else{
//                         if(fgetc(fileBoisson) != '\n'){
//                             break;
//                         }
//                     }
//                 }
//                 rewind(fileBoisson);
//             }
//             printf("\n\t\t=====================================================================================\n\n");
//             if(fgetc(fileCocktail) != '\n'){
//                 break;
//             }
//             if(fgetc(fileListBoisson) != '\n'){
//                 break;
//             }
//         }else{
//             if(fgetc(fileCocktail) != '\n'){
//                 break;
//             }
//             if(fgetc(fileListBoisson) != '\n'){
//                 break;
//             }
//         }
//     }

//     fclose(fileCocktail);
//     fclose(fileBoisson);
//     fclose(fileListBoisson);
// }