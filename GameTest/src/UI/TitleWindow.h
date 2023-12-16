#pragma once
#include "Window.h"

class TitleWindow : public Window
{
public:
	TitleWindow();

	virtual void HandleInput(float deltaTime) override;
	virtual void Render() override;
};
