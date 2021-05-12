#ifndef BOISSONBARMAN_H
#define BOISSONBARMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "boissonClient.h"
#include "interface.h"

// Structure boisson permettant de gérer les informations de chaque boisson
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

// Fonctions pour la gestion du tableau dynamique
void initTab();
void initFichier(int t);
int tailleTabBarman();

boisson* tab;

#endif