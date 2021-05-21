#ifndef BOISSONCLIENT_H
#define BOISSONCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boissonBarman.h"
#include "interface.h"

typedef struct commande
{
    int id;
    int nbrBoisson;
    struct boisson * tabBoisson;
    int nbrCocktail;
    struct cocktail * tabCocktail;
    float prix;
    float quantite;
}commande;

void initFileClient(void);
int idInitCommande(void);
void informationBoissonClient(void);
void commandeBoissonClient(int idBoisson);
void informationCommandeClient(void);


#endif