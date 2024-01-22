#include "stdafx.h"
#include "WindowManager.h"
#include "TitleWindow.h"
#include "LoseWindow.h"

#include "Global/Utils.h"

WindowManager::WindowManager() : m_current_window(nullptr), m_scene(nullptr) {}

void WindowManager::Init(Scene& scene)
{
	m_scene = &scene;

	// set the first window
	SetWindow(WindowState::title);

	// create random positions on screen for twinkling star on background
	for (int i = 0; i < MAX_STAR_NUMBER; i++)
	{
		m_random_pos[i] = Utils::RandomPosition();
	}
}

void WindowManager::SetWindow(Window& window)
{
	//do something before changing to the new one
	if (m_current_window != nullptr)
	{
		m_current_window->OnExit();
	}
	m_current_window = &window;  //pointing to the new one
	m_current_window->OnEnter(); //do something after switching
}

void WindowManager::HandleInput(float deltaTime)
{
	m_current_window->HandleInput(deltaTime);
}

void WindowManager::Render()
{
	RenderBackground();
	m_current_window->Render();
}

// twinkling star background
void WindowManager::RenderBackground()
{
	for (const auto& pos : m_random_pos)
	{
		Utils::DrawDot
		(
			pos, 
			Utils::RandomFloat(1.f, 10.f) / 10.f, 
			Utils::RandomFloat(1.f, 10.f) / 10.f, 
			Utils::RandomFloat(1.f, 10.f) / 10.f
		);
	}
}

// called when R is pressed
void WindowManager::Restart()
{
	m_scene->Restart();
}

WindowManager& WindowManager::GetInstance()
{
	static WindowManager manager;
	return manager;
}