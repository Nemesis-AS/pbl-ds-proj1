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
	Graph* graph;
	Vector2* points;
	int drawn;
} GameStateList;

int runGame() {
	srand(time(NULL));
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "DS Project");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	const int POINT_COUNT = 20;
	const int POINT_RADIUS = 5;
	Vector2* points = malloc(POINT_COUNT * sizeof(Vector2));

	for (int idx = 0; idx < POINT_COUNT; idx++) {
		points[idx] = (Vector2){ POINT_RADIUS + (rand() % (screenWidth - (2 * POINT_RADIUS))), POINT_RADIUS + (rand() % (screenHeight - (2 * POINT_RADIUS))) };
	}

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		BeginDrawing();

		ClearBackground(BLACK);

		// Draw points on screen
		for (int idx = 0; idx < POINT_COUNT; idx++) {
			DrawCircle(points[idx].x, points[idx].y, 5, RAYWHITE);
		}

		// Draw edges
		for (int p1 = 0; p1 < POINT_COUNT; p1++) {
			for (int p2 = 0; p2 < POINT_COUNT; p2++) {
				if (p1 == p2)
					continue;

				DrawLine(points[p1].x, points[p1].y, points[p2].x, points[p2].y, RAYWHITE);
			}
		}

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	CloseWindow();
}

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

	Graph* graph = init_graph();
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