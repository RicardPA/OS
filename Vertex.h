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

void printVertex (Vertex *vertex) 
{
	printf("\n| (Vertice) Identificador: %d | Demanda: %d\n", vertex->identifier, vertex->demand);
}

Vertex* createVertex (int identifier, int demand) 
{
    Vertex* vertex = (Vertex*) malloc(sizeof(Vertex));
    
	if (!vertex) { // Verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória para o vértice.\n");
        return NULL;
    }

    vertex->demand = demand;
    vertex->identifier = identifier;

    return vertex;
}

void destroyVertex(Vertex* vertex) {
    free(vertex);
}