#pragma once
#include "Math/Vector2.h"
#include "System/Scene.h"

class Window;

class WindowManager
{
public:
	WindowManager();
	WindowManager(const WindowManager&) = delete; //avoid copy constructor

	void Init(Scene& scene);
	void SetWindow(Window& window);
	void HandleInput(float deltaTime);
	void Render();

	//getter
	int GetHealth() { return m_scene->GetPlayerHealth(); }
	int GetScore() { return m_scene->GetScore(); }
	Scene* GetScene() { return m_scene; }

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