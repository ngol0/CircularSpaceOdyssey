#include "stdafx.h"
#include "UI.h"
#include "Scene.h"

UI::UI() : m_scene(nullptr), m_collision_manager(nullptr) {}

void UI::Init(Scene& scene)
{
	m_scene = &scene;
}

void UI::Update(float deltaTime)
{
	int score = m_scene->GetScore();
	m_score_string = "Score: " + std::to_string(score);

	int health = m_scene->GetPlayerHealth();
	m_health_string = "Health: " + std::to_string(health);
}

void UI::Render()
{
	App::Print(50, 100, m_score_string.c_str());
	App::Print(50, 50, m_health_string.c_str());
}