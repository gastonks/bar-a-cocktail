/*! \file boissonClient.h
*  \section Présentation
*  Ce header regroupe les bibliothèques, le(s) constante(s), le(s) structure(s) et les prototypes de fonctions/procédures utiles au bon fonctionnement de la gestion des commandes.
*
*  \brief Regroupe les bibliothèques, le(s) constante(s), le(s) structure(s) et les prototypes de fonctions/procédures.
*/

#ifndef BOISSONCLIENT_H
#define BOISSONCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boissonBarman.h"
#include "interface.h"

/*!
*  \class listIdBoisson
*  \brief Déclaration de la structure listIdBoisson.
*/
typedef struct listIdBoisson
{
    int idBoisson;
    int quantiteBoisson;
}listIdBoisson;

/*!
*  \class listIdCocktail
*  \brief Déclaration de la structure listIdCocktail.
*/
typedef struct listIdCocktail
{
    int idCocktail;
    int quantiteCocktail;
}listIdCocktail;

/*!
*  \class commande
*  \brief Déclaration de la structure commande.
*/
typedef struct commande
{
    int nbrBoisson;
    listIdBoisson * listBoisson;
    int nbrCocktail;
    listIdCocktail * listCocktail;
    float prix;

}commande;

/*!
*  \class panier
*  \brief Déclaration de la structure panier.
*/
typedef struct panier
{
    int id;
    int nbrCommande;
    commande * listCommande;
    float prix;
}panier;

panier * tabPanier;

/*!
*  \brief Prototype de la procédure "initFileClient"
*/
void initFileClient(void);

/*!
*  \brief Prototype de la fonction "idInitPanier"
*/
int idInitPanier(void);

/*!
*  \brief Prototype de la procédure "informationBoissonClient"
*/
void informationBoissonClient(void);

/*!
*  \brief Prototype de la procédure "demandeCommande"
*/
void demandeCommande(void);

/*!
*  \brief Prototype de la procédure "initCommande"
*/
void initCommande(panier nPanier);

/*!
*  \brief Prototype de la procédure "informationCommande"
*/
void informationCommande(void);

/*!
*  \brief Prototype de la procédure "supprimerPanier"
*/
void supprimerPanier(int idSupp);

/*!
*  \brief Prototype de la procédure "modifPanier"
*/
void modifPanier(int idModif);

/*!
*  \brief Prototype de la fonction "tailleTabPanier"
*/
int tailleTabPanier(void);

/*!
*  \brief Prototype de la procédure "initTabPanier"
*/
void initTabPanier(void);

/*!
*  \brief Prototype de la procédure "initFichierCommande"
*/
void initFichierCommande(int T);


#endif