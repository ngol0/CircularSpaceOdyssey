#pragma once
#include "Component/EnemySpawner.h"
#include "GameObject/EnemyPool.h"

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

private:
	//spawner
	Object::Ref m_shoot_spawner_obj;
	Object::Ref m_chase_spawner_obj;
	EnemySpawner* m_shoot_spawner;
	EnemySpawner* m_chase_spawner;

	//enemy pool
	EnemyPool m_shoot_enemy_pool;
	EnemyPool m_chase_enemy_pool;

	int enemy1;
	int enemy2;
};
