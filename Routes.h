/*
	-----------------------------------
	Routes.h
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Representação das rotas geradas por
	meio da otimização.
*/

#ifndef ROUTES_H
#define ROUTES_H

#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "Vertex.h"
#define DISTRIBUTION_CENTER_IDENTIFIER 0

typedef struct Routes
{
	int economy;
	int demand;
	int length;
	int *identifiers;
	struct Routes *nextRoute;
} Routes;

Routes* initializeRoutes() 
{
    Routes* routes = (Routes*)malloc(sizeof(Routes));
    routes->length = 2;
    routes->identifiers = (int*)calloc(2, sizeof(int));
    routes->nextRoute = NULL;

    return routes;
}

void addVertex(Routes *routes, int identifier) 
{
    // Verificando se o identificador já está presente
    for (size_t i = 0; i < routes->length; i++)
    {
        if (routes->identifiers[i] == identifier)
        {
            return;  // Já está presente, então retorne sem adicionar novamente
        }
    }

    // Adicionando o novo identificador
    routes->identifiers = (int*)realloc(routes->identifiers, (routes->length + 1) * sizeof(int));
    routes->identifiers[routes->length] = identifier;
    routes->length = routes->length + 1;  
}

void swapRoutes(Routes *a, Routes *b) {
    int tempEconomy = a->economy;
    a->economy = b->economy;
    b->economy = tempEconomy;

    int tempDemand = a->demand;
    a->demand = b->demand;
    b->demand = tempDemand;

    int tempLength = a->length;
    a->length = b->length;
    b->length = tempLength;

    int *tempIdentifiers = a->identifiers;
    a->identifiers = b->identifiers;
    b->identifiers = tempIdentifiers;
}

void sortRoutes(Routes *routes) {
    int swapped; // flag para verificar se uma troca foi feita
    Routes *ptr1 = routes;
    Routes *lptr = NULL;

    if (routes == NULL) // lista vazia
        return;

    do {
        swapped = 0;
        ptr1 = routes;

        while (ptr1->nextRoute != lptr) {
            if (ptr1->economy > ptr1->nextRoute->economy) {
                swapRoutes(ptr1, ptr1->nextRoute);
                swapped = 1;
            }
            ptr1 = ptr1->nextRoute;
        }
        lptr = ptr1;

    } while (swapped);
}

void printRoutes (Routes *routes) 
{
	Routes *routesTemp = routes;

	while (routesTemp != NULL)
    {
        printf("\n|--- (Rota) | Economia: %d | Demanda: %d\n", routesTemp->economy, routesTemp->demand);

        if (routesTemp->identifiers != NULL && routesTemp->length > 0)
        {
            printf("Vertices: |");
            for (size_t i = 0; i < routesTemp->length; i++)
            {
                if (routesTemp->identifiers[i] != -1) {
                    printf(" %d |", routesTemp->identifiers[i]);
                }
            }
            printf("\n");
        }

        printf("|--- Fim Rota ---\n");

        routesTemp = routesTemp->nextRoute;
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

bool identifierInRoute(Routes *route, int identifier) 
{
    for (int i = 0; i < route->length; i++) 
    {
        if (route->identifiers[i] == identifier) 
        {
            return true;
        }
    }
    return false;
}


int costToDistributionCenter(Vertex* vertex, Graph* graph)
{
    size_t currentEdgeIndex = 0;
    Edge* currentEdge = &graph->edges[0];

    while (currentEdgeIndex < graph->quantEdge) 
    {
        if (isVertexInEdge(vertex, currentEdge) && isPathToDistributionCenter(currentEdge)) 
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

		if (routesTemp->nextRoute == NULL && (i + 1) < graph->quantEdge) 
        {  
			routesTemp->nextRoute = initializeRoutes();
			routesTemp = routesTemp->nextRoute;
		}
    }
}

void freeRoutes(Routes* routes)
{
    if(routes != NULL)
    {
        free(routes->identifiers);
        free(routes);
    }
}

bool canCombine(Routes *route1, Routes *route2, int totalDemand) {
    int combinedDemand = route1->demand + route2->demand;

    if (combinedDemand > totalDemand) {
        return false;
    }

    for (int i = 0; i < route1->length; i++) {
        for (int j = 0; j < route2->length; j++) {
            if (route1->identifiers[i] == route2->identifiers[j]) {
                return false;
            }
        }
    }

    return true;
}

Routes* combineRoutes(Routes *route1, Routes *route2, Graph *graph) {
    Routes *newRoute = initializeRoutes();

    // Adicionando os vértices da primeira rota
    for (int i = 0; i < route1->length; i++) {
        addVertex(newRoute, route1->identifiers[i]);
    }

    // Adicionando os vértices da segunda rota, evitando o centro de distribuição
    for (int j = 0; j < route2->length; j++) {
        if(route2->identifiers[j] != DISTRIBUTION_CENTER_IDENTIFIER) { 
            addVertex(newRoute, route2->identifiers[j]);
        }
    }

    newRoute->demand = route1->demand + route2->demand;
    newRoute->economy = route1->economy + route2->economy; 

    return newRoute;
}

void removeRoute(Routes **head, Routes *routeToRemove) {
    if (*head == NULL) return;

    Routes *temp = *head, *prev;

    if (temp != NULL && temp == routeToRemove) {
        *head = temp->nextRoute;
        freeRoutes(temp);
        return;
    }

    while (temp != NULL && temp != routeToRemove) {
        prev = temp;
        temp = temp->nextRoute;
    }

    if (temp == NULL) return;

    prev->nextRoute = temp->nextRoute;
    freeRoutes(temp);
}

void combineAllPossibleRoutes(Graph *graph, Routes **routes, int totalDemand) {
    bool hasCombined = true;
    while (hasCombined) {
        hasCombined = false;
        Routes *currentRoute = *routes;
        while (currentRoute != NULL) {
            Routes *nextRoute = currentRoute->nextRoute;
            while (nextRoute != NULL) {
                if (canCombine(currentRoute, nextRoute, totalDemand)) {
                    Routes *newRoute = combineRoutes(currentRoute, nextRoute, graph);

                    // Adicionando a nova rota na lista
                    newRoute->nextRoute = *routes;
                    *routes = newRoute;

                    // Removendo as rotas antigas
                    removeRoute(routes, currentRoute);
                    removeRoute(routes, nextRoute);

                    // Indicando que uma combinação foi feita e redefinindo o loop
                    hasCombined = true;
                    break;
                }
                nextRoute = nextRoute->nextRoute;
            }
            if (hasCombined) break; // Sai do loop externo se uma combinação foi feita
            currentRoute = currentRoute->nextRoute;
        }
    }
}

#endif 