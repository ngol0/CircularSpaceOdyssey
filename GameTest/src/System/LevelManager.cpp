#include "stdafx.h"
#include "LevelManager.h"
#include "GameObject/GameObjectFactory.h"
#include "Scene.h"
#include "System/Data.h"
#include "System/Utils.h"
#include <limits>

LevelManager::LevelManager() : m_second_spawner(nullptr), m_first_spawner(nullptr) {}

void LevelManager::LoadFile(const char* filename)
{
	input.open(filename);
	m_current_filename = filename;
}

void LevelManager::ReadEnemyType()
{
	if (!input) return;
	std::string s;
	std::getline(input, s, ',');
	enemy_type_1 = stoi(s);

	std::string s2;
	std::getline(input, s2, '\n');
	enemy_type_2 = stoi(s2);
}

void LevelManager::SkipFirstLine()
{
	if (!input) return;
	std::string s;
	std::getline(input, s, '\n');
}

void LevelManager::ReadSpawnInfo()
{
	if (!input) return;
	std::string s1;
	std::string s2;

	std::getline(input, s1, ',');
	m_current_timer = stof(s1);

	std::getline(input, s2, '\n');
	m_current_enemy_type = stoi(s2);
}

void LevelManager::Init(Scene& scene)
{
	if (!input) return;
	ReadEnemyType();

	//enemy pools
	Transform enemy_transform = Transform{ scene.GetPlanetPosition(), 1.2f };
	m_enemy_pool.Init(enemy_transform, static_cast<EnemyType>(enemy_type_1), scene);
	m_enemy_pool_2.Init(enemy_transform, static_cast<EnemyType>(enemy_type_2), scene);

	//enemy spawner init
	m_first_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_first_spawner = &m_first_spawner_obj->GetComponent<EnemySpawner>();
	m_first_spawner->SetUp(m_enemy_pool, 50.f);
	m_first_spawner->InitWaypoints();

	m_second_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_second_spawner = &m_second_spawner_obj->GetComponent<EnemySpawner>();
	m_second_spawner->SetUp(m_enemy_pool_2, 10.f);
	m_second_spawner->InitWaypoints();

	ReadSpawnInfo();
}

void LevelManager::Update(float deltaTime, const Vector2& player_pos)
{
	m_timer += deltaTime / 100.f;

	if (m_timer >= m_current_timer)
	{
		//spawn based on type
		//first one moves towards player
		if (m_current_enemy_type == enemy_type_1)
		{
			//std::cout << "x: "<< player_pos.x << std::endl;
			//spawn enemy
			m_first_spawner->SpawnEnemy(player_pos, deltaTime);
		}
		//second one moves to and stays at waypoint
		else if (m_current_enemy_type == enemy_type_2)
		{
			Waypoint* destination = m_second_spawner->GetAvailableWaypoint();
			if (destination == nullptr) return;
			m_second_spawner->SpawnEnemy(*destination, deltaTime);
		}

		//read the next line
		if (!input.eof())
		{
			ReadSpawnInfo();
		}
		else
		{
			m_current_timer = std::numeric_limits<float>::infinity();
		}
	}
}

void LevelManager::Restart()
{
	//reset waypoints and timer
	m_second_spawner->Reset();
	m_first_spawner->Reset();

	m_enemy_pool.SetUp();
	m_enemy_pool_2.SetUp();

	ReRead();
}

void LevelManager::ReRead()
{
	//close and reload -- skip first line of enemy type
	input.close();
	LoadFile(m_current_filename);
	SkipFirstLine();

	//reset timer and current enemy type
	m_timer = 0.f;
	m_current_timer = 0.f;
	m_current_enemy_type = -1;
}

LevelManager& LevelManager::GetInstance()
{
	static LevelManager manager;
	return manager;
}