#ifndef INTERACTION_H
#define INTERACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct boisson
{
    int id;
    char nom[51];
    float contenance;
    float prix;
    float quantite;
    float degreAlco;
    float degreScr;
}boisson;

void initFile(void);
int idInit(void);
void ajoutBoissonAlcool(void);
void ajoutBoissonNonAlcool(void);
void informationBoisson(void);
void suppBoisson(void);


#endif