
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_FLAG 0

#include "GraphMatrix.c"


int main ()
{
	srand(time(NULL));

	GraphMatrix* graph = create_graph(10);

	printGraph(graph);
	addRandomWeights(graph, 250);
	printGraph(graph);
	createMSTPrim(graph, 0);

	return 0;
}