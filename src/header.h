/*! \file header.h
*  \section Présentation
*  Le header regroupe les bibliothèques, le(s) constante(s), le(s) structure(s) et les prototypes de fonctions/procédures utiles au bon fonctionnement du programme.
*
*  \brief Regroupe les bibliothèques, le(s) constante(s), le(s) structure(s) et les prototypes de fonctions/procédures
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

/* Bibliothèques */

#include <stdio.h>
#include "interface.h"
#include "boissonBarman.h"
#include "boissonClient.h"
#include "cocktail.h"

#endif