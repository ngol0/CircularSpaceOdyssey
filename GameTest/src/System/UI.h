#pragma once

class Scene;

class UI
{
private:
	std::string m_score_string;
	std::string m_health_string;

	Scene* m_scene;

public:
	UI();
	void Init(Scene& scene);
	void Update(float deltaTime);
	void Render();

	void UpdateScoreText(int score);
	void UpdateHealthText(int health);
};