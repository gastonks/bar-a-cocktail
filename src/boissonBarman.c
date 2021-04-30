#include "boissonBarman.h"

//const char* BOISSON_FORMAT_OUT = "{\n\t\"id:\": %d,\n\t\"nomBoisson\": \"%s\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f,\n\t\"dgrScr:\": %.2f\n}\n";
//const char* BOISSON_FORMAT_IN = "{\n\t\"id:\": %d,\n\t\"nomBoisson\": \"%[^\"]\",\n\t\"contenance:\": %.2f,\n\t\"prix:\": %.2f,\n\t\"quantite:\": %.2f,\n\t\"dgrAlc:\": %.2f,\n\t\"dgrScr:\": %.2f\n}";
const char* BOISSON_FORMAT_OUT = "\n(%d, %s, %.2f, %.2f, %.2f, %.2f, %.2f)";
const char* BOISSON_FORMAT_EX = "(%d, %s, %.2f, %.2f, %.2f, %.2f, %.2f)";
const char* BOISSON_FORMAT_IN = "(%d, %[^,], %f, %f, %f, %f, %f)";

const char* COMMANDE_FORMAT_OUT = "\n(%d, %s, %.2f, %.2f)";
const char* COMMANDE_FORMAT_IN = "(%d, %[^,], %f, %f)";
const char* COMMANDE_FORMAT_EX = "(%d, %s, %.2f, %.2f)";

float recetteBar;

void initFileBarman(){
    FILE* file = fopen("data/boissonBarman.dat", "a");

    if(file == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }
    if(ftell(file) == 0){
        fprintf(file, BOISSON_FORMAT_EX, 0, "Exemple",0,0,0,0,0);
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

void ajoutBoissonAlcool(char nom[], float contenance, float prix, float quantite, float degreAlco){

    boisson nouvBoisson;

    nouvBoisson.id = idInit();;
    strcpy(nouvBoisson.nom,nom);
    nouvBoisson.contenance = contenance;
    nouvBoisson.prix = prix;
    nouvBoisson.quantite = quantite;
    nouvBoisson.degreAlco = degreAlco;

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

void ajoutBoissonNonAlcool(char nom[], float contenance, float prix, float quantite, float degreSrc){

    boisson nouvBoisson;

    nouvBoisson.id = idInit();
    strcpy(nouvBoisson.nom,nom);
    nouvBoisson.contenance = contenance;
    nouvBoisson.prix = prix;
    nouvBoisson.quantite = quantite;
    nouvBoisson.degreScr = degreSrc;

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

void suppBoisson(int idSupp){

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

void modifBoisson(int idChange, char nom[], float contenance, float prix, float quantite, float degreAlco, float degreSrc){

    boisson tmp;
    boisson modifBoisson;

    strcpy(modifBoisson.nom, nom);
    modifBoisson.contenance = contenance;
    modifBoisson.prix = prix;
    modifBoisson.quantite = quantite;
    modifBoisson.degreAlco= degreAlco;
    modifBoisson.degreScr = degreSrc;

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
            fprintf(filetmp, BOISSON_FORMAT_OUT, tmp.id, modifBoisson.nom, modifBoisson.contenance,modifBoisson.prix, modifBoisson.degreAlco, modifBoisson.degreScr, modifBoisson.quantite);
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
    
void gestionStock(int idStock, float stockR, float stockV){
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

float recette(float prix){

    recetteBar = recetteBar + prix;

    return recetteBar;

}

void satisfactionCommande(int nCommande){
    FILE* fileCommande = fopen("data/commandeClient.dat", "r");
    FILE* fileBoisson = fopen("data/boissonBarman.dat", "a+");

    if(fileCommande == NULL || fileBoisson == NULL){
        printf("fichier non ouvert");
        exit(-1);
    }

    rewind(fileCommande);

    commande tmp;
    boisson boiss;

    while(!feof(fileCommande)){
        
        fscanf(fileCommande, COMMANDE_FORMAT_IN, &tmp.id, &tmp.idBoisson, tmp.nom, &tmp.prix, &tmp.quantite);

        if(tmp.id == nCommande){
            rewind(fileBoisson);
            while(!feof(fileBoisson)){
                fscanf(fileBoisson, BOISSON_FORMAT_IN, &boiss.id, boiss.nom, &boiss.contenance, &boiss.prix, &boiss.degreAlco, &boiss.degreScr, &boiss.quantite);
                if(tmp.idBoisson == boiss.id){
                    if(boiss.quantite < tmp.quantite){
                        printf("\nCommande impossible à satisfaire.\n");
                        interfaceGestionBoissonBarman();
                    }else{
                        gestionStock(boiss.id, 0, tmp.quantite);
                        printf("\nCommande satisfaite.\n");
                        recette(tmp.prix);
                    }
                }else{
                    if(fgetc(fileBoisson) != '\n'){
                        break;
                    }
                }
            }
        }else{
            if(fgetc(fileCommande) != '\n'){
                break;
            }
        }
    }
    fclose(fileCommande);
    fclose(fileBoisson);
    interfaceGestionBoissonBarman();
}