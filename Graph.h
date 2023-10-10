/*
	-----------------------------------
	Graph.h
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Representação do grafo utilizado no
	trabalho, nele temos um vetor de
	arestas.
*/

#include "Vertex.h"
#include "Edge.h"

typedef struct 
{
	int quant;
	Edge *edges;
	Vertex *vertices;
} Graph;

void createGraph (int quant, Graph *graph) 
{
	graph->vertices = (Vertex*)malloc(quant * sizeof(Vertex));
	graph->edges = (Edge*)malloc(((quant * (quant - 1))/2) * sizeof(Edge));
	graph->quant = quant;
}

int assembleGraphFile (Graph *graph) 
{
	int quantVertex = 0;
	FILE *file;
	
	file = fopen("input.txt", "r");

	if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n Verifique se o arquivo \"input.txt\" se encontra no diretório de execução.\n");
        return 1;
    }

	fscanf(file, "%d", &quantVertex);

	createGraph(quantVertex, graph);

	// Criar vertices
	for (int i = 0; i < graph->quant; i ++)
	{
		int demand;
		
		fscanf(file, "%d", &demand);
					
		createVertex(&graph->vertices[i], i, demand);
	}
	
	// Criar arestas
	for (int i = 0; i < ((graph->quant * (graph->quant - 1))/2); i++) 
	{
		int cost;
		int identifier_origin;
		int identifier_destiny;
		
		fscanf(file, "%d %d %d", &identifier_origin, &identifier_destiny, &cost);
		
		createEdge(&graph->edges[i], &graph->vertices[identifier_origin], &graph->vertices[identifier_destiny], cost);
	}

	fclose(file);
}

void printGraph (Graph *graph) 
{
	printf("\n|--- (Grafo) Quantidade de arestas: %d\n\n", ((graph->quant * (graph->quant - 1))/2));
	
	for (int i = 0; i < ((graph->quant * (graph->quant - 1))/2); i++)
	{
		printEdge(&graph->edges[i]);
	}	
	
	printf("\n|--- Fim Grafo ---\n\n");
}