//#ifndef NULL
//#include <stdlib.h>
//#endif
//
//typedef struct GraphEdge {
//	int weight;
//	int vertex;
//	struct GraphEdge* nextEdge;
//} GraphEdge;
//
//typedef struct GraphVertex {
//	int value;
//	GraphEdge* edges;
//	struct GraphVertex* nextVertex;
//} GraphVertex;
//
//typedef struct Graph {
//	int vertexCount;
//	GraphVertex* vertices;
//} Graph;
//
//Graph* init_graph() {
//	Graph* graph = (Graph*)malloc(sizeof(Graph));
//
//	if (graph == NULL) {
//		printf("Could not initialize graph!\n");
//		return NULL;
//	}
//	
//	graph->vertexCount = 0;
//	graph->vertices = NULL;
//
//	return graph;
//}
//
//void addVertex(Graph* graph, int value) {
//	if (graph == NULL) {
//		printf("Please provide a valid graph!\n");
//		return;
//	}
//
//	GraphVertex* vertex = (GraphVertex*)malloc(sizeof(GraphVertex));
//	vertex->value = value;
//	vertex->nextVertex = NULL;
//	vertex->edges = NULL;
//	
//	
//	if (graph->vertices == NULL) {
//		graph->vertices = vertex;
//		graph->vertexCount = 1;
//		return;
//	}
//
//	GraphVertex* currVertex = graph->vertices;
//	while (currVertex->nextVertex != NULL) {
//		if (currVertex->value == value) {
//			printf("Vertex with value %d already exists!\n", value);
//			return;
//		}
//
//		currVertex = currVertex->nextVertex;
//	}
//	currVertex->nextVertex = vertex;
//	graph->vertexCount++;
//	printf("Added vertex %d to graph!\n", value);
//}
//
//void addEdge(Graph* graph, int from, int to, int weight) {
//	// Steps:
//	// 1. Go to the from vertex
//	// 2. Check if the edge already exists
//	// 3. If it does, then do nothing
//	// 4. Otherwise, create a new edge to "to" vertex and set its weight
//	if (graph == NULL) {
//		printf("Please provide a valid graph!\n");
//		return;
//	}
//
//	if (graph->vertices == NULL) {
//		printf("Graph does not have any vertices!\n");
//		return;
//	}
//
//	GraphVertex* currVertex = graph->vertices;
//	while (currVertex != NULL && currVertex->value != from)
//		currVertex = currVertex->nextVertex;
//
//	if (currVertex == NULL) {
//		printf("The vertex does not exist!\n");
//		return;
//	}
//
//	GraphEdge* newEdge = (GraphEdge*)malloc(sizeof(GraphEdge));
//	newEdge->nextEdge = NULL;
//	newEdge->weight = weight;
//	newEdge->vertex = to;
//
//	if (currVertex->edges == NULL) {
//		currVertex->edges = newEdge;
//		return;
//	}
//
//	GraphEdge* currEdge = currVertex->edges;
//
//	while (currEdge->nextEdge != NULL) {
//		if (currEdge->vertex == to) {
//			printf("Edge already exists from %d to %d!\n", from, to);
//			return;
//		}
//		currEdge = currEdge->nextEdge;
//	}
//
//	printf("Added new edge from %d to %d!\n", from, to);
//	currEdge->nextEdge = newEdge;
//}