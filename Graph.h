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

#include "Edge.h"
#include "Vertex.h"
#include "Routes.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define DISTRIBUTION_CENTER_IDENTIFIER 0

typedef struct {
    int quantVertex;
    int quantEdge;
    Edge *edges;
    Vertex *vertices;
} Graph;

Graph initializeGraph(int quant) {
    Graph graph = {
        .quantVertex = quant,
        .quantEdge = (quant * (quant - 1)) / 2,
        .edges = (Edge *)calloc(((quant * (quant - 1)) / 2), sizeof(Edge)),
        .vertices = (Vertex *)calloc(quant, sizeof(Vertex))
    };

    return graph;
}

Graph assembleGraphFile() {
    int quantVertex = 0;
    FILE *file;
    Graph graph;

    file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n Verifique se o arquivo \"input.txt\" se "
               "encontra no diretório de execução.\n");
        return graph;
    }

    fscanf(file, "%d", &quantVertex);

    graph = initializeGraph(quantVertex);

    // Criar vertices
    for (int i = 0; i < graph.quantVertex; i++) {
        int demand;

        fscanf(file, "%d", &demand);

        initializeVertex(&graph.vertices[i], i, demand);
    }

    // Criar arestas
    for (int i = 0; i < graph.quantEdge; i++) {
        int cost;
        int identifier_origin;
        int identifier_destiny;

        fscanf(file, "%d %d %d", &identifier_origin, &identifier_destiny, &cost);

        initializeEdge(&graph.edges[i], &graph.vertices[identifier_origin],
                       &graph.vertices[identifier_destiny], cost);
    }

    fclose(file);

    return graph;
}

void printGraph(Graph *graph) {
    printf("\n|--- (Grafo) Quantidade de arestas: %d\n\n", graph->quantEdge);

    for (int i = 0; i < graph->quantEdge; i++) {
        printEdge(&graph->edges[i]);
    }

    printf("\n|--- Fim Grafo ---\n\n");
}

void freeGraph(Graph *graph) {
    if (graph != NULL) {
        free(graph->edges);
        free(graph->vertices);
        free(graph);
    }
}

bool isDistributionCenter(Vertex* vertex)
{
    return vertex->identifier == DISTRIBUTION_CENTER_IDENTIFIER;
}

bool isPathToDistributionCenter(Edge* edge)
{
    return (
        isDistributionCenter(edge->origin) ||
        isDistributionCenter(edge->destiny)
    );
}

bool isVertexInEdge(Vertex* vertex, Edge* edge)
{
    return (
        edge->origin->identifier == vertex->identifier ||
        edge->destiny->identifier == vertex->identifier
    );
}

int costToDistributionCenter(Vertex* vertex, Graph* graph)
{
    size_t currentEdgeIndex = 0;
    Edge* currentEdge = &graph->edges[0];

    while (currentEdgeIndex < graph->quantEdge && isPathToDistributionCenter(currentEdge))
    {
        if (isVertexInEdge(vertex, currentEdge))
        {
            return currentEdge->cost;
        }

        currentEdge = &graph->edges[++currentEdgeIndex];
    }

    return 0;
}

void getRoutesEconomy(Graph *graph, Routes *routes)
{
	Routes *routesTemp = routes;

    for (size_t i = 0; i < graph->quantEdge; i++)
    {
        Edge* edge = &graph->edges[i];

        if (isPathToDistributionCenter(edge))
        {
            continue;
        }

        int costFromOriginToDC = costToDistributionCenter(edge->origin, graph);
        int costFromDestinyToDC = costToDistributionCenter(edge->destiny, graph);
        int economy = costFromOriginToDC + costFromDestinyToDC - edge->cost;

		routesTemp->economy = economy;
		routesTemp->demand = edge->origin->demand + edge->destiny->demand;
		routesTemp->identifiers[0] = edge->origin->identifier;
		routesTemp->identifiers[1] = edge->destiny->identifier;

		if ((i + 1) < graph->quantEdge) {
			if (routesTemp->nextRoute == NULL) {  
				routesTemp->nextRoute = initializeRoutes();
				routesTemp = routesTemp->nextRoute;
			}
		}
    }
}

#endif
