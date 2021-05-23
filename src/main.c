/*  
    Nous avons divisé le plus possible le programme afin d'avoir une vue d'ensemble triée et compréhensible.
    De ce fait, nous nous retrouvons avec une fonction main très légère, contenant un fichier header ainsi que l'appelle de quelques fonctions
*/

#include "header.h"

int main(int argc, char** argv){
    recetteBar = 0;
    printf("Initialisation des fichiers barman...\n");
    initFileBarman();
    printf("Initialisation des fichiers client...\n");
    initFileClient();
    printf("Initialisation du fichier cocktail...\n");
    initFileCocktail();
    printf("Initialisation du tableau boisson...\n");
    initTab();
    printf("Initialisation du tableau cocktail...\n");
    initTabCocktail();
    printf("Initialisation du tableau panier...\n");
    initTabPanier();
    printf("Affichage de l'interface.\n");
    interfaceAccueil();

    return 0;
}