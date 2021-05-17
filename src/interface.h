/*
Condition qui permet de définir ou non le header "interface.h" si il est déjà défini quelque part.
*/
#ifndef INTERFACE_H
#define INTERFACE_H

// Bibliothèques et headers
#include <stdio.h>
#include <stdlib.h>
#include "boissonBarman.h"
#include "boissonClient.h"
#include "cocktail.h"


// Interface general pour le client ou le barman
void interfaceAccueil(void);
void interfaceBarman(void);
void interfaceClient(void);

// Interface specifique au barman
void interfaceGestionBoissonBarman(void);
void interfaceGestionCocktail(void);
void interfaceGestionFinance(void);
void interfaceInformationBoissonBarman(void);
void interfaceAjoutOuSuppBoisson(void);
void interfaceAjoutBoissonAlcool(void);
void interfaceAjoutBoissonNonAlcool(void);
void interfaceSuppBoisson(void);
void interfaceModifBoisson(void);
void interfaceModifBoissonAlco(void);
void interfaceModifBoissonNonAlco(void);
void interfaceGestionStock(void);
void interfaceSatisfactionCommande(void);

// Interface specifique au client
void interfaceGestionBoissonClient(void);
void interfaceInformationBoissonClient(void);
void interfaceInformationCommandeClient(void);
void interfaceCommandeBoisson(int recom);

// Interface dans la gestion des cocktail
void interfaceCommandeCocktail(void);
void interfaceCreationCocktail(void);
void interfaceInformationCocktail(void);

#endif