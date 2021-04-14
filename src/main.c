#include <stdio.h>
#include "interface.h"
#include "boissonBarman.h"
#include "boissonClient.h"

int main(int argc, char** argv){
    initFileBarman();
    initFileClient();
    interfaceAccueil();

    return 0;
}