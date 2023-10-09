/*
	-----------------------------------
	Vertex.c 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Simular um local onde a entrega deve
	ser feita, armazenando a quantidade 
	de recurso que deve ser entregue.
*/


typedef struct 
{
	int identifier;
	int demand;
} Vertex;

void createVertex (Vertex *vertex, int identifier, int demand) 
{
	vertex->demand = demand;
	vertex->identifier = identifier;
}

void printVertex (Vertex *vertex) 
{
	printf("\n| (Vertice) Identificador: %d | Demanda: %d\n", vertex->identifier, vertex->demand);
}
