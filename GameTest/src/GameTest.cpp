#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>  
//------------------------------------------------------------------------
#include "System/Scene.h"
#include "UI/UI.h"
#include "UI/WindowManager.h"
#include "UI/Window.h"

Scene scene;
UI ui;
WindowManager window_manager;

void Init()
{
	/*AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);*/

	scene.Init();
	window_manager.Init(scene);
	//ui.Init(scene);
}

void Update(float deltaTime)
{
	//scene.HandleInput(deltaTime);
	window_manager.HandleInput(deltaTime);

	//if (scene.GetState() == SceneState::PAUSED || scene.GetState() == SceneState::START) return;
	//if (*window_manager.GetCurrentWindow() == WindowState::title) return;

	//scene.Update(deltaTime);
	//ui.Update(deltaTime);
}

void Render()
{
	//ui.Render();
	window_manager.Render();

	if (scene.GetState() == SceneState::START) return;
	scene.Render();
}

void Shutdown()
{
	scene.Shutdown();
}