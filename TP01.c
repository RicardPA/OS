/*
	-----------------------------------
	TP01.c 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Implementar a otimização de sistemas 
	de transporte usando grafos.
	
	OBS.: O grafo utilizado sempre será
	completo.
*/

/* Bibliotecas da Linguagem */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>

/* Bibliotecas do Projeto */
#include "Graph.h"
#include "Routes.h"
#include "utils.h"

int main(void) 
{
	// Denpendencias
	Graph graph = assembleGraphFile();
	Routes routes;

	// Criar menu de informações
	int option = -1;
	while (option != 0)
	{
		clearScreen();
		printf("\t- - - MENU - - -\n");
		printf("0) Finalizar\n");
		printf("1) Mostrar grafo\n");
		printf("2) Calcular resultado\n");
		printf("Opcao: ");
		scanf("%d", &option);

		clearScreen();
		
		switch (option)
		{
			case 0:
				printf("\nFinalizando...");
				break;
			case 1:
				printGraph(&graph);
				pressToContinue();
				clearScreen();
				break;
			case 2:
				printGraph(&graph);
				pressToContinue();
                printEconomy(&graph);
				pressToContinue();
				clearScreen();
				break;
			default:
				break;
		}
	}

	freeRoutes(&routes);
	freeGraph(&graph);
	clearScreen();
	
	return 0;
}
