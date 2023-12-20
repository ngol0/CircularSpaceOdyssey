#pragma once
#include "Component/EnemySpawner.h"
#include "GameObject/EnemyPool.h"
#include <fstream>

class Scene;

class LevelManager
{
public:
	LevelManager();

	void LoadFile(const char* filename);
	void Init(Scene& scene);
	void Update(float deltaTime, const Vector2& player_pos);
	void Complete() {};
	void Restart();

	void ReadEnemyType();
	void ReadSpawnInfo();
	void SkipFirstLine();
	void ReRead();

	//singleton
	static LevelManager& GetInstance();

private:
	//spawner
	Object::Ref m_second_spawner_obj;
	Object::Ref m_first_spawner_obj;
	EnemySpawner* m_second_spawner;
	EnemySpawner* m_first_spawner;

	//enemy pool
	EnemyPool m_enemy_pool;
	EnemyPool m_enemy_pool_2;

	int enemy_type_1{ 0 };
	int enemy_type_2{ 0 };

	std::ifstream input;

	float m_timer{ 0.f };
	float m_current_timer{ 0.f };
	int m_current_enemy_type{ -1 };
	const char* m_current_filename;
};
