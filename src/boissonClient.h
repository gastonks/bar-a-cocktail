#ifndef BOISSONCLIENT_H
#define BOISSONCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct commande
{
    int id;
    char nom[51];
    float prix;
    float quantite;
}commande;

void initFileClient(void);
int idInitCommande(void);
void informationBoissonClient(void);
void commandeBoissonClient(int idBoisson);
void informationCommandeClient(void);


#endif