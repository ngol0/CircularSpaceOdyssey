/* An interface for all windows
Inherits by all the specific windows in game */
#pragma once
#include "Global/Event.h"

class Scene;

class Window
{
public:
	virtual ~Window() {};
	virtual void Init(Scene& scene) {};
	virtual void OnEnter() {};
	virtual void HandleInput(float deltaTime) {};
	virtual void Render() {};
	virtual void OnExit() {};
	virtual bool IsInGame() = 0;

	void* m_FONT = GLUT_BITMAP_9_BY_15;

protected:
	static float m_timer;
};

/* Creates all the static windows object to use when needs to set window */
class TitleWindow;
class VitalsWindow;
class PauseWindow;
class LoseWindow;
class LevelWindow;
class WindowManager;
class VictoryWindow;

class WindowState
{
public:
	static TitleWindow title;
	static VitalsWindow vitals;
	static PauseWindow pause;
	static LoseWindow lose;
	static LevelWindow level;
	static VictoryWindow win;
};

