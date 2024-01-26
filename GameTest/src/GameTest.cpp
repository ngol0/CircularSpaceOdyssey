#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>  
//------------------------------------------------------------------------
#include "System/Scene.h"
#include "System/AudioManager.h"
#include "UI/WindowManager.h"
#include "UI/Window.h"

Scene scene;
auto& window = WindowManager::GetInstance();
auto& audio = AudioManager::GetInstance();

/* Creates scene to manages the actual game flow
* Scene uses collision manager and level manager as services
* UI is managed through window manager class
* Auido is managed through audio manager */
void Init()
{
	audio.Init();
	scene.Init();
	window.Init(scene);
}

void Update(float deltaTime)
{
	//handle input to moves between different ui windows 
	window.HandleInput(deltaTime);

	//if current window is not the ingame one, don't update game flow
	if (!window.GetCurrentWindow()->IsInGame()) return;
	scene.Update(deltaTime); //update game flow
}

void Render()
{
	//render background and current window
	window.Render();
	
	//if current window is not the ingame one -> dont render scene
	if (!window.GetCurrentWindow()->IsInGame()) return;
	scene.Render(); //render game objects
}

void Shutdown()
{
	//cleaning up
	scene.Shutdown();
}