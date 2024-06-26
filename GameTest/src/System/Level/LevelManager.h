/*This class is to manage the game levels
* The responsibility of this class is to:
** Initialize all the memory needed for all the enemy pools
** Read a txt file and parse the information into a vector of commands structure
** Loop through the commands and starts spawning enemies based on the commands (i.e: Spawn/Wait)
*/
#pragma once
#include "Component/EnemySpawner.h"
#include "GameObject/EnemyPool.h"
#include "System/Scene.h"
#include <fstream>

enum CommandType { SPAWN, WAIT };

struct Command
{
	CommandType command;
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
	CommandType m_current_command{ SPAWN };

	std::vector<Object::Ref> m_active_enemies;
	std::vector<std::unique_ptr<Command>> m_commands;

	std::vector<Waypoint> m_outer_waypoints;

	bool m_is_complete{ false };
	bool m_is_waiting{ false };
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
	void Restart();

	void ReadCommandInfo();
	void SetUpTimer();
	void SetUpEnemy(Scene& scene);

	bool SpawnEnemy(const Vector2& player_pos);
	bool AreAllEnemiesDead();

	//singleton
	static LevelManager& GetInstance();

	//getter
	int GetCurrentLevel() { return m_current_level; }
	EnemySpawner* GetChildSpawner() { return m_child_spawner; }
	const Vector2& GetPlayerPosition() { return m_scene->GetPlayerPosition(); }
};
