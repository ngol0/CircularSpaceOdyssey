#pragma once
#include "Component/BoxCollider.h"
#include "Component/Health.h"
//
#include "GameObject/GameObjectManager.h"
#include "GameObject/GameObjectFactory.h"
#include "System/CollisionManager.h"


class Scene
{
public:
	Scene();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Shutdown();

	void SetUp() {};

	int GetPlayerHealth() const { return m_player->GetComponent<Health>().amount; }
	int GetScore() const { return m_score; }

	void OnPlayerCollisionEnter(BoxCollider& other);
	void OnEnemyCollisionEnter(BoxCollider& enemy, BoxCollider& bullet);

	GameObjectManager object_manager;
	CollisionManager collision_manager;

private:
	int m_score;
	GameObject* m_player;

	Vector2 circle_center;
	float circle_radius;
};

