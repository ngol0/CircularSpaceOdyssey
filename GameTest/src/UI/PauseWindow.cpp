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

void PauseWindow::HandleInput(float deltaTime, WindowManager& manager)
{
	if (App::IsKeyPressed('P') && m_timer > 2.f)
	{
		manager.SetWindow(WindowState::vitals);
		m_timer = 0.f;
	}
	if (App::IsKeyPressed('R'))
	{
		manager.SetWindow(WindowState::vitals);
		manager.Restart();
	}
	m_timer += deltaTime / 100.f;
}

void PauseWindow::Render()
{
	App::Print(300.f, 550.f, "Paused", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 450.f, "A or D to move", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 400, "LEFT CLICK to shoot or jump between planets", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 350, "R to restart", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 300, "P to continue", 1.f, 1.f, 1.f, m_FONT);
}