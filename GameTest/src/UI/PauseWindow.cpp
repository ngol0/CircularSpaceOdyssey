#include "stdafx.h"
#include "PauseWindow.h"
#include "VitalsWindow.h"
#include "WindowManager.h"
#include "System/Scene.h"

PauseWindow::PauseWindow(){}

void PauseWindow::OnEnter()
{
	m_timer = 0.f;
}

void PauseWindow::HandleInput(float deltaTime)
{
	if (App::IsKeyPressed('P') && m_timer > 2.f)
	{
		WindowManager::GetInstance().SetWindow(WindowState::vitals);
		m_timer = 0.f;
	}
	if (App::IsKeyPressed('R'))
	{
		WindowManager::GetInstance().SetWindow(WindowState::vitals);
		WindowManager::GetInstance().Restart();
	}
	m_timer += deltaTime / 100.f;
}

void PauseWindow::Render()
{
	App::Print(500.f, 550.f, "PAUSED", 0.859, 0.91, 0.043, m_FONT);
	App::Print(300.f, 500.f, "Control list:", 0.98, 0.569, 0.263, m_FONT);
	App::Print(300.f, 450.f, "A or D to move", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 400.f, "LEFT CLICK to shoot", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 350.f, "R to restart", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 200.f, "Press P to continue", 0.467, 0.831, 0.961, m_FONT);
}