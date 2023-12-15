#include "stdafx.h"
#include "VitalsWindow.h"
#include "TitleWindow.h"
#include "System/Scene.h"
#include "WindowManager.h"

VitalsWindow::VitalsWindow() : m_scene(nullptr) {}

void VitalsWindow::Init(Scene& scene)
{
	m_score_string = scene.GetScore();
	m_health_string = scene.GetPlayerHealth();

	m_scene = &scene;
}

void VitalsWindow::HandleInput(float deltaTime, WindowManager& manager)
{
	UpdateScoreText(m_scene->GetScore());
	UpdateHealthText(m_scene->GetPlayerHealth());

	if (App::IsKeyPressed('L'))
	{
		//change to vitals ui
		manager.SetWindow(WindowState::title);
	}
}

void VitalsWindow::Render()
{
	App::Print(50, 100, m_score_string.c_str(), 1.f, 1.f, 1.f, m_FONT);
	App::Print(50, 50, m_health_string.c_str(), 1.f, 1.f, 1.f, m_FONT);
}

void VitalsWindow::UpdateScoreText(int score)
{
	m_score_string = "Score: " + std::to_string(score);
}

void VitalsWindow::UpdateHealthText(int health)
{
	m_health_string = "Health: " + std::to_string(health);
}