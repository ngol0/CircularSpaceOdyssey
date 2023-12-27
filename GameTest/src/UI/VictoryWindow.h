#pragma once
#include "Window.h"

class VictoryWindow : public Window
{
public:
	VictoryWindow();

	virtual void HandleInput(float deltaTime) override;
	virtual void Render() override;
};