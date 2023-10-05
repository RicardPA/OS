/*
	-----------------------------------
	Graph.h
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Representação do grafo utilizado no
	trabalho, nele temos um vetor de
	arestas.
*/


typedef struct 
{
	int quant;
	Edge *edges;
	Vertex *vertices;
} Graph;

void createGraph (int quant, Graph *graph) 
{
	graph->vertex = (Vertex*)malloc(quant * sizeof(Vertex));
	graph->edges = (Edge*)malloc(((quant * (quant - 1))/2) * sizeof(Edge));
	graph->quant = quant;
}

void printGraph (Graph *graph) 
{
	printf("\n|--- (Grafo) Quantidade de arestas: %d\n\n", graph->quant);
	
	for (int i = 0; i < graph->quant; i++)
	{
		printEdge(&graph->edges[i]);
	}	
	
	printf("\n|--- Fim Grafo ---\n\n");
}