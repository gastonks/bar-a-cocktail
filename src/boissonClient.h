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
    int nbBoisson;
    int** tabCommandeBoisson;
    float prix;
}commande;

void initFileClient(void);
void informationBoissonClient(void);
void commandeBoissonClient(int idBoisson, int recom);
void informationCommandeClient(void);

int tailleTabCom();
void initTabCom();
void initFichierCom(int T);

int idTOpos(int id);
int posTOid(int pos);

commande* tabCom;

#endif