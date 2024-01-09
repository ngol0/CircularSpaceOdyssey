#include "stdafx.h"
#include "LevelManager.h"
#include "GameObject/GameObjectFactory.h"
#include "Global/EnemyType.h"
#include "Global/Utils.h"
//
#include <sstream>

LevelManager::LevelManager() : m_scene(nullptr) {}

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
	m_scene = &scene;
	//enemy pools
	Transform starting_transform = Transform{ scene.GetPlanetPosition(), 1.2f };
	m_chase_pool.Init(starting_transform, EnemyType::SlowChaseType, scene);
	m_shoot_pool.Init(starting_transform, EnemyType::ShootType, scene);
	m_child_pool.Init(starting_transform, EnemyType::FastChaseType, scene);
	m_split_pool.Init(starting_transform, EnemyType::SplitType, scene);
	m_defense_pool.Init(starting_transform, EnemyType::TwoModeType, scene);

	//enemy spawner init
	//slow chase enemy
	m_chase_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_chase_spawner = &m_chase_spawner_obj->GetComponent<EnemySpawner>();
	m_chase_spawner->SetUp(m_chase_pool);

	//shoot enemy that stays at waypoint
	m_shoot_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_shoot_spawner = &m_shoot_spawner_obj->GetComponent<EnemySpawner>();
	m_shoot_spawner->SetUp(m_shoot_pool);
	m_shoot_spawner->InitWaypoints();

	//enemy that can splits into different ones if destroyed
	m_split_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_split_spawner = &m_split_spawner_obj->GetComponent<EnemySpawner>();
	m_split_spawner->SetUp(m_split_pool);
	m_split_spawner->InitWaypoints();

	//splitted enemy that follows player in fast speed
	m_child_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_child_spawner = &m_child_spawner_obj->GetComponent<EnemySpawner>();
	m_child_spawner->SetUp(m_child_pool);

	//two mode enemy that can be shot when green and immune to bullet when red
	m_defense_spawner_obj = GameObjectFactory::CreateEnemySpawner(scene.GetPlanetPosition());
	m_defense_spawner = &m_defense_spawner_obj->GetComponent<EnemySpawner>();
	m_defense_spawner->SetUp(m_defense_pool);
}

void LevelManager::Update(float deltaTime, const Vector2& player_pos)
{
	m_timer += deltaTime / 100.f;

	if (m_timer >= m_current_timer && !m_is_complete)
	{
		//spawn based on type
		//chase and explode enemies moves towards player
		if (m_current_enemy_type == (int)EnemyType::SlowChaseType)
		{
			//std::cout << "x: "<< player_pos.x << std::endl;
			//spawn enemy
			m_chase_spawner->SpawnEnemy(player_pos);
		}
		//enemy that can be on defense and stays at waypoint
		else if (m_current_enemy_type == (int)EnemyType::TwoModeType)
		{
			Waypoint* destination = m_shoot_spawner->GetAvailableWaypoint();
			if (destination == nullptr) return;
			m_defense_spawner->SpawnEnemy(*destination);
		}
		//shoot moves to and stays at waypoint
		else if (m_current_enemy_type == (int)EnemyType::ShootType)
		{
			Waypoint* destination = m_shoot_spawner->GetAvailableWaypoint();
			if (destination == nullptr) return;
			m_shoot_spawner->SpawnEnemy(*destination);
		}
		//split type moves randomly
		else if (m_current_enemy_type == (int)EnemyType::SplitType)
		{
			//float x = Utils::RandomFloat();
			m_split_spawner->SpawnEnemy();
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