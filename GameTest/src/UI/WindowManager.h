#pragma once
#include "Math/Vector2.h"

class Window;
class Scene;

class WindowManager
{
public:
	WindowManager();
	void Init(Scene& scene);
	void SetWindow(Window& window);
	void HandleInput(float deltaTime);
	void Render();

	Window* GetCurrentWindow() { return m_current_window; }
	void RenderBackground();

private:
	Window* m_current_window;
	static const int MAX_STAR_NUMBER = 200;
	Vector2 m_random_pos[MAX_STAR_NUMBER];
};