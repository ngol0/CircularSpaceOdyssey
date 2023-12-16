#pragma once
#include "Math/Vector2.h"
#include "System/Scene.h"

class Window;

class WindowManager
{
public:
	WindowManager();
	void Init(Scene& scene);
	void SetWindow(Window& window);
	void HandleInput(float deltaTime);
	void Render();

	//getter
	float GetHealth() { return m_scene->GetPlayerHealth(); }
	float GetScore() { return m_scene->GetScore(); }

	Window* GetCurrentWindow() { return m_current_window; }
	void RenderBackground();
	void Restart();

	//singleton
	static WindowManager& GetInstance();

private:
	Window* m_current_window;

	static const int MAX_STAR_NUMBER = 200;
	Vector2 m_random_pos[MAX_STAR_NUMBER];

	Scene* m_scene;
};