#pragma once
#include "System/Event.h"

class TitleWindow;
class VitalsWindow;
class PauseWindow;
class LoseWindow;
class WindowManager;
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

	void* m_FONT = GLUT_BITMAP_9_BY_15;

protected:
	static float m_timer;
};

class WindowState
{
public:
	static TitleWindow title;
	static VitalsWindow vitals;
	static PauseWindow pause;
	static LoseWindow lose;
};

