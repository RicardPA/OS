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

Routes* initializeRoutes() 
{
    Routes* routes = (Routes*)malloc(sizeof(Routes));
    routes->length = 2;
    routes->identifiers = (int*)calloc(2, sizeof(int));
    routes->nextRoute = NULL;

    return routes;
}

// void addVertex (Routes *routes, Graph *graph, int identifier, int identifier_destiny) 
// {
// 	routes->identifiers = (int*)realloc(routes->identifiers,(routes->length + 1)*sizeof(int));
// }

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
                printf(" %d |", routesTemp->identifiers[i]);
            }
            printf("\n");
        }

        printf("|--- Fim Rota ---\n");

        routesTemp = routesTemp->nextRoute;
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

#endif 