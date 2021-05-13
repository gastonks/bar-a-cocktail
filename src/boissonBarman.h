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
void ajoutBoissonAlcool(char nom[], float contenance, float prix, float quantite, float degreAlco);
void ajoutBoissonNonAlcool(char nom[], float contenance, float prix, float quantite, float degreAlco);
void informationBoissonBarman(void);
void suppBoisson(int idSupp);
void modifBoisson(int idChange);
void gestionStock(int idStock, float stockR, float stockV);
void satisfactionCommande(int nCommande);

// Fonction pour la gestion des finances
float recette(float prix);

// Fonctions pour la gestion du tableau dynamique
void initTab();
void initFichier(int t);
int tailleTabBarman();

boisson* tab;




#endif