#include "stdafx.h"
#include "LoseWindow.h"
#include "VitalsWindow.h"
#include "WindowManager.h"

LoseWindow::LoseWindow() {}

void LoseWindow::HandleInput(float deltaTime)
{
	if (App::IsKeyPressed('R'))
	{
		WindowManager::GetInstance().SetWindow(WindowState::vitals);
		WindowManager::GetInstance().Restart();
	}
}

void LoseWindow::Render()
{
	App::Print(100.f, 650.f, "Oopss..You Lose :(", 1.f, 1.f, 1.f, m_FONT);
	App::Print(100.f, 600.f, "R to restart", 1.f, 1.f, 1.f, m_FONT);
}