#ifndef NULL
#include <stdlib.h>
#endif

#include "union-find.c"

#ifndef DEBUG_FLAG
#define DEBUG_FLAG 0
#endif

typedef struct GraphEdge {
	int weight;
	int vertex;
	struct GraphEdge* nextEdge;
} GraphEdge;

typedef struct GraphVertex {
	int value;
	GraphEdge* edges;
	struct GraphVertex* nextVertex;
} GraphVertex;

typedef struct GraphWeight {
	int from;
	int to;
	int weight;
	struct GraphWeight* nextWeight;
} GraphWeight;

typedef struct GraphList {
	int vertexCount;
	GraphVertex* vertices;
	GraphWeight* weights;
} GraphList;

GraphList* init_graph() {
	GraphList* graph = (GraphList*)malloc(sizeof(GraphList));

	if (graph == NULL) {
		printf("Could not initialize graph!\n");
		return NULL;
	}
	
	graph->vertexCount = 0;
	graph->vertices = NULL;
	graph->weights = NULL;

	return graph;
}

void addVertex(GraphList* graph, int value) {
	if (graph == NULL) {
		printf("Please provide a valid graph!\n");
		return;
	}

	GraphVertex* vertex = (GraphVertex*)malloc(sizeof(GraphVertex));
	vertex->value = value;
	vertex->nextVertex = NULL;
	vertex->edges = NULL;
	
	
	if (graph->vertices == NULL) {
		graph->vertices = vertex;
		graph->vertexCount = 1;
		return;
	}

	GraphVertex* currVertex = graph->vertices;
	while (currVertex->nextVertex != NULL) {
		if (currVertex->value == value) {
			printf("Vertex with value %d already exists!\n", value);
			return;
		}

		currVertex = currVertex->nextVertex;
	}
	currVertex->nextVertex = vertex;
	graph->vertexCount++;
	if (DEBUG_FLAG)
		printf("[DEBUG] Added vertex %d to graph!\n", value);
}

void addEdge(GraphList* graph, int from, int to, int weight) {
	// Steps:
	// 1. Go to the from vertex
	// 2. Check if the edge already exists
	// 3. If it does, then do nothing
	// 4. Otherwise, create a new edge to "to" vertex and set its weight
	if (graph == NULL) {
		printf("Please provide a valid graph!\n");
		return;
	}

	if (graph->vertices == NULL) {
		printf("Graph does not have any vertices!\n");
		return;
	}

	GraphVertex* currVertex = graph->vertices;
	while (currVertex != NULL && currVertex->value != from)
		currVertex = currVertex->nextVertex;

	if (currVertex == NULL) {
		printf("The vertex does not exist!\n");
		return;
	}

	GraphEdge* newEdge = (GraphEdge*)malloc(sizeof(GraphEdge));
	newEdge->nextEdge = NULL;
	newEdge->weight = weight;
	newEdge->vertex = to;

	if (currVertex->edges == NULL) {
		currVertex->edges = newEdge;
		return;
	}

	GraphEdge* currEdge = currVertex->edges;

	while (currEdge->nextEdge != NULL) {
		if (currEdge->vertex == to) {
			printf("[WARN] Edge already exists from %d to %d!\n", from, to);
			return;
		}
		currEdge = currEdge->nextEdge;
	}

	if (DEBUG_FLAG)
		printf("[DEBUG] Added new edge from %d to %d!\n", from, to);
	currEdge->nextEdge = newEdge;
}

void printListGraph(GraphList* graph) {
	if (!graph) {
		printf("No graph provided!");
		return;
	}

	GraphVertex* currVertex = graph->vertices;
	while (currVertex != NULL) {
		printf("Vertex %4d =>  ", currVertex->value);
		GraphEdge* currEdge = currVertex->edges;

		while (currEdge != NULL) {
			printf("(%4d, %4d)->", currEdge->vertex, currEdge->weight);

			currEdge = currEdge->nextEdge;
		}
		printf("NULL\n\n");
		currVertex = currVertex->nextVertex;
	}

	// Print weights
	printf("\nWeights:\n");
	GraphWeight* currWeight = graph->weights;
	while (currWeight != NULL) {
		printf("[WEIGHT] from: %4d, to %4d, weight: %4d\n", currWeight->from, currWeight->to, currWeight->weight);
		currWeight = currWeight->nextWeight;
	}
}

void addListWeight(GraphList* graph, int from, int to, int weight) {
	if (!graph) {
		printf("No graph provided!\n");
		return;
	}

	GraphWeight* currWeight = graph->weights;
	if (currWeight == NULL) {
		GraphWeight* weightNode = (GraphWeight*)malloc(sizeof(GraphWeight));
		if (!weightNode) {
			printf("Could not initialize weight!\n");
			return;
		}

		weightNode->from = from;
		weightNode->to = to;
		weightNode->weight = weight;
		weightNode->nextWeight = NULL;

		graph->weights = weightNode;
		if (DEBUG_FLAG)
			printf("[DEBUG] Added first weight from vertex %4d to vertex %4d with weight %4d\n", from, to, weight);
		return;
	}


	while (currWeight->nextWeight != NULL) {
		if (currWeight->from == from && currWeight->to == to) {
			currWeight->weight = weight;
			if (DEBUG_FLAG)
				printf("[DEBUG] Updated weight from vertex %4d to vertex %4d with weight %4d\n", from, to, weight);
			return;
		}

		currWeight = currWeight->nextWeight;
	}
	
	GraphWeight* weightNode = (GraphWeight*)malloc(sizeof(GraphWeight));
	if (!weightNode) {
		printf("Could not initialize weight!\n");
		return;
	}
	weightNode->from = from;
	weightNode->to = to;
	weightNode->weight = weight;
	weightNode->nextWeight = NULL;

	currWeight->nextWeight = weightNode;
	if (DEBUG_FLAG)
		printf("[DEBUG] Added weight from vertex %4d to vertex %4d with weight %4d\n", from, to, weight);
}

void randomizeGraph(GraphList* graph, int nodeCount, int max) {
	if (!graph) {
		printf("No graph provided!\n");
		return;
	}

	// Add vertices to the graph
	for (int idx = 0; idx < nodeCount; idx++)
		addVertex(graph, idx);

	// Add weights to the graph
	for (int from = 0; from < nodeCount; from++) {
		for (int to = 0; to < nodeCount; to++) {
			if (from == to)
				continue;

			addListWeight(graph, from, to, rand() % max);
		}
	}
}

void insertion_sort(GraphWeight** edges, int edgeCount) {
	for (int i = 1; i < edgeCount; i++) {
		GraphWeight* key = edges[i];
		int j = i - 1;

		while (j >= 0 && edges[j]->weight > key->weight) {
			edges[j + 1] = edges[j];
			j--;
		}
		edges[j + 1] = key;
	}
}

void createMSTKruskal(GraphList* graph) {
	if (!graph || !graph->weights) {
		printf("Graph is empty or has no edges!\n");
		return;
	}

	union_find_elem_t** vertex_sets = malloc(sizeof(union_find_elem_t*) * graph->vertexCount);
	if (!vertex_sets) {
		printf("Memory allocation failed!\n");
		return;
	}

	GraphVertex* currentVertex = graph->vertices;
	int vertexIndex = 0;
	while (currentVertex) {
		vertex_sets[vertexIndex] = make_set((void*)currentVertex);
		currentVertex = currentVertex->nextVertex;
		vertexIndex++;
	}

	int edgeCount = 0;
	GraphWeight* weightNode = graph->weights;
	while (weightNode) {
		edgeCount++;
		weightNode = weightNode->nextWeight;
	}

	GraphWeight** edges = malloc(sizeof(GraphWeight*) * edgeCount);
	if (!edges) {
		printf("Memory allocation failed!\n");
		free(vertex_sets);
		return;
	}

	weightNode = graph->weights;
	for (int i = 0; i < edgeCount; i++) {
		edges[i] = weightNode;
		weightNode = weightNode->nextWeight;
	}

	insertion_sort(edges, edgeCount);

	int mstEdgeCount = 0;
	for (int i = 0; i < edgeCount && mstEdgeCount < graph->vertexCount - 1; i++) {
		GraphWeight* edge = edges[i];

		union_find_elem_t* setFrom = find(vertex_sets[edge->from]);
		union_find_elem_t* setTo = find(vertex_sets[edge->to]);

		if (setFrom != setTo) {
			printf("[KRUSKAl] Add Edge from vertex %d to vertex %d\n", edge->from, edge->to);
			addEdge(graph, edge->from, edge->to, edge->weight);
			merge(setFrom, setTo);
			mstEdgeCount++;
		}
	}

	free(vertex_sets);
	free(edges);
}