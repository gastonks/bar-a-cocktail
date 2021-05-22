/*! \file interface.h
*  \brief Programme contenant les prototypes des fonctions associées au fichier interface.c.
*  \section Présentation
*  Ce header rassemble les prototypes des fonctions et procédures utilisées dans le fichier interface.c.
*  De plus, il contient les headers associés aux autres fichiers .c, pour pouvoir accéder à leurs fonctions si besoin.
*/

/*
Condition qui permet de définir ou non le header "interface.h" si il est déjà défini quelque part.
*/
#ifndef INTERFACE_H
#define INTERFACE_H

// Bibliothèques et headers
#include <stdio.h>
#include <stdlib.h>
#include "boissonBarman.h"
#include "boissonClient.h"
#include "cocktail.h"


// Interface general pour le client ou le barman

/*!
*  \brief Prototype de la procédure "interfaceAccueil"
*/
void interfaceAccueil(void);

/*!
*  \brief Prototype de la procédure "interfaceBarman"
*/
void interfaceBarman(void);

/*!
*  \brief Prototype de la procédure "interfaceClient"
*/
void interfaceClient(void);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// Interface specifique au barman

/*!
*  \brief Prototype de la procédure "interfaceGestionBoissonBarman"
*/
void interfaceGestionBoissonBarman(void);

/*!
*  \brief Prototype de la procédure "interfaceGestionCocktail"
*/
void interfaceGestionCocktail(void);

/*!
*  \brief Prototype de la procédure "interfaceGestionFinance"
*/
void interfaceGestionFinance(void);

/*!
*  \brief Prototype de la procédure "interfaceInformationBoissonBarman"
*/
void interfaceInformationBoissonBarman(void);

/*!
*  \brief Prototype de la procédure "interfaceAjoutOuSuppBoisson"
*/
void interfaceAjoutOuSuppBoisson(void);

/*!
*  \brief Prototype de la procédure "interfaceAjoutBoissonAlcool"
*/
void interfaceAjoutBoissonAlcool(void);

/*!
*  \brief Prototype de la procédure "interfaceAjoutBoissonNonAlcool"
*/
void interfaceAjoutBoissonNonAlcool(void);

/*!
*  \brief Prototype de la procédure "interfaceSuppBoisson"
*/
void interfaceSuppBoisson(void);

/*!
*  \brief Prototype de la procédure "interfaceModifBoisson"
*/
void interfaceModifBoisson(void);

/*!
*  \brief Prototype de la procédure "interfaceModifBoissonAlco"
*/
void interfaceModifBoissonAlco(void);

/*!
*  \brief Prototype de la procédure "interfaceModifBoissonNonAlco"
*/
void interfaceModifBoissonNonAlco(void);

/*!
*  \brief Prototype de la procédure "interfaceGestionStock"
*/
void interfaceGestionStock(void);

/*!
*  \brief Prototype de la procédure "interfaceSatisfactionCommande"
*/
void interfaceSatisfactionCommande(void);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// Interface specifique au client

/*!
*  \brief Prototype de la procédure "interfaceInformationBoissonClient"
*/
void interfaceInformationBoissonClient(void);

/*!
*  \brief Prototype de la procédure "interfaceInformationCocktailClient"
*/
void interfaceInformationCocktailClient (void);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// Interface dans la gestion des cocktails.

/*!
*  \brief Prototype de la procédure "interfaceCreationCocktail"
*/
void interfaceCreationCocktail(void);

/*!
*  \brief Prototype de la procédure "interfaceInformationCocktail"
*/
void interfaceInformationCocktail(void);

/* ----------------------------------------------------------------------------------------------------------------------------- */

//Interface pour la gestion des commandes.

/*!
*  \brief Prototype de la procédure "interfaceInformationCommande"
*/
void interfaceInformationCommande(void);

/*!
*  \brief Prototype de la procédure "interfaceInitCommande"
*/
void interfaceInitCommande(void);

/*!
*  \brief Prototype de la procédure "interfaceModifCommande"
*/
void interfaceModifCommande(void);

/*!
*  \brief Prototype de la procédure "interfaceSuppCommande"
*/
void interfaceSuppCommande(void);

#endif
