/*! \file header.h
*  \section Présentation
*  Ce header rassemble les headers de chaque fichier séparé.
*  Chaque header contient les fonctions du fichier .c qui lui est associé.
*  Nous avons essayé de diviser un maximum le code pour gagner en compréhension.
*/

/*
Condition qui permet de définir ou non le header "interface.h" si il est déjà défini quelque part.
*/
#ifndef HEADER_H
#define HEADER_H

/*  
    Le fichier header principale permet au fichier main d'avoir accès à toutes les fonctions utilisées dans le programme.
    Cela permet ainsi de mieux se retrouver dans les différentes fonctionnalités du programme.
*/

#include <stdio.h>
#include "interface.h"
#include "boissonBarman.h"
#include "boissonClient.h"
#include "cocktail.h"

#endif