#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>  
//------------------------------------------------------------------------
#include "System/Scene.h"
#include "System/AudioManager.h"
//------------------------------------------------------------------------
#include "UI/WindowManager.h"
#include "UI/TitleWindow.h"
#include "UI/PauseWindow.h"
#include "UI/LevelWindow.h"
#include "UI/VictoryWindow.h"

Scene scene;
auto& window = WindowManager::GetInstance();
auto& audio = AudioManager::GetInstance();

/* Creates scene to manages the actual game flow
UI is managed through window_manager class */
void Init()
{
	/*AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);*/

	audio.Init();
	scene.Init();
	window.Init(scene);
}

void Update(float deltaTime)
{
	//handle input to moves between different ui windows 
	window.HandleInput(deltaTime);

	//if current window are those below, don't update game flow
	if (dynamic_cast<TitleWindow*>(window.GetCurrentWindow())) return;
	if (dynamic_cast<PauseWindow*>(window.GetCurrentWindow())) return;
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
	//cleaning up
	scene.Shutdown();
}