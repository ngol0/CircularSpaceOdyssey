#include "stdafx.h"
#include "LevelManager.h"
#include "GameObject/GameObjectFactory.h"
#include "Scene.h"
#include "Global/EnemyType.h"
#include "Global/Utils.h"
//
#include <sstream>

LevelManager::LevelManager() {}

void LevelManager::SetLevel(int current_level)
{
	m_current_level = current_level;
}

void LevelManager::LoadFile(const char* filename)
{
	m_input.open(filename);
	if (!m_input.is_open())
	{
		//std::cerr << "Failed to open file." << std::endl;
		return;
	}
	ReadSpawnInfo();
	m_input.close();
}

void LevelManager::ReadSpawnInfo()
{
	m_enemies.clear();
	std::string line;
	while (std::getline(m_input, line)) 
	{
		std::istringstream iss(line);
		std::unique_ptr<Enemy> enem = std::make_unique<Enemy>();

		if (iss >> enem->timer >> enem->id)
		{
			m_enemies.emplace_back(std::move(enem));
		}
	}
}

void LevelManager::Init(Scene& scene)
{
	SetUpEnemy(scene);
	SetUpTimer();
}

void LevelManager::SetUpEnemy(Scene& scene)
{
	//enemy pools
	Transform enemy_transform = Transform{ scene.GetPlanetPosition(), 1.2f };
	m_chase_pool.Init(enemy_transform, EnemyType::ChaseType, scene);
	m_shoot_pool.Init(enemy_transform, EnemyType::ShootType, scene);

	//enemy spawner init
	m_chase_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_chase_spawner = &m_chase_spawner_obj->GetComponent<EnemySpawner>();
	m_chase_spawner->SetUp(m_chase_pool);
	m_chase_spawner->InitWaypoints();

	m_shoot_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_shoot_spawner = &m_shoot_spawner_obj->GetComponent<EnemySpawner>();
	m_shoot_spawner->SetUp(m_shoot_pool);
	m_shoot_spawner->InitWaypoints();
}

void LevelManager::Update(float deltaTime, const Vector2& player_pos)
{
	m_timer += deltaTime / 100.f;

	if (m_timer >= m_current_timer && !m_is_complete)
	{
		//spawn based on type
		//chase and explode enemies moves towards player
		if (m_current_enemy_type == (int)EnemyType::ChaseType)
		{
			//std::cout << "x: "<< player_pos.x << std::endl;
			//spawn enemy
			m_chase_spawner->SpawnEnemy(player_pos, deltaTime);
		}
		else if (m_current_enemy_type == (int)EnemyType::MultiplyType)
		{

		}
		//shoot and respawn enemies moves to and stays at waypoint
		else if (m_current_enemy_type == (int)EnemyType::ShootType)
		{
			Waypoint* destination = m_shoot_spawner->GetAvailableWaypoint();
			if (destination == nullptr) return;
			m_shoot_spawner->SpawnEnemy(*destination, deltaTime);
		}
		else if (m_current_enemy_type == (int)EnemyType::RespawnType)
		{

		}

		m_index++;
		//if not ends - moves to next enemy
		if (m_index < m_enemies.size())
		{
			m_current_timer = m_enemies[m_index]->timer;
			m_current_enemy_type = m_enemies[m_index]->id;
		}
		else
		{
			m_is_complete = true;
		}
	}
}

void LevelManager::Restart()
{
	//reset waypoints and timer
	m_shoot_spawner->Reset();
	m_chase_spawner->Reset();

	m_chase_pool.SetUp();
	m_shoot_pool.SetUp();
	
	SetUpTimer();
}

void LevelManager::SetUpTimer()
{
	m_timer = 0.f;
	m_index = 0;

	if (m_enemies.size() == 0) return;
	m_current_timer = m_enemies[m_index]->timer;
	m_current_enemy_type = m_enemies[m_index]->id;
}

LevelManager& LevelManager::GetInstance()
{
	static LevelManager manager;
	return manager;
}