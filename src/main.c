/*  
    Nous avons divisé le plus possible le programme afin d'avoir une vue d'ensemble triée et compréhensible.
    De ce fait, nous nous retrouvons avec une fonction main très légère, contenant un fichier header ainsi que l'appelle de quelques fonctions
*/

#include "header.h"

int main(int argc, char** argv){
    initFileBarman();
    initFileClient();
    //initFileCocktail();
    initTab();
    initTabCom();
    interfaceAccueil();

    return 0;
}