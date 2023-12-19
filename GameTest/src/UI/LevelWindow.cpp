#include "stdafx.h"
#include "LevelWindow.h"
#include "WindowManager.h"
#include "VitalsWindow.h"

LevelWindow::LevelWindow() {}

void LevelWindow::HandleInput(float deltaTime)
{
	if (App::IsKeyPressed('1'))
	{
		//load level 1

		WindowManager::GetInstance().SetWindow(WindowState::vitals);
	}
}

void LevelWindow::Render()
{
	App::Print(300.f, 550.f, "Select the levels:", 0.859, 0.91, 0.043, m_FONT);
	App::Print(300.f, 450.f, "Press 1 for first level", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 400, "Press 2 for second level", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 350, "Press 3 for third level", 1.f, 1.f, 1.f, m_FONT);
}