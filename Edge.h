/*
	-----------------------------------
	Edge.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Simular a existencia de uma conexao
	entre dois vertices, alem de ajudar
	nas contas de custo.
*/

typedef struct 
{
	Vertex *destiny;
	Vertex *origin;
	int cost;
} Edge;

void createEdge (Edge *edge, Vertex *destiny, Vertex *origin, int cost) 
{
	edge->destiny = destiny;
	edge->origin = origin;
	edge->cost = cost;
}

void printEdge (Edge *edge) 
{
	printf("\n|--- (Aresta) Custo: %d\n", edge->cost);
	
	printVertex(edge->destiny);
	printVertex(edge->origin);
	
	printf("\n|--- Fim Aresta ---\n");
}
