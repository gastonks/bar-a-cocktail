#include <stdio.h>
#include"interface.h"

int main(int argv, char** argc){
    //interface();
    switch (interface())
    {
    case 1:
        printf("interface barman");
        break;
    case 2:
        printf("interface client");
        break;
    
    default:
        printf("sorti interface");
        break;
    }
}