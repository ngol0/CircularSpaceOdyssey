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
}

void LevelManager::ReadFirstLine()
{
	std::string s;
	std::getline(input, s, ',');
	std::cout << s << "\n";
	enemy1 = stoi(s);

	std::string s2;
	std::getline(input, s2, '\n');
	enemy2 = stoi(s2);
	std::cout << s2 << "\n";
}

void LevelManager::ReadSpecificInfo(float& time, int& type)
{
	std::string s1;
	std::string s2;

	std::getline(input, s1, ',');
	std::cout << s1 << std::endl;
	time = stof(s1);

	std::getline(input, s2, '\n');
	std::cout << "s2: " << s2 << "\n";
	type = stoi(s2);
}

void LevelManager::Init(Scene& scene)
{
	ReadFirstLine();

	//enemy pools
	Transform enemy_transform = Transform{ scene.GetPlanetPosition(), 1.2f };
	m_enemy_pool.Init(enemy_transform, static_cast<EnemyType>(enemy1), scene);
	m_enemy_pool_2.Init(enemy_transform, static_cast<EnemyType>(enemy2), scene);

	//enemy spawner init
	m_first_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_first_spawner = &m_first_spawner_obj->GetComponent<EnemySpawner>();
	m_first_spawner->SetUp(m_enemy_pool, 50.f);
	m_first_spawner->InitWaypoints();

	m_second_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_second_spawner = &m_second_spawner_obj->GetComponent<EnemySpawner>();
	m_second_spawner->SetUp(m_enemy_pool_2, 10.f);
	m_second_spawner->InitWaypoints();

	ReadSpecificInfo(m_current_timer, m_current_enemy_type);
}

void LevelManager::Update(float deltaTime, const Vector2& player_pos)
{
	m_timer += deltaTime / 100.f;

	if (m_timer >= m_current_timer)
	{
		//spawn based on type
		if (m_current_enemy_type == enemy1)
		{
			//spawn enemy
			m_first_spawner->SpawnEnemy(Waypoint{ player_pos, true }, deltaTime);
		}
		else if (m_current_enemy_type == enemy2)
		{
			m_second_spawner->SpawnEnemy(*m_second_spawner->GetAvailableWaypoint(), deltaTime);
		}

		//read the next line
		if (!input.eof())
		{
			ReadSpecificInfo(m_current_timer, m_current_enemy_type);
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
}