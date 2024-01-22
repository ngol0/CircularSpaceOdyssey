#include "stdafx.h"
#include "TitleWindow.h"
#include "LevelWindow.h"
#include "WindowManager.h"
//
#include "System/AudioManager.h"

TitleWindow::TitleWindow() {}

void TitleWindow::HandleInput(float deltaTime)
{
	if (App::IsKeyPressed(VK_SPACE))
	{
		AudioManager::GetInstance().PlaySoundEffect(SoundID::BUTTON, false);
		WindowManager::GetInstance().SetWindow(WindowState::level);
	}
}

void TitleWindow::Render()
{
	App::Print(300.f, 600.f, "Welcome to Circular Space Odyssey.", 0.859, 0.91, 0.043, m_FONT);
	App::Print(300.f, 550.f, "Kill the enemies to collect resources & move to a new planet.", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 450.f, "A or D to move", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 400, "LEFT CLICK to shoot", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 350, "R to restart", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 300, "P to pause", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 200, "Press SPACE to start", 0.467, 0.831, 0.961, m_FONT);
}