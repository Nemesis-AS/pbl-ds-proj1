
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_FLAG 0

#include "GraphMatrix.c"
#include "Graph.c"
#include "Game.c"


typedef enum MST_MODE {
	PRIMS = 0,
	KRUSKALS = 1
} MST_MODE;

int main ()
{
	srand(time(NULL));

	MST_MODE mst_mode = PRIMS;

	const int POINT_RADIUS = 10;
	const int POINT_COUNT = 20;
	GameStateMatrix* state1 = initializeGameMatrix(POINT_COUNT, POINT_RADIUS);
	GameStateList* state2 = initializeGameList(POINT_COUNT, POINT_RADIUS);

	// Game Setup
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "DS Project");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		if (mst_mode == PRIMS) {
			// Input Polling
			if (IsKeyDown(KEY_E) && state1->drawn == 0) {
				//Solve graph
				createMSTPrim(state1->graph, 0);
				state1->drawn = 1;
			}

			// Reset Graph
			if (IsKeyPressed(KEY_R)) {
				state1 = initializeGameMatrix(POINT_COUNT, POINT_RADIUS);
			}

			if (IsKeyPressed(KEY_P)) {
				printGraph(state1->graph);
			}

			if (IsKeyPressed(KEY_M)) {
				mst_mode = KRUSKALS;
			}

			BeginDrawing();

			ClearBackground(BLACK);

			// Draw Text
			DrawText("Prim's Algorithm", 500, 64, 32, RAYWHITE);

			// Draw points on screen
			for (int idx = 0; idx < POINT_COUNT; idx++) {
				DrawCircle(state1->points[idx].x, state1->points[idx].y, 5, RAYWHITE);
			}

			// Draw edges
			for (int p1 = 0; p1 < POINT_COUNT; p1++) {
				for (int p2 = 0; p2 < POINT_COUNT; p2++) {
					if (p1 == p2 || state1->graph->edgeMatrix[p1][p2] == 0)
						continue;

					DrawLine(state1->points[p1].x, state1->points[p1].y, state1->points[p2].x, state1->points[p2].y, RAYWHITE);
				}
			}
		}
		else if (mst_mode == KRUSKALS) {
			// Input Polling
			if (IsKeyDown(KEY_E) && state2->drawn == 0) {
				//Solve graph
				createMSTKruskal(state2->graph);
				state2->drawn = 1;
			}

			// Reset Graph
			if (IsKeyPressed(KEY_R)) {
				state2 = initializeGameList(POINT_COUNT, POINT_RADIUS);
			}

			if (IsKeyPressed(KEY_P)) {
				printListGraph(state2->graph);
			}

			if (IsKeyPressed(KEY_M)) {
				mst_mode = PRIMS;
			}

			BeginDrawing();

			ClearBackground(BLACK);

			// Draw Text
			DrawText("Kruskal's Algorithm", 500, 64, 32, RAYWHITE);

			// Draw points on screen
			for (int idx = 0; idx < POINT_COUNT; idx++) {
				DrawCircle(state2->points[idx].x, state2->points[idx].y, 5, RAYWHITE);
			}

			// Draw edges from graph
			GraphVertex* currVertex = state2->graph->vertices;
			while (currVertex != NULL) {
				GraphEdge* currEdge = currVertex->edges;

				while (currEdge != NULL) {
					DrawLine(state2->points[currVertex->value].x, state2->points[currVertex->value].y, state2->points[currEdge->vertex].x, state2->points[currEdge->vertex].y, RAYWHITE);

					currEdge = currEdge->nextEdge;
				}
				currVertex = currVertex->nextVertex;
			}
		}
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	CloseWindow();

	return 0;
}