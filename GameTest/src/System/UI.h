#pragma once
class Scene;
class CollisionManager;

class UI
{
private:
	std::string m_score_string;
	std::string m_health_string;

	Scene* m_scene;
	CollisionManager* m_collision_manager;

public:
	UI();
	void Init(Scene& scene);
	void Update(float deltaTime);
	void Render();
};