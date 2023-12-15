#pragma once
#include "Window.h"

class PauseWindow : public Window
{
public:
	PauseWindow();

	virtual void OnEnter() override;
	virtual void Init(Scene& scene);
	virtual void HandleInput(float deltaTime, WindowManager& manager) override;
	virtual void Render() override;

private:
	Scene* m_scene;
};