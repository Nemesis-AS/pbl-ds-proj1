#include <math.h>
#include <time.h>
#include "raylib.h"

#include "resource_dir.h"

const int screenWidth = 1280;
const int screenHeight = 720;

typedef struct GameStateMatrix {
	GraphMatrix* graph;
	Vector2* points;
	int drawn;
} GameStateMatrix;

typedef struct GameStateList {
	GraphList* graph;
	Vector2* points;
	int drawn;
} GameStateList;

float edistance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void createPrimGraph(int vertexCount, Vector2* points) {
	GraphMatrix* graph = create_graph(vertexCount);

	for (int a = 0; a < vertexCount; a++) {
		for (int b = 0; b < vertexCount; b++) {
			if (a >= b)
				continue;

			int dist = (int)edistance(points[a].x, points[a].y, points[b].x, points[b].y);
			graph->weightMatrix[a][b] = dist;
			graph->weightMatrix[b][a] = dist;
		}
	}
}

GameStateMatrix* initializeGameMatrix(int pointCount, int POINT_RADIUS) {
	GameStateMatrix* state = (GameStateMatrix*)malloc(sizeof(GameStateMatrix));
	state->drawn = 0;

	Vector2* points = malloc(pointCount * sizeof(Vector2));
	if (!points) {
		printf("Could not iitialize points!\n");
		return NULL;
	}

	for (int idx = 0; idx < pointCount; idx++) {
		points[idx] = (Vector2){ POINT_RADIUS + (rand() % (screenWidth - (2 * POINT_RADIUS))), POINT_RADIUS + (rand() % (screenHeight - (2 * POINT_RADIUS))) };
	}
	state->points = points;


	GraphMatrix* graph = create_graph(pointCount);

	for (int a = 0; a < pointCount; a++) {
		for (int b = 0; b < pointCount; b++) {
			if (a >= b)
				continue;

			int dist = (int)edistance(points[a].x, points[a].y, points[b].x, points[b].y);
			graph->weightMatrix[a][b] = dist;
			graph->weightMatrix[b][a] = dist;
		}
	}
	state->graph = graph;

	return state;
}

GameStateList* initializeGameList(int pointCount, int POINT_RADIUS) {
	GameStateList* state = (GameStateList*)malloc(sizeof(GameStateList));
	state->drawn = 0;

	Vector2* points = malloc(pointCount * sizeof(Vector2));
	if (!points) {
		printf("Could not iitialize points!\n");
		return NULL;
	}

	for (int idx = 0; idx < pointCount; idx++) {
		points[idx] = (Vector2){ POINT_RADIUS + (rand() % (screenWidth - (2 * POINT_RADIUS))), POINT_RADIUS + (rand() % (screenHeight - (2 * POINT_RADIUS))) };
	}
	state->points = points;

	GraphList* graph = init_graph();
	for (int idx = 0; idx < pointCount; idx++)
		addVertex(graph, idx);

	for (int a = 0; a < pointCount; a++) {
		for (int b = 0; b < pointCount; b++) {
			if (a == b)
				continue;

			int dist = (int)edistance(points[a].x, points[a].y, points[b].x, points[b].y);
			addListWeight(graph, a, b, dist);
		}
	}
	state->graph = graph;

	return state;
}

void waitFor(unsigned int secs) {
	unsigned int retTime = time(0) + secs;
	while (time(0) < retTime);
}