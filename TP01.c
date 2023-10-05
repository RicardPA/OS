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
	int quantEdge;

	scanf("%d", &quantVertex);
	

	if (quantVertex && quantVertex > 0) 
	{
	
		// Criar vertices
		createGraph(quantVertex, &graph);
		
		for (int i = 0; i < quantVertex - 1; i ++)
		{
			int value;

			scanf("%d", &value);
						
			createVertex(&graph.vertices[i], i, value);
		}
		
		for (int i = 0; i < quantEdge; i++) 
		{
			
		}

		printGraph(&graph);
	}
	else
	{
		printf("Erro: Valor passado é invalido.");
	}

	return 0;
}
