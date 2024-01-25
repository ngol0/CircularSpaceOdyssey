#include "stdafx.h"
#include "VitalsWindow.h"
#include "PauseWindow.h"
#include "WindowManager.h"
//
#include "Global/Utils.h"
#include "System/AudioManager.h"
#include "System/Level/LevelManager.h"

VitalsWindow::VitalsWindow() {}

void VitalsWindow::OnEnter()
{
	m_timer = 0.f;
	AudioManager::GetInstance().PlayMusic(MusicID::IN_GAME, true);

	m_current_level = LevelManager::GetInstance().GetCurrentLevel();
	m_level_string = "Level: " + std::to_string(m_current_level);
}

void VitalsWindow::HandleInput(float deltaTime)
{
	if (App::IsKeyPressed('P') && m_timer > 2.f)
	{
		WindowManager::GetInstance().SetWindow(WindowState::pause);
		m_timer = 0.f;
	}
	if (App::IsKeyPressed('R') && m_timer > 2.f)
	{
		WindowManager::GetInstance().Restart();
		m_timer = 0.f;
	}

	m_timer += deltaTime / 100.f;

	UpdateHealthText(WindowManager::GetInstance().GetHealth());
	UpdateScoreText(WindowManager::GetInstance().GetScore());
}

void VitalsWindow::Render()
{
	//score amount
	App::Print(170.f, 35.f, m_score_string.c_str(), 1.f, 1.f, 1.f, m_FONT);

	//health amount
	App::Print(50.f, 730.f, m_health_string.c_str(), 1.f, 1.f, 1.f, m_FONT);

	//resources bar
	Utils::DrawRectangle(Vector2{ 270.f, 30.f }, 1.f, 1.f, 1.f, Vector2{ 510.f, 17.f });

	//health bar
	Utils::DrawRectangle(Vector2{ 120.f, 725.f }, 1.f, 1.f, 1.f, Vector2{ 455.f, 17.f });

	//level text
	App::Print(880.f, 730.f, m_level_string.c_str(), 1.f, 1.f, 1.f, m_FONT);
}

void VitalsWindow::UpdateScoreText(int score)
{
	m_score_string = "Resources: " + std::string(score, '|');
}

void VitalsWindow::UpdateHealthText(int health)
{
	m_health_string = "Health: " + std::string(health, '|');
}

void VitalsWindow::OnExit()
{
	AudioManager::GetInstance().StopMusic(MusicID::IN_GAME);
}