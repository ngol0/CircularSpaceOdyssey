#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>  
//------------------------------------------------------------------------
#include "System/Scene.h"
#include "System/UI.h"

Scene scene;
UI ui;

void Init()
{
	/*AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);*/

	scene.Init();
	ui.Init(scene);
}

void Update(float deltaTime)
{
	scene.HandleInput(deltaTime);

	if (scene.GetState() != SceneState::PAUSED)
	{
		scene.Update(deltaTime);
		ui.Update(deltaTime);
	}
}

void Render()
{
	ui.Render();

	if (scene.GetState() == SceneState::START) return;
	scene.Render();
}

void Shutdown()
{
	scene.Shutdown();
}