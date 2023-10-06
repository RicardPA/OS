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

int main(void) 
{
	// Denpendencias
	Graph graph;
	int quantVertex;

	scanf("%d", &quantVertex);
	
	if (quantVertex && quantVertex > 0) 
	{
		createGraph(quantVertex, &graph);
		
		for (int i = 0; i < quantVertex; i++)
		{
			graph.vertices[i] = *createVertex(i, 1);
		}
		
		// for (int i = 0; i < quantEdge; i++) 
		// {
			
		// }
		
		printGraph(&graph);
	} 
	else
	{
		printf("Erro: Valor passado é invalido.");
	}
	
	return 0;
}
