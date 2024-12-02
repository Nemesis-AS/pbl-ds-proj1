
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_FLAG 0

#include "GraphMatrix.c"
#include "Graph.c"
#include "Game.c"


int main ()
{
	srand(time(NULL));

	// Test Case
	int m[4][4] = {
		{ 0, 2, 4, 6 },
		{ 2, 0, 3, 5 },
		{ 4, 3, 0, 7 },
		{ 6, 5, 7, 0 }
	};

	//GraphMatrix* graph = create_graph(4);
	////printGraph(graph);
	////addWeight();
	//
	//for (int x = 0; x < 4; x++) {
	//	for (int y = 0; y < 4; y++) {
	//		addWeight(graph, x, y, m[x][y]);
	//	}
	//}
	//printGraph(graph);

	//addRandomWeights(graph, 250);
	//createMSTPrim(graph, 0);
	//printGraph(graph);

	//Graph* graph = init_graph();
	////randomizeGraph(graph, 4, 250);
	//for (int idx = 0; idx < 4; idx++)
	//	addVertex(graph, idx);
	//for (int x = 0; x < 4; x++) {
	//	for (int y = 0; y < 4; y++) {
	//		if (x == y) continue;

	//		addListWeight(graph, x, y, m[x][y]);
	//	}
	//}
	//createMSTKruskal(graph);
	//printListGraph(graph);


	const int POINT_RADIUS = 5;
	const int POINT_COUNT = 5;
	//GameStateMatrix* state = initializeGameMatrix(POINT_COUNT, POINT_RADIUS);
	GameStateList* state = initializeGameList(POINT_COUNT, POINT_RADIUS);

	// Game Setup
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "DS Project");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// Input Polling
		if (IsKeyDown(KEY_E) && state->drawn == 0) {
			 //Solve graph
			//createMSTPrim(state->graph, 0);
			createMSTKruskal(state->graph);
			state->drawn = 1;
		}

		// Reset Graph
		if (IsKeyPressed(KEY_R)) {
			//state = initializeGameMatrix(POINT_COUNT, POINT_RADIUS);
			state = initializeGameList(POINT_COUNT, POINT_RADIUS);
		}

		if (IsKeyPressed(KEY_P)) {
			printListGraph(state->graph);
			//printGraph(state->graph);
		}


		BeginDrawing();

		ClearBackground(BLACK);

		// Draw points on screen
		for (int idx = 0; idx < POINT_COUNT; idx++) {
			DrawCircle(state->points[idx].x, state->points[idx].y, 5, RAYWHITE);
		}

		// Draw edges
		/*for (int p1 = 0; p1 < POINT_COUNT; p1++) {
			for (int p2 = 0; p2 < POINT_COUNT; p2++) {
				if (p1 == p2 || state->graph->edgeMatrix[p1][p2] == 0)
					continue;

				DrawLine(state->points[p1].x, state->points[p1].y, state->points[p2].x, state->points[p2].y, RAYWHITE);
			}
		}*/

		// Draw edges from graph
		GraphVertex* currVertex = state->graph->vertices;
		while (currVertex != NULL) {
			GraphEdge* currEdge = currVertex->edges;

			while (currEdge != NULL) {
				DrawLine(state->points[currVertex->value].x, state->points[currVertex->value].y, state->points[currEdge->vertex].x, state->points[currEdge->vertex].y, RAYWHITE);

				currEdge = currEdge->nextEdge;
			}
			currVertex = currVertex->nextVertex;
		}

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	CloseWindow();

	return 0;
}