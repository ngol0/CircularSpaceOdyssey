#pragma once
#include "Window.h"

class LoseWindow : public Window
{
public:
	LoseWindow();

	virtual void HandleInput(float deltaTime) override;
	virtual void Render() override;
};
