//#include <time.h>
//#include <stdlib.h>
//
//#include "raylib.h"
//
//#include "resource_dir.h"
//
//const int screenWidth = 1280;
//const int screenHeight = 720;
//
//int runGame() {
//	srand(time(NULL));
//	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
//
//	// Create the window and OpenGL context
//	InitWindow(screenWidth, screenHeight, "DS Project");
//
//	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
//	SearchAndSetResourceDir("resources");
//
//	const int POINT_COUNT = 20;
//	const int POINT_RADIUS = 5;
//	Vector2* points = malloc(POINT_COUNT * sizeof(Vector2));
//
//	for (int idx = 0; idx < POINT_COUNT; idx++) {
//		points[idx] = (Vector2){ POINT_RADIUS + (rand() % (screenWidth - (2 * POINT_RADIUS))), POINT_RADIUS + (rand() % (screenHeight - (2 * POINT_RADIUS))) };
//	}
//
//	// game loop
//	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
//	{
//		BeginDrawing();
//
//		ClearBackground(BLACK);
//
//		// Draw points on screen
//		for (int idx = 0; idx < POINT_COUNT; idx++) {
//			DrawCircle(points[idx].x, points[idx].y, 5, RAYWHITE);
//		}
//
//		// Draw edges
//		for (int p1 = 0; p1 < POINT_COUNT; p1++) {
//			for (int p2 = 0; p2 < POINT_COUNT; p2++) {
//				if (p1 == p2)
//					continue;
//
//				DrawLine(points[p1].x, points[p1].y, points[p2].x, points[p2].y, RAYWHITE);
//			}
//		}
//
//		// end the frame and get ready for the next one  (display frame, poll input, etc...)
//		EndDrawing();
//	}
//
//	CloseWindow();
//}