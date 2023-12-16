#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>  
//------------------------------------------------------------------------
#include "System/Scene.h"
#include "UI/WindowManager.h"
#include "UI/TitleWindow.h"
#include "UI/PauseWindow.h"

Scene scene;

void Init()
{
	
	/*AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);*/

	scene.Init();
	WindowManager::GetInstance().Init(scene);
}

void Update(float deltaTime)
{
	WindowManager::GetInstance().HandleInput(deltaTime);

	if (dynamic_cast<TitleWindow*>(WindowManager::GetInstance().GetCurrentWindow())) return;
	if(dynamic_cast<PauseWindow*>(WindowManager::GetInstance().GetCurrentWindow())) return;

	scene.Update(deltaTime);
}

void Render()
{
	WindowManager::GetInstance().Render();

	if (dynamic_cast<TitleWindow*>(WindowManager::GetInstance().GetCurrentWindow())) return;
	if (dynamic_cast<PauseWindow*>(WindowManager::GetInstance().GetCurrentWindow())) return;

	scene.Render();
}

void Shutdown()
{
	scene.Shutdown();
}