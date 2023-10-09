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
#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

int main(void) 
{
	// Denpendencias
	Graph graph;
	int quantVertex;

	scanf("%d", &quantVertex);
	

	if (quantVertex && quantVertex > 0) 
	{
	
		// Criar vertices
		createGraph(quantVertex, &graph);
		
		for (int i = 0; i < quantVertex - 1; i ++)
		{
			int demand;

			scanf("%d", &demand);
						
			createVertex(&graph.vertices[i], i, demand);
			
			printVertex(&graph.vertices[i]);
		}
		
		for (int i = 0; i < ((quantVertex * (quantVertex - 1))/2); i++) 
		{
			int cost;
			int identifier_origin;
			int identifier_destiny;
			
			scanf("%d %d %d", &identifier_origin, &identifier_destiny, &cost);
			
			createEdge(&graph.edges[i], &graph.vertices[identifier_origin], &graph.vertices[identifier_destiny], cost);
		}

		printGraph(&graph);
	}
	else
	{
		printf("Erro: Valor passado é invalido.");
	}

	return 0;
}
