#include "stdafx.h"
#include "LevelManager.h"
#include "GameObject/GameObjectFactory.h"
#include "Scene.h"
#include "System/Data.h"
#include "System/Utils.h"

#include <fstream>

LevelManager::LevelManager() : m_shoot_spawner(nullptr), m_chase_spawner(nullptr) {}

void LevelManager::LoadFile(const char* filename)
{
	std::ifstream input;
	input.open(filename);

	std::string s;
	std::getline(input, s, ',');
	std::cout << s << "\n";
	enemy1 = stoi(s);
	
	std::string s2;
	std::getline(input, s2, '\n');
	enemy2 = stoi(s2);
	std::cout << s2 << "\n";
}

void LevelManager::Init(Scene& scene)
{
	//enemy pools
	Transform enemy_transform = Transform{ scene.GetPlanetPosition(), 1.2f };
	m_shoot_enemy_pool.Init(enemy_transform, static_cast<EnemyType>(enemy2), scene);
	m_chase_enemy_pool.Init(enemy_transform, static_cast<EnemyType>(enemy1), scene);

	//shoot enemy spawner init
	m_shoot_spawner_obj = GameObjectFactory::CreateShootEnemySpawner(scene.GetPlanetPosition());
	m_shoot_spawner = &m_shoot_spawner_obj->GetComponent<EnemySpawner>();
	m_shoot_spawner->SetUp(m_shoot_enemy_pool, 10.f);
	m_shoot_spawner->InitWaypoints();

	//chase enemy spawner init
	m_chase_spawner_obj = GameObjectFactory::CreateChaseEnemySpawner(scene.GetPlanetPosition());
	m_chase_spawner = &m_chase_spawner_obj->GetComponent<EnemySpawner>();
	m_chase_spawner->SetUp(m_chase_enemy_pool, 50.f);
}

void LevelManager::Update(float deltaTime, const Vector2& player_pos)
{
	//spawn enemy
	m_chase_spawner->SpawnEnemy(Waypoint{ player_pos, true }, deltaTime);
	m_shoot_spawner->SpawnEnemyToWaypoint(deltaTime);

	//check if upcoming enemy has waypoints
	//if yes -- pass waypoint
	//if no -- pass player's pos
	
}

void LevelManager::Restart()
{
	//reset waypoints and timer
	m_shoot_spawner->Reset();
	m_chase_spawner->Reset();

	m_shoot_enemy_pool.SetUp();
	m_chase_enemy_pool.SetUp();
}