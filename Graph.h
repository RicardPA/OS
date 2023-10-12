/*
	-----------------------------------
	Graph.h
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Representação do grafo utilizado no
	trabalho, nele temos um vetor de
	arestas.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
	int quantVertex;
	int quantEdge;
	Edge *edges;
	Vertex *vertices;
} Graph;

Graph initializeGraph (int quant) 
{
	Graph graph = {
		.vertices = (Vertex*)malloc(quant * sizeof(Vertex)),
		.edges = (Edge*)malloc(((quant * (quant - 1))/2) * sizeof(Edge)),
		.quantVertex = quant,
		.quantEdge = (quant * (quant - 1))/2
	};

	return graph;
}

Graph assembleGraphFile () 
{
	int quantVertex = 0;
	FILE *file;
	Graph graph;
	
	file = fopen("input.txt", "r");

	if (file == NULL) {
		printf("Erro ao abrir o arquivo.\n Verifique se o arquivo \"input.txt\" se encontra no diretório de execução.\n");
		return graph;
	} 

	fscanf(file, "%d", &quantVertex);

	graph = initializeGraph(quantVertex);

	// Criar vertices
	for (int i = 0; i < graph.quantVertex; i ++)
	{
		int demand;
		
		fscanf(file, "%d", &demand);
					
		initializeVertex(&graph.vertices[i], i, demand);
	}
	
	// Criar arestas
	for (int i = 0; i < graph.quantEdge; i++) 
	{
		int cost;
		int identifier_origin;
		int identifier_destiny;
		
		fscanf(file, "%d %d %d", &identifier_origin, &identifier_destiny, &cost);
		
		initializeEdge(&graph.edges[i], &graph.vertices[identifier_origin], &graph.vertices[identifier_destiny], cost);
	}

	fclose(file);

	return graph;
}

void printGraph (Graph *graph) 
{
	printf("\n|--- (Grafo) Quantidade de arestas: %d\n\n", graph->quantEdge);
	
	for (int i = 0; i < graph->quantEdge; i++)
	{
		printEdge(&graph->edges[i]);
	}	
	
	printf("\n|--- Fim Grafo ---\n\n");
}

void freeGraph(Graph* graph)
{
    if(graph != NULL)
    {
        free(graph->edges);
		free(graph->vertices);
        free(graph);
    }

void printEconomy (Graph *graph)
{	
	for (int i = 0; i < graph->quantVertex; i++)
	{
		for (int j = 0; j < graph->quantEdge; j++)
		{
			if (graph->edges[j].origin->identifier == 0)
			{
				
			}
		}
	}
}}


#endif 