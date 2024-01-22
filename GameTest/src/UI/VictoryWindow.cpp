#include "stdafx.h"
#include "WindowManager.h"
#include "VictoryWindow.h"
#include "LevelWindow.h"
#include "VitalsWindow.h"
//
#include "System/Level/LevelManager.h"

auto& window_mgr = WindowManager::GetInstance();
auto& level_mgr = LevelManager::GetInstance();

VictoryWindow::VictoryWindow() {}

void VictoryWindow::HandleInput(float deltaTime)
{
	if (App::IsKeyPressed(VK_SPACE) && m_timer > 2.f)
	{
		int current_level = level_mgr.GetCurrentLevel();
		switch (current_level)
		{
		case 1:
			level_mgr.LoadFile(".\\Data\\Level2.txt");
			level_mgr.SetLevel(2);

			window_mgr.SetWindow(WindowState::vitals);
			break;
		case 2:
			level_mgr.LoadFile(".\\Data\\Level3.txt");
			level_mgr.SetLevel(3);

			window_mgr.SetWindow(WindowState::vitals);
			break;
		case 3:
			window_mgr.SetWindow(WindowState::level);
			break;
		}

		window_mgr.GetScene()->Restart();
		m_timer = 0.f;
	}
	m_timer += deltaTime / 100.f;
}

void VictoryWindow::Render()
{
	int current_level = level_mgr.GetCurrentLevel();
	if (current_level < 3)
	{
		App::Print(300.f, 450.f, "Congratulations!!! You have won this level!", 1.f, 1.f, 1.f, m_FONT);
		App::Print(300.f, 370.f, "Press SPACE to move to next level", 0.467f, 0.831f, 0.961f, m_FONT);
	}
	else
	{
		App::Print(300.f, 450.f, "Congratulations!!! You have won the final level!", 1.f, 1.f, 1.f, m_FONT);
		App::Print(300.f, 370.f, "Press SPACE to go to the Level Menu", 0.467f, 0.831f, 0.961f, m_FONT);
	}
}