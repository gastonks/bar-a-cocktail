#ifndef BOISSONCLIENT_H
#define BOISSONCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boissonBarman.h"
#include "interface.h"

typedef struct commande
{
    char nom[51];
    float prix;
    float quantite;
}commande;

void initFileClient(void);
void informationBoissonClient(void);
void commandeBoissonClient(int idBoisson);
void informationCommandeClient(void);

int calcTailleCom();
void initTabCom();
void initFichierCom(int T);

commande* tabCom;

#endif