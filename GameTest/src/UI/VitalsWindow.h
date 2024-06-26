/* Includes health and resources bar */
#pragma once
#include "Window.h"
#include "Math/Vector2.h"

class VitalsWindow : public Window
{
public:
	VitalsWindow();

	virtual void OnEnter() override;
	virtual void HandleInput(float deltaTime) override;
	virtual void OnExit() override;
	virtual void Render() override;
	virtual bool IsInGame() override { return true; }

	void UpdateScoreText(int score);
	void UpdateHealthText(int health);

private:
	std::string m_score_string;
	std::string m_health_string;
	std::string m_level_string;

	int m_current_level{1};
};