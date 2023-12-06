#pragma once
#include "Math/Vector2.h"

class Scene;

class UI
{
private:
	std::string m_score_string;
	std::string m_health_string;

	Scene* m_scene;
	static const int MAX_STAR_NUMBER = 200;
	Vector2 m_random_pos[MAX_STAR_NUMBER];

	void* m_FONT = GLUT_BITMAP_9_BY_15;

public:
	UI();
	void Init(Scene& scene);
	void Update(float deltaTime);
	void Render();

	void UpdateScoreText(int score);
	void UpdateHealthText(int health);

	void RenderBackground();
};