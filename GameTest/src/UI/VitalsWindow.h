#pragma once
#include "Window.h"
#include "Math/Vector2.h"

class VitalsWindow : public Window
{
public:
	VitalsWindow();

	virtual void OnEnter() override;
	virtual void HandleInput(float deltaTime, WindowManager& manager) override;
	virtual void Render() override;

	void UpdateScoreText(int score);
	void UpdateHealthText(int health);

private:
	std::string m_score_string;
	std::string m_health_string;
};