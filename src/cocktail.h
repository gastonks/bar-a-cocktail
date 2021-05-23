/*! \file cocktail.h
*  \section Présentation
*  Ce header regroupe les bibliothèques, le(s) constante(s), le(s) structure(s) et les prototypes de fonctions/procédures utiles au bon fonctionnement de la gestion des cocktails.
*
*  \brief Regroupe les bibliothèques, le(s) constante(s), le(s) structure(s) et les prototypes de fonctions/procédures.
*/

#ifndef COCKTAIL_H
#define COCKTAIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boissonBarman.h"

#define N 20

/*!
*  \class cocktail
*  \brief Déclaration de la structure cocktail.
*/

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

// Fonction pour initialiser les fichiers

/*!
*  \brief Prototype de la procédure "initFileCocktail"
*/
void initFileCocktail(void);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// Fonction pour la gestion des cocktails

/*!
*  \brief Prototype de la fonction "idInitCocktail"
*/
int idInitCocktail(void);

/*!
*  \brief Prototype de la procédure "creationCocktailBarman"
*/
void creationCocktailBarman(void);

/*!
*  \brief Prototype de la procédure "informationCocktail"
*/
void informationCocktail(void);

/*!
*  \brief Prototype de la procédure "informationCocktailClient"
*/
void informationCocktailClient(void);

/*!
*  \brief Prototype de la procédure "creationCocktailClient"
*/
void creationCocktailClient(void);

/*!
*  \brief Prototype de la procédure "supprimerCocktail"
*/
void supprimerCocktail(int idCocktail);

/*!
*  \brief Prototype de la procédure "supprimerCocktailDemande"
*/
void supprimerCocktailDemande(void);

/*!
*  \brief Prototype de la procédure "suppPanierCocktail"
*/
void suppPanierCocktail(int idCocktail);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// Fonctions pour la gestion du tableau dynamique

/*!
*  \brief Prototype de la procédure "initTabCocktail"
*/
void initTabCocktail();

/*!
*  \brief Prototype de la procédure "initFichierCocktail"
*/
void initFichierCocktail(int t);

/*!
*  \brief Prototype de la fonction "tailleTabBarmanCocktail"
*/
int tailleTabBarmanCocktail();

cocktail * tabCocktail;

#endif