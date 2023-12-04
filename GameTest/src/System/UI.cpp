#include "stdafx.h"
#include "UI.h"
#include "Scene.h"
#include "Utils.h"

UI::UI() : m_scene(nullptr) {}

void UI::Init(Scene& scene)
{
	m_scene = &scene;

	UpdateScoreText(m_scene->GetScore());
	UpdateHealthText(m_scene->GetPlayerHealth());

	Utils::GenerateRandomPositions(200, m_random_pos);
}

void UI::Update(float deltaTime)
{
	UpdateScoreText(m_scene->GetScore());
	UpdateHealthText(m_scene->GetPlayerHealth());
}

void UI::RenderBackground()
{
	for (const auto& pos : m_random_pos)
	{
		Utils::DrawDot(pos, Utils::RandomFloat(0, 2.f), Utils::RandomFloat(0, 2.f), Utils::RandomFloat(0, 2.f));
	}
}

void UI::Render()
{
	RenderBackground();

	switch (m_scene->GetState())
	{
	case SceneState::START:
		App::Print(500.f, 500.f, "START");
		App::Print(450.f, 450.f, "Hit Space to start");
		break;

	case SceneState::COMBAT:
		App::Print(50, 100, m_score_string.c_str());
		App::Print(50, 50, m_health_string.c_str());
		break;

	case SceneState::PAUSED:
		App::Print(500.f, 730.f, "PAUSED");
		break;

	case SceneState::GAME_OVER:
		break;
	}
}

void UI::UpdateScoreText(int score)
{
	m_score_string = "Score: " + std::to_string(score);
}

void UI::UpdateHealthText(int health)
{
	m_health_string = "Health: " + std::to_string(health);
}