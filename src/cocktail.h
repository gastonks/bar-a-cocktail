#ifndef COCKTAIL_H
#define COCKTAIL_H
/*! \file cocktail.h
*  \section Présentation
*  Ce header regroupe les bibliothèques, le(s) constante(s), le(s) structure(s) et les prototypes de fonctions/procédures utiles au bon fonctionnement de la gestion des cocktails.
*
*  \brief Regroupe les bibliothèques, le(s) constante(s), le(s) structure(s) et les prototypes de fonctions/procédures.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boissonBarman.h"

#define N 20

typedef struct cocktail
{
    int id;
    char nom[N];
    int tailleListBoisson;
    int * listIdBoisson;
    float contenance;
    float prix;
    float degreAlco;
    float degreScr;
}cocktail;

// Fonction pour la gestion des cocktails
void initFileCocktail(void);
int idInitCocktail(void);
void creationCocktailBarman(void);
void informationCocktail(void);
void informationCocktailClient(void);

void creationCocktailClient(void);

void supprimerCocktail(int idCocktail);
void supprimerCocktailDemande(void);

void suppCocktailBoisson(int idBoisson);

void initTabCocktail();
void initFichierCocktail(int t);
int tailleTabBarmanCocktail();

cocktail * tabCocktail;

#endif