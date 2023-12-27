#include "stdafx.h"
#include "Window.h"
#include "TitleWindow.h"
#include "VitalsWindow.h"
#include "PauseWindow.h"
#include "LoseWindow.h"
#include "LevelWindow.h"
#include "VictoryWindow.h"

TitleWindow WindowState::title;
VitalsWindow WindowState::vitals;
PauseWindow WindowState::pause;
LoseWindow WindowState::lose;
LevelWindow WindowState::level;
VictoryWindow WindowState::win;

float Window::m_timer;

