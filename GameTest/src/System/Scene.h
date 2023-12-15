#pragma once
#include "Component/BoxCollider.h"
#include "Component/Health.h"
#include "Component/EnemySpawner.h"
#include "Component/Transform.h"
//
#include "GameObject/EnemyPool.h"
#include "GameObject/GameObjectFactory.h"

#include "System/Event.h"

class WindowManager;

class Scene
{
public:
	Scene();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Shutdown() {};
	void SetUp();
	void Restart();
	void OnScore();
	void OnGameOver();

	//getters
	int GetPlayerHealth() const { return m_player->GetComponent<Health>().amount; }
	int GetScore() const { return m_score; }
	const Vector2& GetPlayerPos() { return m_player->GetComponent<Transform>().position; }

	//event callback
	void OnPlayerCollisionEnter(BoxCollider& other);
	void OnEnemyCollisionEnter(BoxCollider& enemy, BoxCollider& bullet);

	//event
	Event<WindowManager, bool> check_game_over;

private:
	Object::Ref m_player;
	Object::Ref m_planet;

	//planet
	Vector2 circle_center;
	float circle_radius;

	//general datas
	int m_score;

	//enemy pool
	EnemyPool m_shoot_enemy_pool;
	EnemyPool m_chase_enemy_pool;

	//spawner
	Object::Ref m_shoot_spawner_obj;
	Object::Ref m_chase_spawner_obj;
	EnemySpawner* m_shoot_spawner;
	EnemySpawner* m_chase_spawner;
};

