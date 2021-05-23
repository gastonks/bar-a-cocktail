#ifndef BOISSONCLIENT_H
#define BOISSONCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boissonBarman.h"
#include "interface.h"

typedef struct listIdBoisson
{
    int idBoisson;
    int quantiteBoisson;
}listIdBoisson;

typedef struct listIdCocktail
{
    int idCocktail;
    int quantiteCocktail;
}listIdCocktail;


typedef struct commande
{
    int nbrBoisson;
    listIdBoisson * listBoisson;
    int nbrCocktail;
    listIdCocktail * listCocktail;
    float prix;

}commande;

typedef struct panier
{
    int id;
    int nbrCommande;
    commande * listCommande;
    float prix;
}panier;

panier * tabPanier;

void initFileClient(void);
int idInitPanier(void);
void informationBoissonClient(void);

void demandeCommande(void);
void initCommande(panier nPanier);
void informationCommande(void);
void supprimerPanier(int idSupp);
int tailleTabPanier(void);
void initTabPanier(void);
void initFichierCommande(int T);


#endif