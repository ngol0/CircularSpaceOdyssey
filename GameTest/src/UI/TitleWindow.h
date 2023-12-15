#pragma once
#include "Window.h"

class TitleWindow : public Window
{
public:
	TitleWindow();

	virtual void HandleInput(float deltaTime, WindowManager& manager) override;
	virtual void Render() override;

	int a = 5;
};
