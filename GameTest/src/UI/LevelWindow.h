/* Level select window */
#pragma once
#include "Window.h"

class LevelWindow : public Window
{
public:
	LevelWindow();

	virtual void HandleInput(float deltaTime) override;
	virtual void Render() override;
};