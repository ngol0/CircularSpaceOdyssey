#include "stdafx.h"
#include "TitleWindow.h"
#include "VitalsWindow.h"
#include "WindowManager.h"

TitleWindow::TitleWindow() {}

void TitleWindow::HandleInput(float deltaTime, WindowManager& manager)
{
	if (App::IsKeyPressed(VK_SPACE))
	{
		//change to vitals ui
		manager.SetWindow(WindowState::vitals);
	}
}

void TitleWindow::Render()
{
	App::Print(300.f, 550.f, "Welcome. Let's move through space", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 450.f, "WSAD to move", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 400, "LEFT CLICK to shoot or jump between planets", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 250, "Hit `SPACE` to start", 1.f, 1.f, 1.f, m_FONT);
}