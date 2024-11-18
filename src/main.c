
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_FLAG 0

#include "GraphMatrix.c"
#include "Graph.c"


int main ()
{
	srand(time(NULL));

	/*GraphMatrix* graph = create_graph(10);

	printGraph(graph);
	addRandomWeights(graph, 250);
	createMSTPrim(graph, 0);
	printGraph(graph);*/


	Graph* graph = init_graph();
	randomizeGraph(graph, 5, 250);
	createMSTKruskal(graph);
	printListGraph(graph);

	return 0;
}