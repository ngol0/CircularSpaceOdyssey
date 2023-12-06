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

	for (int i = 0; i < MAX_STAR_NUMBER; i++)
	{
		m_random_pos[i] = Utils::RandomPosition();
	}
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
		App::Print(300.f, 550.f, "Welcome. Let's move through space", 1.f, 1.f, 1.f, m_FONT);
		App::Print(300.f, 450.f, "WSAD to move", 1.f, 1.f, 1.f, m_FONT);
		App::Print(300.f, 400, "LEFT CLICK to shoot or jump between planets", 1.f, 1.f, 1.f, m_FONT);
		App::Print(300.f, 250, "Hit `SPACE` to start", 1.f, 1.f, 1.f, m_FONT);
		break;

	case SceneState::COMBAT:
		App::Print(50, 100, m_score_string.c_str(), 1.f, 1.f, 1.f, m_FONT);
		App::Print(50, 50, m_health_string.c_str(), 1.f, 1.f, 1.f, m_FONT);
		break;

	case SceneState::PAUSED:
		App::Print(500.f, 730.f, "PAUSED", 1.f, 1.f, 1.f, m_FONT);
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