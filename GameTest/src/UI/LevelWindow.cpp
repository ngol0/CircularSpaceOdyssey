#include "stdafx.h"
#include "LevelWindow.h"
#include "WindowManager.h"
#include "VitalsWindow.h"
#include "System/Level/LevelManager.h"
#include "System/AudioManager.h"

auto& window_mg = WindowManager::GetInstance();
auto& level_mg = LevelManager::GetInstance();

LevelWindow::LevelWindow() {}

void LevelWindow::HandleInput(float deltaTime)
{
	if (App::IsKeyPressed('1'))
	{
		//load level 1
		level_mg.LoadFile(".\\Data\\Level1.txt");
		level_mg.Init(*window_mg.GetScene());
		level_mg.SetLevel(1);

		window_mg.SetWindow(WindowState::vitals);
		AudioManager::GetInstance().PlaySoundEffect(SoundID::BUTTON, false);
	}
	else if (App::IsKeyPressed('2'))
	{
		//load level 2
		level_mg.LoadFile(".\\Data\\Level2.txt");
		level_mg.Init(*window_mg.GetScene());
		level_mg.SetLevel(2);

		window_mg.SetWindow(WindowState::vitals);
		AudioManager::GetInstance().PlaySoundEffect(SoundID::BUTTON, false);
	}
	else if (App::IsKeyPressed('3'))
	{
		//load level 3
		level_mg.LoadFile(".\\Data\\Level3.txt");
		level_mg.Init(*window_mg.GetScene());
		level_mg.SetLevel(3);

		window_mg.SetWindow(WindowState::vitals);
		AudioManager::GetInstance().PlaySoundEffect(SoundID::BUTTON, false);
	}
}

void LevelWindow::Render()
{
	App::Print(300.f, 550.f, "Select the levels:", 0.859, 0.91, 0.043, m_FONT);
	App::Print(300.f, 450.f, "Press 1 for first level", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 400, "Press 2 for second level", 1.f, 1.f, 1.f, m_FONT);
	App::Print(300.f, 350, "Press 3 for third level", 1.f, 1.f, 1.f, m_FONT);
}