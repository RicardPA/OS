/*
	-----------------------------------
	Edge.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Simular a existencia de uma conexao
	entre dois vertices, alem de ajudar
	nas contas de custo.
*/

#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>

#include "Vertex.h"

typedef struct 
{
	Vertex *destiny;
	Vertex *origin;
	int cost;
} Edge;

void printEdge (Edge *edge) 
{
	printf("\n|--- (Aresta) Custo: %d\n", edge->cost);
	
	printVertex(edge->destiny);
	printVertex(edge->origin);
	
	printf("\n|--- Fim Aresta ---\n");
}


void initializeEdge (Edge *edge, Vertex *destiny, Vertex *origin, int cost) 
{
	edge->destiny = destiny;
	edge->origin = origin;
	edge->cost = cost;
}

#endif
