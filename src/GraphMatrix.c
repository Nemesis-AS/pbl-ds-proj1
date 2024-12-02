#ifndef NULL
#include <stdio.h>
#endif /* ifndef NULL */

#include "PriorityQueue.c"

#ifndef DEBUG_FLAG
#define DEBUG_FLAG 0
#endif

typedef struct GraphMatrix {
  int vertices;
  int** weightMatrix;
  int** edgeMatrix;
} GraphMatrix;


GraphMatrix* create_graph(int vertexCount) {
  GraphMatrix* graph = (GraphMatrix*)malloc(sizeof(GraphMatrix));

  if (!graph) {
    printf("Could not initialize graph!\n");
    return NULL;
  }

  graph->vertices = vertexCount;

  int** weightMatrix = (int**)malloc(sizeof(int*)  * vertexCount);
  if (!weightMatrix) {
    printf("Could not initialize matrix!\n");
    return NULL;
  }

  for (int y = 0; y < vertexCount; y++) {
    int* row = (int*)malloc(sizeof(int) * vertexCount);
    if(!row) {
      printf("Could not initialize row!\n");
      return NULL;
    }

    for (int x = 0; x < vertexCount; x++) {
      row[x] = 0;
    }

    weightMatrix[y] = row;
  }
  graph->weightMatrix = weightMatrix;

  int** edgeMatrix = (int**)malloc(sizeof(int*) * vertexCount);
  if (!edgeMatrix) {
      printf("Could not initialize matrix!\n");
      return NULL;
  }

  for (int y = 0; y < vertexCount; y++) {
      int* row = (int*)malloc(sizeof(int) * vertexCount);
      if (!row) {
          printf("Could not initialize row!\n");
          return NULL;
      }

      for (int x = 0; x < vertexCount; x++) {
          row[x] = 0;
      }

      edgeMatrix[y] = row;
  }
  graph->edgeMatrix = edgeMatrix;

  return graph;
}

void addWeight(GraphMatrix* graph, int from, int to, int weight) {
  if (!graph) {
    printf("No graph provided!");
    return;
  }

  //graph->edgeMatrix[from][to] = 1;
  graph->weightMatrix[from][to] = weight;
  if (DEBUG_FLAG)
    printf("[DEBUG] Added edge from vertex %d to vertex %d with weight %d\n", from, to, weight);
}

void printGraph(GraphMatrix* graph) {
    if (!graph) {
        printf("No graph provided!");
        return;
    }

    printf("\n\n");

    int vertexCount = graph->vertices;

    printf("\nWeightMatrix:\n");
    // Vertex Names Row
    printf("      ");
    for (int idx = 0; idx < vertexCount; idx++) {
        printf("%4d ", idx);
    }
    printf("\n\n");

    for (int y = 0; y < vertexCount; y++) {
           // Vertex Names Column
        printf("%4d  ", y);

        for (int x = 0; x < vertexCount; x++) {
            printf("%4d ", graph->weightMatrix[y][x]);
        }

        printf("\n");
    }

    // Padding for readability
    printf("\n\n");


    printf("\nEdgeMatrix:\n");
    // Vertex Names Row
    printf("      ");
    for (int idx = 0; idx < vertexCount; idx++) {
        printf("%4d ", idx);
    }
    printf("\n\n");

    for (int y = 0; y < vertexCount; y++) {
        // Vertex Names Column
        printf("%4d  ", y);

        for (int x = 0; x < vertexCount; x++) {
            printf("%4d ", graph->edgeMatrix[y][x]);
        }

        printf("\n");
    }

    // Padding for readability
    printf("\n\n");
}

void printArr(int* arr, int size) {
    printf("Arr: ");
    for (int idx = 0; idx < size; idx++) {
        printf("%d ", arr[idx]);
    }
    printf("\n");
}

void createMSTPrim(GraphMatrix* graph, int startNode) {
    if (!graph) {
        printf("No graph provided!");
        return;
    }

    if (startNode >= graph->vertices || startNode < 0) {
        printf("Invalid vertex!");
        return;
    }

    int vertexCount = graph->vertices;
    int currVertex = startNode;
    int** matrix = graph->weightMatrix;

    int* visited = (int*)malloc(sizeof(int) * vertexCount);
    if (!visited) {
        printf("Could not initialize visited array!");
        return;
    }
    // Initialize Array
    for (int idx = 0; idx < vertexCount; idx++)
        visited[idx] = 0;
    visited[currVertex] = 1;

    PriorityQueue* q = create_queue();
    // Add weights to priority queue
    for (int idx = 0; idx < vertexCount; idx++) {
        if (idx == currVertex) continue;
        enqueue(q, matrix[currVertex][idx], currVertex, idx);
    }

    while (q->size > 0) {
        ListNode* edge = dequeue(q);

        if (visited[edge->to] == 1)
            continue;

        printf("[PRIM] Add Edge from vertex %d to vertex %d\n", edge->from, edge->to);
        graph->edgeMatrix[edge->from][edge->to] = 1;
        visited[edge->to] = 1;

        for (int idx = 0; idx < vertexCount; idx++) {
            if (idx == edge->to) continue;

            if (visited[idx] == 0)
                enqueue(q, matrix[edge->to][idx], edge->to, idx);
        }
    }
}

// Utility Method
void addRandomWeights(GraphMatrix* graph, int max) {
    if (!graph) {
        printf("No graph provided!\n");
        return;
    }
    
    int vertexCount = graph->vertices;
    for (int a = 0; a < vertexCount; a++) {
        for (int b = 0; b < vertexCount; b++) {
            if (a == b)
                continue;

            addWeight(graph, a, b, rand() % max);
        }
    }

    if (DEBUG_FLAG)
        printf("\n[DEBUG] Added random weights to graph\n\n");
}