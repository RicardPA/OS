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

typedef struct Routes
{
	int economy;
	int demand;
	int length;
	int *identifiers;
	struct Routes *nextRoute;
} Routes;

void initializeRoutes (Routes *routes, Graph *graph, int identifier_origin, int identifier_destiny) 
{
	routes->length = 2;
	routes->identifiers = (int*)malloc(2 * sizeof(int));
	routes->nextRoute = NULL;
}

void addVertex (Routes *routes, Graph *graph, int identifier, int identifier_destiny) 
{
	routes->identifiers = (int*)realloc(routes->identifiers,(routes->length + 1)*sizeof(int));
}

void freeRoutes(Routes* routes)
{
    if(routes != NULL)
    {
        free(routes->identifiers);
        free(routes);
    }
}

#endif 