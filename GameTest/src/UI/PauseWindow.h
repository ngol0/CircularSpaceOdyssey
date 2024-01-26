#pragma once
#include "Window.h"

class PauseWindow : public Window
{
public:
	PauseWindow();

	virtual void OnEnter() override;
	virtual void HandleInput(float deltaTime) override;
	virtual void Render() override;
	virtual bool IsInGame() override { return false; }
};