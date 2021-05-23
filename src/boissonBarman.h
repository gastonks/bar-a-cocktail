/*! \file boissonBarman.h
*  \brief Programme contenant les prototypes des fonctions associées au fichier boissonBarman.c.
*  \section Présentation
*  Ce header rassemble les prototypes des fonctions et procédures utilisées dans le fichier boissonBarman.c.
*  De plus, il contient les headers associés aux autres fichiers .c, pour pouvoir accéder à leurs fonctions si besoin.
*/

#ifndef BOISSONBARMAN_H
#define BOISSONBARMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "boissonClient.h"
#include "interface.h"

/*!
*  \class boisson
*  \brief Déclaration de la structure boisson.
*/

typedef struct boisson
{
    int id;
    char nom[20];
    float contenance;
    float prix;
    float quantite;
    float degreAlco;
    float degreScr;
}boisson;


// Fonction pour initialiser les fichiers

/*!
*  \brief Prototype de la procédure "initFileBarman"
*/
void initFileBarman(void);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// Fonction pour la gestion des boissons

/*!
*  \brief Prototype de la fonction "idInit"
*/
int idInit(void);

/*!
*  \brief Prototype de la procédure "ajoutBoissonAlcool"
*/
void ajoutBoissonAlcool(char nom[], float contenance, float prix, float quantite, float degreAlco);

/*!
*  \brief Prototype de la procédure "ajoutBoissonNonAlcool"
*/
void ajoutBoissonNonAlcool(char nom[], float contenance, float prix, float quantite, float degreAlco);

/*!
*  \brief Prototype de la procédure "informationBoissonBarman"
*/
void informationBoissonBarman(void);

/*!
*  \brief Prototype de la procédure "suppBoisson"
*/
void suppBoisson(int idSupp);

/*!
*  \brief Prototype de la procédure "suppCocktailBoisson"
*/
void suppCocktailBoisson(int idSupp);

/*!
*  \brief Prototype de la procédure "suppPanierBoisson"
*/
void suppPanierBoisson(int idSupp);

/*!
*  \brief Prototype de la procédure "modifBoisson"
*/
void modifBoisson(int idChange);

/*!
*  \brief Prototype de la procédure "gestionStock"
*/
void gestionStock(int idStock, float stockR, float stockV);

/*!
*  \brief Prototype de la procédure "satisfactionCommande"
*/
void satisfactionCommande(int nCommande);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// Fonction pour la gestion des finances

/*!
*  \brief Prototype de la fonction "recette"
*/
float recette(float prix);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// Fonctions pour la gestion du tableau dynamique

/*!
*  \brief Prototype de la procédure "initTab"
*/
void initTab();

/*!
*  \brief Prototype de la procédure "initFichier"
*/
void initFichier(int t);

/*!
*  \brief Prototype de la fonction "tailleTabBarman"
*/
int tailleTabBarman();

boisson* tab;

#endif