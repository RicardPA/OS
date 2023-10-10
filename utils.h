/*
	-----------------------------------
	utils.c 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Operacoes para melhorar a usabilidade
*/
#include <stdio.h>
#include <stdlib.h>

void pressToContinue() {
	getchar();
    printf("\n\tPressione qualquer tecla para continuar...\n");
    getchar();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}