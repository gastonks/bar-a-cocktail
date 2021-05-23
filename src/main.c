/*! \file main.c
*  \author Barre Romain
*  \author Guillerm Francois
*  \version 1
*  \date 20/05/2021 Début de la documentation doxygen du projet
*  \brief Programme principal du projet, il contient simplement les fonctions d'initialisations, puis la fonction d'affichage du premier interface.  
*/

/*! \mainpage Présentation
*  \section introduction Introduction
*
*  Le programme commence par initialiser les tableaux de structures pour les boissons, les cocktails et les commandes.\n
*  L'interface est ensuite affichée, permettant à l'utilisateur de naviguer entre les différentes fonctionnalités du programme.
*
*  \section fichiers Fichiers
*
*  Le code est divisé en fichiers afin de mieux se repérer et d'avoir une meilleure vue d'ensemble du projet.
*
*  \section fonctions_procedures Fonctions et procédures
*
*  Le programme est décomposé en plusieurs fonctions et procédures afin d'avoir le moins de code brut possible.
*
*  \section organisation Organisation
*
*  Romain a fait l'interface, la gestion des cocktails et la gestion des commandes.\n
*  François a fait la gestion des boissons et les commentaires, ainsi que les commentaires doxygen.
*/

/*  
    Nous avons divisé le plus possible le programme afin d'avoir une vue d'ensemble triée et compréhensible.
    De ce fait, nous nous retrouvons avec une fonction main très légère, contenant un fichier header ainsi que l'appelle de quelques fonctions
*/

#include "header.h"

int main(int argc, char** argv){
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