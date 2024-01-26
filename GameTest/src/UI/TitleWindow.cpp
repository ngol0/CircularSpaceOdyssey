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
	App::Print(300.f, 600.f, "Welcome to Circular Space Odyssey.", 0.859f, 0.91f, 0.043f, m_FONT);
	App::Print(300.f, 550.f, "Kill all enemies to collect enough resources & move to next level.", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 450.f, "A or D to move", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 400.f, "LEFT CLICK to shoot", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 350.f, "R to restart", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 300.f, "P to pause", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 200.f, "Press SPACE to start", 0.467f, 0.831f, 0.961f, m_FONT);
}