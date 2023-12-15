#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>  
//------------------------------------------------------------------------
#include "System/Scene.h"
#include "UI/WindowManager.h"
#include "UI/TitleWindow.h"
#include "UI/PauseWindow.h"

Scene scene;
WindowManager window_manager;

void Init()
{
	/*AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);*/

	scene.Init();
	window_manager.Init(scene);
}

void Update(float deltaTime)
{
	window_manager.HandleInput(deltaTime);
	if (dynamic_cast<TitleWindow*>(window_manager.GetCurrentWindow())) return;
	if(dynamic_cast<PauseWindow*>(window_manager.GetCurrentWindow())) return;

	scene.Update(deltaTime);
}

void Render()
{
	window_manager.Render();

	if (dynamic_cast<TitleWindow*>(window_manager.GetCurrentWindow())) return;
	if (dynamic_cast<PauseWindow*>(window_manager.GetCurrentWindow())) return;
	scene.Render();
}

void Shutdown()
{
	scene.Shutdown();
}