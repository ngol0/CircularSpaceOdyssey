#pragma once
#include "Component/EnemySpawner.h"
#include "GameObject/EnemyPool.h"
#include "Scene.h"
#include <fstream>

struct Enemy
{
	float timer;
	int id;
};

class LevelManager
{
private:
	//spawner
	Object::Ref m_shoot_spawner_obj;
	Object::Ref m_chase_spawner_obj;
	Object::Ref m_child_spawner_obj;
	Object::Ref m_split_spawner_obj;
	Object::Ref m_defense_spawner_obj;
	EnemySpawner* m_shoot_spawner{ nullptr };
	EnemySpawner* m_chase_spawner{ nullptr };
	EnemySpawner* m_child_spawner{ nullptr };
	EnemySpawner* m_split_spawner{ nullptr };
	EnemySpawner* m_defense_spawner{ nullptr };

	//enemy pool
	EnemyPool m_chase_pool;
	EnemyPool m_shoot_pool;
	EnemyPool m_child_pool;
	EnemyPool m_split_pool;
	EnemyPool m_defense_pool;

	std::ifstream m_input;

	float m_timer{ 0.f };
	float m_current_timer{ 0.f };
	int m_current_enemy_type{ -1 };

	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<Waypoint> m_outer_waypoints;

	bool m_is_complete{ false };
	int m_index{ 0 };

	int m_current_level{ 0 };
	Scene* m_scene{ nullptr };

public:
	LevelManager();
	LevelManager(const LevelManager&) = delete; //avoid copy constructor

	void SetLevel(int current_level);
	void LoadFile(const char* filename);
	void Init(Scene& scene);
	void Update(float deltaTime, const Vector2& player_pos);
	void Complete() {};
	void Restart();

	void ReadSpawnInfo();
	void SetUpTimer();
	void SetUpEnemy(Scene& scene);

	//singleton
	static LevelManager& GetInstance();

	//getter
	int GetCurrentLevel() { return m_current_level; }
	EnemySpawner* GetChildSpawner() { return m_child_spawner; }
	const Vector2& GetPlayerPosition() { return m_scene->GetPlayerPosition(); }
};
