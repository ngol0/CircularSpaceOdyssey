#include "stdafx.h"
#include "TitleWindow.h"
#include "VitalsWindow.h"
#include "WindowManager.h"

TitleWindow::TitleWindow() {}

void TitleWindow::HandleInput(float deltaTime, WindowManager& manager)
{
	if (App::IsKeyPressed(VK_SPACE))
	{
		manager.SetWindow(WindowState::vitals);
	}
}

void TitleWindow::Render()
{
	App::Print(300.f, 550.f, "Welcome. Let's move through space", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 450.f, "A or D to move", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 400, "LEFT CLICK to shoot or jump between planets", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 350, "R to restart", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 300, "P to pause", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 200, "`SPACE` to start", 1.f, 1.f, 1.f, m_FONT);
}