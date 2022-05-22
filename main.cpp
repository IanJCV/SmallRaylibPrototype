#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <raylib.h>
#include <raygui.h>
#include <raymath.h>
#include <physac.h>
#include <memory>

#include "scene.h"
#include "gameutils.h"
#include "gamecore.h"
#include "shrinkingspace.h"

void ReInitScene(Scene* testScene)
{
	if (testScene->loaded)
		testScene->unload();

	testScene->load();
}

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1200;
	int screenHeight = 800;

	Rectangle pauseRect = Rectangle();
	pauseRect.x = screenWidth - 60;
	pauseRect.y = 20;
	pauseRect.width = 40;
	pauseRect.height = 40;

	Rectangle rect = Rectangle();
	rect.x = screenWidth - 60;
	rect.y = 80;
	rect.width = 40;
	rect.height = 40;

	InitWindow(screenWidth, screenHeight, "raylib test");
	SetExitKey(KEY_F10);

	SetTargetFPS(120);

	//--------------------------------------------------------------------------------------
	
	Scene testScene = Scene("Test Scene 1");
	ReInitScene(&testScene);

	std::string pauseButton = "UNPAUSE";
	bool pause = true;

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update loop

		if (!pause)
		{
			testScene.update();
		}

		// Drawing loop

		BeginDrawing();

		ClearBackground(RAYWHITE);

		testScene.draw();

		if (GuiButton(pauseRect, "RESET"))
		{
			ReInitScene(&testScene);
		}

		if (GuiButton(rect, pauseButton.c_str()))
		{
			pause = !pause;
			pauseButton = pause ? "UNPAUSE" : "PAUSE";
		}

		if (IsKeyDown(KEY_D) && testScene.getObjectCount() > 0)
		{
			testScene.getObject(GetRandomValue(0, testScene.getObjectCount() - 1))->active = false;
		}

		if (IsKeyDown(KEY_A))
		{
			std::shared_ptr<GameObject> go(new GameObject());
			int a = testScene.addObject(go);
			testScene.getObject(a)->setPosition(Vector3Scale(insideUnitSphere(), 3.0f));
		}

		DrawFPS(0, 0);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	testScene.unload();   // Unload the test scene. Also gets rid of the physics system.

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}