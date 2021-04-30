#ifndef INTERFACE_H
#define INTERFACE_H

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

// Interface specifique au client
void interfaceGestionBoissonClient(void);
void interfaceInformationBoissonClient(void);
void interfaceInformationCommandeClient(void);
void interfaceCommandeBoisson(void);

// Interface dans la gestion des cocktail
void interfaceCommandeCocktail(void);
void interfaceCreationCocktail(void);
void interfaceInformationCocktail(void);

#endif
