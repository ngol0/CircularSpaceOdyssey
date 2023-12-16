#include "stdafx.h"
#include "WindowManager.h"
#include "TitleWindow.h"
#include "LoseWindow.h"

#include "System/Utils.h"

WindowManager::WindowManager() : m_current_window(nullptr), m_scene(nullptr) {}

void WindowManager::Init(Scene& scene)
{
	m_scene = &scene;

	SetWindow(WindowState::title);

	for (int i = 0; i < MAX_STAR_NUMBER; i++)
	{
		m_random_pos[i] = Utils::RandomPosition();
	}
}

void WindowManager::SetWindow(Window& window)
{
	if (m_current_window != nullptr)
	{
		m_current_window->OnExit();
	}
	m_current_window = &window; 
	m_current_window->OnEnter();
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

void WindowManager::RenderBackground()
{
	for (const auto& pos : m_random_pos)
	{
		Utils::DrawDot(pos, Utils::RandomFloat(0, 3.f), Utils::RandomFloat(0, 3.f), Utils::RandomFloat(0, 3.f));
	}
}

void WindowManager::Restart()
{
	m_scene->Restart();
}

WindowManager& WindowManager::GetInstance()
{
	static WindowManager manager;
	return manager;
}