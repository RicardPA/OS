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

// Valores definidos
#define LENGTH_INSTRUCTIONS 3 
#define LENGTH_RECORDER 6
#define LENGTH_MEMORY 6
#define LENGTH_BUFFER (LENGTH_RECORDER*2)

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
		createGraph(quantEdge, &graph);
		
		createVertex(graph.edges[0].origin, 0, 10);
		
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
