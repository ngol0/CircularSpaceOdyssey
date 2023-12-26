#pragma once
#include "Component/EnemySpawner.h"
#include "GameObject/EnemyPool.h"
#include <fstream>

class Scene;

struct Enemy
{
	float timer;
	int id;
};

class LevelManager
{
public:
	LevelManager();

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

private:
	//spawner
	Object::Ref m_shoot_spawner_obj;
	Object::Ref m_chase_spawner_obj;
	EnemySpawner* m_shoot_spawner;
	EnemySpawner* m_chase_spawner;

	//enemy pool
	EnemyPool m_chase_pool;
	EnemyPool m_shoot_pool;

	std::ifstream m_input;

	float m_timer{ 0.f };
	float m_current_timer{ 0.f };
	int m_current_enemy_type{ -1 };
	const char* m_current_filename{ nullptr };

	std::vector<std::unique_ptr<Enemy>> m_enemies;
	bool m_is_complete;
	int m_index;
};
