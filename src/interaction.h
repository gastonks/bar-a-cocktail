#ifndef INTERACTION_H
#define INTERACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct boissonAlcool
{
    char nom[51];
    float contenance;
    float prix;
    float quantite;
    float degreAlco;
}boissonAlcool;

typedef struct boissonScr
{
    char* nom;
    float contenance;
    float prix;
    float quantite;
    float degreScr;
}boissonScr;

void ajoutBoissonAlcool(void);
void ajoutBoissonNonAlcool(void);

#endif