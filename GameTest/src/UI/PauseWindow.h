#pragma once
#include "Window.h"

class PauseWindow : public Window
{
public:
	PauseWindow();

	virtual void OnEnter() override;
	virtual void HandleInput(float deltaTime, WindowManager& manager) override;
	virtual void Render() override;
};