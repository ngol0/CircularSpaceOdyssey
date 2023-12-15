#include "stdafx.h"
#include "VitalsWindow.h"
#include "PauseWindow.h"
#include "System/Scene.h"
#include "WindowManager.h"
#include "System/Utils.h"

VitalsWindow::VitalsWindow() : m_scene(nullptr) {}

void VitalsWindow::OnEnter()
{
	m_timer = 0.f;
}

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

	if (App::IsKeyPressed('P') && m_timer > 2.f)
	{
		manager.SetWindow(WindowState::pause);
		m_timer = 0.f;
	}
	if (App::IsKeyPressed('R'))
	{
		m_scene->Restart();
	}

	m_timer += deltaTime / 100.f;
}

void VitalsWindow::Render()
{
	App::Print(120, 35, m_score_string.c_str(), 1.f, 1.f, 1.f, m_FONT);
	App::Print(50, 700, m_health_string.c_str(), 1.f, 1.f, 1.f, m_FONT);

	Utils::DrawRectangle(Vector2{220.f, 30.f}, 1.f, 1.f, 1.f, Vector2{600.f, 17.f});
}

void VitalsWindow::UpdateScoreText(int score)
{
	m_score_string = "Resources: " + std::string(score, '|');
}

void VitalsWindow::UpdateHealthText(int health)
{
	m_health_string = "Health: " + std::to_string(health);
}