#pragma once
#include "System/Event.h"

class TitleWindow;
class VitalsWindow;
class WindowManager;
class Scene;

class Window
{
public:
	virtual ~Window() {};
	virtual void Init(Scene& scene) {};
	virtual void HandleInput(float deltaTime, WindowManager& manager) = 0;
	virtual void Render() = 0;

	void* m_FONT = GLUT_BITMAP_9_BY_15;
};

class WindowState
{
public:
	static TitleWindow title;
	static VitalsWindow vitals;
};

