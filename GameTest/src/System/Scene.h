#pragma once
#include "Component/BoxCollider.h"
#include "Component/Health.h"
#include "Component/EnemySpawner.h"
#include "Component/Transform.h"
//
#include "GameObject/EnemyPool.h"
#include "GameObject/GameObjectFactory.h"

class UI;

enum class SceneState
{
	START,
	COMBAT,
	PAUSED,
	GAME_OVER,
};

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

	//getters
	int GetPlayerHealth() const { return m_player->GetComponent<Health>().amount; }
	int GetScore() const { return m_score; }
	SceneState& GetState() { return m_scene_state; };
	const Vector2& GetPlayerPos() { return m_player->GetComponent<Transform>().position; }

	//event callback
	void OnPlayerCollisionEnter(BoxCollider& other);
	void OnEnemyCollisionEnter(BoxCollider& enemy, BoxCollider& bullet);

	//input handling
	void HandleInput(float deltaTime);

private:
	Object::Ref m_player;
	Object::Ref m_planet;

	//planet
	Vector2 circle_center;
	float circle_radius;

	//general datas
	int m_score;
	SceneState m_scene_state;
	float m_timer{ 0.f };

	//enemy pool
	EnemyPool m_shoot_enemy_pool;
	EnemyPool m_chase_enemy_pool;

	//spawner
	Object::Ref m_shoot_spawner_obj;
	Object::Ref m_chase_spawner_obj;
	EnemySpawner* m_shoot_spawner;
	EnemySpawner* m_chase_spawner;
};

