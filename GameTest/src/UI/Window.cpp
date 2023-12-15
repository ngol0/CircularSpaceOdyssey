#include "stdafx.h"
#include "Window.h"
#include "TitleWindow.h"
#include "VitalsWindow.h"
#include "PauseWindow.h"
#include "LoseWindow.h"

TitleWindow WindowState::title;
VitalsWindow WindowState::vitals;
PauseWindow WindowState::pause;
LoseWindow WindowState::lose;

float Window::m_timer;

