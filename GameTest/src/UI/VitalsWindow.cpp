#include "stdafx.h"
#include "VitalsWindow.h"
#include "PauseWindow.h"
#include "System/Scene.h"
#include "WindowManager.h"
#include "Global/Utils.h"
#include "Global/GameGlobal.h"
#include "System/AudioManager.h"

VitalsWindow::VitalsWindow() {}

void VitalsWindow::OnEnter()
{
	m_timer = 0.f;
	AudioManager::GetInstance().PlayMusic(MusicID::IN_GAME, true);
}

void VitalsWindow::HandleInput(float deltaTime)
{
	if (App::IsKeyPressed('P') && m_timer > 2.f)
	{
		WindowManager::GetInstance().SetWindow(WindowState::pause);
		m_timer = 0.f;
	}
	if (App::IsKeyPressed('R'))
	{
		WindowManager::GetInstance().Restart();
	}

	m_timer += deltaTime / 100.f;

	UpdateHealthText(WindowManager::GetInstance().GetHealth());
	if (WindowManager::GetInstance().GetScore() > GameGlobal::MAX_SCORE) return;
	UpdateScoreText(WindowManager::GetInstance().GetScore());
}

void VitalsWindow::Render()
{
	App::Print(120, 35, m_score_string.c_str(), 1.f, 1.f, 1.f, m_FONT);
	App::Print(50, 730, m_health_string.c_str(), 1.f, 1.f, 1.f, m_FONT);

	Utils::DrawRectangle(Vector2{220.f, 30.f}, 1.f, 1.f, 1.f, Vector2{600.f, 17.f});
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