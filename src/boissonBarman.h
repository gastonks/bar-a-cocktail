#ifndef BOISSONBARMAN_H
#define BOISSONBARMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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

void initFileBarman(void);
int idInit(void);
void ajoutBoissonAlcool(void);
void ajoutBoissonNonAlcool(void);
void informationBoissonBarman(void);
void suppBoisson(void);

void modifBoisson(void);
void gestionStock(void);

float recetteJour(void);
float recetteHier(void);
void remiseZero(void);


#endif