/*
	-----------------------------------
	Vertex.c 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Simular um local onde a entrega deve
	ser feita, armazenando a quantidade 
	de recurso que deve ser entregue.
*/

#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int identifier;
	int demand;
} Vertex;

void initializeVertex (Vertex *vertex, int identifier, int demand) 
{
	vertex->demand = demand;
	vertex->identifier = identifier;
}

void printVertex (Vertex *vertex) 
{
	printf("\n| (Vertice) Identificador: %d | Demanda: %d\n", vertex->identifier, vertex->demand);
}

void freeVertex(Vertex* vertex) {
    free(vertex);
}

#endif