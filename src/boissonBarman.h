#ifndef BOISSONBARMAN_H
#define BOISSONBARMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "boissonClient.h"
#include "interface.h"


typedef struct boisson
{
    char nom[51];
    float contenance;
    float prix;
    float quantite;
    float degreAlco;
    float degreScr;
}boisson;


// Fonction pour initialiser les fichiers
void initFileBarman(void);

// Fonction pour la gestion des boissons
int idInit(void);
void ajoutBoissonAlcool(void);
void ajoutBoissonNonAlcool(void);
void informationBoissonBarman(void);
void suppBoisson(void);
void modifBoisson(void);
void gestionStock(void);

// Fonction pour la gestion des finances
float recette(void);

void initTab();
void initFichier(int t);
int calcTaille();

boisson* tab;

#endif