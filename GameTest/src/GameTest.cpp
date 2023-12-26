#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>  
//------------------------------------------------------------------------
#include "System/Scene.h"
//------------------------------------------------------------------------
#include "UI/WindowManager.h"
#include "UI/TitleWindow.h"
#include "UI/PauseWindow.h"
#include "UI/LevelWindow.h"
#include "UI/VictoryWindow.h"

Scene scene;
auto& window = WindowManager::GetInstance();

void Init()
{
	/*AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);*/

	scene.Init();
	window.Init(scene);
}

void Update(float deltaTime)
{
	window.HandleInput(deltaTime);

	if (dynamic_cast<TitleWindow*>(window.GetCurrentWindow())) return;
	if(dynamic_cast<PauseWindow*>(window.GetCurrentWindow())) return;
	if (dynamic_cast<LevelWindow*>(window.GetCurrentWindow())) return;
	if (dynamic_cast<VictoryWindow*>(window.GetCurrentWindow())) return;

	scene.Update(deltaTime);
}

void Render()
{
	window.Render();

	if (dynamic_cast<TitleWindow*>(window.GetCurrentWindow())) return;
	if (dynamic_cast<PauseWindow*>(window.GetCurrentWindow())) return;
	if (dynamic_cast<LevelWindow*>(window.GetCurrentWindow())) return;
	if (dynamic_cast<VictoryWindow*>(window.GetCurrentWindow())) return;

	scene.Render();
}

void Shutdown()
{
	scene.Shutdown();
}